#ifndef CITY_HPP__
#define CITY_HPP__

#include <list>
#include <iosfwd>
#include <memory>

class City
{
public:
    City();
    ~City();
    struct Point {
        Point(int x, int y);
        int x_;
        int y_;
    };
    using Skyline = std::list<Point>;
    //typedef std::list<Point> Skyline;
    void addBldg(int x1, int x2, int y);
    void getSkyline(Skyline& skyline) const;
private:
    class impl;
    std::unique_ptr<impl> pimpl_;
};

std::ostream& operator<<(std::ostream& os, const City::Point& pt);
std::ostream& operator<<(std::ostream& os, const City::Skyline& skyline);

#endif // CITY_HPP__
