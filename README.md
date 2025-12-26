# Maze Generator and Solver

A C++ implementation of a recursive maze generator and solver with an interactive graphical user interface. This project demonstrates advanced algorithms including recursive backtracking for maze generation and depth-first search for maze solving.

##  Table of Contents
- [Overview](#overview)
- [Features](#features)
- [Project Structure](#project-structure)
- [Algorithm Details](#algorithm-details)
- [Getting Started](#getting-started)
- [Usage](#usage)
- [Implementation Details](#implementation-details)
- [Requirements](#requirements)
- [License](#license)

##  Overview

This project implements both a maze generator and solver using recursive algorithms. The maze generator creates perfect mazes (mazes with exactly one path between any two cells) using a recursive backtracking algorithm. The solver then finds the path from the start to the end using depth-first search with backtracking.

The project was developed as part of the ICS 46 course (Winter 2022, Project #1: Dark at the End of the Tunnel) and showcases fundamental computer science concepts including recursion, backtracking, and graph traversal.

##  Features

- **Perfect Maze Generation**: Creates mazes with exactly one solution path between any two cells
- **Recursive Backtracking Algorithm**: Generates random, solvable mazes using depth-first search
- **Intelligent Maze Solver**: Automatically finds the solution path from start to finish
- **Unsolvable Maze Detection**: Identifies and reports when a maze has no solution
- **Graphical User Interface**: Interactive visualization of maze generation and solving
- **Dynamic Factory Pattern**: Uses ICS 46 DynamicFactory for flexible component registration
- **Customizable Maze Size**: Supports variable width and height dimensions
- **Unit Testing Support**: Integrated Google Test framework

##  Project Structure

```
maze-generator-and-solver/
 app/
    main.cpp              # Main application with GUI launcher
 core/
    MazeGene.hpp          # Maze generator class header
    MazeGene.cpp          # Maze generation implementation
    Solution.hpp          # Maze solver class header
    Solution.cpp          # Maze solving implementation
 exp/
    expmain.cpp           # Experimental testing environment
 gtest/
    gtestmain.cpp         # Google Test runner
 README.md                 # Project documentation
```

### Directory Descriptions

- **app/**: Contains the main application launcher with GUI integration
- **core/**: Core maze generation and solving algorithms
- **exp/**: Experimental environment for testing algorithms independently
- **gtest/**: Unit testing framework and test cases

##  Algorithm Details

### Maze Generation: Recursive Backtracking

The maze generator uses a **recursive backtracking algorithm** (also known as depth-first search) to create perfect mazes:

#### Algorithm Steps:

1. **Initialize**: Start with a grid where all walls are present
2. **Mark Start Cell**: Begin at cell (0, 0) and mark it as visited
3. **Random Direction Selection**: Randomly choose one of four directions (up, down, left, right)
4. **Validate Move**:
   - Check if the neighbor cell is within bounds
   - Verify the neighbor hasn''t been visited yet
   - Ensure a wall exists to remove
5. **Carve Path**: Remove the wall between current and neighbor cells
6. **Recursive Call**: Move to the neighbor cell and repeat
7. **Backtrack**: If all neighbors are visited, return to previous cell
8. **Complete**: Algorithm finishes when all cells have been visited

#### Key Characteristics:
- **Time Complexity**: O(W  H) where W is width and H is height
- **Space Complexity**: O(W  H) for visited cells tracking
- **Guarantee**: Always produces a perfect maze (one unique path between any two cells)

### Maze Solving: Depth-First Search with Backtracking

The maze solver uses **depth-first search (DFS)** with backtracking to find the solution path:

#### Algorithm Steps:

1. **Start Position**: Begin at the maze entrance
2. **Try Directions**: Attempt to move in all valid directions (right, left, up, down)
3. **Wall Check**: Only move if no wall blocks the direction
4. **Avoid Backtracking**: Don''t immediately return to the previous cell
5. **Mark Path**: Extend the solution path as you explore
6. **Check Completion**: Test if the exit has been reached
7. **Backtrack on Dead End**: If no valid moves exist, back up one step
8. **Repeat**: Continue until solution is found or all paths exhausted

#### Key Characteristics:
- **Time Complexity**: O(W  H) in worst case
- **Space Complexity**: O(W  H) for recursion stack
- **Path Quality**: Finds a solution but not necessarily the shortest path
- **Dead End Handling**: Automatically backtracks when reaching dead ends

##  Getting Started

### Prerequisites

- C++11 or later compiler (g++, clang++, MSVC)
- ICS 46 libraries (Maze, MazeGenerator, MazeSolver, etc.)
- Qt or equivalent GUI framework
- Google Test framework (for unit testing)

### Building the Project

```bash
# Extract project files (if not already extracted)
tar -xzf maze_generator_and_solver.tar.gz

# Build with g++ (example)
g++ -std=c++11 -o maze app/main.cpp core/MazeGene.cpp core/Solution.cpp -lics46 -lQt5Core -lQt5Gui -lQt5Widgets
```

### Running Tests

```bash
# Build and run Google Tests
g++ -std=c++11 -o test_runner gtest/gtestmain.cpp core/MazeGene.cpp core/Solution.cpp -lgtest -lics46
./test_runner
```

##  Usage

### Running the Application

1. Launch the application:
   ```bash
   ./maze
   ```

2. The GUI will open with options to:
   - Set maze dimensions (width and height)
   - Generate a new random maze
   - Solve the generated maze
   - Visualize the generation and solving process

### Using the Maze Generator

The generator creates a perfect maze starting from the top-left corner (0, 0):

```cpp
MazeGene generator;
Maze maze(width, height);
generator.generateMaze(maze);
```

### Using the Maze Solver

The solver finds a path from start to finish:

```cpp
Solution solver;
MazeSolution solution;
solver.solveMaze(maze, solution);

if (solution.isComplete()) {
    // Solution found!
} else {
    // No solution exists
}
```

##  Implementation Details

### MazeGene Class

The `MazeGene` class handles maze generation:

```cpp
class MazeGene : public MazeGenerator {
public:
    void generateMaze(Maze& maze) override;
    
private:
    void recursiveAlgorithm(Maze& m, std::default_random_engine& e,
                          std::uniform_int_distribution<int>& d,
                          int x, int y);
    bool checkVisit(std::pair<int, int> p);
    bool checkWalls(Maze& ma, const int x, const int y);
    
    std::vector<std::pair<int, int>> visited;
};
```

#### Key Methods:

- **`generateMaze()`**: Entry point that initializes the maze with all walls
- **`recursiveAlgorithm()`**: Core recursive function that carves paths
- **`checkVisit()`**: Verifies if a cell has been visited
- **`checkWalls()`**: Checks if all adjacent cells are visited

### Solution Class

The `Solution` class implements the maze solver:

```cpp
class Solution : public MazeSolver {
public:
    void solveMaze(const Maze& maze, MazeSolution& mazeSolution) override;
    
private:
    bool recursiveAlgorithm(const Maze& mz, MazeSolution& ms);
};
```

#### Key Methods:

- **`solveMaze()`**: Entry point for solving the maze
- **`recursiveAlgorithm()`**: Recursive DFS implementation with backtracking
  - Returns `true` if a solution path is found
  - Returns `false` if the current path leads to a dead end

### Factory Registration

Both classes are registered with the ICS 46 DynamicFactory:

```cpp
ICS46_DYNAMIC_FACTORY_REGISTER(MazeGenerator, MazeGene, "My generator(Required)");
ICS46_DYNAMIC_FACTORY_REGISTER(MazeSolver, Solution, "My solution(Required)");
```

##  Algorithm Visualization

### Maze Generation Process

```
1. Start: All walls present    2. Random carving begins    3. Backtracking occurs
                                           
                                                
                                              
                                                
                                           
```

### Maze Solving Process

```
1. Start at entrance          2. Explore paths            3. Backtrack on dead end
                                     
   S                       S                     S     
                                             X  
          E                      E                    E
                                     
```

##  Requirements

- **C++ Standard**: C++11 or later
- **Dependencies**:
  - ICS 46 libraries (`ics46/factory/DynamicFactory.hpp`)
  - Maze, MazeGenerator, MazeSolver base classes
  - Direction enum for movement representation
  - DarkApplication (GUI framework)
  - Google Test (for testing)

##  Educational Value

This project demonstrates several important computer science concepts:

- **Recursion**: Both generation and solving use recursive algorithms
- **Backtracking**: Essential for exploring paths and returning when stuck
- **Graph Traversal**: Mazes are represented as graphs with DFS traversal
- **Random Algorithms**: Maze generation uses randomness for variety
- **State Management**: Tracking visited cells and solution paths
- **Object-Oriented Design**: Clean separation of concerns with interfaces

##  License

This project was created as part of the ICS 46 coursework at UC Irvine (Winter 2022, Project #1). Please refer to your institution''s academic integrity policies regarding the use and distribution of coursework.

##  Future Enhancements

Potential improvements for the maze generator and solver:

### Generation Enhancements:
- **Prim''s Algorithm**: Alternative maze generation approach
- **Kruskal''s Algorithm**: Using minimum spanning tree
- **Eller''s Algorithm**: Row-by-row generation
- **Weighted Cells**: Variable difficulty paths

### Solving Enhancements:
- **Breadth-First Search**: Find shortest path
- **A* Algorithm**: Optimal pathfinding with heuristics
- **Dijkstra''s Algorithm**: Weighted path finding
- **Bidirectional Search**: Search from both ends simultaneously
- **Multiple Solutions**: Find all possible paths

### Visualization:
- **Animation Speed Control**: Adjustable generation/solving speed
- **Step-by-Step Mode**: Manual stepping through algorithm
- **Color-Coded Paths**: Different colors for explored vs solution paths
- **Statistics Display**: Show algorithm performance metrics

##  Author

Created for ICS 46 Project #1: Dark at the End of the Tunnel

---

**Happy Maze Solving! **
