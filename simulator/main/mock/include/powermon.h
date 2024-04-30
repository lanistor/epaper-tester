#pragma once

#include "basic.h"

class PowerMon_Class {
 public:
  void correctAdcReference(void);
  bool getVoltageRaw(uint32_t& Battery, uint32_t& Bus);
  bool getVoltage(uint32_t& Battery, uint32_t& Bus);
};
