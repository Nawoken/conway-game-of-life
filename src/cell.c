#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <error.h>

#include "cell.h"


void nil(list *p_list) {

    *p_list = NULL;

}

void print_list(list cell_list) {

    elem *p_current_elem = cell_list;
	char character = 'W';

    while (p_current_elem != NULL) {
 
        printf(" (%d,%d) ", p_current_elem->cell.pos.x, p_current_elem->cell.pos.y);

		if (p_current_elem->cell.status == NEWBORN) {

			character = 'N';

		} else if (p_current_elem->cell.status == ALIVE) {

			character = 'A';

		} else {

			character = 'D';			

		}

		printf("%c", character);

		printf(" [ ");

		for (int i = 0; i<=7; i++) {

			if (p_current_elem->cell.neighbors[i] != NULL) {

				printf("(%d,%d) ", p_current_elem->cell.neighbors[i]->pos.x, p_current_elem->cell.neighbors[i]->pos.y);

			} else {

				printf("M ");

			}

		}

		printf("]\n");

        p_current_elem=(*p_current_elem).next;

    }

}

position delta(int i) {

	position pos;

    if (i == 0) {
    	pos.x = 0;
		pos.y = 1;
    }
    if (i == 1) {
    	pos.x = 1;
		pos.y = 1;
    }
    if (i == 2) {
    	pos.x = 1;
		pos.y = 0;
    }
    if (i == 3) {
    	pos.x = 1;
		pos.y = -1;
    }
    if (i == 4) {
    	pos.x = 0;
		pos.y = -1;
    }
    if (i == 5) {
    	pos.x = -1;
		pos.y = -1;
    }
    if (i == 6) {
    	pos.x = -1;
		pos.y = 0;
    }
    if (i == 7) {
    	pos.x = -1;
		pos.y = 1;
    }

    return pos;
}

//Ajoute la cellule au début de la liste
void cons(list *p_list, cell my_cell) {

    elem *p_new_elem = malloc(sizeof(elem));

	if (p_new_elem == NULL) {
		printf("Couldn't allocate memory !\n");
	}
		
    p_new_elem->cell = my_cell;
	p_new_elem->next = *p_list;

    *p_list = p_new_elem;

}

cell *get_cell(list *p_list, int x, int y) {
	
    elem *p_current_elem = *p_list;

    while (p_current_elem != NULL) {

        if (p_current_elem->cell.pos.x == x && p_current_elem->cell.pos.y == y) {

			cell *found_cell = malloc(sizeof(cell));

			if (found_cell == NULL) {
				printf("Couldn't allocate memory !\n");
			}

			*found_cell = p_current_elem->cell;

            return found_cell;

        }

        p_current_elem=(*p_current_elem).next;

    }

    return NULL;

}


int count_neighbors(cell my_cell) {

    int n = 0;

    for (int i = 0; i<=7; i++) {
        if (my_cell.neighbors[i] != NULL) {
			if (my_cell.neighbors[i]->status != NEWBORN) {
            	n = n + 1;
			}
        }
    }

	return n;

}

void delete_cell(list *p_list, int pos) {

	position cell_pos;
	elem *p_current_elem = *p_list;
	elem *p_current_elem_2 = *p_list;

	if (pos == 0) {

		cell_pos.x = (*p_list)->cell.pos.x;
		cell_pos.y = (*p_list)->cell.pos.y;

		while (p_current_elem != NULL) {

			for (int i = 0; i <= 7; i++) {

				if (p_current_elem->cell.neighbors[i] != NULL) {

					if ((p_current_elem->cell.neighbors[i]->pos.x == cell_pos.x) && (p_current_elem->cell.neighbors[i]->pos.y == cell_pos.y)) {

						p_current_elem->cell.neighbors[i] = NULL;

					}

				}

			}

			p_current_elem = p_current_elem->next;

		}

		elem *p_next = (*p_list)->next;
		free(*p_list);
		*p_list=p_next;

	} else {

		for (int i = 0; i < pos-1; i++) {

			p_current_elem = p_current_elem->next;

		}

		cell_pos.x = p_current_elem->next->cell.pos.x;
		cell_pos.y = p_current_elem->next->cell.pos.y;

		while (p_current_elem_2 != NULL) {

			for (int i = 0; i <= 7; i++) {

				if (p_current_elem_2->cell.neighbors[i] != NULL) {

					if ((p_current_elem_2->cell.neighbors[i]->pos.x == cell_pos.x) && (p_current_elem_2->cell.neighbors[i]->pos.y == cell_pos.y)) {

						p_current_elem_2->cell.neighbors[i] = NULL;

					}

				}

			}
			
			p_current_elem_2 = p_current_elem_2->next;

		}

		elem *p_next = (p_current_elem->next)->next;
		p_current_elem->next = p_next;
	}

}


list nextgen(list *p_list, int size_x, int size_y) {

    elem *p_current_elem = *p_list;
    int pos = 0;
    int n = 0;
	int X;
	int Y;

// Suppress all the dying cells in the list and transform all newly born cells in alive cells
    while (p_current_elem != NULL) {

        if (p_current_elem->cell.status == DYING) {

            delete_cell(p_list, pos);
			pos = pos - 1;

        }

        if (p_current_elem->cell.status == NEWBORN) {

			p_current_elem->cell.status = ALIVE;

			elem *p_current_elem_4 = *p_list;

			//p_current_elem->cell's status is changed in his neighbors' neighbors list

			while (p_current_elem_4 != NULL) {

				for (int i = 0; i <= 7; i++) {

					int j = i + 4;

					if (j > 7) {
						j = i-4;
					}

					X = p_current_elem->cell.pos.x + delta(i).x;
					Y = p_current_elem->cell.pos.y + delta(i).y;

					if (X > size_x) {
						X = 0;
					}
						
					if (X < 0) {
						X = size_x;
					}

					if (Y > size_y) {
						Y = 0;
					}
						
					if (Y < 0) {
						Y = size_y;
					}

					if ((p_current_elem_4->cell.pos.x == X) && (p_current_elem_4->cell.pos.y == Y)) {

						p_current_elem_4->cell.neighbors[j]->status = ALIVE;

					}

				}

				p_current_elem_4 = p_current_elem_4->next;

			}

        }

        p_current_elem=(*p_current_elem).next;
        pos = pos + 1;
    
    }

    p_current_elem = *p_list;

	//For each cell verify if it's dying
    while (p_current_elem != NULL) {

        n = count_neighbors(p_current_elem->cell);

        if ((n < 2) || (n > 3)) {

            p_current_elem->cell.status = DYING;

			elem *p_current_elem_4 = *p_list;

			//p_current_elem->cell's status is changed in his neighbors' neighbors list

			while (p_current_elem_4 != NULL) {

				for (int i = 0; i <= 7; i++) {

					int j = i + 4;

					if (j > 7) {
						j = i-4;
					}

					X = p_current_elem->cell.pos.x + delta(i).x;
					Y = p_current_elem->cell.pos.y + delta(i).y;

					if (X > size_x) {
						X = 0;
					}
						
					if (X < 0) {
						X = size_x;
					}

					if (Y > size_y) {
						Y = 0;
					}
						
					if (Y < 0) {
						Y = size_y;
					}

					if ((p_current_elem_4->cell.pos.x == X) && (p_current_elem_4->cell.pos.y == Y)) {

						p_current_elem_4->cell.neighbors[j]->status = DYING;

					}

				}

				p_current_elem_4 = p_current_elem_4->next;

			}

        }

		p_current_elem=(*p_current_elem).next;

    }

    p_current_elem = *p_list;

	//For each cell that is not a newborn do
    while (p_current_elem != NULL) {

        if (p_current_elem->cell.status != NEWBORN) {

			// For each neighbor i of the current cell that does not exist do
            for (int i = 0; i<=7; i++) {

                if (p_current_elem->cell.neighbors[i] == NULL) {

                    cell *p_new_cell = malloc(sizeof(cell));

					if (p_new_cell == NULL) {
						printf("Couldn't allocate memory !\n");
					}

                    p_new_cell->status = NEWBORN;

					X = p_current_elem->cell.pos.x + delta(i).x;
					Y = p_current_elem->cell.pos.y + delta(i).y;

					if (X > size_x) {
						X = 0;
					}
						
					if (X < 0) {
						X = size_x;
					}

					if (Y > size_y) {
						Y = 0;
					}
						
					if (Y < 0) {
						Y = size_y;
					}						

                    p_new_cell->pos.x = X;
                    p_new_cell->pos.y = Y;

					//This condition allows the program to delete any doubles
					if (get_cell(p_list, X, Y) == NULL) {
                        
                    	for (int j = 0; j<=7; j++) {

							int Xbis = p_new_cell->pos.x + delta(j).x;
							int Ybis = p_new_cell->pos.y + delta(j).y;

							if (Xbis > size_x) {
								Xbis = 0;
							}
						
							if (Xbis < 0) {
								Xbis = size_x;
							}

							if (Ybis > size_y) {
								Ybis = 0;
							}
						
							if (Ybis < 0) {
								Ybis = size_y;
							}

							

							if (get_cell(p_list, Xbis, Ybis) != NULL) {

                     			p_new_cell->neighbors[j] = get_cell(p_list, Xbis, Ybis);

							} else {

								p_new_cell->neighbors[j] = NULL;

							}

                    	}

                   		n = count_neighbors(*p_new_cell);

                    	if (n == 3) {

							cons(p_list, *p_new_cell);

							elem *p_current_elem_3 = *p_list;

							//p_new_cell is added to its neighbors' neighbors list

							while (p_current_elem_3 != NULL) {

								for (int i = 0; i <= 7; i++) {

									int j = i + 4;

									if (j > 7) {
										j = i-4;
									}

									X = p_new_cell->pos.x + delta(i).x;
									Y = p_new_cell->pos.y + delta(i).y;

									if (X > size_x) {
										X = 0;
									}
						
									if (X < 0) {
										X = size_x;
									}

									if (Y > size_y) {
										Y = 0;
									}
						
									if (Y < 0) {
										Y = size_y;
									}

									if ((p_current_elem_3->cell.pos.x == X) && (p_current_elem_3->cell.pos.y == Y)) {

										p_current_elem_3->cell.neighbors[j] = p_new_cell;

									}

								}

								p_current_elem_3 = p_current_elem_3->next;

							}

						} else {

							free(p_new_cell);
							p_new_cell = NULL;
						
						}

					//The cell created is a double of an existing cell and has to be deleted
                	} else {

						free(p_new_cell);
						p_new_cell = NULL;
				
					}
				}
            }
        }

		p_current_elem=(*p_current_elem).next;

    }

	return *p_list;

}

void deallocate(list *p_list) {

    elem *p_current_elem = *p_list;
	elem *p_temp;

    while (p_current_elem != NULL) {

		p_temp = p_current_elem;
        p_current_elem = p_current_elem->next;
		free(p_temp);
		p_temp = NULL;
    }

}



