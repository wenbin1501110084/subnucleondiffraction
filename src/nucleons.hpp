/*
 * Nucleus that consists of nucleons
 *
 * Heikki Mäntysaari <mantysaari@bnl.gov>, 2015
 */

#ifndef nucleons_hpp
#define nucleons_hpp

#include "dipole.hpp"
#include <vector>
#include "ipsat_proton.hpp"
#include "vector.hpp"
#include "gdist_dglap.hpp"

class Nucleons : public DipoleAmplitude
{
public:
    // Evaluate dipole ampltitude, qaurks at coordinates x1 and x2
    // Array points are x and y coordinates
    double Amplitude(double xpom, double q1[2], double q2[2] );
    
    void InitializeTarget();
    
    
    
    Nucleons(std::vector<DipoleAmplitude*> nucleons);
    ~Nucleons();
    double WS_unnorm(double r );
    
    std::string InfoStr();
    
private:
    int A;
    std::vector<DipoleAmplitude*> nucleons; // Todo: change to support general proton/nucleon class?
    std::vector<Vec> nucleon_positions;
    
    double ws_delta;
    double ws_ra;
    
};

#endif /* nucleons_hpp */
