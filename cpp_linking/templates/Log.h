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
