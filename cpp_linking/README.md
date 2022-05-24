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

Вспомним разницу между объявлением и определением.

`declare_definition/declare_definition.cpp`

```cpp
int x; //declare
extern int y; //non-definition declare

void f(int x); //declare

int main()
{
   x = 10; //definition
   y = 20; //definition
  // f(50); Linker error! Not compile!
};
```

Переменные **x**, **y** и функция **void f(int x)** за пределами функции **main** -- объявлены. Мы говорим компилятору, мол "мы объявили это, а определения лежат где-то за пределами". Иначе говоря, мы создали переменные, но не выделили на них память (haven't allocate em).

Далее, в функции **main** определяем переменные **x** и **у**, но не определяем функция **void f(int x)**. 

При этом, компиляция выполнится успешно (если мы расскомменитруем f(50)). Но проект не соберется, так как Линкер не найдет определение для данной функции!

Рассмотрим следующий пример. Имеем два файла 
`main.cpp`
```cpp
//void Log(const char* message, int x);

int main()
{
   int x = 10;
   Log("Hello, world\n", x);
   return 0;
};
```

`log.cpp`
```cpp
#include <iostream>

void Log(const char* message, int x)
{
   std::cout << message << "\nx = " << x << '\n';
};
```

Имеется функция **Log(const char* message, int x)**, которая расположена в `log.cpp` файле. Поскольку в `main.cpp` закомментировано объявление данной функции, 
компилятор выдаст ошибку компилятора **log wasn't declared in this scope**. Стоит добавить объявление функции (раскомментировать объявление в `main.cpp`), и проблема решится. Работает все по такой же схеме: создаются два объектных файла `log.o` и `main.o`,и далее линкер преобразует объектные файлы в исполняемый файл.  :)
.

## Header файлы

Рассмотрим ещё один пример с **header** файлами. Обычно, header-файлы хранят в себе объявление переменных, функций и т.д.

Как мы помним, препроцессор включает содержимое header-файлов в файл, содержащий соответствующую **#include** директиву.

Тут стоит сказать о нескольких важных моментах:

### ODR rule

**One definition rule** -- translation units defines entity exactly one time.
 
Каждый объектный файл определяет сущность лишь единжды.

Линкер может столкнуться со следующими проблемами:
1. undefined reference
2. multiple references
3. pragma once moments


### Undefined reference

Undefined reference говорит, что линкер не может найти определения для некоторой сущности. Пример:

`a.ii after preprocessing`
```cpp
//a.h
int a;
void f();
//a.cpp
a = 10;
```


```cpp
#include "a.h"

void f();

main()
{
   a = 20; // changes a which defined in a.cpp
   f(); // linker error
   return 0;
};
```

Посколкьу не имеется определения для функции **void f()**, линкер выдает ошибку типа **undefined reference**

--------
### `Multiple reference`

`multiple.h`
```cpp
void test()
{};
```

`a.h`
```cpp
#include "multiple.h"
```

`b.h`
```cpp
#include "multiple.h"
```

`main.cpp`
```cpp
#include "a.h"
#include "b.h"

int main()
{
   test();
};
```

Чтобы понять в чем тут загвоздка, посмотрим, как будет выглядеть `main.cpp` после компиляции:

`main.ii`
```cpp
//#include "a.h"
////a includes multiple.h
void test(){};
//#include "b.h"
////b includes multiple.h too
void test() {};


int main()
{
   test();// linker doesn't know which one is needed
};
```

### pragma once moment

Почти всегда в `*.h` файлах первой строкой можно увидеть инструкцию препроцессора **#pragma once**
Данная инструкция говорит, что нужно включать данный заголовочный файл **единожды**, дабы не возникло **multiple reference**

# Шаблоны

Немного о шаблонах. Если мы создаем шаблон некого класса, то, как известно, нам нужно объявить определение шаблона в заголовочном файле.
**Шаблоны -- это рецепт для компилятора, который будет в рантайме создавать нужный код**

`Log.h`
```cpp
#pragma once
#include <iostream>

template <class T>
class Logger
{
   public:
      Logger();
      void Log(T t);
};

template<class T>
Logger<T>::Logger(){};

template <class T>
void Logger<T>::Log(T t)
{
   std::cout << t << '\n';
};
```

Для каждого шаблона будет создана своя версия кода определения:

```cpp
#include "Log.h"

int main()
{
   Logger<int> intLog{}; //compiler creates a class<int> Logger...
   Logger<char> charLog{}; //compiler creates a class<char> Logger...
   Logger<double> doubleLog{}; //compiler creates a class<double> Logger...

   intLog.Log(2); //compiler creates a function<int> Log(int t)...
   charLog.Log('a'); //compiler creates a function<char> Log(char t)...
   doubleLog.Log(2.2); //compiler creates a function<double> Log(double t)...
};
```


**Замечание**
Если мы создаем специализацию шаблоны, то **мы должны объявить его определение явно**, поскольку:
1. **шаблоны функции -- это не функция**
2. **специализация шаблоны -- это функция**

# Таблица символов
TBD
