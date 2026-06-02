#pragma once

#include "pathfind/astar.h"

void platform_init();

void platform_sleep_ms(uint32_t ms);

class System {
 public:
  pathfind::Astar& router() { return router_; }

 private:
  static pathfind::Astar router_;
};
