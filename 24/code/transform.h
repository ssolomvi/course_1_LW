#ifndef __TRANSFORM_H__
#define __TRANSFORM_H__

#include "tree.h"

void find_minus_operator(Tree*);
void push_minus_up(Tree*);
void remove_extra_minuses(Tree*);

void div_transform(Tree*, Tree*, Tree*);
void do_div(Tree*);
void division_transform_iterator(Tree*);
void check_if_mult(Tree*);
void find_div(Tree*, Tree*, Tree*);
void tree_div_trans(Tree*, Tree*, bool);

void copy(Tree* to_copy, Tree* subtree_copy);

#endif // __TRANSFORM_H__
