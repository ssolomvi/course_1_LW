# Отчет по лабораторной работе N 11 по курсу
# "Фундаментальная информатика"

Студентка группы: M8О-113Б, Соломатина Светлана Викторовна\
Контакты: ssolomvi@gmail.com\
Работа выполнена: 11.11.2021\
Преподаватель: Довженко Анастасия Александровна

## 1. Тема

Обработка последовательности литер входного текстового файла. Простейшие приёмы лексического анализа. Диаграммы состояний и переходов.

## 2. Цель работы

Составить программу на языке Си, выполняющую анализ и обработку вводимого текста в соответствии с выданным преподователем вариантом задания.

## 3. Задание

Вариант 28. Составить программу, выполняющую анализ и обработку вводимого ascii-текста. Требуется построчно выделить первое и последнее (по счету) десятичные числа строк текста.

## 4. Оборудование

Процессор: AMD Ryzen 5 4500U with Radeon Graphics 2.38 GHz\
ОП: 16384 Мб\
НМД: 512 Гб\
Монитор: 1920x1080

## 5. Программное обеспечение

Операционная система семейства: **linux (ubuntu)**, версия **21.04**\
Интерпретатор команд: **bash**, версия **5.1.4**.\
Местонахождение и имена файлов программ и данных на домашнем компьютере: **/home/ssolomvi**

## 6. Идея, метод, алгоритм решения задачи

Из поставленной задачи следуют наборы состояний (case): SEARCH1, IS_F_NUM, FIRST, SEARCH2, IS_L_DIGIT, LAST, IS_L, где SEARCH1 -- пропуск вводимых символов до первого десятичного слова, IS_F_NUM -- состояние, в котором определяется, нашли ли мы первое число, FIRST -- обработка первого десятичного слова, LAST -- обработка второго десятичного слова, SEARCH2 -- обработка знака последнего десятичного слова, IS_L_DIGIT -- поиск последнего десятичного слова, IS_L -- пропуск вводимых символов до пробела или перевода строки, выбираемый, в случае, если рассматриваемое слово недесятичное. \
Используются следующие переменные: c - вводимый символ, number2 -- первое число, number3 -- второе число, number4 -- буфер для второго числа, fsign -- знак певрого числа, lsign -- знак второго числа, lnumber -- буфрерное количество разрядов второго числа, i -- количество разрядов первого числа, j -- количество разрядов второго числа, znak -- буферная переменная для хранения знака второго числа.

## 7. Сценарий выполнения работы

1. Изучить материалы лекции
2. Составить алгоритм действий, переходов состояний
3. Написать программу, удовлетворяющую условиям лабораторной работы
4. Запротоколировать сеанс.

| Тест  | Ввод | Вывод |
|----|---------------|---------------|
| 1  | 928357av -careful 1234 | 1234 1234 |
| 2  | nothing |  |
| 3  | aim do 05 -150 man -19 | 05 -19 |
| 4  | s12 18h -0 1827 56 sagh 89 | -0 89 |
| 5  | +0 sd -12q hello world! | +0 +0 |

## 8. Распечатка протокола

```C
#include <stdio.h>
#include <math.h>

int is_num(char c)
{
    return c >= '0' && c <= '9'; 
}

void cout(long long x, int j, int s)
{
    int q;
    if (s == 1) {
        printf("+");
    } else if (s == -1) {
        printf("-");
    }
    if (x >= 0) {
        while (j != 0) {
            q = x / pow(10, j - 1);
            printf("%d", q);
            x = x - q * pow(10, j - 1);
            j = j - 1;
        }
    }
    printf(" ");
}

typedef enum {SEARCH1, IS_F_NUM, FIRST, SEARCH2, IS_L_DIGIT, LAST, IS_L} State;

int main(void)
{
    char c;
    long long number2 = 0, number3 = 0, number4 = 0;
    int fsign = 0, lsign = 0, lnumber = 0, i = 1, j = 1, znak = 0;

    State state = SEARCH1;
    while ((c = getchar()) != EOF) {
        switch (state) {
            case SEARCH1:
                if (c == '+') {
                    fsign = 1;
                    state = IS_F_NUM;
                } else if (c == '-') {
                    fsign = -1;
                    state = IS_F_NUM;
                } else if (is_num(c)) {
                    fsign = 0;
                    number2 = c - '0';
                    state = FIRST;
                }
                break;

            case IS_F_NUM:
                if (is_num(c)) {
                    number2 = c - '0';
                    state = FIRST;
                } else if (c == '\n' || c == ' ') {
                    state = SEARCH1;
                }
                break;


            case FIRST:
                if (is_num(c)) {
                    number2 = number2 * 10 + c - '0';
                    i += 1;
                } else if (c == '\n') {
                    cout(number2, i, fsign);
                    cout(number2, i, fsign);
                    printf("\n");
                    i = 1;
                    number2 = 0;
                    fsign = 0;
                    state = SEARCH1;
                } else if (c == ' ') {
                    cout(number2, i, fsign);
                    number4 = number2;
                    lnumber = i;
                    lsign = fsign;
                    state = SEARCH2;
                } else {
                    i = 1;
                    number2 = 0;
                    fsign = 0;
                    state = SEARCH1;
                }
                break;

            case SEARCH2:
                if (is_num(c)) {
                    number3 = c - '0';
                    lsign = 0;
                    state = LAST;
                } else if (c == '+') {
                    lsign = 1;
                    state = IS_L_DIGIT;
                } else if (c == '-') {
                    lsign = -1;
                    state = IS_L_DIGIT;
                } else if (c == ' ') {
                    number4 = number3;
                    lnumber = j;
                    znak = lsign;
                    lsign = 0;
                    j = 1;
                } else if (c == '\n') {
                    znak = lsign;
                    cout(number4, lnumber, znak);
                    printf("\n");
                    j = 1;
                    i = 1;
                    fsign = 0; lsign = 0; znak = 0;
                    lnumber = 0; number4 = 0; number3 = 0; number2 = 0;
                    state = SEARCH1;
                } else {
                    state = IS_L;
                }
                break;

            case IS_L_DIGIT:
                if (is_num(c)) {
                    number3 = c - '0';
                    state = LAST;
                } else if (c == ' ') {
                    state = SEARCH2;
                } else if (c == '\n') {
                    cout(number4, lnumber, znak);
                    printf("\n");
                    j = 1; i = 1;
                    fsign = 0; lsign = 0; znak = 0;
                    lnumber = 0; number4 = 0; number3 = 0; number2 = 0;
                    state = SEARCH1;
                } else {
                    state = IS_L;
                }
                break;

            case LAST:
                if (is_num(c)) {
                    number3 = number3 * 10 + c - '0';
                    j += 1;
                } else if (c == '\n') {
                    lnumber = j;
                    znak = lsign;
                    cout(number3, lnumber, znak);
                    printf("\n");
                    j = 1;
                    i = 1;
                    fsign = 0; lsign = 0; znak = 0;
                    lnumber = 0; number4 = 0; number3 = 0; number2 = 0;
                    state = SEARCH1;
                } else if (c == ' ') {
                    number4 = number3;
                    znak = lsign;
                    lsign = 0;
                    lnumber = j;
                    j = 1;
                    state = SEARCH2;
                } else {
                    j = 1;
                    number3 = 0;
                    lsign = 0;
                    state = IS_L;
                }
                break;

            case IS_L:
                if (c == ' ') {
                    state = SEARCH2;
                } else if (c == '\n') {
                    cout(number4, lnumber, znak);
                    printf("\n");
                    j = 1; i = 1;
                    fsign = 0; lsign = 0; znak = 0;
                    lnumber = 0; number4 = 0; number3 = 0; number2 = 0;
                    state = SEARCH1;
                }
                break;
        }
    }
    return 0;
}
```

## 9. Дневник отладки

| №  | Лаб. или дом. | Дата       | Время | Событие   | Действие по исправлению | Примечание          |
|----|---------------|------------|-------|-----------|-------------------------|---------------------|
| 0  | Дом.          | --.--.202- | 21:30 | --        | --                      | Всё прошло исправно |

## 10. Замечания автора по существу работы

На самом деле, метод использования состояний для решения задачи удивил некоторым удобством, поскольку преследует строгую логику, но показался подходящим только для обработки каких-то мелких единичных процессов. Очень напомнил машину Тьюринга.

## 11. Выводы

Выяснила, что иногда использование состояний, а также объявление и использование перечисляемых типов данных в языке Си может быть полезным для решения некоторых задач. Научилась обрабатывать последовательность литер, используя язык Си, познакомилась с диаграммами состояний и переходов, их использованием для решения задач. Научилась объявлять перечисляемый тип данных и использовать его в решении задач. Написала программу для решения конкретной задачи на языке Си.
