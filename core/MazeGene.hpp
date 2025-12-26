#ifndef MAZEGENE_HPP
#define MAZEGENE_HPP
#include "MazeGenerator.hpp"
#include <random>
#include <vector>
#include <utility>


class MazeGene: public MazeGenerator{
public:
    void generateMaze(Maze& maze) override;
    void recursiveAlgorithm(Maze& m, std::default_random_engine& e, std::uniform_int_distribution<int>& d, int x, int y); // The recursive function the build up the maze
    bool checkVisit(std::pair<int, int> p); // check  whether the cell entered is in the visited vector
    bool checkWalls(Maze& ma, const int x, const int y);   //check whether all four direction of the current cell could be able to remove the wall but doesn't violate our maze.
private:
    std::vector<std::pair<int, int>> visited;  //A container to record whether a cell is visited or not
};

#endif