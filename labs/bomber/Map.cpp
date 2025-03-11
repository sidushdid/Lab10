#include "Map.h"

// Member Functions
Map::Map(std::istream& stream){
    
    std::vector<std::string> vect;
    std::string temp;
    while(stream >> temp){
        vect.push_back(temp);
    }
    y_size = vect.size();
    x_size = vect[0].size();
    map = new char*[y_size];
    for(size_t i = 0; i < y_size; i++){
        map[i] = new char[x_size];
        for(size_t j = 0; j < x_size; j++){
            map[i][j] = vect[i][j];
        }
    }
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

void Map::print(){
    for(size_t i = 0; i < y_size; i++){
        for(size_t j = 0; j < x_size; j++){
            std::cout << map[i][j];
        }
        std::cout << "\n";
    }
}

