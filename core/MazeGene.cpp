#include "MazeGene.hpp"
#include "Maze.hpp"
#include <random>
#include <ics46/factory/DynamicFactory.hpp>
#include "Direction.hpp"

ICS46_DYNAMIC_FACTORY_REGISTER(MazeGenerator, MazeGene, "My generator(Required)");

//The main function that we are going to use to generate a maze
void MazeGene::generateMaze(Maze& maze) {
    maze.addAllWalls();
    std::random_device device;
    std::default_random_engine engine{device()};
    //choose 1 out of 4 walls and remove one of them
    std::uniform_int_distribution<int> distribution{1,4};
    recursiveAlgorithm(maze,engine, distribution, 0, 0);

}

void MazeGene::recursiveAlgorithm(Maze& m, std::default_random_engine& e, std::uniform_int_distribution<int>& d, int x, int y){
    //Add the pair into our visited vector
    if(!checkVisit(std::make_pair(x,y))){
        visited.push_back(std::make_pair(x,y));
    }
    //Handle the case that when all the cells are visited
    if(visited.size() == m.getHeight()*m.getWidth()){
        return;
    }
    int number = d(e);
    if(number == 1 && x !=0 && m.wallExists(x,y, Direction::left)&& !checkVisit(std::make_pair(x-1, y))){
        m.removeWall(x,y, Direction::left);
        
        recursiveAlgorithm(m, e, d, x-1, y);
    }
    //Handle the case of removing the down wall
    if(number == 2 && y != m.getHeight()-1 && m.wallExists(x,y, Direction::down) && !checkVisit(std::make_pair(x,y+1))){

        m.removeWall(x,y, Direction::down);
        recursiveAlgorithm(m, e, d, x, y+1);
    }
    //Handle the case of removing the right wall
    if(number ==3 && x != m.getWidth()-1 && m.wallExists(x,y, Direction::right) && !checkVisit(std::make_pair(x+1, y))){
        m.removeWall(x,y, Direction::right);
        recursiveAlgorithm(m, e, d,x+1, y);
    }
    //Handle the case of removing the up wall
    if(number ==4 && y != 0 && m.wallExists(x,y, Direction::up)&& !checkVisit(std::make_pair(x, y-1))){
        m.removeWall(x,y, Direction::up);
        recursiveAlgorithm(m, e, d, x, y-1);
    }
    //Handle the cases of rest of adjacent walls that may be existed
    if(!checkWalls(m, x, y)){
        recursiveAlgorithm(m,e,d,x,y);
    }
    
    
    
}

bool MazeGene::checkVisit(std::pair<int, int> p){
    //See if the provided pairs are in the vector visited
    for(int i=0;i<visited.size();i++){
        if(p.first == visited[i].first && p.second == visited[i].second){
            return true;
        }
    }
    return false;
}

bool MazeGene::checkWalls(Maze& ma, const int x, const int y){
    //check whether the four cells around are visited or not
    //It returns true if all the cells around are visited.
    int count =0;
    if (x==0 || checkVisit(std::make_pair(x-1,y))){
        count++;
    }
    if (x==ma.getWidth()-1 || checkVisit(std::make_pair(x+1,y))){
        count++;
    }
    if (y==0 || checkVisit(std::make_pair(x,y-1))){
        count++;
    }
    if (y==ma.getHeight()-1 || checkVisit(std::make_pair(x,y+1))){
        count++;
    }
    if(count == 4){
        return true;
    }
    return false;
    
}
