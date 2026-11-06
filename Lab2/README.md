# Лабораторна робота 2

Варіант 9 — квитковий облік театру. Клас `Performance` описує виставу.



## Збирання і тести

Потрібні CMake 3.20+ та компілятор C++17.
У Terminal перейдіть у каталог із цим README:

```bash
cmake -S . -B build-sanitized -DENABLE_SANITIZERS=ON -DCMAKE_BUILD_TYPE=Debug
cmake --build build-sanitized
ctest --test-dir build-sanitized --output-on-failure
./build-sanitized/Lab2
```


## Файли

- `Lab2/performance.h` — інтерфейс та інваріант.
- `Lab2/performance.cpp` — реалізація перевірок та операцій.
- `Lab2/main.cpp` — приклад роботи з виставою.
- `tests/performance_test.cpp` — 15 тестів doctest.
- `docs/lab02_design.md` — операції, поля та проєктні рішення.
- `Lab2_Zasukhin_Georgy_V9.docx` — звіт.

Окремої гілки та коміту цієї роботи ще немає. Перед здаванням потрібно
зафіксувати перевірені зміни у власному репозиторії, додати фактичний хеш
до звіту та опублікувати гілку. У репозиторії вже були підготовлені зміни
Lab2–Lab4; автоматично включати їх в один коміт не слід.
