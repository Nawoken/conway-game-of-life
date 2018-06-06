#ifndef CELL_H
#define CELL_H

/**
 * @brief The different statuses for the cells
 */
typedef enum {
    ALIVE,
    NEWBORN,
    DYING
} status;

/**
 * @brief An alias to the struct representing the (x,y) position of a cell
 */
typedef struct position position;

/**
 * @brief An alias to the struct representing a cell
 */
typedef struct cell cell;

/**
 * @brief An alias to the struct representing a cell (element) of the linked list of cells
 */
typedef struct elem elem;

/**
 * @brief An list of cells is just a pointer to the first element
 */
typedef elem * list;

/**
 * @brief An alias to the struct representing the grid
 */
typedef struct problem problem;

/**
 * @brief An structure representing a (x,y) position on the grid
 */
struct position {
	int x;
	int y;
};

/**
 * @brief An structure representing a cell : its status, its position 
 * on the grid and pointers to its 8 neighbors
 */
struct cell {
    status status;
    position pos;
    cell *neighbors[8];
};

/**
 * @brief An structure representing an element of the linked list of cells
 */
struct elem {
    cell cell;
    elem *next;
};

/**
 * @brief An structure representing the grid : its width and height, the number 
 * of iterations to be made in the game and the list of cells
 */
struct problem {
    int size_x;
	int size_y;
    int nb_steps;
    list cell_list;
};

/**
 * @brief Initializes a pointer to a list of cells to NULL
 *
 * @param p_list  a pointer to a list of cells
 */
void nil(list *p_list);

/**
 * @brief Prints the position and status of each cell in the list
 *
 * @param list  a list of cells
 */
void print_list(list cell_list);

/**
 * @brief Returns a position delta for the i-th neighbor
 *
 * @param  i an int representing the neighbor number
 *                  (0 : cell directly underneath the
 *                  current cell then up anti-clockwise)
 *
 * @return a position
 */
position delta(int i);

/**
 * @brief Adds my_cell at the beginning of the list
 *
 * @param p_list  a pointer to a list of cells
 *
 * @param my_cell  the cell to be added
 */
void cons(list *p_list, cell my_cell);

/**
 * @brief Returns a pointer to a cell of the list which position is (x,y)
 *
 * @param p_list  a pointer to a list of cells
 *
 * @param x  the abscissa of the cell to be retrieved
 *
 * @param y  the ordinate of the cell to be retrieved
 *
 * @return a pointer to the corresponding cell
 */
cell *get_cell(list *p_list, int x, int y);

/**
 * @brief Deletes the cell which position in the list is pos
 *
 * @param p_list  a pointer to a list of cells
 *
 * @param pos  the position of the cell to be deleted
 */
void delete_cell(list *p_list, int pos);

/**
 * @brief Counts the number of neighbors of my_cell
 *
 * @param my_cell  a cell
 *
 * @return the number of neighbors (not counting newborn cells) of my_cell
 */
int count_neighbors(cell my_cell);

/**
 * @brief Goes forward one generation according to the rules of the Game of Life
 *
 * @param p_list  a pointer to a list of cells
 *
 * @param size_x  the width of the grid
 *
 * @param size_y  the height of the grid
 *
 * @return the updated list of cells
 */
list nextgen(list *p_list, int size_x, int size_y);

/**
 * @brief Deallocates all the allocated memory
 *
 * @param p_list  a pointer to a list of cells
 */
void deallocate(list *p_list);


#endif
