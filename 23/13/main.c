#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "tree.h"

#define VALID_USER_INPUT(x) ((x) == '1' || (x) == '2' || (x) == '3' || (x) == '4' || (x) == '5' || (x) == '6')

void print_item(T, int);
void print_way(way, int, T);
void help();

int main()
{
    int i;
    char user_input[BUFSIZ];
    tree t;
    way_with_target* found_ways_to_parent;
    way_with_target* found_ways_to_value_to_remove;
    way_with_target selected_way_with_target;
    int found_ways_to_parent_count, selected_way_index;
    int found_ways_to_value_to_remove_count;
    bool is_tree_structured_as_list;

    T value_to_insert = -1, parent_value, value_to_remove;
    int exited = 0;

    init_tree(&t);
    help();

    while (!exited)
    {
        scanf("%s", user_input);
        if (strlen(user_input) != 1 || !VALID_USER_INPUT(*user_input))
        {
            printf("Invalid input! Try again...\n\n");
            continue;
        }

        switch (*user_input - 48)
        {
            case 1:
                printf("Input value to insert: ");
                scanf("%d", &value_to_insert);
                // TODO TYPE VALIDATION
                printf("Input value of parent element: ");
                scanf("%d", &parent_value);
                // TODO TYPE VALIDATION

                if (t.root != NULL)
                {
                    find_ways_to(t, parent_value, &found_ways_to_parent, &found_ways_to_parent_count);

                    if (found_ways_to_parent_count == 0) {
                        printf("There is no such value = %d in tree... Try again\n\n", parent_value);
                        continue;
                    }

                    for (i = 0; i < found_ways_to_parent_count; i++) {
                        print_way(found_ways_to_parent[i].way_to_target, i + 1, parent_value);
                    }

                    printf("\nSelect way to inserted item's parent: ");
                    scanf("%d", &selected_way_index);

                    if (selected_way_index <= 0 || selected_way_index > found_ways_to_parent_count) {
                        printf("Invalid selected way index! Try again...\n\n");
                        continue;
                    }

                    selected_way_with_target = found_ways_to_parent[selected_way_index - 1];

                    insert_item(&t, selected_way_with_target.target, value_to_insert);

                    for (i = 0; i < found_ways_to_parent_count; i++)
                    {
                        free(found_ways_to_parent[i].way_to_target.chain);
                    }
                    free(found_ways_to_parent);
                }
                else
                {
                    selected_way_with_target.target = NULL;
                    selected_way_with_target.way_to_target.chain = NULL;
                    selected_way_with_target.way_to_target.chain_length = 0;

                    insert_item(&t, selected_way_with_target.target, value_to_insert);
                }
                printf("\n");
                break;
            case 2:
                printf("Input value to remove it and it's subtree from tree: ");
                // TODO TYPE VALIDATION
                scanf("%d", &value_to_remove);

                found_ways_to_value_to_remove = NULL;
                found_ways_to_value_to_remove_count = 0;
                find_ways_to(t, value_to_remove, &found_ways_to_value_to_remove, &found_ways_to_value_to_remove_count);

                if (found_ways_to_value_to_remove_count == 0)
                {
                    printf("There is no such value = %d in tree... Try again\n\n", value_to_remove);
                    continue;
                }

                for (i = 0; i < found_ways_to_value_to_remove_count; i++)
                {
                    print_way(found_ways_to_value_to_remove[i].way_to_target, i + 1, value_to_remove);
                }

                printf("\nSelect way to [subtree's to remove] root: ");
                scanf("%d", &selected_way_index);

                if (selected_way_index <= 0 || selected_way_index > found_ways_to_value_to_remove_count)
                {
                    printf("Invalid selected way index! Try again...\n\n");
                    continue;
                }

                selected_way_with_target = found_ways_to_value_to_remove[selected_way_index - 1];

                remove_item(&t, selected_way_with_target.target);

                for (i = 0; i < found_ways_to_value_to_remove_count; i++)
                {
                    free(found_ways_to_value_to_remove[i].way_to_target.chain);
                }
                free(found_ways_to_value_to_remove);
                printf("\n\n");
                break;
            case 3:
                printf("Tree state:\n--------------------\n\n");
                prefix_traverse(t, print_item);
                printf("\n--------------------\n\n");
                break;
            case 4:
                is_tree_structured_as_list = is_structured_like_linear_list(t);
                printf("Tree is %structured as list\n\n", is_tree_structured_as_list == yes ? "s" : "not s");
                break;
            case 5:
                help();
                break;
            case 6:
                exited = 1;
                printf("\n");
                break;
        }
    }

    clear(&t);

    return 0;
}

void print_item(T value, int depth)
{
    int i;

    for (i = 0; i < depth; i++)
    {
        printf("    ");
    }

    printf("%d|\n", value);
}

void print_way(way found_way, int index, T target_value)
{
    int i;

    printf("%d. ", index);

    for (i = 0; i < found_way.chain_length; i++)
    {
        printf("%d ---%d---> ", found_way.chain[i].value,
               found_way.chain[i].index_from_parent_item);
    }

    printf("%d\n", target_value);
}

void help()
{
    printf("The program operates with a general tree with items of integer type\n");
    printf("    1 - insert value into tree\n");
    printf("    2 - remove value from tree\n");
    printf("    3 - print tree\n");
    printf("    4 - check tree for list structure\n");
    printf("    5 - help menu\n");
    printf("    6 - exit\n");
    printf("Your choose: ");
}
