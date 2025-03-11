#include "Map.h"

// Member Functions
Map::Map(std::istream& stream){
    y_size = std::count(std::istreambuf_iterator<char>(stream), std::istreambuf_iterator<char>(), '\n');
    std::string temp;
    stream >> temp;
    x_size = temp.size();
    map = new char*[y_size];
    size_t size = 0;
    do{
        map[size] = new char[x_size];
        for(size_t i = 0; i < x_size; i++){
            map[size][i] = temp[i];
        }
    }while(stream >> temp);
}

Map::~Map(){
    for(size_t i = 0; i < y_size; i++){
        delete []map[i];
    }
    delete []map;
}

std::string Map::route(Point src, Point dst){
    return "Stub";
}
