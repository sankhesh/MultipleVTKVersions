#include <classA.h>
#include <classB.h>

int main(int argc, char* argv[])
{
  std::cout << "Instantiating B" << std::endl;
  B::classB* b = new B::classB();
  std::cout << "Instantiating A" << std::endl;
  A::classA* a = new A::classA();
  std::cout << "Passing libB VTK object to libA" << std::endl;
  a->SetFilter(b->w.GetPointer());
  std::cout << "Passing libA VTK object to libB" << std::endl;
  b->SetFilter(a->w.GetPointer());

  delete b;
  delete a;
  return EXIT_SUCCESS;
}
