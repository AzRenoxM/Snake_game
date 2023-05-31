#include "Snake.h"

Snake::Snake(size_t map_size_x, size_t map_size_y)
   : map_size_x{map_size_x}, map_size_y{map_size_y}, location_head_x{0},
   location_head_y{0}, food_location_x{0}, food_location_y{0}, size_snake{3}{
      //TODO logic of the map

}

Void Snake::control_snake(std::queue<std::map<unsigned int, unsigned int>>& memory_snake){

}

Void Snake::display(){

}
