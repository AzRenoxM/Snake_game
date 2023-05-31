#pragma once

#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <map>

class Snake{
private:
   char16_t head{'X'}, borders{'#'}, food{'O'}, body{'+'}; 
   size_t map_size_x, map_size_y;
   unsigned int location_head_x, location_head_y;
   unsigned int food_location_x, food_location_y;
   unsigned int size_snake;
   std::queue<std::map<unsigned int, unsigned int>> memory_snake;
public:
   Snake(size_t map_size_x = 10, size_t map_size_y = 10);
   ~Snake() = default;

   void control_snake(std::queue<std::map<unsigned int, unsigned int>>& memory_snake);
   std::ofstream& display();
};
