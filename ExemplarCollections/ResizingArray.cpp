#include "ResizingArray.h"

#include <string>

// Template note:
// Generic templates are defined in headers.
// We keep this .cpp to satisfy a header/cpp layout and to provide a few
// explicit instantiations that are commonly used in exercises.

template class exemplar::ResizingArray<int>;
template class exemplar::ResizingArray<std::string>;
