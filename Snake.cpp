#include "Snake.h"

//! private

std::tuple<unsigned int, unsigned int> generate_random(){
   int random_food_x = std::rand();
   int random_food_y = std::rand();
   return std::make_tuple(random_food_x, random_food_y);
}

std::tuple<unsigned int, unsigned int> Snake::change_location_food(unsigned int location_head_x, unsigned int location_head_y){
   this->size_snake++;
   std::tie(this->food_location_x, this->food_location_y) = generate_random();
   bool nocrush_food{false};

   while(nocrush_food){
      if(this->food_location_x == this->location_head_x && this->food_location_y == this->location_head_y){
         std::tie(this->food_location_x, this->food_location_y) = generate_random();      
         continue;
      }
      for(const std::map)
      if(){

         continue;
      }
      nocrush_food = true;
   }
   //TODO random food != head
   //TODO random food != body snake
}

//! public

Snake::Snake(size_t map_size_x, size_t map_size_y)
   : map_size_x{map_size_x}, map_size_y{map_size_y}, location_head_x{0},
   location_head_y{0}, food_location_x{0}, food_location_y{0}, size_snake{3}{
      //TODO location head
      //TODO spawn food != location head
      //TODO 
}

void Snake::control_snake(std::queue<std::map<unsigned int, unsigned int>>& memory_snake){
   //TODO taking input from the player
}

std::ofstream& Snake::display(){
   //TODO one frame after taking input
}
