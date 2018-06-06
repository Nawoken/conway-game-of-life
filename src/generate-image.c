#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <error.h>

#include "generate-image.h"

void write_file(list *p_list, int size_x, int size_y, int index) {
	
	FILE *p_file = NULL;
	char c[100];
	char filename[100]="";
	sprintf(c,"%d",index);
	strcat(filename, "/home/promo19/j.leflour/IN101-labs/project/out/test");

	if (index<10) {

		strcat(filename, "00");

	} else if (index<100) {

		strcat(filename, "0");
	}

	strcat(filename,c);
	strcat(filename, ".ppm");
	p_file = fopen(filename, "w");

	if (p_file == NULL) {
		error(1,0, "Cannot write to file");
	}
	
	fprintf(p_file, "P3\n");
	fprintf(p_file, "%d %d\n", size_x, size_y);
	fprintf(p_file, "255\n");
	int mat[size_x][size_y];
	
	for (int j = 0; j < size_y; j++) {
		for (int i = 0; i < size_x; i++) {
			mat[i][j] = 3;
		}
	}

	elem *p_current_elem = *p_list;

	while (p_current_elem != NULL) {

		int x = p_current_elem->cell.pos.x;
		int y = p_current_elem->cell.pos.y;

		if (p_current_elem->cell.status == ALIVE) {

			mat[x][y] = 0;

		} else if (p_current_elem->cell.status == NEWBORN) {

			mat[x][y] = 1;

		} else if (p_current_elem->cell.status == DYING) {

			mat[x][y] = 2;

		}

		p_current_elem = p_current_elem->next;

	}

	for (int j = 0; j < size_y; j++) {

		for (int i = 0; i < size_x; i++) {

			if (mat[i][j] == 0 && i == size_x) {

				fprintf(p_file, "157 220 21\n");

			} else if (mat[i][j] == 1 && i == size_x) {

				fprintf(p_file, "255 213 57\n");

			} else if (mat[i][j] == 2 && i == size_x) {

				fprintf(p_file, "202 32 77\n");

			} else if (mat[i][j] == 2 && i != size_x) {

				fprintf(p_file, "202 32 77  ");

			} else if (mat[i][j] == 0 && i != size_x) {

				fprintf(p_file, "157 220 21  ");

			} else if (mat[i][j] == 1 && i != size_x) {

				fprintf(p_file, "255 213 57\n");

			} else if (mat[i][j] == 3 && i == size_x) {

				fprintf(p_file, "0 0 0\n");
				
			} else if (mat[i][j] == 3 && i != size_x) {

				fprintf(p_file, "0 0 0  ");

			}
		}
	}

	fclose(p_file);
	p_file = NULL;
}


