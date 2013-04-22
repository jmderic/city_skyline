// $Id$ get this working on git
// g++ -o city_skyline main.cpp

#include <list>
#include <map>

class City
{
public:
  struct Bldg {
    Bldg(int x1, int x2, int y) : x1_(x1), x2_(x2), y_(y) {}
    bool operator==(const Bldg& rhs) {
      return ( x1_==rhs.x1_ && x2_==rhs.x2_ && y_==rhs.y_ );
    }
    int x1_;
    int x2_;
    int y_;
  };
  struct Point {
    Point(int x, int y) : x_(x), y_(y) {}
    int x_;
    int y_;
  };
  typedef std::list<Point> Skyline;
  void addBldg(int x1, int x2, int y) {
    bldgs.push_back(Bldg(x1, x2, y));
  }
  void getSkyline(Skyline& skyline) const {
    BData xdata, ydata;
    std::list<Bldg>::const_iterator b_it, b_endit=bldgs.end();
    for ( b_it=bldgs.begin(); b_it!=b_endit; ++b_it ) {
      xdata.insert(std::make_pair(b_it->x1_, *b_it));
      xdata.insert(std::make_pair(b_it->x2_, *b_it));
    }
    BData::const_iterator x_it, x_endit=xdata.end(), y_it;
    int last_x = -1;
    for ( x_it=xdata.begin(); x_it!=x_endit; ++x_it ) {
      int this_x = x_it->first;
      if ( last_x != this_x ) {
        // give the result for lastx
        Point p(last_x, 0);
        if ( ydata.begin() != (y_it=ydata.end()) ) {
          p.y_ = (--y_it)->first;
        }
        skyline.push_back(p);
      }
      const Bldg& b = x_it->second;
      if (this_x == b.x1_) { // start of building (leading edge)
        ydata.insert(std::make_pair(b.y_, b));
      }
      else { //  this_x == b.x2_ end of building (trailing edge)
        std::pair<BData::iterator, BData::iterator> eq_y =
          ydata.equal_range(b.y_);
        for ( ; eq_y.first!=eq_y.first; ++(eq_y.first) ) {
          if ( eq_y.first->second == b ) {
            ydata.erase(eq_y.first);
            break;
          }
        }
      }
      last_x = this_x;
    }
    Point p(last_x, 0);
    skyline.push_back(p);
  }
private:
  typedef std::multimap<int, Bldg> BData;
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
      if ( 0 <= bldg_coords[0] && bldg_coords[0] < bldg_coords[1] ) {
        // constraint knowledge, 0 <= x1 < x2, should be in City::Bldg ctor
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
    else if ( cmd == "getSkyline" ) {
      handled = true;
      std::cout << "getSkyline" << std::endl;
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
