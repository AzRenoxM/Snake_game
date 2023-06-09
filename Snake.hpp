#pragma once

#include <ncurses.h>
#include "Body.hpp"
#include <iostream>
#include <ostream>
#include <cstdlib>
#include <vector>
#include <queue>
#include <ctime>
#include <tuple>
#include <map>

class Snake{
private:
   char16_t head{'X'}, borders{'#'}, food{'O'}, body{'+'}, blank{' '}; //! character symbols
   size_t map_size_x, map_size_y; //! size of the map
   unsigned int location_head_x, location_head_y; //! location of the head 
   unsigned int food_location_x, food_location_y; //! location of the food 
   unsigned int size_snake; //! points or how many7 object body has
   std::vector<Body> memory_snake; //! has a memory where x and y are

   friend std::tuple<unsigned int, unsigned int> generate_random(); //! generate 2 randoms numbers
   bool is_inside(unsigned int x_row, unsigned int y_column);
   std::tuple<unsigned int, unsigned int> change_location_food(); //! changes the location of the food using the method friend before
public:
   Snake(size_t map_size_x = 10, size_t map_size_y = 10); //! generates a map proprieties 
   ~Snake() = default;

   void control_snake(); //! takes input from the player 
   void display(); //! better to call this just run
   friend void run();
};
