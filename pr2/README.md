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
примітки щодо його вимог до розміру часу виконання);<br>
● текстовий сегмент більшою мірою піддається перевіркам оптимізації;<br>
● на розмір файлу a.out впливає компіляція для налагодження, але не сегменти.<br>
