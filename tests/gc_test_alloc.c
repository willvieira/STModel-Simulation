#include <assert.h>
#include <time.h>
#include <gsl/gsl_rng.h>

#include "../src/grid_cell.c"

int main() {

	/* DESC: creates a cell, assigns values to it, and tries to get them back out */ 
	
	// Init cell
	size_t histSize = 10;
	GridCell * cell = gc_make_cell(histSize);
	
	// Define first state
	*(cell->currentState) = DECIDUOUS;

	// Assertion of the state and the cell
	assert(cell->stateHistory[0] == DECIDUOUS);
	assert(cell->historySize == histSize);

	// printf("currentState[%d]:%d \t",0,(int)*(cell->currentState) );
	// printf("stateHistory[%d]:%d \n",0,(int) cell->stateHistory[0] );

	// Fill state history
	for(int i = 1; i < histSize; i++) {
		cell->currentState++;
		*(cell->currentState) = TRANSITIONAL;
		// printf("currentState[%d]:%d \t",i,(int)*(cell->currentState) );
		// printf("stateHistory[%d]:%d \n",i,(int) cell->stateHistory[i] );
	}

	// Assert value of the last time step
	assert(cell->stateHistory[histSize-1] == TRANSITIONAL);
	
	// Basic writing test in cell struct
	cell->climate.meanTemp = 0;
	cell->prevalence[0] = cell->transitionProbs[0] = 0.5;
	
	// Free memory
	gc_destroy_cell(cell);
}