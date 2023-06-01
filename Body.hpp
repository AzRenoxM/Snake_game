#pragma once

#include<tuple>

class Body{
   private:
      unsigned int corp_x;
      unsigned int corp_y;
      size_t points;
   public:
      Body(unsigned int corp_x = 1, unsigned int corp_y = 1, size_t points = 0);
      ~Body() = default;

      std::tuple<unsigned int, unsigned int, size_t> body_values();
      void food_eaten();
};
