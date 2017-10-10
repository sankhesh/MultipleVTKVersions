#ifndef __classB_h
#define __classB_h

#include <vtkNew.h>
#include <vtkWindowToImageFilter.h>

namespace B
{
class classB
{
public:
  classB();
  ~classB();

  vtkNew<vtkWindowToImageFilter> w;
};
}

#endif //__classB_h
