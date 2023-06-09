#pragma once

#include <ncurses.h>
#include "Snake.hpp"
#include <iostream>
#include <ostream>
#include <cstdlib>
#include <vector>
#include <queue>
#include <ctime>
#include <tuple>
#include <map>

class Body{
   public:
      unsigned int corp_x; //! construct ini
      unsigned int corp_y; //! construct ini
      size_t points; //! construct ini
      Body(unsigned int corp_x = 1, unsigned int corp_y = 1, size_t points = 0);
      ~Body() = default;

      std::tuple<unsigned int, unsigned int> body_values();
      void food_eaten();
};
