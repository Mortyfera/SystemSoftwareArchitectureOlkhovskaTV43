**Приклад 1**  
Crash handler із SA\_SIGINFO і register dump  
**Компіляція програми**  
gcc \-Wall \-Wextra \-O0 \-g \-fno-omit-frame-pointer \-no-pie crash\_diag.c \-o crash\_diag  
**Запуск програми**  
./crash\_diag  
**Пошук рядка за RIP:**  
addr2line \-e ./crash\_diag \-f \-C 0x40171f  
**Результат роботи програми**  
About to crash. PID=62301

\=== crash captured \===  
signal: 11  
si\_code: 1  
fault address: 0x0  
RIP: 0x401818  
RSP: 0x7ffe98b497c0  
RBP: 0x7ffe98b497c0  
RAX: 0x0  
RBX: 0x7ffe98b498f8  
RCX: 0x7da8ff71c5a4  
RDX: 0x1  
RSI: 0x402035  
RDI: 0x2  
**Результат пошука рядка за RIP**  
install\_crash\_handlers  
/home/morty/Documents/АСПз/SystemSoftwareArchitectureOlkhovskaTV43/pr10/crash\_diag.c:115  
**Пояснення**  
Програма реалізує обробник критичних сигналів, використовуючи SA\_SIGINFO для доступу до контексту виконання. За допомогою безпечних функцій код виводить значення регістрів та адресу відмови під час крашу. Отриманий дамп у поєднанні з утилітою addr2line дозволяє точно визначити рядок коду, де стався збій.  
**Приклад 2**  
Correct sleeping: nanosleep() restart loop і clock\_nanosleep() absolute deadline  
**Компіляція програми**  
gcc \-Wall \-Wextra \-O2 sleep\_correct.c \-o sleep\_correct  
**Запуск програми**  
./sleep\_correct  
**В іншому терміналі:**  
kill \-USR1 \<pid\>  
**Результат роботи програми**  
PID=63476. In another terminal: kill \-USR1 63476  
Relative sleep for 5 seconds using nanosleep restart loop...  
Relative sleep finished. got\_usr1=0  
Now 5 periodic ticks with absolute clock\_nanosleep deadlines...  
tick 1  
tick 2  
tick 3  
tick 4  
tick 5  
**Пояснення**  
Програма демонструє методи високоточного затримання часу в Linux. Реалізовано обробку переривань для nanosleep, що гарантує повне відпрацювання інтервалу. Використання clock\_nanosleep із прапорцем TIMER\_ABSTIME дозволяє уникнути накопичення похибок, оскільки кожен наступний момент пробудження прив’язаний до абсолютної шкали. Це забезпечує ідеальну періодичність, необхідну для систем реального часу.  
**Приклад 3**  
Малий publisher-subscriber на real-time signals, sigqueue(), sigwaitinfo() і sigtimedwait()  
**Компіляція програми**  
gcc \-Wall \-Wextra \-O2 rt\_pubsub.c \-o rt\_pubsub  
**В іншому терміналі:**  
./rt\_pubsub pub \<PID\_SUBSCRIBER\> 10 20 30 \-1  
**Варіант із timeout:**  
./rt\_pubsub sub-timeout  
**Результат роботи програми**  
./rt\_pubsub pub 63853 10 20 30 \-1  
sent value=10 to pid=63853 via signal=34  
sent value=20 to pid=63853 via signal=34  
sent value=30 to pid=63853 via signal=34  
sent value=-1 to pid=63853 via signal=34

./rt\_pubsub sub-timeout  
subscriber PID=63853, waiting for signal 34 (SIGRTMIN)  
timeout: no messages for 5 seconds  
timeout: no messages for 5 seconds  
timeout: no messages for 5 seconds  
timeout: no messages for 5 seconds  
timeout: no messages for 5 seconds  
timeout: no messages for 5 seconds  
timeout: no messages for 5 seconds  
timeout: no messages for 5 seconds  
received signal=34 value=10 from pid=64126 uid=1000  
received signal=34 value=20 from pid=64126 uid=1000  
received signal=34 value=30 from pid=64126 uid=1000  
received signal=34 value=-1 from pid=64126 uid=1000  
negative value received: shutting down subscriber  
**Пояснення**  
Програма реалізує модель Publisher-Subscriber, використовуючи сигнали реального часу. Завдяки sigqueue() повідомлення передаються разом із даними, а передплатник синхронно зчитує їх через sigwaitinfo(). Такий підхід гарантує черговість доставки без втрат під навантаженням. Тести також підтвердили коректну роботу тайм-аутів у sigtimedwait() при відсутності нових подій протягом 5 секунд.  
**Задача за варіантом \- варіант 13**  
Розширте просту оболонку так, щоб вона дозволяла вводити команду з аргументами, розділеними пробілами, і запускати їх у дочірньому процесі.  
**Компіляція програми**  
gcc \-Wall pr1013.c \-o pr1013  
**Запуск програми**  
./pr1013  
**Результат роботи програми**  
myshell\> ls  
pr1013  pr1013.c  
myshell\> ls \-l  
total 24  
\-rwxrwxr-x 1 morty morty 16528 тра  4 18:16 pr1013  
\-rw-rw-r-- 1 morty morty  1067 тра  4 18:14 pr1013.c  
myshell\> pwd  
/home/morty/Documents/АСПз/SystemSoftwareArchitectureOlkhovskaTV43/pr10  
myshell\> exit  
**Пояснення**  
Програма реалізує власну командну оболонку. Вона використовує strtok для розбору введеного рядка на аргументи та execvp для запуску системних утиліт через змінну PATH. Батьківський процес керує дочірніми за допомогою waitpid, що гарантує послідовне виконання команд і стабільну роботу інтерфейсу myshell\>.