#include "bibs.hpp"
#include <math.h>

double squareRoot(double a) {
  double b = sqrt(a);
  if (isnan(b)) {
    return -1.0;
  } else {
    return b;
  }
}
