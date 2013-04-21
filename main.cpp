// $Id$ get this working on git
// g++ -o city_skyline main.cpp


class City
{
};

#include <iostream>
#include <string>

int main(int argc, char* argv[])
{
  City c;
  bool quit = false;
  std::string cmd;

  while ( !quit ) {
    std::cout << "city >> " << std::flush;
    std::cin >> cmd;
    if ( cmd == "quit" ) {
      quit = true;
      std::cout << "done" << std::endl;
    }
    else {
      std::cout << "Unknown command \"" << cmd << "\", quit to exit"
        << std::endl;
    }
  }
  return 0;
}
