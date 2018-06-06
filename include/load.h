#ifndef LOAD_H
#define LOAD_H

#include "cell.h"

/**
 * @brief Initializes a grid from a file
 *
 * @param filename  the name of the data file to be read
 *
 * @return a strucutre representing the first state of the grid
 */
problem load_grid(char filename[100]);

#endif
