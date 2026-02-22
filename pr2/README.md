### Завдання 1<br>
Напишіть програму для визначення моменту, коли time_t<br>
закінчиться.Дослідіть, які зміни відбуваються в залежності від 32- та<br>
64-бітної архітектури. Дослідіть сегменти виконуваного файлу.<br>
**Компіляція та запуск**<br>
Для 64-бітної архітектури<br>
```
gcc pr2_1.c -o pr2_1_64
./pr2_1_64
```
Результат<br>
```
Size of time_t: 8 bytes (64 bits)
Architecture: 64-bit time_t equivalent
Max timestamp value: 9223372036854775807
Date is too far in the future to display!
```
Для 32-бітної архітектури<br>
```
gcc -m32 pr2_1.c -o pr2_1_32
./pr2_1_32
```
Результат<br>
```
Size of time_t: 4 bytes (32 bits)
Architecture: 32-bit time_t equivalent
Max timestamp value: 2147483647
End of time date (UTC): Tue Jan 19 03:14:07 2038
```
Щоб побачити різницю в розподілі пам'яті між двома архітектурами, використовую утиліту size:<br>
```
size pr2_1_64 pr2_1_32
```
Результат<br>
```
text     data      bss      dec      hex  filename
2130      632        8     2770      ad2  pr2_1_64
1924      320        4     2248      8c8  pr2_1_32
```
Для детальної перевірки заголовків ELF-файлів використовую:<br>
```
readelf -h pr2_1_64
```
для файлу з 64-бітною архітектурою.<br>
Результат<br>
```
ELF Header:
  Magic:   7f 45 4c 46 02 01 01 00 00 00 00 00 00 00 00 00 
  Class:                             ELF64
  Data:                              2's complement, little endian
  Version:                           1 (current)
  OS/ABI:                            UNIX - System V
  ABI Version:                       0
  Type:                              DYN (Position-Independent Executable file)
  Machine:                           Advanced Micro Devices X86-64
  Version:                           0x1
  Entry point address:               0x10e0
  Start of program headers:          64 (bytes into file)
  Start of section headers:          14152 (bytes into file)
  Flags:                             0x0
  Size of this header:               64 (bytes)
  Size of program headers:           56 (bytes)
  Number of program headers:         13
  Size of section headers:           64 (bytes)
  Number of section headers:         31
  Section header string table index: 30
```
Та для файлу з 32-бітною архітектурою використовую<br>
```
readelf -h pr2_1_32
```
Результат<br>
```
ELF Header:
  Magic:   7f 45 4c 46 01 01 01 00 00 00 00 00 00 00 00 00 
  Class:                             ELF32
  Data:                              2's complement, little endian
  Version:                           1 (current)
  OS/ABI:                            UNIX - System V
  ABI Version:                       0
  Type:                              DYN (Position-Independent Executable file)
  Machine:                           Intel 80386
  Version:                           0x1
  Entry point address:               0x10a0
  Start of program headers:          52 (bytes into file)
  Start of section headers:          13920 (bytes into file)
  Flags:                             0x0
  Size of this header:               52 (bytes)
  Size of program headers:           32 (bytes)
  Number of program headers:         11
  Size of section headers:           40 (bytes)
  Number of section headers:         29
  Section header string table index: 28
```
### Завдання 2<br>
Розгляньте сегменти у виконуваному файлі.<br>
1. Скомпілюйте програму &quot;hello world&quot;, запустіть ls -l для<br>
виконуваного файлу, щоб отримати його загальний розмір, і<br>
запустіть size, щоб отримати розміри сегментів всередині нього.<br>
2. Додайте оголошення глобального масиву із 1000 int,<br>
перекомпілюйте й повторіть вимірювання. Зверніть увагу на відмінності.<br>
3. Тепер додайте початкове значення в оголошення масиву<br>
(пам’ятайте, що C не змушує вас вказувати значення для кожного<br>
елемента масиву в ініціалізаторі). Це перемістить масив із сегмента<br>
BSS у сегмент даних. Повторіть вимірювання. Зверніть увагу на різницю.<br>
4. Тепер додайте оголошення великого масиву в локальну функцію.<br>
Оголосіть другий великий локальний масив з ініціалізатором.<br>
Повторіть вимірювання. Дані розташовуються всередині функцій,<br>
залишаючись у виконуваному файлі? Яка різниця, якщо масив<br>
ініціалізований чи ні?<br>
5. Які зміни відбуваються з розмірами файлів і сегментів, якщо ви<br>
компілюєте для налагодження? Для максимальної оптимізації?<br>
Проаналізуйте результати, щоб переконатися, що:<br>
● сегмент даних зберігається у виконуваному файлі;<br>
● сегмент BSS не зберігається у виконуваному файлі (за винятком<br>
**Компіляція та отримання загального розміру файлу і розмірів сегментів:**<br>
```
gcc hello_world.c -o hw
ls -l hw
size hw
```
Результат<br>
```
-rwxrwxr-x 1 morty morty 15968 лют 21 16:41 hw
text     data      bss      dec      hex  filename
1374      600        8     1982      7be  hw
```
**2. Додавання неініціалізованого глобального масиву (1000 int)**<br>
Перекомпіляція та вимірювання після додавання масиву до сегменту BSS:<br>
```
gcc hello_world.c -o hw
ls -l hw
size hw
```
Результат<br>
```
-rwxrwxr-x 1 morty morty 16008 лют 21 17:00 hw
text     data      bss      dec      hex  filename
1374      600     4032     6006     1776  hw
```
**3. Додавання початкового значення до глобального масиву**<br>
Переміщення масиву з сегмента BSS у сегмент даних (Data):<br>
```
gcc hello_world.c -o hw
ls -l hw
size hw
```
Результат<br>
```
-rwxrwxr-x 1 morty morty 20024 лют 21 17:03 hw
text     data      bss      dec      hex  filename
1374     4616        8     5998     176e  hw
```
**4. Оголошення великих локальних масивів всередині функції**<br>
Перевірка розташування локальних даних (ініціалізованих та неініціалізованих):<br>
```
gcc hello_world.c -o hw
ls -l hw
size hw
```
Результат<br>
```
-rwxrwxr-x 1 morty morty 16016 лют 21 17:26 hw
text     data      bss      dec      hex  filename
1594      608        8     2210      8a2  hw
```
**5. Компіляція для налагодження та максимальної оптимізації**<br>
```
gcc -g hello_world.c -o hw
ls -l hw
size hw
```
Результат<br>
```
-rwxrwxr-x 1 morty morty 21208 лют 21 17:30 hw
text     data      bss      dec      hex  filename
1374     4616        8     5998     176e  hw
```
Для максимальної оптимізації (прапорець -O3):<br>
```
gcc -O3 hello_world.c -o hw
ls -l hw
size hw
```
Результат<br>
```
-rwxrwxr-x 1 morty morty 20016 лют 21 17:32 hw
text     data      bss      dec      hex  filename
1374     4616        8     5998     176e  hw
```
### Завдання 3<br>
Скомпілюйте й запустіть тестову програму, щоб визначити приблизне розташування стека у вашій системі:<br>
``` c
#include stdio.h;
int main() {
int i;
printf("The stack top is near %p\n", &i);
return 0;
}
```
Знайдіть розташування сегментів даних і тексту, а також купи всередині<br>
сегмента даних, оголосіть змінні, які будуть поміщені в ці сегменти, і виведіть їхні адреси.<br>
Збільшіть розмір стека, викликавши функцію й оголосивши кілька<br>
великих локальних масивів. Яка зараз адреса вершини стека?<br>
Примітка: стек може розташовуватися за різними адресами на різних<br>
архітектурах та різних ОС. Хоча ми говоримо про вершину стека, на<br>
більшості процесорів стек зростає вниз, до пам’яті з меншими значеннями адрес.<br>
Результат<br>
```
--- Memory Layout Addresses ---
Text segment (code) is near  0x638c0302923f
Data segment (initialized) is near  0x638c0302c010
BSS segment (uninitialized) is near 0x638c0302c018
Heap (dynamic data) is near  0x638c1bdbc2a0
The stack top in main is near      0x7ffc8d7d460c
The stack top inside grow_stack is near 0x7ffc8d7ca99c
```
### Завдання 4<br>
Ваше завдання – дослідити стек процесу або пригадати, як це робиться. Ви можете:<br>
● Автоматично за допомогою утиліти gstack.<br>
● Вручну за допомогою налагоджувача GDB.<br>
Користувачі Ubuntu можуть зіткнутися з проблемою: на момент написання<br>
(Ubuntu 18.04) gstack, схоже, не був доступний (альтернативою може бути<br>
pstack). Якщо gstack не працює, використовуйте другий метод – через GDB, як показано нижче.<br>
Спочатку подивіться на стек за допомогою gstack(1). Нижче наведений<br>
приклад стека bash (аргументом команди є PID процесу):<br>
```
$ gstack 14654
#0 0x00007f359ec7ee7a in waitpid () from /lib64/libc.so.6
#1 0x000056474b4b41d9 in waitchild.isra ()
#2 0x000056474b4b595d in wait_for ()
#3 0x000056474b4a5033 in execute_command_internal ()
#4 0x000056474b4a5c22 in execute_command ()
#5 0x000056474b48f252 in reader_loop ()
#6 0x000056474b48dd32 in main ()
$
```
Розбір стека:<br>
● Номер кадру стека відображається ліворуч перед символом #.<br>
● Кадр #0 – це найнижчий кадр. Читайте стек знизу вверх (тобто від<br>
main() – кадр #6 – до waitpid() – кадр #0).<br>
● Якщо процес багатопотоковий, gstack покаже стек кожного потоку окремо.<br>
Аналіз стека в режимі користувача через GDB<br>
Щоб переглянути стек процесу вручну, використовуйте GDB, приєднавшись до процесу.<br>
Нижче наведена невелика тестова програма на C, що виконує кілька<br>
вкладених викликів функцій. Граф викликів виглядає так:<br>
```
main() --&gt; foo() --&gt; bar() --&gt; bar_is_now_closed() --&gt; pause()
```
Системний виклик pause() – це приклад блокуючого виклику. Він<br>
переводить викликаючий процес у сплячий режим, очікуючи (або<br>
блокуючи) сигнал. У цьому випадку процес блокується, поки не отримає будь-який сигнал.<br>
```
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>

#define MSG "In function %20s; &localvar = %p\n"

static void bar_is_now_closed(void) {
    int localvar = 5;
    printf(MSG, __FUNCTION__, &localvar);
    printf("\n Now blocking on pause()...\n");

    pause();
}

static void bar(void) {
    int localvar = 5;
    printf(MSG, __FUNCTION__, &localvar);
    bar_is_now_closed();
}
static void foo(void) {
    int localvar = 5;
    printf(MSG, __FUNCTION__, &localvar);
    bar();
}

int main(int argc, char **argv) {
    int localvar = 5;
    printf(MSG, __FUNCTION__, &localvar);
    foo();
    exit(EXIT_SUCCESS);
}
```
Тепер відкрийте GDB<br>
У ньому підключіться (attach) до процесу (в наведеному прикладі PID =<br>
24957) і дослідіть стек за допомогою команди backtrace (bt):<br>
```
$ gdb --quiet
(gdb) attach 24957
Attaching to process 24957
Reading symbols from &lt;...&gt;/hspl/unit2/stacker...done.
Reading symbols from /lib64/libc.so.6...Reading symbols from
/usr/lib/debug/usr/lib64/libc-2.26.so.debug...done.
done.
Reading symbols from /lib64/ld-linux-x86-64.so.2...Reading symbols
...
(gdb) bt
...
```
Примітка: В Ubuntu, через питання безпеки, GDB не дозволяє<br>
підключатися до довільного процесу. Це можна обійти, запустивши GDB<br>
від імені користувача root.<br>
Аналіз того ж процесу через gstack<br>
$ gstack 24957<br>
...<br>
gstack — це, по суті, оболонковий скрипт (wrapper shell script), який<br>
неінтерактивно викликає GDB і запускає команду backtrace, яку ви щойно використали.<br>
Завдання: Ознайомтеся з виводом gstack і порівняйте його з GDB.<br>
