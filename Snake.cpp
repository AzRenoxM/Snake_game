#include "Snake.hpp"
#include "Body.hpp"

//! private
std::tuple<unsigned int, unsigned int> generate_random(Snake* source){
   std::srand(static_cast<unsigned int>(std::time(nullptr)));
   int random_food_x = (std::rand() % (source->map_size_x - 2)) + 1;
   int random_food_y = (std::rand() % (source->map_size_y - 2)) + 1;
   return std::make_tuple(random_food_x, random_food_y);
}

std::tuple<unsigned int, unsigned int> Snake::change_location_food(){
   std::tie(this->food_location_x, this->food_location_y) = generate_random(this);
   bool crush_food{true};

   while(crush_food){
      for(size_t index{0}; index < this->memory_snake.size(); index++){
         if((this->memory_snake[index]).body_values() == std::tie(this->food_location_x, this->food_location_y)){
            std::tie(this->food_location_x, this->food_location_y) = generate_random(this);      
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
      this->display();
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
         this->location_head_x++;
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
   system("clear");
   for(size_t inner_index{0}; inner_index < this->map_size_x; inner_index++){
      std::cout << this->borders;
   }
   std::cout << '\n';

   for(size_t y_column{1}; y_column < (this->map_size_y - 1); y_column++){
      std::cout << this->borders; 

      for (size_t x_row{1}; x_row < (this->map_size_x - 1); x_row++){
      
         if(this->location_head_x == x_row && this->location_head_y == y_column){
            std::cout << this->head;
         } else if(this->is_inside(x_row, y_column)){
            std::cout << this->body;
         } else if(this->food_location_x == x_row && this->food_location_y == y_column){
            std::cout << this->food;
         } else {
            std::cout << this->blank;
         }
      }
      std::cout << this->borders << '\n';
   }
   
   for(size_t inner_index{0}; inner_index < this->map_size_x; inner_index++){
      std::cout << this->borders;
   }
   std::cout << '\n';

   //! developer sake
   std::cout << "food_location_x: " << this->food_location_x << std::endl;
   std::cout << "food_location_y: " << this->food_location_y << std::endl;
}

