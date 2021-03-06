# Отчет по лабораторной работе N 12 по курсу
# "Фундаментальная информатика"

Студентка группы: M8О-113Б, Соломатина Светлана Викторовна\
Контакты: ssolomvi@gmail.com\
Работа выполнена: 23.10.2021\
Преподаватель: Довженко Анастасия Александровна

## 1. Тема

Техника работы с целыми числами. Системы счисления

## 2. Цель работы

Составить программу на языке Си в целом типе данных, которая для любых допустимых и корректно записанных чисел этого типа в десятичном изображении, поступающих на стандартный ввод программы, выполняет указанное заданием действие над их значениями.

## 3. Задание

Вариант 9. Проверить упорядоченность цифр числа по неубыванию

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

Используя цикл, сравнивать последнюю и предпоследнюю цифры входного числа, при каждой итерации обновлять число целочисленным делением на 10.

## 7. Сценарий выполнения работы

1. Изучить материалы лекции, дополнительную литературу.
2. Составить алгоритм
3. Написать программу на Си
4. Заолнить отчёт

| Тест  | Ввод | Вывод |
|----|---------------|---------------|
| 1  | 1234567 | True |
| 2  | -192837 | False |
| 3  | +9 | True |
| 4  | 100 | False |
| 5  | 1111 | True |
| 5  | 268953 | False|
| 5  | 123123 | False |

## 8. Распечатка протокола

```C
#include <stdio.h>

int abs(int x)
{
    return (x < 0) ? -x : x;
}

int main(void)
{
    int number = 0;
    while (scanf("%d", &number) == 1) {
        number = abs(number);
        while (number != 0 && number % 10 >= number % 100 / 10) {
            number /= 10;
        }
        if (number == 0) {
            printf("True\n");
        } else {
            printf("False\n");
        }
    }
    return 0;
}
```

## 9. Дневник отладки

| №  | Лаб. или дом. | Дата       | Время | Событие   | Действие по исправлению | Примечание          |
|----|---------------|------------|-------|-----------|-------------------------|---------------------|
| 1  | Лаб.          | 23.10.2021 | 13:40 | Нарушение правил оформления программ       | Исправила code-style программы           | Помогло |

## 10. Замечания автора по существу работы

Задание было лёгким и расслабляющим, так что выполнение этой лабораторной очень понравилось. Можно добавить, что оно являет собой подвтерждение великой народной мудрости: нечего в мух пушкой стрелять. 

## 11. Выводы

Выяснила, что можно рассматривать разряды числа, не используя массивы, строки, указатели, а лишь примитивные методы работы с целыми числами.\
Научилась работать с целыми числами. Написала программу на Си для решения конкретной задачи.
