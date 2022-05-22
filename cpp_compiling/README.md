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

При этом, результатом препроцессинга будут файл `*.ii`, который называются `translation unit`.

## Преобразование текста в машинный код

Далее, на основе текста после препроцессинга, компилятор создает абстрактное синтаксическое дерево на основе которого будет создавать текст, состоящий из
1. машинных инструкций
2. констант

Поэтапно это выглядит следующим образом:
1. создание абстракного синтаксического дерева
2. преобразование в ассемблерный код
3. преобразование ассемемблерного кода в машинный

Рассмотрим подробнее пункт два и пункт три:

### Преобразование в ассемблерный код

Выполнив команду `g++ -S plus.cpp -o plus.s` компилятор остановит свою работу после ассемблирования и результатом работы будет файл, содержащий ассемблерный код?

```assembly
   .file "plus.cpp"
   .text
   .globl _Z4plusii
   .type _Z4plusii, @function
_Z4plusii:
   .LFB0:
   .cfi_startproc
endbr64
pushq %rbp
   .cfi_def_cfa_offset 16
   .cfi_offset 6, -16
movq %rsp, %rbp
   .cfi_def_cfa_register 6
movl %edi, -20(%rbp)
movl %esi, -24(%rbp)
movl -20(%rbp), %edx
movl -24(%rbp), %eax
addl %edx, %eax
movl %eax, -4(%rbp)
movl -4(%rbp), %eax
popq %rbp
   .cfi_def_cfa 7, 8
ret
   .cfi_endproc
   .LFE0:
   .size _Z4plusii, .-_Z4plusii
   .ident "GCC: (Ubuntu 11.2.0-19ubuntu1) 11.2.0"
   .section .note.GNU-stack,"",@progbits
   .section .note.gnu.property,"a"
   .align 8
   .long 1f - 0f
   .long 4f - 1f
   .long 5
0:
.string "GNU"
1:
   .align 8
   .long 0xc0000002
   .long 3f - 2f
2:
   .long 0x3
3:
   .align 8
4:
```

Стоит сказать, что в зависимости от написаного кода на C++ может и измениться ассемблерный код.

`plusv1.cpp`
```cpp

int plus(int a, int b)
{
   return a + b;
}
```

Преобразовав `plusv1.cpp` в ассемблерный код, получим:

```assembly
   .file "plusv1.cpp"
   .text
   .globl _Z4plusii
   .type _Z4plusii, @function
_Z4plusii:
   .LFB0:
   .cfi_startproc
endbr64
pushq %rbp
   .cfi_def_cfa_offset 16
   .cfi_offset 6, -16
movq %rsp, %rbp
   .cfi_def_cfa_register 6
movl %edi, -4(%rbp)
movl %esi, -8(%rbp)
movl -4(%rbp), %edx
movl -8(%rbp), %eax
addl %edx, %eax
popq %rbp
   .cfi_def_cfa 7, 8
ret
   .cfi_endproc
   .LFE0:
   .size _Z4plusii, .-_Z4plusii
   .ident "GCC: (Ubuntu 11.2.0-19ubuntu1) 11.2.0"
   .section .note.GNU-stack,"",@progbits
   .section .note.gnu.property,"a"
   .align 8
   .long 1f - 0f
   .long 4f - 1f
   .long 5
0:
   .string "GNU"
1:
   .align 8
   .long 0xc0000002
   .long 3f - 2f
2:
   .long 0x3
3:
   .align 8
4:
```

То есть, желательно создавать **оптимизированный** код.

### Преобразование ассемблерного кода в машинный

Данный этап создает **объектный** файл, который содержит в себе куски машинного кода.

Введя команду `g++ plus.cpp -o plus.o` мы получим объектный файл, содержащий в себе 0 и 1.

---

## По итогу

Процесс компиляции файлов (без линкера) выглядит следующим образом:
1. Этап препроцессинга -- обработка директив, макросов и удаление комментариев
2. Этап создания абстрактного синтаксического дерева
3. Этап преобразования в ассемблерный код
4. Этап преобразования в объектный файл
