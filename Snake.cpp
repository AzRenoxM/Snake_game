#include "Snake.hpp"
#include "Body.hpp"

//! private
std::tuple<unsigned int, unsigned int> generate_random(){
   int random_food_x = std::rand();
   int random_food_y = std::rand();
   return std::make_tuple(random_food_x, random_food_y);
}

std::tuple<unsigned int, unsigned int> Snake::change_location_food(){
   std::tie(this->food_location_x, this->food_location_y) = generate_random();
   bool crush_food{true};

   while(crush_food){
      for(size_t index{0}; index < this->memory_snake.size(); index++){
         if((this->memory_snake[index]).body_values() == std::tie(this->food_location_x, this->food_location_y)){
            std::tie(this->food_location_x, this->food_location_y) = generate_random();      
            continue;
         }
      }
      crush_food = false;
   }
   return std::make_tuple(this->food_location_x, this->food_location_y);
}
 
//! public

Snake::Snake(size_t map_size_x, size_t map_size_y)
   : map_size_x{map_size_x}, map_size_y{map_size_y}, location_head_x{0},
   location_head_y{0}, food_location_x{0}, food_location_y{0}, size_snake{/*(this->memory_snake).size()*/0}{ //TODO something with the size
      //! location head
      if(this->map_size_x % 2 == 1){
         this->location_head_x = ((this->map_size_x - 1) / 2) + 1;
      } else {
         this->location_head_x = this->map_size_x / 2; 
      }

      if(this->map_size_y % 2 == 1){
         this->location_head_y = ((this->map_size_y - 1) / 2) + 1;
      } else {
         this->location_head_y = this->map_size_y / 2; 
      }
      //! spawn food != location head
      this->change_location_food();
}

void Snake::control_snake(){
   //! taking input from the player 
   initscr();
   cbreak();
   noecho();
   keypad(stdscr, TRUE);

   int input = getch();

   switch (input) {
      case 'w':
         this->location_head_y--;
         break;
      case 'a':
         this->location_head_x--;
         break;
      case 's':
         this->location_head_y++;
         break;
      case 'd':
         this->location_head_x--;
         break;
      default:
         break;
   }
   endwin();
}

bool Snake::is_inside(unsigned int x_row, unsigned int y_column){
   for(Body& corps_obj : this->memory_snake){
      if(corps_obj.corp_x == x_row && corps_obj.corp_y == y_column){
         return true;
      }
   }
   return false;
}

void Snake::display(){
   //! one frame after taking input
   for(size_t inner_index{0}; inner_index < map_size_x; inner_index++){
      std::cout << this->borders;
   }
   std::cout << '\n';
   int x_row{1};

   for(size_t y_column{1}; y_column < map_size_y; y_column++){
      std::cout << this->borders; 

      if(location_head_x == x_row && location_head_y == y_column){
         std::cout << this->head;
      } else if(this->is_inside(x_row, y_column)){
         std::cout << this->body;
      } else {
         std::cout << this->blank;
      }
      std::cout << this->borders << '\n';
      x_row++;
   }
   for(size_t inner_index{0}; inner_index < map_size_x; inner_index++){
      std::cout << this->borders;
   }
}

