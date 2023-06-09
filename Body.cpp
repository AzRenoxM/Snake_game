#include "Snake.hpp"
#include "Body.hpp"

Body::Body(unsigned int corp_x, unsigned int corp_y, size_t points)
   : corp_x{corp_x}, corp_y{corp_y}, points{points}{}

std::tuple<unsigned int, unsigned int> Body::body_values(){
   return std::make_tuple(corp_x, corp_y);
}

void Body::food_eaten(){
   this->points++;
}
