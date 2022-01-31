/*
 * Diffraction at sub-nucleon scale
 * Heikki Mäntysaari <mantysaari@bnl.gov>, 2015
 */
#ifndef subnucleon_config_h
#define subnucleon_config_h

const int ZINT_INTERVALS = 20;
const double ZINT_RELACCURACY = 0.0001;
const double MCINTACCURACY = 0.2;

const double DELTA_Y = 0.1; // delta y (y=ln 1/x) used to calculate corrections

const double JPSI_MASS = 3.0969;

extern bool FACTORIZE_ZINT;   // if true, we neglect exp[(1-z)r.Delta] coupling and
    // the only z dependence is in the wave function 

extern int MCINTPOINTS ;

extern bool REAL_PART;  // Calculate real part of the amplitude

enum MCINTEGRAL
{
    VEGAS,
    MISER
};

//const MCINTEGRAL MCINT = MISER;
extern MCINTEGRAL MCINT;

enum PROCESS
{
    COHERENT,
    INCOHERENT
};

enum FORM_FACTOR
{
    POINT_CHARGE,
    APPROXIMATIVE
};

enum EXPERIMENT
{
    RHIC,
    LHC
};

extern FORM_FACTOR NUCLEAR_FF;
extern EXPERIMENT KINEMATICS;


// Globar random number generator - avoid initializing it mulitple times
#include <gsl/gsl_rng.h>

extern gsl_rng *global_rng;

#endif /* subnucleon_config_h */

