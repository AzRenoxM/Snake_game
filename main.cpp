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

//done Show the food on the map
//TODO after eating generate body mass
//TODO traversing the walls
//TODO you can go backwards 

//TODO if you dont move in time, go forward 
//TODO menu and visual
