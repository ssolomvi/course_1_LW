# Отчет по лабораторной работе N 3 по курсу
# "Фундаментальная информатика"

Студентка группы: M8О-113Б, Соломатина Светлана Викторовна\
Контакты: ssolomvi@gmail.com\
Работа выполнена: 16.09.2021\
Преподаватель: Довженко Анастасия Александровна

## 1. Тема

Операционная среда ОС UNIX

## 2. Цель работы

Изучение и освоение программного обеспечения ОС UNIX и приобретение навыков, необходимых для выполнения курсовых и лабораторных работ в среде UNIX.

## 3. Задание

Написать осмысленный сценарий использования команд, о которых шла речь на лабораторной и предоставить листинг их использования -- протокол из терминала.

## 4. Оборудование

Процессор: Intel Core i5-8265U @ 8x 3.9GH\
ОП: 7851 Мб\
НМД: 1024 Гб\
Монитор: 1920x1080\

## 5. Программное обеспечение

Операционная система семейства: **linux (ubuntu)**, версия **21.04**\
Интерпретатор команд: **bash**, версия **5.1.4**.\
Система программирования: **--**, версия **--**\
Редактор текстов: **emacs**, версия **25.2.2**\
Утилиты операционной системы: **ssh, scp, rsync, ping, tar, gunzip**\
Прикладные системы и программы: **--**\
Местонахождение и имена файлов программ и данных на домашнем компьютере: **/home/ssolomvi**\

## 6. Идея, метод, алгоритм решения задачи

Изучить сетевые средства ОС Unix и архиваторы.\

1. Сгенерировать ssh-ключи.
2. Добавить ключ на удалённый сервер, убедиться в возможности зайти на сервер.
3. На локальной машине создать файл, скопировать его в домашнюю директорию на удалённый сервер, зайти на удалённый сервер, убедиться что файл скопирован, выйти с удалённого сервера.
4. Создать непустую директорию, скопировать её в домашнюю директорию на удалённый сервер, зайти на удалённый сервер, убедиться что директория скопирована, выйти с удалённого сервера.
5. Скопировать файл ~/dir1/file1 с удалённого сервера на локальную машину, посмотреть его содержимое.
6. Скопировать директорию ~/dir2 с удалённого сервера на локальную машину, посмотреть содержимое файла dir2/file2.
7. Скопировать файл file3 с удалённого сервера на локальную машину, узнать кодировку файла, перекодировать файл в кодировку utf-8, посмотреть его содержимое.
8. Скопировать архивы archive.tar,  archive.tgz c удалённого сервера на локальную машину. Архив archive.tar распаковать, посмотреть его содержимое. Архив archive.tgz разжать и распаковать, посмотреть его содержимое.
9. Создать непустую директорию, заархивировать её, сжать архив, скопировать его на удалённую машину, проверить наличие архива на сервере.

## 7. Сценарий выполнения работы

1. Прослушать лекцию, изучить справочный материал и дополнительную литературу. 
2. Продемонстрировать владение основами работы с сетевыми средствами.
3. Запротоколировать сеанс.

## 8. Распечатка протокола

```bash
ssolomvi@ssolomvi:~$ ping -c 2 89.108.70.155
PING 89.108.70.155 (89.108.70.155) 56(84) bytes of data.
64 bytes from 89.108.70.155: icmp_seq=1 ttl=50 time=14.2 ms
64 bytes from 89.108.70.155: icmp_seq=2 ttl=50 time=9.30 ms

-— 89.108.70.155 ping statistics —-
2 packets transmitted, 2 received, 0% packet loss, time 1022ms
rtt min/avg/max/mdev = 9.298/11.736/14.175/2.438 ms
ssolomvi@ssolomvi:~$ telnet 89.108.70.155 5432
Trying 89.108.70.155...
Connected to 89.108.70.155.
Escape character is '^]'.
^]
Connection closed by foreign host.
ssolomvi@ssolomvi:~$ ssh-keygen
Generating public/private rsa key pair.
Enter file in which to save the key (/home/ssolomvi/.ssh/id_rsa): 
Enter passphrase (empty for no passphrase): 
Enter same passphrase again: 
Your identification has been saved in /home/ssolomvi/.ssh/id_rsa
Your public key has been saved in /home/ssolomvi/.ssh/id_rsa.pub
The key fingerprint is:
SHA256:lcKb91skLFUULClGWu/muLFeGyUE7OKeQXFZkR2Xugs ssolomvi@ssolomvi
The keys randomart image is:
+---[RSA 3072]----+
|         o+ooB=oo|
|       ..o*++.oo |
|        +=o.+..  |
|        o=.= .   |
|       oS.o * +  |
|        o. E *   |
|       . oo * o  |
|        o  = *   |
|         .+ o    |
+----[SHA256]-----+
ssolomvi@ssolomvi:~$ ssh-copy-id -f solomatina@89.108.70.155
INFO: attempting to log in with the new key(s), to filter out any that are already installed
INFO: 1 keys(s) remain to be installed -- if you are prompted now it is to install the new keys
solomatina@89.108.70.155 password:

Number of key(s) added: 2

Now try logging into the machine, with:   "ssh solomatina@89.108.70.155"
and check to make sure that only the key(s) you wanted were added.
ssolomvi@ssolomvi:~$ ssh solomatina@89.108.70.155
Welcome to Ubuntu 20.04.3 LTS (GNU/Linux 5.4.0-84-generic x86_64)

* Documentation: https://help.ubuntu.com
* Management: https://landscape.canonical.com
* Support: https://ubuntu.com/advantage
Last login: Sat Sep 11 13:55:33 2021 from 185.215.176.15
solomatina@89-108-70-155:~$ exit
logout
Connection to 89.108.70.155 closed.
ssolomvi@ssolomvi:~$ echo "bla bla bla" > filek
ssolomvi@ssolomvi:~$ scp filek solomatina@89.108.70.155:/home/solomatina
filek 100% 12 0.5KB/s 00:00
ssolomvi@ssolomvi:~$ ssh solomatina@89.108.70.155
Welcome to Ubuntu 20.04.3 LTS (GNU/Linux 5.4.0-84-generic x86_64)

* Documentation: https://help.ubuntu.com
* Management: https://landscape.canonical.com
* Support: https://ubuntu.com/advantage
Last login: Wed Sep 15 23:26:29 2021 from 79.104.4.161
solomatina@89-108-70-155:~$ ls
archive.tar dir1 file1 filek pr_stud.pub
archive.tgz dir2 file3 pr_stud stud
solomatina@89-108-70-155:~$ exit
logout
Connection to 89.108.70.155 closed.
 
ssolomvi@ssolomvi:~$ mkdir stud-dir
ssolomvi@ssolomvi:~$ cd stud-dir ; touch stud-file ; cd ..
ssolomvi@ssolomvi:~$ scp -r stud-dir solomatina@89.108.70.155:/home/solomatina
stud-file 100% 0 0.0KB/s 00:00
ssolomvi@ssolomvi:~$ ssh solomatina@89.108.70.155
Welcome to Ubuntu 20.04.3 LTS (GNU/Linux 5.4.0-84-generic x86_64)

* Documentation: https://help.ubuntu.com
* Management: https://landscape.canonical.com
* Support: https://ubuntu.com/advantage
Last login: Wed Sep 15 23:36:13 2021 from 79.104.4.161
solomatina@89-108-70-155:~$ ls
archive.tar dir1 file1 filek pr_stud.pub stud-dir
archive.tgz dir2 file3 pr_stud stud
solomatina@89-108-70-155:~$
solomatina@89-108-70-155:~$ exit
logout
Connection to 89.108.70.155 closed.
ssolomvi@ssolomvi:~/stud-dir$ scp solomatina@89.108.70.155:~/dir1/file1 /home/ssolomvi/stud-dir
file1 100% 823 70.3KB/s 00:00
ssolomvi@ssolomvi:~/stud-dir$ ls
file1
ssolomvi@ssolomvi:~/stud-dir$ scp -r solomatina@89.108.70.155:~/dir2 /home/ssolomvi/stud-dir
file2 100% 320 28.1KB/s 00:00
ssolomvi@ssolomvi:~/stud-dir$ cd dir2 ; cat file2
Small is beautiful.
Make each program do one thing well.
Build a prototype as soon as possible.
Choose portability over efficiency.
Store data in flat text files.
Use software leverage to your advantage.
Use shell scripts to increase leverage and portability.
Avoid captive user interfaces.
Make every program a filter.
ssolomvi@ssolomvi:~$ cd stud-dir ; touch file3
ssolomvi@ssolomvi:~/stud-dir$ rsync -zh solomatina@89.108.70.155:~/file3 /home/ssolomvi/stud-dir/file3
ssolomvi@ssolomvi:~/stud-dir$ file -i file3
file3: text/plain; charset=windows-1251
ssolomvi@ssolomvi:~/stud-dir$ iconv -f windows-1251 -t utf-8 files file3
Стандарт передачи IP дейтаграмм с помощью почтовых голубей.


Назначение этой заметки

Эта заметка описывает экспериментальный метод инкапсуляции IP дейтаграмм в птице-носителе. Эта спецификация полностью работоспособна в условиях городской сети. Это экспериментальный, не рекомендуемый стандарт. Стандарт может применятся без ограничений.

Обзор и применение

Птицы-носители могут обеспечивать высокую задержку, низкую пропускную способность а также низкую высоту уверенного приема сервиса. Топология соединения ограничена к одному точка-точка пути для каждого носителя, но много носителей могут использоваться без каких либо значительных помех для всех остальных, кроме ранней весны. Это возможно из за того что носители используют 3D пространство, вместо 1D реализуемого в IEEE802.3. Носители имеют встроенных механизм защиты от столкновений, что повышает их доступность. В отличии от некоторых сетевых технологий, как например радо, соединение не ограничено зоной прямой видимости. Сервисы приема уже доступны в некоторых городах, как правило они базируются на центральных узлах связи.
Формат блока данных
IP дейтаграмма печатается на маленьком скрученном листке бумаги, в шестнадцатеричном формате, где каждый октет разделен белым полем и черными символами. Скрученная бумажка оборачивается вокруг одной ноги птице-носителя. Для защиты дейтаграммы используется полоска трубчатой ленты. Пропускная способность ограничена длинной ноги носителя. MTU является переменной величиной, и парадоксальной, но в целом возрастает с увеличением возраста носителя. Типичное значение MTU равно 256 миллиграммам. Некоторым дейтаграммам возможно понадобится заполнение пустой информацией(padding).
После получения, трубчатая лента снимается, и бумажная копия дейтаграммы сканируется в электронную удобную для дальнейшей обработки форму.

Обсуждение

Некоторые виды сервиса могут быть предоставлены с приоритетно поклеванным порядком(QoS). Дополнительным свойством является встроенный механизм обнаружения червей и их ликвидация. Поскольку протокол IP гарантирует только лучший алгоритм доставки, то утеря одного несущего считается терпимой. Со временем несущие самовоспроизводятся. Бури могут служить причиной отсутствия вещания. В случае потери(падения птицы-носителя) связи, попытки доставки будут осуществляться снова и снова. Аудит работы автоматически генерируется, и может быть найден на бревнах и столбах связи.

Безопасность

Безопасность не является проблемой в условиях нормальной эксплуатации, но специальные меры (шифрование данных) должны быть приняты в условиях тактического применения птиц- 
ssolomvi@ssolomvi:~/stud-dir$ rsync solomatina@89.108.70.155:~/archive.tar /home/ssolomvi/stud-dir
 
ssolomvi@ssolomvi:~/stud-dir$ tar -tf archive.tar
mybestmemes/
mybestmemes/._01.jpg
mybestmemes/01.jpg
mybestmemes/._03.jpg
mybestmemes/03.jpg
mybestmemes/._02.jpg
mybestmemes/02.jpg
ssolomvi@ssolomvi:~/stud-dir$ tar -xvf archive.tar
mybestmemes/
mybestmemes/._01.jpg
mybestmemes/01.jpg
mybestmemes/._03.jpg
mybestmemes/03.jpg
mybestmemes/._02.jpg
mybestmemes/02.jpg
 
ssolomvi@ssolomvi:~/stud-dir$ cd mybestmemes ; ls -la
total 200
drwxr-xr-x 2 ssolomvi ssolomvi 4096 сен 11 07:15 .
drwxrwxr-x 4 ssolomvi ssolomvi 4096 сен 16 09:21 ..
-rw-r--r— 1 ssolomvi ssolomvi 178 сен 11 07:15 ._01.jpg
-rw-r--r— 1 ssolomvi ssolomvi 63962 сен 11 07:15 01.jpg
-rw-r--r— 1 ssolomvi ssolomvi 178 сен 11 07:15 ._02.jpg
-rw-r--r— 1 ssolomvi ssolomvi 46249 сен 11 07:15 02.jpg
-rw-r--r— 1 ssolomvi ssolomvi 178 сен 11 07:15 ._03.jpg
-rw-r--r— 1 ssolomvi ssolomvi 66450 сен 11 07:15 03.jpg
 
ssolomvi@ssolomvi:~/stud-dir/mybestmemes$ cd .. ; rsync solomatina@89.108.70.155:~/archive.tgz /home/ssolomvi/stud-dir
ssolomvi@ssolomvi:~/stud-dir$ gunzip -c archive.tgz | tar xvf -
memes/
memes/._01.jpg
memes/01.jpg
memes/._03.jpg
memes/03.jpg
memes/._02.jpg
memes/02.jpg
ssolomvi@ssolomvi:~/stud-dir$ cd memes ; ls -la ; cd ..
total 112
drwxr-xr-x 2 ssolomvi ssolomvi 4096 сен 11 07:06 .
drwxrwxr-x 5 ssolomvi ssolomvi 4096 сен 16 09:28 ..
-rw-r--r— 1 ssolomvi ssolomvi 178 сен 11 07:05 ._01.jpg
-rw-r--r— 1 ssolomvi ssolomvi 27409 сен 11 07:05 01.jpg
-rw-r--r— 1 ssolomvi ssolomvi 178 сен 11 07:06 ._02.jpg
-rw-r--r— 1 ssolomvi ssolomvi 35725 сен 11 07:06 02.jpg
-rw-r--r— 1 ssolomvi ssolomvi 178 сен 11 07:06 ._03.jpg
-rw-r--r— 1 ssolomvi ssolomvi 26082 сен 11 07:06 03.jpg
ssolomvi@ssolomvi:~/stud-dir$ mkdir grust ; cd grust ; echo "I'm so sad">plac ; cd ..
ssolomvi@ssolomvi:~/stud-dir$ tar -czf my-arch.tar.gz grust
ssolomvi@ssolomvi:~/stud-dir$ scp my-arch.tar.gz solomatina@89.108.70.155:~/
my-arch.tar.gz 100% 166 20.4KB/s 00:00
ssolomvi@ssolomvi:~/stud-dir$ ssh solomatina@89.108.70.155
Welcome to Ubuntu 20.04.3 LTS (GNU/Linux 5.4.0-84-generic x86_64)

* Documentation: https://help.ubuntu.com
* Management: https://landscape.canonical.com
* Support: https://ubuntu.com/advantage
Last login: Thu Sep 16 08:31:30 2021 from 185.215.176.15 
solomatina@89-108-70-155:~$ ls
archive.tar dir1 file1 filek pr_stud stud
archive.tgz dir2 file3 my-arch.tar.gz pr_stud.pub stud-dir
```

## 9. Дневник отладки


| №  | Лаб. или дом. | Дата       | Время | Событие   | Действие по исправлению | Примечание          |
|----|---------------|------------|-------|-----------|-------------------------|---------------------|
| 0  | Дом           | 16.09.2021 | 21:30 | --        | --                      | Всё прошло исправно |



## 10. Замечания автора по существу работы

Работа была полезной.

## 11. Выводы

Убедилась, что Linux -- лучшая система для удалённого использования, поскольку она является самой защищённой ОС, и в ней легко работать с сетевыми средствами.

Изучила основы работы с сетевыми средствами в ОС Linux. Научилась подключаться к удалённому серверу, перемещаться по его директориям, манипулировать файлами, пользоваться утилитами tar и gunzip.
