#pragma once

#include "basic.h"
#include "fl_utils.h"
#include <string>

using namespace std;

typedef function<void()> fl_common_cb;

// rect
struct fl_rect {
  int x      = 0;
  int y      = 0;
  int width  = 0;
  int height = 0;
};
