// -*- c-basic-offset: 2 -*-

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
    // fill the xdata multimap two entries per building: one key for the leading
    // edge; the other key, trailing; the building is the value for both entries
    std::list<Bldg>::const_iterator b_it, b_endit=bldgs.end();
    for ( b_it=bldgs.begin(); b_it!=b_endit; ++b_it ) {
      xdata.insert(std::make_pair(b_it->x1_, *b_it));
      xdata.insert(std::make_pair(b_it->x2_, *b_it));
    }
    // walk the x values in order, adding or deleting a building from the ydata
    // collection for each node.  Report changes in the largest y value; those
    // changes define the skyline.
    BData::const_iterator x_it, nextx_it, x_endit=xdata.end(), y_it;
    int last_y = 0;
    for ( x_it=xdata.begin(), nextx_it=x_it; x_it!=x_endit; ++x_it ) {
      int this_x = x_it->first;
      const Bldg& b = x_it->second;
      if (this_x == b.x1_) { // start of building (leading edge) insert it
        ydata.insert(std::make_pair(b.y_, b));
      }
      else { //  this_x == b.x2_ end of building (trailing edge) erase it
        std::pair<BData::iterator, BData::iterator> eq_y =
          ydata.equal_range(b.y_);
        // several buildings could have this y value, erase the right one
        for ( ; eq_y.first!=eq_y.second; ++(eq_y.first) ) {
          if ( eq_y.first->second == b ) {
            ydata.erase(eq_y.first);
            break;
          }
        }
      }
      if ( ++nextx_it == x_endit || nextx_it->first != this_x ) {
        // the next x value is the end _or_ it is different from this one;
        // so test now whether y max changed, generate a result if it did
        Point pt(this_x, 0);
        if ( ydata.begin() != (y_it=ydata.end()) ) {
          pt.y_ = (--y_it)->first;
        }
        if ( pt.y_ != last_y ) {
          skyline.push_back(pt);
          last_y = pt.y_;
        }
      }
    }
  }
private:
  typedef std::multimap<int, Bldg> BData;
  std::list<Bldg> bldgs;
};

#include <ostream>

std::ostream& operator<<(std::ostream& os, const City::Point& pt) {
  os << '[' << pt.x_ << ", " << pt.y_ << ']';
  return os;
}

std::ostream& operator<<(std::ostream& os, const City::Skyline& skyline) {
  City::Skyline::const_iterator skl_it = skyline.begin(),
    skl_beginit = skl_it, skl_endit = skyline.end();
  for ( ; skl_it!=skl_endit; ++skl_it ) {
    if ( skl_it!=skl_beginit )
      os << ", ";
    os << *skl_it;
  }
  return os;
}

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
      if ( 0 <= bldg_coords[0] && bldg_coords[0] < bldg_coords[1]
           && 0 < bldg_coords[2] ) {
        // constraint knowledge, 0 <= x1 < x2 and y > 0, should be in City::Bldg
        // ctor
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
      std::cout << "done" << std::endl;
      quit = handled = true;
    }
    else if ( cmd == "addBldg" ) {
      int bldg_coords[3];
      if ( get_bldg_coords(bldg_coords, remnant) ) {
        c.addBldg(bldg_coords[0], bldg_coords[1], bldg_coords[2]);
        std::cout << "addBldg [x1, x2, y] = [" << bldg_coords[0] << ", "
          << bldg_coords[1] << ", " <<  bldg_coords[2] << ']' << std::endl;
        handled = true;
      }
    }
    else if ( cmd == "getSkyline" ) {
      City::Skyline skyline;
      c.getSkyline(skyline);
      std::cout << "getSkyline\n" << skyline << std::endl;
      handled = true;
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
