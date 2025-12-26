#include "Solution.hpp"
#include <ics46/factory/DynamicFactory.hpp>
#include "Direction.hpp"
#include <vector>
#include "Maze.hpp"
#include <iostream>
ICS46_DYNAMIC_FACTORY_REGISTER(MazeSolver, Solution, "My solution(Required)");

void Solution::solveMaze(const Maze& maze, MazeSolution& mazeSolution){
    recursiveAlgorithm(maze, mazeSolution);
}

//This function returns false if there is no way to go at the end of the path or the solution is completed
bool Solution::recursiveAlgorithm(const Maze& mz, MazeSolution& ms){
    if (!ms.isComplete()){
        std::vector<Direction> movement = ms.getMovements();
        std::pair<int, int> p = ms.getCurrentCell();
        int count = 0;
        //These if statements help to handle four directions when we get to a cell.
        //It determines whether it's possible to go in each way.
        if(!mz.wallExists(p.first, p.second, Direction::right) && ( movement.size() == 0 || movement[movement.size()-1] != Direction::left )){
            
            if(ms.isComplete()){
                return true;
            }
            ms.extend(Direction::right);
            if(!recursiveAlgorithm(mz, ms)){
                ms.backUp();
            }
            else{
                count++;
            }
            
            
        }
        if(!mz.wallExists(p.first, p.second, Direction::left) && (movement.size() == 0 || movement[movement.size()-1] != Direction::right)){
            
            if(ms.isComplete()){
                return true;
            }
            ms.extend(Direction::left);
            if (!recursiveAlgorithm(mz, ms)){
                ms.backUp();
            }
            else{
                count++;
            }
            
        }
        if(!mz.wallExists(p.first, p.second, Direction::up)&& (movement.size() == 0 || movement[movement.size()-1] != Direction::down)){
            
            if(ms.isComplete()){
                return true;
            }
            ms.extend(Direction::up);
            if(!recursiveAlgorithm(mz, ms)){
                ms.backUp();
            }
            else{
                count++;
            }
            
        }
        if(!mz.wallExists(p.first, p.second, Direction::down) && (movement.size() == 0 || movement[movement.size()-1] != Direction::up)){
            
            if(ms.isComplete()){
                return true;
            }
            ms.extend(Direction::down);
            if(!recursiveAlgorithm(mz, ms)){
                ms.backUp();
            }
            else{
                count++;
            } 
                    
        }
        //If none of the direction could be a potential way to go, then it just return false and backUp.
        if(count == 0){
            return false;
        }
    }
    return true;
}
