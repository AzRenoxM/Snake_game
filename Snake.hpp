#pragma once

#include <ncurses.h>
#include "Body.hpp"
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

class Snake{
private:
   char head{'X'}, borders{'#'}, food{'O'}, body{'+'}, blank{' '}; //! character symbols
   unsigned int location_head_x, location_head_y; //! location of the head 
   unsigned int food_location_x, food_location_y; //! location of the food 
   unsigned int size_snake; //! points or how many7 object body has

   bool is_inside(unsigned int x_row, unsigned int y_column); //! search inside memory_snake vector
   friend std::tuple<unsigned int, unsigned int> generate_random(Snake& source); //! generate 2 randoms numbers
   std::tuple<unsigned int, unsigned int> change_location_food(); //! changes the location of the food using the method friend before
   void go_opposite(); //! opposite direction
   void eat_food(); //! position head == position food
   void body_upload(int input);
public:
   Snake(size_t map_size_x = 20, size_t map_size_y = 10); //! generates a map proprieties 
   ~Snake() = default;
   std::vector<Body> memory_snake; //! has a memory where x and y are
   bool game_con; //TODO give private

   size_t map_size_x, map_size_y; //! size of the map

   void head_touch_snake();
   void control_snake(); //! takes input from the player 
   void display(); //! better to call this just run
   void speed_snake();

   void thread_one();
   void thread_two();
   void run();

};