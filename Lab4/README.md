# Лабораторна робота №4

Варіант №9. Меню ресторану, у якому страва зберігає список
інгредієнтів із вагою в грамах. C++17.

```sh
cd "/Users/egor/SmartGit/OOP_Home_Task/Lab4"
cmake -S . -B build-sanitized -DENABLE_SANITIZERS=ON -DBUILD_EXPERIMENTS=ON -DCMAKE_BUILD_TYPE=Debug
cmake --build build-sanitized
ctest --test-dir build-sanitized --output-on-failure
./build-sanitized/Lab4
./build-sanitized/vector_counts
./build-sanitized/vector_counts_may_throw
```

У демонстрації оригінал показує 200 г помідорів, а копія меню 150 г.
Розмір до і після самоприсвоєння становить 2. Результати санітайзерів,
лічильників і doctest збережені в `docs`.

`shallow_copy` спеціально відтворює помилку двох власників одного масиву.
Його запуск із ASan завершується помилкою. `no_destructor` відтворює
початковий витік, який перевірено в Linux із LeakSanitizer.
Робоча програма та тести ці демонстрації не викликають.

`third_party/doctest.h` є готовим заголовком фреймворку doctest 2.4.11.
Власні сценарії містяться в `tests/ingredient_list_test.cpp`.

