int x; //declare
extern int y; //non-definition declare

void f(int x); //declare

int main()
{
   x = 10; //definition
   y = 20; //definition
  // f(50); Linker error! Not compile!
};
