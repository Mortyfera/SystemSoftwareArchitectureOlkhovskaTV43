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
Результат:<br>
```
morty@puter:~/Documents/АСПз/SystemSoftwareArchitectureOlkhovskaTV43/pr2$ ./pr2_3 &
[2] 21911
morty@puter:~/Documents/АСПз/SystemSoftwareArchitectureOlkhovskaTV43/pr2$ In function                 main; &localvar = 0x7ffd6c4cf4b4
In function                  foo; &localvar = 0x7ffd6c4cf484
In function                  bar; &localvar = 0x7ffd6c4cf464
In function    bar_is_now_closed; &localvar = 0x7ffd6c4cf444

 Now blocking on pause()...
sudo gdb --quiet
(gdb) attach 21911
Attaching to process 21911
Reading symbols from /home/morty/Documents/АСПз/SystemSoftwareArchitectureOlkhovskaTV43/pr2/pr2_3...
Reading symbols from /lib/x86_64-linux-gnu/libc.so.6...
Reading symbols from /usr/lib/debug/.build-id/8e/9fd827446c24067541ac5390e6f527fb5947bb.debug...
Reading symbols from /lib64/ld-linux-x86-64.so.2...
Reading symbols from /usr/lib/debug/.build-id/da/07864eb4c1b06504b8688d25d7e84759fe708d.debug...
[Thread debugging using libthread_db enabled]
Using host libthread_db library "/lib/x86_64-linux-gnu/libthread_db.so.1".
0x000076b433cfa3d4 in __libc_pause () at ../sysdeps/unix/sysv/linux/pause.c:29
warning: 29    ../sysdeps/unix/sysv/linux/pause.c: No such file or directory
(gdb) bt
#0  0x000076b433cfa3d4 in __libc_pause () at ../sysdeps/unix/sysv/linux/pause.c:29
#1  0x00005a3fc0016224 in bar_is_now_closed () at pr2_3.c:13
#2  0x00005a3fc0016287 in bar () at pr2_3.c:19
#3  0x00005a3fc00162ea in foo () at pr2_3.c:24
#4  0x00005a3fc0016354 in main (argc=1, argv=0x7ffd6c4cf5e8) at pr2_3.c:30
(gdb) detach
Detaching from program: /home/morty/Documents/АСПз/SystemSoftwareArchitectureOlkhovskaTV43/pr2/pr2_3, process 21911
[Inferior 1 (process 21911) detached]
(gdb) quit
```
### Завдання 5<br>
Відомо, що при виклику процедур і поверненні з них процесор використовує стек.<br>
Чи можна в такій схемі обійтися без лічильника команд (IP), використовуючи замість нього вершину стека?<br>
Обґрунтуйте свою відповідь та наведіть приклади.<br>
Рішення<br>
Повністю відмовитися від лічильника команд (IP) і використовувати лише вершину стека практично неможливо.<br>
Головне завдання IP — автоматично та швидко вказувати на адресу наступної команди в пам'яті для забезпечення послідовного виконання коду.<br>
Стек за своєю природою створений для тимчасового зберігання даних і адрес повернення з підпрограм.<br>
Якби вершина стека постійно працювала як лічильник команд, кожна базова інструкція вимагала б безперервного запису<br>
та зчитування адреси наступної команди зі стека. Це змішало б робочі дані з потоком керування та катастрофічно сповільнило<br>
б роботу процесора, оскільки звернення до оперативної пам'яті (де знаходиться стек) набагато повільніше за оновлення апаратного регістра всередині процесора.<br>
Навіть під час повернення з процедури, коли система дійсно використовує стек для навігації, вона не працює безпосередньо з нього.<br>
Процесор бере збережену адресу з вершини стека і записує її саме в регістр IP, щоб відновити нормальний робочий цикл.<br>
Тому для ефективної архітектури ці два інструменти суворо розділяють: IP керує послідовністю дій, а стек обслуговує дані та контекст викликів.<br>
### Завдання 13<br> 
Дослідіть вплив оптимізації -Os на розмір сегментів.<br>
Рішення:
Компілюю код з прапорцем -O0 та -Os та порівнюю розмір структур файлів за допомогою утиліти size<br>
```
morty@puter:~/Documents/АСПз/SystemSoftwareArchitectureOlkhovskaTV43/pr2$ gcc -O0 pr2_13.c -o pr2_13
morty@puter:~/Documents/АСПз/SystemSoftwareArchitectureOlkhovskaTV43/pr2$ gcc -Os pr2_13.c -o pr2_13_opt
morty@puter:~/Documents/АСПз/SystemSoftwareArchitectureOlkhovskaTV43/pr2$ size pr2_13 pr2_13_opt
   text     data      bss      dec      hex  filename
   1537      604     4032     6173     181d  pr2_13
   1477      604     4032     6113     17e1  pr2_13_opt
```
За допомогою утиліти objdump та прапорця -d дизасемблюю код та порівнюю готові файли, щоб подивитись як саме був код скорочений за допомогою прапорця -Os<br>
```
morty@puter:~/Documents/АСПз/SystemSoftwareArchitectureOlkhovskaTV43/pr2$ objdump -d pr2_13 > pr2_13.asm
morty@puter:~/Documents/АСПз/SystemSoftwareArchitectureOlkhovskaTV43/pr2$ objdump -d pr2_13_opt > pr2_13_opt.asm
```
Функція function в не оптимізованому коді:<br>
```
0000000000001149 <function>:
    1149:	f3 0f 1e fa          	endbr64
    114d:	55                   	push   %rbp
    114e:	48 89 e5             	mov    %rsp,%rbp
    1151:	48 83 ec 10          	sub    $0x10,%rsp
    1155:	c7 45 f8 00 00 00 00 	movl   $0x0,-0x8(%rbp)
    115c:	c7 45 fc 00 00 00 00 	movl   $0x0,-0x4(%rbp)
    1163:	eb 40                	jmp    11a5 <function+0x5c>
    1165:	8b 05 a5 2e 00 00    	mov    0x2ea5(%rip),%eax        # 4010 <initialized_variable>
    116b:	0f af 45 fc          	imul   -0x4(%rbp),%eax
    116f:	8b 55 fc             	mov    -0x4(%rbp),%edx
    1172:	48 63 d2             	movslq %edx,%rdx
    1175:	48 8d 0c 95 00 00 00 	lea    0x0(,%rdx,4),%rcx
    117c:	00 
    117d:	48 8d 15 bc 2e 00 00 	lea    0x2ebc(%rip),%rdx        # 4040 <uninitialized_array>
    1184:	89 04 11             	mov    %eax,(%rcx,%rdx,1)
    1187:	8b 45 fc             	mov    -0x4(%rbp),%eax
    118a:	48 98                	cltq
    118c:	48 8d 14 85 00 00 00 	lea    0x0(,%rax,4),%rdx
    1193:	00 
    1194:	48 8d 05 a5 2e 00 00 	lea    0x2ea5(%rip),%rax        # 4040 <uninitialized_array>
    119b:	8b 04 02             	mov    (%rdx,%rax,1),%eax
    119e:	01 45 f8             	add    %eax,-0x8(%rbp)
    11a1:	83 45 fc 01          	addl   $0x1,-0x4(%rbp)
    11a5:	81 7d fc e7 03 00 00 	cmpl   $0x3e7,-0x4(%rbp)
    11ac:	7e b7                	jle    1165 <function+0x1c>
    11ae:	8b 45 f8             	mov    -0x8(%rbp),%eax
    11b1:	89 c6                	mov    %eax,%esi
    11b3:	48 8d 05 4a 0e 00 00 	lea    0xe4a(%rip),%rax        # 2004 <_IO_stdin_used+0x4>
    11ba:	48 89 c7             	mov    %rax,%rdi
    11bd:	b8 00 00 00 00       	mov    $0x0,%eax
    11c2:	e8 89 fe ff ff       	call   1050 <printf@plt>
    11c7:	90                   	nop
    11c8:	c9                   	leave
    11c9:	c3                   	ret
```
Функція function в оптимізованому коді:<br>
```
0000000000001159 <function>:
    1159:	f3 0f 1e fa          	endbr64
    115d:	48 8d 05 dc 2e 00 00 	lea    0x2edc(%rip),%rax        # 4040 <uninitialized_array>
    1164:	8b 15 a6 2e 00 00    	mov    0x2ea6(%rip),%edx        # 4010 <initialized_variable>
    116a:	31 c9                	xor    %ecx,%ecx
    116c:	48 8d b0 a0 0f 00 00 	lea    0xfa0(%rax),%rsi
    1173:	89 08                	mov    %ecx,(%rax)
    1175:	48 83 c0 04          	add    $0x4,%rax
    1179:	01 d1                	add    %edx,%ecx
    117b:	48 39 f0             	cmp    %rsi,%rax
    117e:	75 f3                	jne    1173 <function+0x1a>
    1180:	69 d2 2c 9f 07 00    	imul   $0x79f2c,%edx,%edx
    1186:	48 8d 35 77 0e 00 00 	lea    0xe77(%rip),%rsi        # 2004 <_IO_stdin_used+0x4>
    118d:	bf 02 00 00 00       	mov    $0x2,%edi
    1192:	31 c0                	xor    %eax,%eax
    1194:	e9 b7 fe ff ff       	jmp    1050 <__printf_chk@plt>
    ```
