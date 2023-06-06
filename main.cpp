#include "Snake.hpp"
#include "Body.hpp"

struct sss {
   union {
      uint32_t ab;
      struct {
         uint16_t b, a;
      };
   };
};

int main(int argc, char** argv){
   sss Stru;
   Stru.ab = 0x11119999;
   std::cout << std::hex << Stru.ab << "; " << Stru.a << "; " << Stru.b << ";\n";

   return 0;
}
