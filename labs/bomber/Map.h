#ifndef MAP_H
#define MAP_H

#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <queue>
#include <unordered_map>

#include "Point.h"
#include "Errors.h"

class Map {
    // Member Variables
    const std::vector<std::pair<int, int>> directions = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}};
    const std::vector<char> moves = {'n', 'e', 's', 'w'};
    char** map;
    size_t x_size;
    size_t y_size;
    struct State{
        int x, y;
        int g;
        int f;
        std::string path;
        int bomb;
        Point* goal;
        State(int x, int y, int g, std::string path, int bomb, Point* goal) : x(x), y(y), g(g), path(path), bomb(bomb), goal(goal) {
            f = g + manhattanDistance();
        }

        int manhattanDistance() const {
            return std::abs(x - goal->lat) + std::abs(y - goal->lng);
        }

        bool operator<(const State& other) const {
            return f > other.f;  // Min-heap: smaller f has higher priority
        }
    };
private:
//helper function
    bool isValid(int x, int y);
    bool isWalkable(int x, int y, int bombs);
public:
    Map(std::istream& stream);
    ~Map();
    void print();
    std::string route(Point src, Point dst);
};

#endif
