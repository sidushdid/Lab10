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

bool Map::isValid(int y, int x){
    return x >= 0 && x < static_cast<int>(x_size) && y >= 0 && y < static_cast<int>(y_size);
}

bool Map::isWalkable(int y, int x, int bombs, std::unordered_set<std::string> treat_as_ground) {
    if(treat_as_ground.find(y + " " + x) != treat_as_ground.end()) return true;
    char cell = map[y][x];
    if (cell == '~') return false; 
    if (cell == '#' && bombs == 0) return false;
    return true;
}

std::string Map::route(Point src, Point dst){
    if(!isValid(src.lat, src.lng) || !isWalkable(src.lat, src.lng, 0, std::unordered_set<std::string>()))throw PointError(src);//checking for point error of the starting point
    if(!isValid(dst.lat, dst.lng)) throw PointError(dst);//checking for point error of the ending point
    std::string pastPath = std::to_string(src.lng) + " " + std::to_string(src.lat) + " " + std::to_string(dst.lng) + " " + std::to_string(dst.lat);
    if(past.find(pastPath) != past.end()) return past[pastPath]; // Check if we've visited this before

    //std::ofstream out;
    //out.open("output_file.txt");
    std::priority_queue<State> minHeap; //functions as a minHeap calculating for f
    std::unordered_map<std::string, int> visited; //store visited states
    int starting_bomb = 0;
    std::unordered_set<std::string> temp;
    
    if(map[src.lat][src.lng] == '*'){
        starting_bomb ++;
        temp.insert(std::to_string(src.lat) + " " + std::to_string(src.lng));
    } 
    minHeap.push(State(src.lng, src.lat, 0, "", starting_bomb, &dst, temp, 0)); //pushing in the initial state

    while(!minHeap.empty()){
        State curr = minHeap.top();
        minHeap.pop();
        
        if(curr.y == dst.lat && curr.x == dst.lng){
            past[pastPath] = curr.path;

            return curr.path;
        }

        std::string key = std::to_string(curr.y) + "," + std::to_string(curr.x) + "," + std::to_string(curr.bomb);
        if(visited.find(key) != visited.end() && visited[key] <= curr.g){
            continue;
        }

        visited[key] = curr.g;
        
        //debug(curr.path, src.lat, src.lng, out);
        for(size_t i = 0; i < directions.size(); i++){
            int newY = curr.y + directions[i].first;
            int newX = curr.x + directions[i].second;

            if (!isValid(newY, newX) || !isWalkable(newY, newX, curr.bomb, curr.treat_as_ground)) {//check if you can walk there
                continue;
            }

            //updating bomb number
            int newBomb = curr.bomb;
            int newWallEncountered = curr.wall_encountered;
            char cell = map[newY][newX];
            std::unordered_set<std::string> new_treat_as_ground = curr.treat_as_ground;
            
            if(curr.treat_as_ground.find(std::to_string(newY) + " " + std::to_string(newX)) == curr.treat_as_ground.end() && cell == '*'){
                newBomb++;
                new_treat_as_ground.insert(std::to_string(newY) + " " + std::to_string(newX));
            }
            else if(curr.treat_as_ground.find(std::to_string(newY) + " " + std::to_string(newX)) == curr.treat_as_ground.end() && cell == '#'){
                newBomb--;
                new_treat_as_ground.insert(std::to_string(newY) + " " + std::to_string(newX));
                newWallEncountered++;
            }
            
            //update new path
            std::string newPath = curr.path + moves[i];
            
            //updating g
            int newG = curr.g + 1;
            minHeap.push(State(newX, newY, newG, newPath, newBomb, &dst, new_treat_as_ground,newWallEncountered));
        }
    }
    //out.close();
    throw RouteError(src,dst);
}

void Map::print(){
    for(size_t i = 0; i < y_size; i++){
        for(size_t j = 0; j < x_size; j++){
            std::cout << map[i][j];
        }
        std::cout << "\n";
    }
}

void Map::debug(std::string route, int startY, int startX, std::ofstream& out){

    char temp[y_size][x_size];

    for(size_t i = 0 ;i < y_size; i++){

        for(size_t j = 0; j < x_size; j++){

            temp[i][j] = map[i][j];

        }

    }

    int currY = startY;

    int currX = startX;

    temp[currY][currX] = '$';

    for(size_t i = 0; i < route.size(); i++){

        if(route[i] == 'n'){

            currY--;

            temp[currY][currX] = '$';

        }

        else if(route[i] == 's'){

            currY++;

            temp[currY][currX] = '$';

        }

        else if(route[i] == 'e'){

            currX++;

            temp[currY][currX] = '$';

        }

        else if(route[i] == 'w'){

            currX--;

            temp[currY][currX] = '$';

        }

    }

    for(size_t i = 0 ;i < y_size; i++){

        for(size_t j = 0; j < x_size; j++){

            out << temp[i][j];

        }

        out << "\n";

    }

    out  <<"\n";

}
