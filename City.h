/* Copyright 2013-2021 J. Mark Deric */
#ifndef CITY_H_
#define CITY_H_

#include <list>
#include <memory>

class City {
 public:
    City();
    ~City();
    struct Point {
        Point(int x, int y);
        int x_;
        int y_;
    };
    using Skyline = std::list<Point>;
    void addBldg(int x1, int x2, int y);
    void getSkyline(Skyline& skyline) const;
 private:
    class impl;
    std::unique_ptr<impl> pimpl_;
};

#endif  // CITY_H_
