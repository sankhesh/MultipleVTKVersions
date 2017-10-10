#include "classA.h"

A::classA::classA()
{
  this->w->SetMagnification(2.0);
}

A::classA::~classA()
{
}

void A::classA::SetFilter(vtkWindowToImageFilter* wi)
{
  if (!wi)
  {
    return;
  }
  wi->SetMagnification(3.0);
}
