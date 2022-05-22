# Процесс компиляции

Компиляция включает в себя два основных этапа:
1. Препроцессинг
2. Компиляция

## Препроцессинг

Этап препроцессинга выполняется следующим образом: обрабатываются макросы, удаляются комментарии.

Создадим два файла `plus.cpp` и `result.h`.

plus.cpp
```cpp

int plus(int a, int b)
{
   #include "./result.h"
   //int res = a + b;
   return res;
}
```

`result.h`
```cpp
int res = a + b;
```

Выполнив команду в терминале `g++ -E plus.cpp -o plus.ii`, компилятор остановит работу после препроцессинга, а результат компиляции будет файл `plus.ii`,
который будет содержать в себе следующие строки:

```cpp
# 0 "plus.cpp"
# 0 "<built-in>"
# 0 "<command-line>"
# 1 "/usr/include/stdc-predef.h" 1 3 4
# 0 "<command-line>" 2
# 1 "plus.cpp"

int plus(int a, int b)
{
# 1 "./result.h" 1
int res = a + b;
# 4 "plus.cpp" 2
   return res;
}
```

В данном случае комплятор заменял `#include "./result.h"` на содержимое фалйа `result.h`. 

При этом, результатом препроцессинга будет файл `plus.ii`, который называется `translation unit`.


