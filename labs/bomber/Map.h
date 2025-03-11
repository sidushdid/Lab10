#ifndef MAP_H
#define MAP_H

#include <iostream>
#include <string>
#include <iterator>
#include <algorithm>

#include "Point.h"


class Map {
    // Member Variables
    char** map;
    size_t x_size;
    size_t y_size;
public:
    Map(std::istream& stream);
    ~Map();
    // ~Map();

    std::string route(Point src, Point dst);
};

#endif
