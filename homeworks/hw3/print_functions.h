#ifndef __PRINT_FUNCTIONS_H__
#define __PRINT_FUNCTIONS_H__

/**
 * \file print_functions.h
 * \brief Provides print-related functionalities
 *
 * \details This header file declares all print-related functionalities for printing the maze, solution, and errors
 */

/**
 * \brief The function to print the maze
 *
 * \details This function takes three parameters: a pointer of a constant array of characters that represents a maze, two constant integers that are the maze's width and height, and it prints the maze on the screen (i.e. stdout).
 * 
 * \param[in] maze        A pointer to a constant 2D array of characters, which represents the maze
 * \param[in] maze_width  A constant integer, which is the maze's width
 * \param[in] maze_height A constant integer, which is the maze's height
 */
void printMaze(char maze[][200], const int maze_width, const int maze_height);

/**
 * \brief The function to print the maze's solution
 *
 * \details This function takes four parameters: a pointer of a constant array of characters that represents a maze, two constant integers that are the maze's width and height, and a pointer to a constant array of characters that represents a solution path. The function prints the maze and the solution path on the screen (i.e. stdout).
 * 
 * \param[in] maze        A pointer to a constant 2D array of characters, which represents the maze
 * \param[in] maze_width  A constant integer, which is the maze's width
 * \param[in] maze_height A constant integer, which is the maze's height
 * \param[in] sol         A pointer to a constant 2D array of characters, which represents a soluton path of the maze
 */
void printSolution(char maze[][200], const int maze_width, const int maze_height, char sol[][200]);

/**
 * \brief The function to print the error message
 *
 * \details This function takes two parameters: a constant integer that is a return code and an array of c-strings that is the input command line arguments. The function prints the corresponding error messages based on the input return code to the screen (i.e. stdout).
 * 
 * \param[in] return_code A constant integer, which is the return code of the program        
 * \param[in] argv        An array of c-strings, which is the input command line arguments
 */
void printError(const int return_code, char* argv[]);

#endif // __PRINT_FUNCTIONS_H__
