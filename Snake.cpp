#include "Snake.hpp"
#include "Body.hpp"

//! private
std::tuple<unsigned int, unsigned int> generate_random(Snake *source)
{
   std::srand(static_cast<unsigned int>(std::time(nullptr)));
   int random_food_x = (std::rand() % (source->map_size_x - 2)) + 1;
   int random_food_y = (std::rand() % (source->map_size_y - 2)) + 1;
   return std::make_tuple(random_food_x, random_food_y);
}

std::tuple<unsigned int, unsigned int> Snake::change_location_food()
{
   std::tie(this->food_location_x, this->food_location_y) = generate_random(this);
   bool crush_food{true};

   while (crush_food)
   {
      for (size_t index{0}; index < this->memory_snake.size(); index++)
      {
         if (this->memory_snake[index].body_values() == std::tie(this->food_location_x, this->food_location_y))
         {
            std::tie(this->food_location_x, this->food_location_y) = generate_random(this);
            break;
         }
         crush_food = false;
      }
   }
   return std::make_tuple(this->food_location_x, this->food_location_y);
}

void Snake::go_opposite()
{
   if (0 == this->memory_snake[0].corp_x)
   {
      this->memory_snake[0].corp_x = this->map_size_x - 2;
   }
   else if (this->memory_snake[0].corp_x == this->map_size_x - 1)
   {
      this->memory_snake[0].corp_x = 1;
   }
   else if (0 == this->memory_snake[0].corp_y)
   {
      this->memory_snake[0].corp_y = this->map_size_y - 2;
   }
   else if (this->memory_snake[0].corp_y == this->map_size_y - 1)
   {
      this->memory_snake[0].corp_y = 1;
   }
}

// TODO
void Snake::eat_food()
{
   if (this->memory_snake[0].corp_x == this->food_location_x && this->memory_snake[0].corp_y == this->food_location_y)
   {
      // this->memory_snake[this->size_snake].points++;
      this->size_snake++;
      for (size_t index{1}; index < this->memory_snake.size(); index++)
      {
         this->memory_snake[index].points++;
      }
      this->change_location_food();
   }
   else
      return;
}

void Snake::body_upload(int input)
{
   //! creates body after the move of the head
   Body _buffer;
   switch (input)
   {
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
   this->memory_snake.push_back(_buffer);
   this->eat_food();
   for (size_t index{1}; index < this->memory_snake.size(); index++)
   {
      if (this->memory_snake[index].points <= 0)
      {
         this->memory_snake.erase(this->memory_snake.begin() + index);
      }
      this->memory_snake[index].points--;
   }
}

//! public

Snake::Snake(size_t map_size_x, size_t map_size_y)
    : map_size_x{map_size_x}, map_size_y{map_size_y}, location_head_x{0},
      location_head_y{0}, food_location_x{0}, food_location_y{0}, size_snake{3}
{
   //! location head
   if (this->map_size_x % 2 == 1)
   {
      this->location_head_x = ((this->map_size_x - 1) / 2) + 1;
   }
   else
   {
      this->location_head_x = this->map_size_x / 2;
   }

   if (this->map_size_y % 2 == 1)
   {
      this->location_head_y = ((this->map_size_y - 1) / 2) + 1;
   }
   else
   {
      this->location_head_y = this->map_size_y / 2;
   }
   Body head_body(location_head_x, location_head_y, 1);
   this->memory_snake.push_back(head_body);

   //! spawn food != location head
   this->change_location_food();
   this->display();
}

void Snake::control_snake()
{
   //! taking input from the player
   initscr();
   cbreak();
   noecho();
   keypad(stdscr, TRUE);
   bool enter_refresh{true};
   int input{0};
   input = getch();

   switch (input)
   {
   case 'w':
      if (this->memory_snake[0].corp_y - 1 != this->memory_snake[this->memory_snake.size() - 1].corp_y)
         this->memory_snake[0].corp_y--;
      else
         enter_refresh = false;
      break;
   case 'a':
      if (this->memory_snake[0].corp_x - 1 != this->memory_snake[this->memory_snake.size() - 1].corp_x)
         this->memory_snake[0].corp_x--;
      else
         enter_refresh = false;
      break;
   case 's':
      if (this->memory_snake[0].corp_y + 1 != this->memory_snake[this->memory_snake.size() - 1].corp_y)
         this->memory_snake[0].corp_y++;
      else
         enter_refresh = false;
      break;
   case 'd':
      if (this->memory_snake[0].corp_x + 1 != this->memory_snake[this->memory_snake.size() - 1].corp_x)
         this->memory_snake[0].corp_x++;
      else
         enter_refresh = false;
      break;
   default:
      break;
   }
   endwin();
   if (enter_refresh)
      this->body_upload(input); // TODO debug the food eating check the game
   if (input != 0)
      this->go_opposite(); // TODO corps when go to wall
   // return true;
}

bool Snake::is_inside(unsigned int x_row, unsigned int y_column)
{
   for (Body &corps_obj : this->memory_snake)
   {
      if (corps_obj.corp_x == x_row && corps_obj.corp_y == y_column)
      {
         return true;
      }
   }
   return false;
}

void Snake::head_touch_snake()
{
   for (size_t index{1}; index < this->memory_snake.size(); index++)
   {
      if (this->memory_snake[index].body_values() == this->memory_snake[0].body_values()){
         this->game_con = false;
         return;
      }
   }
   this->game_con = true;
}

void Snake::speed_snake()
{
   int random_input{0};
   if (this->memory_snake[0].corp_x == this->memory_snake[this->memory_snake.size() - 1].corp_x + 1)
   {
      this->memory_snake[0].corp_x++;
      random_input = 'd';
   }
   else if (this->memory_snake[0].corp_x == this->memory_snake[this->memory_snake.size() - 1].corp_x - 1)
   {
      this->memory_snake[0].corp_x--;
      random_input = 'a';
   }
   else if (this->memory_snake[0].corp_y == this->memory_snake[this->memory_snake.size() - 1].corp_y - 1)
   {
      this->memory_snake[0].corp_y--;
      random_input = 'w';
   }
   else if (this->memory_snake[0].corp_y == this->memory_snake[this->memory_snake.size() - 1].corp_y + 1)
   {
      this->memory_snake[0].corp_y++;
      random_input = 's';
   }
   std::cout << random_input << std::endl;
   this->body_upload(random_input);
   this->go_opposite();
   std::chrono::milliseconds delay(1000);
   std::this_thread::sleep_for(delay);
}

void Snake::display()
{
   //! one frame after taking input
   system("clear");
   for (size_t inner_index{0}; inner_index < this->map_size_x; inner_index++)
   {
      std::cout << this->borders;
   }
   std::cout << '\n';

   for (size_t y_column{1}; y_column < (this->map_size_y - 1); y_column++)
   {
      std::cout << this->borders;

      for (size_t x_row{1}; x_row < (this->map_size_x - 1); x_row++)
      {

         if (this->memory_snake[0].corp_x == x_row && this->memory_snake[0].corp_y == y_column)
         {
            std::cout << this->head;
         }
         else if (this->is_inside(x_row, y_column))
         {
            std::cout << this->body;
         }
         else if (this->food_location_x == x_row && this->food_location_y == y_column)
         {
            std::cout << this->food;
         }
         else
         {
            std::cout << this->blank;
         }
      }
      std::cout << this->borders << '\n';
   }

   for (size_t inner_index{0}; inner_index < this->map_size_x; inner_index++)
   {
      std::cout << this->borders;
   }
   std::cout << '\n';

   //! developer sake
   std::cout << "Points: " << this->size_snake << '\n';
   // std::cout << this->map_size_x << '\n';
   // std::cout << this->map_size_y << '\n';
   std::cout << this->game_con << '\n';

   std::cout << '\n';
   for (size_t something{0}; something < this->memory_snake.size(); something++)
   {
      std::cout << "this->memory_snake[" << something << "].corp_x: " << this->memory_snake[something].corp_x << std::endl;
      std::cout << "this->memory_snake[" << something << "].corp_y: " << this->memory_snake[something].corp_y << std::endl;
      std::cout << "this->memory_snake[" << something << "].points: " << this->memory_snake[something].points << std::endl;
      std::cout << '\n';
   }
}

// void Snake::run()
// {
//    Snake game;
//    game.game_con = true;
//    while (this->game_con)
//    {
//       std::thread thread_first (thread_one, std::ref(game));
//       std::thread thread_second (thread_two, std::ref(game));
//    }
// }

void Snake::run()
{
   this->game_con = true;
   this->thread_one();
   this->thread_two();
}

void Snake::thread_one()
{
   while (this->game_con)
   {
      this->display();
      this->control_snake();
      this->head_touch_snake();
   }
}

void Snake::thread_two()
{
   if(this->memory_snake[0].body_values() != this->memory_snake[this->memory_snake.size() - 1].body_values()){
      // while (this->game_con)
      while(true)
      {
         this->speed_snake();
         this->display();
      }
   }
}