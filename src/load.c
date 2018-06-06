#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <error.h>

#include "load.h"

problem load_grid(char filename[100]) {

	FILE *p_file = NULL;

	p_file = fopen(filename, "r");

    if (p_file == NULL) {
        error(1, 0, "Cannot read file %s!\n", filename);
    }

	list cell_list;
	nil(&cell_list);
    int size_x;
    int size_y;
	position pos;
	pos.x = 0;
	pos.y = 0;
	char character;
    int fscanf_result = 0;

    fscanf(p_file, "%d %d", &size_x, &size_y);
	size_x = size_x - 1;
	size_y = size_y - 1;

	int nb_steps;

	fscanf(p_file, "%d", &nb_steps);
	//This line is mandatory because C sees a wordwarp as a character
	fscanf_result = fscanf(p_file, "%c", &character);

	while (fscanf_result != EOF) {

		fscanf_result = fscanf(p_file, "%c", &character);

		if ((fscanf_result == 1) && (character == 'o')) {

			cell new_cell;
            new_cell.status = ALIVE;
			new_cell.pos = pos;

			cons(&cell_list, new_cell);

		}

		pos.x = pos.x + 1;

		if (pos.x > size_x) {

			//This line is mandatory because C sees a wordwarp as a character
			fscanf_result = fscanf(p_file, "%c", &character);

			pos.x = 0;
			pos.y = pos.y + 1;

			if (pos.y > size_y) {
				//This line is mandatory because C detects a nonexistent character at the end
				fscanf_result = fscanf(p_file, "%c", &character);
			}
			
		}

	}

	elem *p_current_elem = cell_list;

    while (p_current_elem != NULL) {

    	for (int i = 0; i<=7; i++) {

			int X = p_current_elem->cell.pos.x + delta(i).x;
			int Y = p_current_elem->cell.pos.y + delta(i).y;

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

    	    if (get_cell(&cell_list, X, Y) != NULL) {                   
  
      		  	p_current_elem->cell.neighbors[i] = get_cell(&cell_list, X, Y);

      	    } else {			

        		p_current_elem->cell.neighbors[i] = NULL;

        	}

		}

	p_current_elem = p_current_elem->next;

	}


    fclose(p_file);

    p_file = NULL;

	problem prob;
	prob.size_x = size_x;
	prob.size_y = size_y;
	prob.nb_steps = nb_steps;
	prob.cell_list = cell_list;

	return prob;
		
}

