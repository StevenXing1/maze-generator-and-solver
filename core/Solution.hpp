#ifndef SOLUTION_HPP
#define SOLUTION_HPP
#include "MazeSolver.hpp"
#include "MazeSolution.hpp"

class Solution:public MazeSolver{
public:
    void solveMaze(const Maze& maze, MazeSolution& mazeSolution) override;
    bool recursiveAlgorithm(const Maze& mz, MazeSolution& ms);          //The recursive algorithm we are going to utilize
};
#endif