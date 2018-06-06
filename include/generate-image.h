#ifndef GENERATE_IMAGE_H
#define GENERATE_IMAGE_H

#include "cell.h"

/**
 * @brief Generates the .ppm image corresponding to the state of the list
 *
 * @param p_list  a pointer to a list of cells
 *
 * @param size_x  the width of the grid
 *
 * @param size_y  the height of the grid
 *
 * @param index  the number of the current iteration
 */
void write_file(list *p_list, int size_x, int size_y, int index);

#endif
