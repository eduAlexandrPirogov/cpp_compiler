#include "Log.h"

int main()
{
   Logger<int> intLog{};
   Logger<char> charLog{};
   Logger<double> doubleLog{};

   intLog.Log(2);
   charLog.Log('a');
   doubleLog.Log(2.2);
};
