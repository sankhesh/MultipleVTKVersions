#include "classB.h"

B::classB::classB()
{
  this->w->SetMagnification(2.0);
}

B::classB::~classB()
{
}

void B::classB::SetFilter(vtkWindowToImageFilter* wi)
{
  if (!wi)
  {
    return;
  }
  wi->SetMagnification(3.0);
}
