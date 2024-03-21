#include <iostream>

#include "game.h"
#include "object.h"
#include "player.h"


int main() {
  try{
    game game;
    game.start();
  }
  catch (std::exception(e)) {
    std::cerr << "Exception: " << e.what() << std::endl;
    return -1;
  }

  return 0;
}
