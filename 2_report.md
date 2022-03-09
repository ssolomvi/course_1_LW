# Отчет по лабораторной работе N 2 по курсу
# "Фундаментальная информатика"

Студентка группы: M8О-113Б, Соломатина Светлана Викторовна\
Контакты: ssolomvi@gmail.com\
Работа выполнена: 14.09.2021\
Преподаватель: Довженко Анастасия Александровна

## 1. Тема

Операционная среда ОС UNIX

## 2. Цель работы

Изучение и освоение программного обеспечения ОС UNIX и приобретение навыков, необходимых для выполнения курсовых и лабораторных работ в среде UNIX.

## 3. Задание

Написать осмысленный сценарий использования команд, о которых шла речь на лабораторной и предоставить листинг их использования -- протокол из терминала. 

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

В процессе выполнения этой л/б, знакомилась с виртуальной машиной, новой _(для себя)_ операционной системой, терминалом, основными командами, работала с интерактивным учебником, Google, ошибалась и исправляла ошибки.

В листинге команд попыталась изложить накопленные знания по основам работы с Bash. Включила команды по созданию/удалению/перемещению файлов, перемещению по директориям, работе с переменными, операторами. Постаралась минимально использовать команды перемещения по директориям, просмотра их содержимого.

Задачей ставила научиться использованию следующих команд, операторов, приёмов:
1. cd
2. ls
3. cat
4. echo
5. touch
6. cp
7. mv
8. rm
9. ps
10. mkdir
11. rmdir
12. chmod
13. chown
14. Переменные окружения
15. Пернаправление ввода/вывода
16. Конвейер (|)
17. Операторы && || ; &

## 7. Сценарий выполнения работы

Прежде всего, как для новичка, стояла задача увидеть новое и прекрасное в небезосновательно популярной Linux Ubuntu. Первостепенно важной показалось работа с файлами -- от создания до удаления.

Сложности возникли лишь с командой chown -- для разрешения проблемы всего лишь нужно было заглянуть в man chown, чтобы понять и разобрать синтаксис команды.
```bash
ssolomvi@ssolomvi:~$ chown root /home/ssolomvi/stud
chown: changing ownership of '/home/ssolomvi/stud': Operation not permitted
```
Итак, начав с изучения интерактивного учебника, в этой л/б я закончила на операторах -- наиболее интригующими показались возможности, предполагаемые конвейером pipe, но, до конца не осознавая, как правильно их применить, скудно отразила их в конечном листинге.

Сценарий работы:
1. Создание нового пользователя
2. Добавление ssh ключей для него
3. Создание директорий
4. Создание файлов, запись в них с терминала, их конкатенация
5. Вывод текста ошибок, возникавших у меня в процессе подготовки, в файл
6. Создание и вывод локальной переменной
7. Запуск sleep-процесса, вывод действительных процессов
8. Вывод отсортированного списка файлов
9. Наделение правами чтения-записи-выполнения файла всех пользователей системы
10. Изменение прав на файл для пользователя
11. Удаление директорий
12. Удаление пользователя

## 8. Распечатка протокола

```bash
ssolomvi@ssolomvi:~$ sudo bash
[sudo] password for ssolomvi:
root@ssolomvi:/home/ssolomvi# useradd solom
root@ssolomvi:/home/ssolomvi# passwd solom
New password:
Retype new password:
passwd: password updated successfully
root@ssolomvi:/home/ssolomvi# su - solom
$ pwd
/home/solom
$ whoami
solom
$ ssh-keygen
Generating public/private rsa key pair.
Enter file in which to save the key (/home/solom/.ssh/id_rsa): keys
Enter passphrase (empty for no passphrase):
Enter same passphrase again:
Your identification has been saved in keys
Your public key has been saved in keys.pub
The key fingerprint is:
SHA256:1LIrKIbJaFw4/NXZRRpTOMwYvUCIUvAloItv0jFfbPA solom@ssolomvi
The keys randomart image is:
+---[RSA 3027]----+
|      .++o       |
|      ++++       |
|   . ..** .      |
|E.. o oo o + o   |
|.+.o .  S o B    |
|+.o.o    . o     |
|=.o*..           |
|o=++=            |
|.*O+.            |
+----[SHA256]-----+
$ ls -la
total 36
drwxr-x-— 3 solom solom 4096 сен 14 19:44 .
drwxr-xr-x 4 root root 4096 сен 14 18:12 ..
-rw-r--r— 1 solom solom 220 мар 19 19:02 .bash_logout
-rw-r--r— 1 solom solom 3771 мар 19 19:02 .bashrc
-rw-----— 1 solom solom 2655 сен 14 19:44 keys
-rw-r--r— 1 solom solom 568 сен 14 19:44 keys.pub
-rw-r--r— 1 solom solom 807 мар 19 19:02 .profile
-rw-rw-r— 1 solom solom 53 сен 14 18:35 rm-error.log
drwxrwxr-x 2 solom solom 4096 сен 14 18:33 stud1
$ mkdir stud stud1 stud2
$ cd stud
$ touch file1 file2
$ ls -la
total 8
drwxrwxr-x 2 solom solom 4096 сен 14 18:31 .
drwxr-x--- 5 solom solom 4096 сен 14 18:31 ..
-rw-rw-r-- 1 solom solom    0 сен 14 18:31 file1
-rw-rw-r-- 1 solom solom    0 сен 14 18:31 file2
$ echo "Hello world!" > file1 ; echo "My name is Svetlana" > file2 
$ cat file1 file2
Hello world!
My name is Svetlana
$ cp file1 /home/solom/stud1 ; mv file2 /home/solom/stud2 ; rm file1
$ cd ..
$ rm stud 2>rm-error.log
$ rmdir sstud 2>rm-error.log
$ rmdir stud1 2>rm-error.log
$ cat rm-error.log
rmdir: failed to remove 'stud1': Directory not empty
$ rmdir --ignore-fail-on-non-empty stud
$ foo="there is work to be done"
$ echo $foo
there is work to be done
$ sleep 20 &
$ ps
    PID TTY          TIME CMD
   2158 pts/0    00:00:00 sh
   2184 pts/0    00:00:00 sleep
   2185 pts/0    00:00:00 ps
$ ls | grep s
stud1
stud2
$ chmod ugo+rwx /home/solom/stud1/file1
[1] + Done                       sleep 20
$ chown ssolomvi -c /home/solom/stud1
chown: changing ownership of '/home/solom/stud1': Operation not permitted
$ chown solom -c /home/solom/stud1
$ echo $PATH
/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin:/usr/games:/usr/local/games:/snap/bin
$ echo "My cat's name is Shusha" > /home/ssolomvi/stud1/file1 || df -h
sh: 9: cannot create /home/ssolomvi/stud1/file1: Permission denied
Filesystem Size Used Avail Use% Mounted on
tmpfs 198M 1,8M 197M 1% /run
/dev/sda3 20G 8,4G 9,8G 47% /
tmpfs 990M 0 990M 0% /dev/shm
tmpfs 5,0M 4,0K 5,0M 1% /run/lock
tmpfs 4,0M 0 4,0M 0% /sys/fs/cgroup
/dev/sda2 512M 5,3M 507M 2% /boot/efi
tmpfs 198M 1,3M 197M 1% /run/user/1000
tmpfs 198M 164K 198M 1% /run/user/1001
$ su - ssolomvi
Password:
ssolomvi@ssolomvi:~$ sudo bash
root@ssolomvi:/home/ssolomvi# userdel -f solom
root@ssolomvi:/home/ssolomvi#
```

## 9. Дневник отладки

| №  | Лаб. или дом. | Дата       | Время | Событие   | Действие по исправлению | Примечание          |
|----|---------------|------------|-------|-----------|-------------------------|---------------------|
| 0  | Дом           | 14.09.2021 | 21:30 | --        | --                      | Всё прошло исправно |

## 10. Замечания автора по существу работы

Иногда было весело (когда ошибки находили решение) иногда очень грустно (когда возникали ошибки)

## 11. Выводы

Подытоживая, скажу, что выполнять лабораторную по основам работы с терминалом было достаточно любопытно. В процессе не раз думала установить ОС Linux параллельно с Windows, т.к. осознаю, что это более безопасная и интересная система. Предполагаю, полученные знания мне понадобятся в дальнейшей работе. Linux, привлекательный своей логикой, вдохновил и продолжает вдохновлять многих на создание подобных почти интуитивно понятных для пользователя систем -- это сложившеейся в ходе выполнения лабораторной работы впечатление, причина, почему я считаю освоение этой ОС важным.

Хотя было и не очень интересное. Например, разбираться с миллионом глупых ошибок, искать применение сочетаний операторов вроде '||', './', '~/' и не находить или попадать на статьи для продвинутых пользователей линукс. Последнее по ощущениям было хуже всего. 
