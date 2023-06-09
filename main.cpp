#include "Snake.hpp"
#include "Body.hpp"

void run(){
   Snake game;
   while(true){
      game.display();
      game.control_snake();
   }
}

int main(int argc, char** argv){

   run();
   

   return 0;
}
