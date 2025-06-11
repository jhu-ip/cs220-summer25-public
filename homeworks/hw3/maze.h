#ifndef __MAZE_H__
#define __MAZE_H__

/**
 * \file maze.h
 * \brief Provides maze-related functionalities
 *
 * \details This header file declares all maze-related functionalities for reading/writing/solving/generating the maze and releasing related memories.
 */

/**
 * \brief The function to read the maze from a file
 *
 * \details This function takes four parameters: the name of the file to read, the maze itself, and the maze's width and height. The function reads the file, filling in maze's data, width and height. It returns 0 on success, -1 if failed to open the file to read, or -2 if encountering any other read error.
 */
// TODO: write the readMaze function declaration

/**
 * \brief The function to write the maze to a file
 *
 * \details This function takes four parameters: the name of the file to write, the maze itself, and the maze's width and height. The function writes the maze's data, width and height to the specified file. It returns 0 on success, -4 if failed to open the file to write, or -5 if encountering any other write error.
 */
// TODO: write the writeMaze function declaration

/**
 * \brief The function to solve a solution path for the maze
 *
 * \details This function takes four parameters: a constant pointer to the maze (which is a pointer to an array of characters), two constant integers that are the maze's width and height, and a pointer to the solution path (which is a pointer to an array of characters). The function allocates memory for the solution path, and calls solvePath to find a solution path for the maze. It returns 0 if a solution path is found; otherwise return 1.
 * 
 * \param[in]   maze          A 2D character array, which is the maze representation
 * \param[in]   maze_width    A constant integer, which is the maze's width
 * \param[in]   maze_height   A constant integer, which is the maze's height
 * \param[out]  sol           A 2D character array, which is the maze solution
 *
 * \return  The return code of the function
 * \retval  0  if a solution path is found
 * \retval  1  if no solution path is found
 */
int solveMaze(char maze[][200], const int maze_width, const int maze_height, char sol[][200]);

/**
 * \brief The function to solve a solution path recursively
 *
 * \details This function takes six parameters: a constant 2D character array that is the  maze, two constant integers that are the maze's width, two constant integers that are the current column and row positions, and a 2D array that is the maze with a path from the start position to the current position. The function checks if the current path leads to a complete solution path. It returns 0 if a solution path is found; otherwise it extends the current path to its neighbor (strictly following this order: left, right, up, down) and recursively calls solvePath to find a solution path.  If no solution path is found, it returns 1.
 * 
 * \param[in]     maze          A 2D array of characters that represents the maze's data
 * \param[in]     maze_width    A constant integer, which is the maze's width
 * \param[in]     maze_height   A constant integer, which is the maze's height
 * \param[in]     col           A constant integer, which is the current column position
 * \param[in]     row           A constant integer, which is the current row position
 * \param[in,out] sol           A 2D array of characters that represents a path from start position to current position
 *
 * \return  The return code of the function
 * \retval  0  if a solution path is found
 * \retval  1  if no solution path is found
 */
int solvePath(char maze[][200], const int maze_width, const int maze_height, const int col, const int row, char sol[][200]);

/**
 * \brief The function to generate a maze
 *
 * \details This function takes five parameters: a 2D array of characters that represents the maze to be generated, two constant integers that are the maze's width, a constant double that is a threshold to determine whether a position is a wall, and a constant integer that specifies the seed for C pseudorandom number generator. The function generates the start and target positions, and the maze's walls using C pseudorandom number initialized by the input seed. The wall generation is determined by the input threshold.
 * 
 * \param[out]  maze          A 2D array of characters that represents the maze's data
 * \param[in]   maze_width    A constant integer, which is the maze's width
 * \param[in]   maze_height   A constant integer, which is the maze's height
 * \param[in]   threshold     A constant double, which is the threshold used to determine if a wall should be generated
 * \param[in]   seed          A constant integer, which is the seed for C pseudorandom number generator
 */
void genMaze(char maze[][200], const int maze_width, const int maze_height, const double threshold, const int seed);

#endif // __MAZE_H__
