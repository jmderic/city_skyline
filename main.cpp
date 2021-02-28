/* Copyright 2013-2021 J. Mark Deric */
#include "City.h"

#include <iostream>  // std::cin, std::cout
#include <string>
#include <boost/regex.hpp>
#include <boost/lexical_cast.hpp>

bool get_bldg_coords(int (&bldg_coords)[3], std::string& remnant) {
    static boost::regex e("^\\h*(\\d+)\\h+(\\d+)\\h+(\\d+)\\h*$");
    bool gotten = false;
    std::getline(std::cin, remnant);
    if ( !std::cin.good() ) {
        remnant += " <cin stream fails>";
        std::cin.clear();
    } else if ( !remnant.empty() ) {
        boost::smatch what;
        if ( boost::regex_match(remnant, what, e ) ) {
            for ( int i = 0; i < 3; ++i ) {
                // should catch for value > INT_MAX
                bldg_coords[i] = boost::lexical_cast<int>(what[i+1]);
            }
            if ( 0 <= bldg_coords[0] && bldg_coords[0] < bldg_coords[1]
                 && 0 < bldg_coords[2] ) {
                // constraint knowledge, 0 <= x1 < x2 and y > 0, should be in
                // City::Bldg ctor
                gotten = true;
            }
        }
    }
    return gotten;
}

int main(int, char**) {
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
        } else if ( cmd == "addBldg" ) {
            int bldg_coords[3];
            if ( get_bldg_coords(bldg_coords, remnant) ) {
                c.addBldg(bldg_coords[0], bldg_coords[1], bldg_coords[2]);
                std::cout << "addBldg [x1, x2, y] = [" << bldg_coords[0] << ", "
                    << bldg_coords[1] << ", " <<  bldg_coords[2] << ']'
                    << std::endl;
                handled = true;
            }
        } else if ( cmd == "getSkyline" ) {
            City::Skyline skyline;
            c.getSkyline(skyline);
            std::cout << "getSkyline\n" << skyline << std::endl;
            handled = true;
        } else {
            std::getline(std::cin, remnant);
        }
        if ( !handled ) {
            std::cout << "command error \"" << (cmd + remnant)
                << "\", quit to exit" << std::endl;
        }
    }
    return 0;
}
