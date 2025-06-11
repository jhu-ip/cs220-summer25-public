#include "maze.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/**
 * \file maze.c
 * \brief Provides maze-related functionalities
 *
 * \details This source file implements all maze-related functionalities for reading/writing/solving/generating the maze and releasing related memories.
 */

/* The function to read the maze from a file given the filename, maze
   array, maze width and maze height: open file, read sizes, read maze, close file
*/
// TODO: write the entirety of this readMaze function


/* The function to write the maze to a file given the filename, maze
   array, maze width and maze height: open file, write maze, close file
*/
// TODO: write the entirety of this writeMaze function


// The function to solve a solution path for the maze
int solveMaze(char maze[][200], const int maze_width, const int maze_height, char sol[][200]) {
  // TODO: implement this function
  return solvePath(maze, maze_width, maze_height, 0, 0, sol); // TODO: replace this stub
}

// The function to solve a solution path recursively
int solvePath(char maze[][200], const int maze_width, const int maze_height, const int col, const int row, char sol[][200]) {
  // TODO: implement this function
  return 0; // TODO: replace this stub
}

// The function to generate a maze (given)
void genMaze(char maze[][200], const int maze_width, const int maze_height, const double threshold, const int seed) {
  // set random seed
  srand(seed);
  // gen start and end positions
  int start_x = rand() % (maze_width - 2) + 1;
  int start_y = rand() % (maze_height - 2) + 1;
  int end_x = rand() % (maze_width - 2) + 1;
  int end_y = rand() % (maze_height - 2) + 1;
  // gen maze
  for (int r = 0; r < maze_height; ++r) {
    for (int c = 0; c < maze_width; ++c) {
      if (r == 0 || c == 0 || r == maze_height - 1 || c == maze_width - 1) maze[r][c] = '#';
      else if (c == start_x && r == start_y) maze[r][c] = '@';
      else if (c == end_x && r == end_y) maze[r][c] = '<';
      else {
        double rand_value = rand() / (double) RAND_MAX;
        if (rand_value >= threshold) maze[r][c] = '#';
        else maze[r][c] = ' ';
      }
    }
  }
}

