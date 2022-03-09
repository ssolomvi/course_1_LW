# Отчёт по лабораторной работе N 10 по курсу
# "Фундаментальная информатика"

Студентка группы: M8О-113Б, Соломатина Светлана Викторовна\
Контакты: ssolomvi@gmail.com\
Работа выполнена: 15.11.2021\
Преподаватель: Довженко Анастасия Александровна

## 1. Тема

Отладчик системы программирования ОС UNIX

## 2. Цель работы

Научиться производить отладку программ при помощи отладчика gdb.

## 3. Задание

Написать программу на языке Си и провести её отладку.

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

Использовать программу, составленную для решения задания 9 лабораторной работы, провести её отладку при помощи отладчика gdb.

## 7. Сценарий выполнения работы

1. Изучить учбеный материал по отладке программ.
2. Попробовать разные возможности отладчика gdb на примере программы, составленной для выполнения задания 9 лабораторной работы.
3. Запротоколировать сеанс.

## 8. Распечатка протокола

```Bash

ssolomvi@ssolomvi:~$ echo "0 0 0" >> igl.txt
ssolomvi@ssolomvi:~$ gcc -g2 file.c -o output
ssolomvi@ssolomvi:~$ gdb output
GNU gdb (Ubuntu 10.1-2ubuntu2) 10.1.90.20210411-git
Copyright (C) 2021 Free Software Foundation, Inc.
License GPLv3+: GNU GPL version 3 or later <http://gnu.org/licenses/gpl.html>
This is free software: you are free to change and redistribute it.
There is NO WARRANTY, to the extent permitted by law.
Type "show copying" and "show warranty" for details.
This GDB was configured as "x86_64-linux-gnu".
Type "show configuration" for configuration details.
For bug reporting instructions, please see:
<https://www.gnu.org/software/gdb/bugs/>.
Find the GDB manual and other documentation resources online at:
    <http://www.gnu.org/software/gdb/documentation/>.

For help, type "help".
Type "apropos word" to search for commands related to "word"...
Reading symbols from output...
(gdb) b main
Breakpoint 1 at 0x13b1: file file.c, line 29.
(gdb) b 37
Breakpoint 2 at 0x13ec: file file.c, line 37.
(gdb) run < ijl.txt
Starting program: /home/ssolomvi/output < ijl.txt
/bin/bash: line 1: ijl.txt: No such file or directory
During startup program exited with code 1.
(gdb) b main
Breakpoint 1 at 0x1371: file file.c, line 30.
(gdb) l main
24	}
25	int compute_l(int i, int j, int l){
26	    return mod(i, 10) + mod(j, 10) + mod(l, 10);
27	}
28	
29	int main(void) {
30	    int i, j = 0, l = 0, k;
31	    int i_old = i;
32	    int j_old = j;
33	    int l_old = l;
(gdb) list
34	
35	    for (k = 1; k < 50 && !in_area(i_old, j_old); ++k){
36	        i = compute_i(i_old, j_old, l_old, k);
37	        j = compute_j(i_old, j_old, l_old);
38	        l = compute_l(i_old, j_old, l_old);
39	
40	        i_old = i;
41	        j_old = j;
42	        l_old = l;
43	    }
(gdb) b 35
Breakpoint 2 at 0x1391: file file.c, line 35.
(gdb) s
The program is not being run.
(gdb) run
Starting program: /home/ssolomvi/output 

Breakpoint 1, main () at file.c:30
30	    int i, j = 0, l = 0, k;
(gdb) s
31	    int i_old = i;
(gdb) c
Continuing.

Breakpoint 2, main () at file.c:35
35	    for (k = 1; k < 50 && !in_area(i_old, j_old); ++k){
(gdb) c
Continuing.
Yes
8 -5 19 22
[Inferior 1 (process 4714) exited normally]
(gdb) l main
24	}
25	int compute_l(int i, int j, int l){
26	    return mod(i, 10) + mod(j, 10) + mod(l, 10);
27	}
28	
29	int main(void) {
30	    int i, j = 0, l = 0, k;
31	    int i_old = i;
32	    int j_old = j;
33	    int l_old = l;
(gdb) run
Starting program: /home/ssolomvi/output 

Breakpoint 1, main () at file.c:30
30	    int i, j = 0, l = 0, k;
(gdb) watch i
Hardware watchpoint 3: i
(gdb) s
31	    int i_old = i;
(gdb) s
32	    int j_old = j;
(gdb) s
33	    int l_old = l;
(gdb) s

Breakpoint 2, main () at file.c:35
35	    for (k = 1; k < 50 && !in_area(i_old, j_old); ++k){
(gdb) s
in_area (x=0, y=0) at file.c:17
17	    return (x >= 5 && 15 >= x && y >= -15 && -5 >= y);
(gdb) n
18	}
(gdb) n
main () at file.c:36
36	        i = compute_i(i_old, j_old, l_old, k);
(gdb) n
37	        j = compute_j(i_old, j_old, l_old);
(gdb) n
38	        l = compute_l(i_old, j_old, l_old);
(gdb) print i
$1 = 0
(gdb) print j
$2 = 2
(gdb) print l
$3 = 0
(gdb) kill
Kill the program being debugged? (y or n) y
[Inferior 1 (process 4721) killed]
(gdb) quit

```

## 9. Дневник отладки

| №  | Лаб. или дом. | Дата       | Время | Событие   | Действие по исправлению | Примечание          |
|----|---------------|------------|-------|-----------|-------------------------|---------------------|
| 0  | Дом.          | 15.11.2021 | 21:30 | --        | --                      | Всё прошло исправно |

## 10. Замечания автора по существу работы

Не смотря на возможности, предлагаемые отладчиком gdb, думаю, в современности он неудобен, т.к. большинство сред разработки предлагают встроенные отладчики, или так называемые дебаггеры, где весь функционал gdb реализован проще и понятнее.

## 11. Выводы

Выяснила, что отладка программы при помощи gdb гораздо продуктивнее, чем отладка программ при помощи бумаги и пошагового прохождения по программе вручную, т.к. в отладчике gdb есть множество полезных команд, которые упрощают отладку. Также такая отладка показывает, как именно происходит работа программы на конкретной машине, что является очень полезным, т.к. многие проблемы написанного кода сложно найти, не узнав, как работает код на данной машине.

Научилась работать с отладчиком gdb. Использовав программу, составленную для решения задания 9 лабораторной работы, провела её отладку при помощи отладчика gdb.
