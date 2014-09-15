// #define NDEBUG   // enable this to switch off debugging/assertions

#include <stdio.h>
#include <assert.h>
#include <time.h>
#include <string.h>

#include <gsl/gsl_rng.h>

#include "grid.h"
#include "climate.h"

// set global modelling constants
static int MAX_TIME = 21;
static int GR_SIZE_X = 3;
static int GR_SIZE_Y = 3;
static int CLIM_X_DIM = 10;
static int CLIM_Y_DIM = 10;
static const NeighborhoodType NBTYPE = MOORE;
static const double DISTURB_RATE = 0.20;
static const char * climateDataFile = "climate_test.csv";

int main(int argc, char **argv) {

	for(int i = 0; i < argc; i++) {
		if(strncmp(argv[i],"-t",2)==0)
			MAX_TIME = atoi(argv[++i]);
		if(strncmp(argv[i],"-s",2)==0)
			GR_SIZE_X = GR_SIZE_Y = atoi(argv[++i]);
		if(strncmp(argv[i],"-x",2)==0)
			GR_SIZE_X = atoi(argv[++i]);
		if(strncmp(argv[i],"-y",2)==0)
			GR_SIZE_Y = atoi(argv[++i]);
	}

  // set up RNG
  gsl_rng *rng = gsl_rng_alloc(gsl_rng_mt19937);
  assert(rng);
  gsl_rng_set(rng, (int)time(NULL));
  
  
  ClimateGrid * climGrid = cg_make_climate_grid(climateDataFile, CLIM_X_DIM, CLIM_Y_DIM, MAX_TIME - 1);

  // set up the grid
  Grid *grid = gr_make_grid(GR_SIZE_X, GR_SIZE_Y, MAX_TIME, NBTYPE, UNIFORM, DISTURB_RATE, rng);

  // main loop in time -- we start on year 1, end on MAX_TIME - 1; this gives us
  // MAX_TIME total time steps (including the initial conditions)
  for (int year = 1; year < MAX_TIME; year++)
  	gr_update_all_cells(grid, rng);

  gr_output(grid);

  // cleanup
  gr_destroy_grid(grid);
  gsl_rng_free(rng);
}
