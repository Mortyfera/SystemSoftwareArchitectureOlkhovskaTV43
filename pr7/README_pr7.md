**Задача 1**  
Використайте popen(), щоб передати вивід команди rwho (команда UNIX) до more (команда UNIX) у програмі на C.  
**Компіляція програми**  
gcc \-Wall pr71.c \-o pr71  
**Запуск програми**  
sudo ./pr71  
**Результат роботи програми**  
morty    puter:pts/19 May  2 20:13  
**Пояснення**  
Програма працює як конвеєр rwho | more у Linux. Вона використовує popen() для зв'язку двох процесів: бере дані про користувачів з rwho і перенаправляє їх у more для зручного посторінкового перегляду. В кінці канали безпечно закриваються через pclose().

**Задача 2**  
Напишіть програму мовою C, яка імітує команду ls \-l в UNIX — виводить список усіх файлів у поточному каталозі та перелічує права доступу тощо.  
(Варіант вирішення, що просто виконує ls \-l із вашої програми, — не підходить.)  
**Компіляція програми**  
gcc \-Wall pr72.c \-o pr72  
**Запуск програми**  
./pr72  
**Результат роботи програми**  
drwxrwxr-x 10 morty morty  4096 Apr 10 16:28 ..  
\-rwxrwxr-x 1 morty morty 16496 May 02 20:27 pr72  
\-rwxrwxr-x 1 morty morty 16224 May 02 20:12 pr71  
drwxrwxr-x 2 morty morty  4096 May 02 20:27 .  
\-rw-rw-r-- 1 morty morty   586 May 02 20:01 pr73.c  
\-rw-rw-r-- 1 morty morty   707 Apr 13 19:04 pr71.c  
\-rw-rw-r-- 1 morty morty  1733 May 02 20:24 pr72.c  
**Пояснення**  
Програма працює точно як команда ls \-l у Linux, але робить усе з нуля. Вона відкриває поточну папку, перевіряє кожен файл і через функцію stat() дістає всю системну інформацію про нього. Потім переводить машинні дані у зрозумілий для людини текст та акуратно виводить це на екран.  
**Задача 3**  
Напишіть програму, яка друкує рядки з файлу, що містять слово, передане як аргумент програми (проста версія утиліти grep в UNIX).  
**Компіляція програми**  
gcc \-Wall pr73.c \-o pr73  
**Запуск програми**  
./pr73 hello text.txt  
**Результат роботи програми**  
hello dear reader  
hello dear writer  
hello world  
**Вміст файлу text.txt**  
hello dear reader  
hello dear writer  
hello world  
world  
**Пояснення**  
Програма працює як базова команда grep у Linux. Вона просто відкриває вказаний текст, переглядає його рядок за рядком і шукає потрібне слово. Щойно знаходить збіг – показує цей рядок на екрані. Наприкінці програма коректно закриває файл, щоб не тримати ресурси системи зайнятими.  
**Задача 4**  
Напишіть програму, яка виводить список файлів, заданих у вигляді аргументів, з зупинкою кожні 20 рядків, доки не буде натиснута клавіша (спрощена версія утиліти more в UNIX).  
**Компіляція програми**  
gcc \-Wall pr74.c \-o pr74  
**Запуск програми**  
./pr74 file1.txt file2.txt  
**Результат роботи програми**  
Casa de Jackson  
No gold-plated throne for guests  
Seriously, dude?  
ANOTHER THING I have never understood: How can you mortals live in such  
tiny places? Where is your pride? Your sense of style?  
The Jackson apartment had no grand throne room, no colonnades, no terraces  
or banquet halls or even a thermal bath. It had a tiny living room with an  
attached kitchen and a single hallway leading to what I assumed were the  
bedrooms. The place was on the fifth floor, and while I wasn’t so picky as to  
expect an elevator, I did find it odd there was no landing deck for flying chariots.  
What did they do when guests from the sky wanted to visit?  
Standing behind the kitchen counter, making a smoothie, was a strikingly  
attractive mortal woman of about forty. Her long brown hair had a few gray  
streaks, but her bright eyes, quick smile, and festive tie-dyed sundress made her  
look younger.  
As we entered, she turned off the blender and stepped out from behind the  
counter.  
“Sacred Sibyl\!” I cried. “Madam, there is something wrong with your  
midsection\!”  
The woman stopped, mystified, and looked down at her hugely swollen

\--More-- (Press any key, q to quit)  
belly. “Well, I’m seven months pregnant.”  
I wanted to cry for her. Carrying such a weight didn’t seem natural. My  
sister, Artemis, had experience with midwifery, but I had always found it one  
area of the healing arts best left to others. “How can you bear it?” I asked. “My  
mother, Leto, suffered through a long pregnancy, but only because Hera cursed  
her. Are you cursed?”  
Percy stepped to my side. “Um, Apollo? She’s not cursed. And can you notTag with plague spirits  
You’re it, and you’re infectious  
Have fun with that, LOL  
“NOSOI?” PERCY PLANTED HIS FEET in a fighting stance. “You know, I  
keep thinking, I have now killed every single thing in Greek mythology. But the  
list never seems to end.”  
“You haven’t killed me yet,” I noted.  
“Don’t tempt me.”  
The three nosoi shuffled forward. Their cadaverous mouths gaped. Their  
tongues lolled. Their eyes glistened with a film of yellow mucus.  
“These creatures are not myths,” I said. “Of course, most things in those old  
myths are not myths. Except for that story about how I flayed the satyr Marsyas  
alive. That was a total lie.”  
Percy glanced at me. “You did what?”  
“Guys.” Meg picked up a dead tree branch. “Could we talk about that later?”  
The middle plague spirit spoke. “Apollooooo...” His voice gurgled like a  
seal with bronchitis. “We have coooome to—”  
“Let me stop you right there.” I crossed my arms and feigned arrogant  
indifference. (Difficult for me, but I managed.) “You’ve come to take your  
revenge on me, eh?” I looked at my demigod friends. “You see, nosoi are the

\--More-- (Press any key, q to quit)  
spirits of disease. Once I was born, spreading illnesses became part of my job. I  
use plague arrows to strike down naughty populations with smallpox, athlete’s  
foot, that sort of thing.”  
“Gross,” Meg said.  
“Somebody’s got to do it\!” I said. “Better a god, regulated by the Council of  
Olympus and with the proper health permits, than a horde of uncontrolled spirits  
**Вміст файлу file1.txt**  
Casa de Jackson  
No gold-plated throne for guests  
Seriously, dude?  
ANOTHER THING I have never understood: How can you mortals live in such  
tiny places? Where is your pride? Your sense of style?  
The Jackson apartment had no grand throne room, no colonnades, no terraces  
or banquet halls or even a thermal bath. It had a tiny living room with an  
attached kitchen and a single hallway leading to what I assumed were the  
bedrooms. The place was on the fifth floor, and while I wasn’t so picky as to  
expect an elevator, I did find it odd there was no landing deck for flying chariots.  
What did they do when guests from the sky wanted to visit?  
Standing behind the kitchen counter, making a smoothie, was a strikingly  
attractive mortal woman of about forty. Her long brown hair had a few gray  
streaks, but her bright eyes, quick smile, and festive tie-dyed sundress made her  
look younger.  
As we entered, she turned off the blender and stepped out from behind the  
counter.  
“Sacred Sibyl\!” I cried. “Madam, there is something wrong with your  
midsection\!”  
The woman stopped, mystified, and looked down at her hugely swollen  
belly. “Well, I’m seven months pregnant.”  
I wanted to cry for her. Carrying such a weight didn’t seem natural. My  
sister, Artemis, had experience with midwifery, but I had always found it one  
area of the healing arts best left to others. “How can you bear it?” I asked. “My  
mother, Leto, suffered through a long pregnancy, but only because Hera cursed  
her. Are you cursed?”  
Percy stepped to my side. “Um, Apollo? She’s not cursed. And can you not  
**Вміст файлу file2.txt**  
Tag with plague spirits  
You’re it, and you’re infectious  
Have fun with that, LOL  
“NOSOI?” PERCY PLANTED HIS FEET in a fighting stance. “You know, I  
keep thinking, I have now killed every single thing in Greek mythology. But the  
list never seems to end.”  
“You haven’t killed me yet,” I noted.  
“Don’t tempt me.”  
The three nosoi shuffled forward. Their cadaverous mouths gaped. Their  
tongues lolled. Their eyes glistened with a film of yellow mucus.  
“These creatures are not myths,” I said. “Of course, most things in those old  
myths are not myths. Except for that story about how I flayed the satyr Marsyas  
alive. That was a total lie.”  
Percy glanced at me. “You did what?”  
“Guys.” Meg picked up a dead tree branch. “Could we talk about that later?”  
The middle plague spirit spoke. “Apollooooo...” His voice gurgled like a  
seal with bronchitis. “We have coooome to—”  
“Let me stop you right there.” I crossed my arms and feigned arrogant  
indifference. (Difficult for me, but I managed.) “You’ve come to take your  
revenge on me, eh?” I looked at my demigod friends. “You see, nosoi are the  
spirits of disease. Once I was born, spreading illnesses became part of my job. I  
use plague arrows to strike down naughty populations with smallpox, athlete’s  
foot, that sort of thing.”  
“Gross,” Meg said.  
“Somebody’s got to do it\!” I said. “Better a god, regulated by the Council of  
Olympus and with the proper health permits, than a horde of uncontrolled spirits  
like these.”  
**Пояснення**  
Це власна реалізація команди more. Програма відкриває файл і виводить його на екран по 20 рядків, роблячи паузу. Головна фішка – використання бібліотеки \<termios.h\>, завдяки якій програма ловить натискання клавіш миттєво, без необхідності щоразу тиснути Enter. Вона може відкривати відразу кілька файлів один за одним і акуратно звільняє всі ресурси після завершення роботи.  
**Задача 5**  
Напишіть програму, яка перелічує всі файли в поточному каталозі та всі файли в підкаталогах.  
**Компіляція програми**  
gcc \-Wall pr75.c \-o pr75  
**Запуск програми**  
./pr75  
**Результат роботи програми**  
./text.txt  
./file2.txt  
./pr73  
./pr75  
./pr72  
./pr71  
./file1.txt  
./pr74  
./pr73.c  
./pr71.c  
./pr72.c  
./pr75.c  
./pr74.c  
**Пояснення**  
Програма виконує рекурсивний обхід файлової системи, використовуючи opendir, readdir та lstat. Вона послідовно зчитує вміст каталогів, ігнорує системні посилання . і .. та автоматично заглиблюється в підкаталоги, виводячи повні шляхи до всіх знайдених об'єктів.  
**Задача 6**  
Напишіть програму, яка перелічує лише підкаталоги у алфавітному порядку.  
**Компіляція програми**  
gcc \-Wall pr76.c \-o pr76  
**Запуск програми**  
./pr76  
**Результат роботи програми**  
test\_folder  
**Пояснення**  
Цей код вибирає лише папки серед усього вмісту поточної директорії. Програма перевіряє тип кожного об’єкта, і якщо це каталог, додає його назву до списку. Потім цей список сортується за алфавітом і виводиться на екран, а вся використана оперативна пам'ять коректно очищається.  
**Задача 7**  
Напишіть програму, яка показує користувачу всі його/її вихідні програми на C, а потім в інтерактивному режимі запитує, чи потрібно надати іншим дозвіл на читання (read permission); у разі ствердної відповіді — такий дозвіл повинен бути наданий.  
**Компіляція програми**  
gcc \-Wall pr77.c \-o pr77  
**Запуск програми**  
./pr77  
**Результат роботи програми**  
C source files:

File: pr77.c  
Allow others to read this file? (y/n): y  
Read permission for others added.

File: pr73.c  
Allow others to read this file? (y/n): y  
Read permission for others added.

File: pr71.c  
Allow others to read this file? (y/n): y  
Read permission for others added.

File: pr76.c  
Allow others to read this file? (y/n): y  
Read permission for others added.

File: pr72.c  
Allow others to read this file? (y/n): y  
Read permission for others added.

File: pr75.c  
Allow others to read this file? (y/n): y  
Read permission for others added.

File: pr74.c  
Allow others to read this file? (y/n): y  
Read permission for others added.  
**Пояснення**  
Програма автоматично знаходить усі .c файли в поточній директорії, використовуючи opendir, readdir та stat. Для кожного знайденого файлу запускається інтерактивний цикл: програма запитує дозвіл користувача на зміну прав. У разі згоди, функція chmod додає право на читання іншим користувачам за допомогою побітового АБО.  
**Задача 8**  
Напишіть програму, яка надає користувачу можливість видалити будь-який або всі файли у поточному робочому каталозі. Має з’являтися ім’я файлу з запитом, чи слід його видалити.  
**Компіляція програми**  
gcc \-Wall pr78.c \-o pr78  
**Запуск програми**  
./pr78  
**Результат роботи програми**  
Delete file 'pr76'? (y/n/a/q): n  
Delete file 'text.txt'? (y/n/a/q): n  
Delete file 'file2.txt'? (y/n/a/q): n  
Delete file 'pr73'? (y/n/a/q): n  
Delete file 'pr78'? (y/n/a/q): n  
Delete file 'pr77'? (y/n/a/q): n  
Delete file 'pr75'? (y/n/a/q): q  
**Пояснення**  
Програма на C реалізує інтерактивне видалення файлів у поточній директорії. За допомогою opendir, readdir та stat вона знаходить лише звичайні файли, ігноруючи папки. Для кожного об'єкта користувач обирає дію через меню, а саме видалення виконується функцією remove(). Тестування підтвердило коректну обробку команд та безпечне завершення програми.  
**Задача 9**  
Напишіть програму на C, яка вимірює час виконання фрагмента коду в мілісекундах.  
**Компіляція програми**  
gcc \-Wall pr79.c \-o pr79  
**Запуск програми**  
./pr79  
**Результат роботи програми**  
Execution time: 31.337 ms  
**Пояснення**  
Цей код заміряє, скільки часу займає виконання 100 мільйонів кроків у циклі. Щоб вимірювання було точним, використано монотонний системний таймер, який не залежить від коригування часу в системі. Завдяки ключовому слову volatile компілятор не ігнорує порожню роботу, тому ми бачимо реальну швидкість заліза – приблизно 31 мс.  
**Задача 10**  
Напишіть програму мовою C для створення послідовності випадкових чисел з плаваючою комою у діапазонах:  
 (a) від 0.0 до 1.0  
 (b) від 0.0 до n, де n — будь-яке дійсне число з плаваючою точкою.  
 Початкове значення генератора випадкових чисел має бути встановлене так, щоб гарантувати унікальну послідовність.  
Примітка: використання прапорця \-Wall під час компіляції є обов’язковим.  
**Компіляція програми**  
gcc \-Wall pr710.c \-o pr710  
**Запуск програми**  
./pr710  
**Результат роботи програми**  
Enter number of random values: 10  
Enter n (upper bound for range \[0, n\]): 75

Random numbers in range \[0.0, 1.0\]:  
0.023326  
0.574939  
0.595559  
0.361140  
0.915277  
0.659520  
0.027211  
0.499687  
0.547704  
0.541133

Random numbers in range \[0.0, 75.00\]:  
61.956680  
12.129438  
39.051426  
72.194000  
10.659263  
51.543461  
42.707241  
14.463127  
21.926363  
47.967865  
**Пояснення**  
Цей код створює випадкові дробові числа. Спочатку програма отримує значення від 0 до 1, ділячи результат стандартної функції rand() на її максимально можливе значення. Щоб розширити цей діапазон до заданого користувачем числа n, програма просто множить отриманий дріб на n. Завдяки прив'язці до системного часу, числа при кожному запуску будуть новими.  
**Задача за варіантом \- варіант 13**  
Напишіть утиліту, яка визначає "аномальні" виконувані файли в системі.  
**Компіляція програми**  
gcc \-Wall pr713.c \-o pr713  
**Запуск програми**  
./pr713  
**Результат роботи програми**  
Scanning: .  
**Пояснення**  
Програма – системний сканер для виявлення підозрілих виконуваних файлів. Вона рекурсивно обходить директорії та аналізує два критерії: права доступу та сигнатури файлів. Утиліта зчитує перші байти, щоб підтвердити формат ELF, що дозволяє виявляти аномальні об'єкти в системі.