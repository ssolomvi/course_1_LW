# Отчет по лабораторной работе N 13 по курсу
# "Фундаментальная информатика"

Студентка группы: M8О-113Б, Соломатина Светлана Викторовна\
Контакты: ssolomvi@gmail.com\
Работа выполнена: 12.12.2021\
Преподаватель: Довженко Анастасия Александровна

## 1. Тема

Множества

## 2. Цель работы

Составить программу на языке Си, выполняющую работу со множествами

## 3. Задание

Вариант 25. Вывести ответ на вопрос "есть ли в наборе английских слов слово, все согласные которого сонорные {m, n, l, h, j, r, w}?" Букву 'y' для простоты считать согласной. Реализовать операции над множествами.

## 4. Оборудование

Процессор: AMD Ryzen 5 4500U with Radeon Graphics 2.38 GHz\
ОП: 16384 Мб\
ОЗУ: 512 Гб\
Монитор: 1920x1080

## 5. Программное обеспечение

Операционная система семейства: **linux (ubuntu)**, версия **21.04**\
Интерпретатор команд: **bash**, версия **5.1.4**.\
Местонахождение и имена файлов программ и данных на домашнем компьютере: **/home/ssolomvi**

## 6. Идея, метод, алгоритм решения задачи

1. Создать 2 битовых маски vowel и son, представляющие множество гласных и множество сонорных согласных
2. Завести флаг, отражающий вхождение сонорной согласной в слово
3. Проходя по каждому введённому слову, создавать битовую маску слова mask, представляющую набор его букв
4. По окончании слова производить побитовую конъюнкцию его маски и инвертированных масок множества гласных и согласных букв, и, с учётом состояния флага, выводить информацию о вхождении нужного слова в последовательность либо продолжать обработку последовательности слов
5. В случае, если по мере обработки последовательности встречен конец вводимых данных, а слова, удовлетворяющего условиям задания, не встречено, вывести соответствующую информацию

## 7. Сценарий выполнения работы

1. Изучить материалы лекции
2. Составить алгоритм программы
3. Написать программу на Си
4. Запротоколировать сеанс

| Тест  | Ввод | Вывод |
|----|---------------|---------------|
| 1  | humanum errare est | Yes |
| 2  | primus inter pares | No |
| 3  | AaioeOU | No |
| 4  | , | No |
| 5  | Wingardium Leviosa, Imperio | No |

## 8. Распечатка протокола

```C
#include <stdio.h>
typedef unsigned long Set;

#define EMPTY_SET (Set (0UL))


Set set_insert(Set s, unsigned idx)
{
    return s | ((Set) 1UL << idx);
}

Set set_intersection(Set s1, Set s2)
{
    return s1 & s2;
}

Set set_union(Set s1, Set s2)
{
    return s1 | s2;
}
Set set_complement(Set s1)
{
    return ~s1;
}
Set set_difference(Set s1, Set s2)
{
    return set_complement(set_intersection(s1, s2));
}
Set set_symmetric_difference(Set s1, Set s2)
{
    return set_difference(set_union(s1, s2), set_intersection(s1, s2));
}

int to_lower(char c)
{
    return (c >= 'A' && c <= 'Z') ? c + 32 : c;
}

int main(void)
{
    int vowel = 1 << 0 | 1 << ('e' - 'a') | 1 << ('i' - 'a') | 1 << ('o' - 'a') | 1 << ('u' - 'a');
    int son = 1 << ('m' - 'a') | 1 << ('n' - 'a')  | 1 << ('l' - 'a') | 1 << ('j' - 'a')  | 1 << ('h' - 'a') | 1 << ('r' - 'a')  | 1 << ('w' - 'a');
    int mask = 0, flag = 0;
    char c;

    while ((c = getchar()) != EOF) {
        c = to_lower(c);
        if (c >= 'a' && c <= 'z') {
            if ((1 << (c - 'a')) & son) {
                flag = 1;
            }
            mask |= 1 << (c - 'a');
        } else if (c == ' ' || c == ',' || c == '\t' || c == '\n') {
            if ((mask & ~vowel & ~son) == 0 && flag) {
                printf("Yes\n");
                return 0;
            } else {
                mask = 0;
                flag = 0;
            }
        }
    }
    printf("No\n");
    return 0;
}
```


## 9. Дневник отладки

| №  | Лаб. или дом. | Дата       | Время | Событие   | Действие по исправлению | Примечание          |
|----|---------------|------------|-------|-----------|-------------------------|---------------------|
| 1  | Дом.          | 28.11.2021 | 21:30 | Ошибка при вводе пустой строки        | Введение специального флага, указывающую на пустую строку во вводе                      | Неправильная трактовка ошибки |
| 2  | Дом.          | 30.11.2021 | 18:30 | Неправильный ответ в тесте 27        | Переосмысление алгоритма, попытка переписать программу, использующую конечные автоматы                      | Не самое удачное решение |
| 3  | Дом.          | 12.12.2021 | 19:30 | Ошибка при вводе слова, состоящего только из гласных        | Введение специального флага, указывающего на вхождение сонорной согласной в слово                      | Удачное решение |

## 10. Замечания автора по существу работы

Работа с множествами в ключе побитовых сдвигов показалась полезной. Это своеобразная замена множества без повторений, но, думаю, идея может пригодиться в решении дальнейших задач.

## 11. Выводы

Узнала, как производить битовые операции, а также как, не имея типа set в Си, создавать множества, используя битовые маски. Изучила несколько методов, с помощью которых можно заполнять битовые маски и работать с ними. Написала программу на языке Си для выполнения конкретной задачи, используя множества.
