#include "UIduino.hpp"
void Button::clicked() {
  if (*clickCallback != NULL) {
    clickCallback();
  }
}
