#ifndef __classA_h
#define __classA_h

#include <vtkNew.h>
#include <vtkWindowToImageFilter.h>

namespace A
{
class classA
{
public:
  classA();
  ~classA();

  vtkNew<vtkWindowToImageFilter> w;
};
}

#endif //__classA_h
