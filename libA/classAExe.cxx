#include <classA.h>
#include <classB.h>

int main(int argc, char* argv[])
{
  std::cout << "Instantiating B" << std::endl;
  B::classB();
  std::cout << "Instantiating A" << std::endl;
  A::classA();
  return EXIT_SUCCESS;
}
