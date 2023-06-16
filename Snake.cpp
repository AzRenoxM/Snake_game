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

void Snake::go_opposite(){
   for(auto& body_chain : this->memory_snake){
      if(1 > body_chain.corp_x){
         body_chain.corp_x = this->map_size_x - 2;
      } else if(body_chain.corp_x >= this->map_size_x - 1){
         body_chain.corp_x = 1;
      } else if(1 > body_chain.corp_y){
         body_chain.corp_y = this->map_size_y - 2;
      } else if(body_chain.corp_y >= this->map_size_y - 1){
         body_chain.corp_y = 1;
      }
   }
}

//TODO
void Snake::eat_food(){
   if(this->memory_snake[0].corp_x == this->food_location_x && this->memory_snake[0].corp_y == this->food_location_y){
      this->size_snake++;
      for(size_t index{1}; index < this->memory_snake.size(); index++){
         this->memory_snake[index].points++;
      }
      this->change_location_food();
   } else return;
}
 
void Snake::body_upload(int input){
   //! creates body after the move of the head
   Body _buffer;
   switch (input) {
      case 'w':
         _buffer.set_values(this->memory_snake[0].corp_x, this->memory_snake[0].corp_y + 1, this->size_snake);
         break;
      case 'a':
         _buffer.set_values(this->memory_snake[0].corp_x + 1, this->memory_snake[0].corp_y, this->size_snake);
         break;
      case 's':
         _buffer.set_values(this->memory_snake[0].corp_x, this->memory_snake[0].corp_y - 1, this->size_snake);
         break;
      case 'd':
         _buffer.set_values(this->memory_snake[0].corp_x - 1, this->memory_snake[0].corp_y, this->size_snake);
         break;
      default:
         break;
   }
   //! eliminates one point of each link
   for(size_t index{1}; index < this->memory_snake.size(); index++){
      this->memory_snake[index].points--;
      if(this->memory_snake[index].points <= 0) this->memory_snake.erase(this->memory_snake.begin() + index); 
   }
   this->memory_snake.push_back(_buffer);
}

//! public

Snake::Snake(size_t map_size_x, size_t map_size_y)
   : map_size_x{map_size_x}, map_size_y{map_size_y}, location_head_x{0},
   location_head_y{0}, food_location_x{0}, food_location_y{0}, size_snake{1}{
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
      Body head_body(location_head_x, location_head_y, 1);
      this->memory_snake.push_back(head_body);

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

   Body buffer(this->memory_snake[0].corp_y, this->memory_snake[0].corp_y, this->size_snake);

   int input{0};
   input = getch();

   switch (input) {
      case 'w':
         this->memory_snake[0].corp_y--;
         break;
      case 'a':
         this->memory_snake[0].corp_x--;
         break;
      case 's':
         this->memory_snake[0].corp_y++;
         break;
      case 'd':
         this->memory_snake[0].corp_x++;
         break;
      default:
         break;
   }
   endwin();
   if(input != 0) this->go_opposite(); //TODO corps when go to wall
   if(input != 0) this->eat_food();
   if(input != 0) this->body_upload(input); //TODO debug the food eating check the game
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
      
         if(this->memory_snake[0].corp_x == x_row && this->memory_snake[0].corp_y == y_column){
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
   std::cout << "size snike: " <<this->size_snake << std::endl;

   std::cout << '\n';
   for(size_t something{0}; something < this->memory_snake.size(); something++){
      std::cout << "this->memory_snake[" << something << "].corp_x: " << this->memory_snake[something].corp_x << std::endl;
      std::cout << "this->memory_snake[" << something << "].corp_y: " << this->memory_snake[something].corp_y << std::endl;
      std::cout << "this->memory_snake[" << something << "].points: " << this->memory_snake[something].points << std::endl;
      std::cout << '\n';
   }
}

void Snake::run(){
   Snake game;
   while(true){
      game.display();
      game.control_snake();
   }
}
