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

  void SetFilter(vtkWindowToImageFilter* w);
  vtkNew<vtkWindowToImageFilter> w;
};
}

#endif //__classB_h
