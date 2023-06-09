#pragma once

#include <ncurses.h>
#include "Snake.hpp"
#include <iostream>
#include <ostream>
#include <cstdlib>
#include <vector>
#include <thread>
#include <chrono>
#include <queue>
#include <ctime>
#include <tuple>
#include <map>

class Body{
   public:
      unsigned int corp_x; //! construct ini
      unsigned int corp_y; //! construct ini
      size_t points; //! construct ini
  
      Body(unsigned int corp_x = 1, unsigned int corp_y = 1, size_t points = 1);
      ~Body() = default;

      std::tuple<unsigned int, unsigned int> body_values();
      void food_eaten();
      void set_values(unsigned int location_x, unsigned int location_y, size_t point);
};