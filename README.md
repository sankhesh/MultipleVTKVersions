MultipleVTKVersions
===================

This project tests a specific case involving the VTK library versioning and
linkage.

```txt
     +----------+                        +----------+
     | VTK v8.1 |                        | VTK v6.2 |
     +----------+                        +----------+
         ^                                    ^
         |                                    |
         |                                    |
         |                                    |
         |                                    |
     +---+-----+                         +----+-----+
     | lib A   |                         |  lib B   |
     +---+-----+                         +----+-----+
         ^                                     ^
          \                                   /
           \                                 /
            \                               /
             \                             /
              \                           /
               \                         /
                \+---------------------+/
                 |      libAExe        |
                 +---------------------+
```

The setup is described in the figure above.

- lib A links to VTK v8.1
- lib B links to VTK v6.2
- libAExe links to both libA and libB

For the sake of differentiating, `vtkWindowToImageFilter::SetMagnification()` is
chosen as the test. The method was deprecated in v8.0 and leads to a warning
when used. If the calling application is linking against any version prior
to v8.0, it would not complain.

## Tests and results

libAExe tests the following (the results are noted in ***BOLD TEXT***:

- Instantiate libB::classB; which calls
`v6.2::vtkWindowToImageFilter::SetMagnification()`. ***NO WARNING***
- Instantiate libA::classA; which calls
`v8.1::vtkWindowToImageFilter::SetMagnification()`. ***WARNING***
- Pass `v6.2::vtkWindowToImageFilter` to libA::classA and call the test method.
***WARNING i.e. the passed class behaves as a v8.1 class inside libA***
- Pass `v8.1::vtkWindowToImageFilter` to libB::classB and call the test method.
***NO WARNING i.e. the passed class behaves as a v6.2 class inside libB***

## Inferences
Based on the results, it seems that dynamically linking to two different
versions over a dependency tree could work as long as certain constraints are
adhered to. When an object of a different VTK version is passed to the library
linking to a different VTK version, it behaves as the new version. This could
lead to potential issues where the old object did not have certain data members
that the new object has or vice versa.
