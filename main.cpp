// $Id$ get this working on git
// g++ -o city_skyline main.cpp

#include <list>

class City
{
public:
  struct Bldg
  {
    Bldg(int x1, int x2, int y) : x1_(x1), x2_(x2), y_(y) {}
    int x1_;
    int x2_;
    int y_;
  };
  void addBldg(int x1, int x2, int y) {
    bldgs.push_back(Bldg(x1, x2, y));
  }
private:
  std::list<Bldg> bldgs;
};

#include <iostream>
#include <string>
#include <boost/regex.hpp>
#include <boost/lexical_cast.hpp>

bool get_bldg_coords(int (&bldg_coords)[3], std::string& remnant)
{
  static boost::regex e("^\\h*(\\d+)\\h+(\\d+)\\h+(\\d+)\\h*$");
  bool gotten = false;
  std::getline(std::cin, remnant);
  if ( !std::cin.good() ) {
    remnant += " <cin stream fails>";
    std::cin.clear();
  }
  else if ( !remnant.empty() ) {
    boost::smatch what;
    if( boost::regex_match(remnant, what, e ) ) {
      for ( int i=0; i<3; ++i ) {
        // should catch for value > INT_MAX
        bldg_coords[i] = boost::lexical_cast<int>(what[i+1]);
      }
      if ( bldg_coords[0] <= bldg_coords[1] ) {
        // knowledge that x1 <= x2 should be in City::Bldg ctor
        gotten = true;
      }
    }
  }
  return gotten;
}

int main(int argc, char* argv[])
{
  City c;
  bool quit = false;

  while ( !quit ) {
    std::string cmd, remnant;
    bool handled = false;
    std::cout << "city >> " << std::flush;
    std::cin >> cmd;
    if ( cmd == "quit" ) {
      quit = handled = true;
      std::cout << "done" << std::endl;
    }
    else if ( cmd == "addBldg" ) {
      int bldg_coords[3];
      if ( get_bldg_coords(bldg_coords, remnant) ) {
        c.addBldg(bldg_coords[0], bldg_coords[1], bldg_coords[2]);
        handled = true;
        std::cout << "addBldg" << std::endl;
      }
    }
    else {
      std::getline(std::cin, remnant);
    }
    if ( !handled ) {
      std::cout << "command error \"" << ( cmd + remnant )
        << "\", quit to exit" << std::endl;
    }
  }
  return 0;
}
