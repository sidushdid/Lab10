#include "Map.h"

// Member Functions
Map::Map(std::istream& stream){
    std::istream temp_stream = stream;
    std::string temp;
    y_size = 0;
    while(temp_stream >> temp){
        y_size ++;
    }
    stream >> temp;
    x_size = temp.size();
    size_t size = 0;
    do{
        for(int i = 0; i < x_size; i++){
            map[size][i] = temp[i];
        }
    }while(stream >> temp);
}