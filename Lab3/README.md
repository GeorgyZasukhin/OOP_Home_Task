# Лабораторна робота №3 — варіант 9

Конструктори, деструктор, час життя об’єктів.
Предметна область: насіннєвий фонд господарства.
Автор: Засухін Георгій, група 51-271.

## Збирання та тести

```sh
cd "/Users/egor/SmartGit/OOP_Home_Task/Lab3"
cmake -S . -B build-sanitized -DENABLE_SANITIZERS=ON
cmake --build build-sanitized
ctest --test-dir build-sanitized --output-on-failure
./build-sanitized/Lab3
./build-sanitized/lifetime_demo 2> lifetime.log
cat lifetime.log
```

Очікувано: 16/16 тестів; у кінці lifetime.log — live=0.
Журнал ctor/dtor йде в std::clog, звичайний вивід main — у std::cout.

## Файли

- `src/seed_variety.*` — сорт: назва, культура, урожайність, рік районування.
- `src/agronomist.*` — агроном: ім’я, спеціалізація, номер, стаж.
- `src/lifetime_log.*` — спільний лічильник і безпечний журнал.
- `src/main.cpp` — приклад предметної області.
- `experiments/lifetime_demo.cpp` — демонстрація способів створення.
- `tests/constructor_test.cpp` — власні тести на doctest.
- `third_party/doctest.h` — готова стороння бібліотека, не власний код.
- `docs/` — передбачення, фактичні журнали, діагностика та результати тестів.
- `Lab3_Zasukhin_Georgy_V9.docx` — звіт у стилі першої роботи.

## Окремі навчальні досліди

Звичайний lifetime_demo не має витоку. Прапорець --leak спеціально
відтворює попередній помилковий стан; це не команда для звичайної перевірки:

```sh
./build-sanitized/lifetime_demo --leak 2> lifetime-before.log
clang++ -std=c++17 -Wall -Wextra -Wreorder -Isrc -c \
  experiments/reorder_warning.cpp -o /tmp/lab3-reorder.o
clang++ -std=c++17 -Isrc -c experiments/implicit_conversion.cpp \
  -o /tmp/lab3-implicit.o
```

Перша компіляція навмисно дає попередження, друга — помилку explicit.
Вони не входять до звичайного збирання.
Apple ASan на перевіреному Mac не підтримує detect_leaks=1.
Тому витік перевірено в Linux aarch64, GCC 14, ASan+UBSan+LSan;
фактичні журнали: docs/lsan-before.log і docs/lsan-after.log.
Відтворення за наявності Docker

```sh
docker run --rm -v "$PWD:/project:ro" gcc:14 bash -c '
  g++ -std=c++17 -g -O0 -fsanitize=address,undefined \
    -fno-omit-frame-pointer -I/project/src \
    /project/src/seed_variety.cpp /project/src/agronomist.cpp \
    /project/src/lifetime_log.cpp \
    /project/experiments/lifetime_demo.cpp -o /tmp/lifetime
  ASAN_OPTIONS=detect_leaks=1 /tmp/lifetime --leak
  ASAN_OPTIONS=detect_leaks=1 /tmp/lifetime
'
```

До виправлення: exit=1, один витік 80 байтів, live=1.
Після: exit=0, повідомлень санітайзерів немає, live=0.

