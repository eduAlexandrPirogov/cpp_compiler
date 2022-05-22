# Линковка

После компиляции **cpp** файлов, наступает этап линковки. Обычно программа разбита на несколько файлов и после компиляции у нас появляются несколько файлов **.obj**. Чтобы преобразовать объектные файлы **.obj** в исполняемый код, в дело вступает линкер.

Основная функция линкера (Linker) -- найти, где находится **определение** каждого символа, каждой функции и т.п.,а также находит **entry point** вашей программы.

Выглядит примерно все следующим образом:

```

a.cpp------>|->a.obj-->|
                       |
b.h-------->|          |
            |->b.obj-->|
            |          |
b.cpp------>|          |--->LINKER---->executable program
                       | 
c.h-------->|          |
            |->c.obj-->|
c.cpp------>|
```

## Объявления и определения

## Header файлы

## ODR rule
