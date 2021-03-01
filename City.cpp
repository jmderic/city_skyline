/* Copyright 2013-2021 J. Mark Deric */

#include "City.h"
#include <map>  // multimap
#include <utility>  // pair
#include <list>

class City::impl {
 public:
    void addBldg(int x1, int x2, int y) {
        bldgs.push_back(Bldg(x1, x2, y));
    }
    void getSkyline(City::Skyline& skyline) const {
        BData xdata, ydata;
        // fill the xdata multimap two entries per building: one key for the
        // leading edge; the other key, trailing; the building is the value for
        // both entries
        std::list<Bldg>::const_iterator b_it, b_endit = bldgs.end();
        for ( b_it=bldgs.begin(); b_it != b_endit; ++b_it ) {
            xdata.insert(std::make_pair(b_it->x1_, *b_it));
            xdata.insert(std::make_pair(b_it->x2_, *b_it));
        }
        // walk the x values in order, adding or deleting a building from the
        // ydata collection for each node.  Report changes in the largest y
        // value; those changes define the skyline.
        BData::const_iterator x_it, nextx_it, x_endit = xdata.end(), y_it;
        int last_y = 0;
        for ( x_it=xdata.begin(), nextx_it = x_it; x_it != x_endit; ++x_it ) {
            int this_x = x_it->first;
            const Bldg& b = x_it->second;
            if (this_x == b.x1_) {  // start of building insert it
                ydata.insert(std::make_pair(b.y_, b));
            } else {  //  this_x == b.x2_ end of building erase it
                std::pair<BData::iterator, BData::iterator> eq_y =
                    ydata.equal_range(b.y_);
                // several buildings could have this y value, erase the right
                // one
                for ( ; eq_y.first != eq_y.second; ++(eq_y.first) ) {
                    if ( eq_y.first->second == b ) {
                        ydata.erase(eq_y.first);
                        break;
                    }
                }
            }
            if ( ++nextx_it == x_endit || nextx_it->first != this_x ) {
                // the next x value is the end _or_ it is different from this
                // one; so test now whether y max changed, generate a result if
                // it did
                City::Point pt(this_x, 0);
                if ( ydata.begin() != (y_it=ydata.end()) ) {
                    pt.y_ = (--y_it)->first;
                }
                if ( pt.y_ != last_y ) {
                    skyline.push_back(pt);
                    last_y = pt.y_;
                }
            }
        }
        Point first = skyline.front();
        first.y_ = 0;
        skyline.push_front(first);
    }
 private:
    struct Bldg {
        Bldg(int x1, int x2, int y) : x1_(x1), x2_(x2), y_(y) {}
        bool operator==(const Bldg& rhs) {
            return ( x1_ == rhs.x1_ && x2_ == rhs.x2_ && y_ == rhs.y_ );
        }
        int x1_;
        int x2_;
        int y_;
    };
    typedef std::multimap<int, Bldg> BData;
    std::list<Bldg> bldgs;
};

// connectors to the city class and trivial implementations
City::City() : pimpl_(new City::impl()) {}

City::~City() = default;

City::Point::Point(int x, int y) : x_(x), y_(y) {}

void City::addBldg(int x1, int x2, int y) {
    pimpl_->addBldg(x1, x2, y);
}

void City::getSkyline(Skyline& skyline) const {
    pimpl_->getSkyline(skyline);
}
