/*
	API definition for the grid of a cellular automaton model
	Presently also includes the API for implementing the grid cell -- to do? move to new file?
*/

#ifndef GRID_H
#define GRID_H

#include "grid_cell.h"

#include <assert.h>	// for assert()
#include <stdlib.h> // for size_t

/*
	DATA STRUCTURES
*/

// this is where you write a comment explaining what random vs mixed vs uniform mean

typedef enum {RANDOM, UNIFORM, MIX} GridType;

typedef struct {
	size_t 		xDim, yDim;
	GridCell * 	gridData;

} Grid;


/*
	FUNCTION PROTOTYPES
*/

// TODO: add parameters and function description

Grid * 		gr_make_grid		               (size_t xsize, size_t ysize, size_t numTimeSteps, GridType gridType, gsl_rng* rng);
void 		gr_destroy_grid		   (Grid * grid);
GridCell * 	gr_get_cell		               (Grid * grid, size_t x, size_t y);
void	           gr_set_cell	                           (Grid* grid, State* value, size_t x, size_t y);
void                gr_compute_neighbor_states      (Grid *grid, State *dest, size_t x, size_t y,size_t neighborhoodSize);
void                gr_compute_prevalence              (Grid * grid, size_t x, size_t y);


#endif