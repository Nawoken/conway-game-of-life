#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include "cell.h"
#include "load.h"
#include "generate-image.h"

int main() {

	//Initializing the grid
	problem prob = load_grid("/home/promo19/j.leflour/IN101-labs/project/data/data.txt");

	list cell_list = prob.cell_list;

	//Generating the first image
	write_file(&cell_list, prob.size_x, prob.size_y, 0);

	for (int i = 1; i <= prob.nb_steps; i++) {

		//Going forward one generation
		cell_list = nextgen(&cell_list, prob.size_x, prob.size_y);

		//Generating the associated image
		write_file(&cell_list, prob.size_x, prob.size_y, i);
	
	}

	//Deallocating the memory
	deallocate(&cell_list);

	return 0;

}

