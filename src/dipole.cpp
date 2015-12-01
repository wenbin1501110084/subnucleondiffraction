/*
 * Dipole cross section with explicit impact parameter and r dependence
 * Abstract class
 * All nuclear (target) dependence is described by this class]
 *
 * Heikki Mäntysaari <mantysaari@bnl.gov>, 2015
 */

#include "dipole.hpp"
#include "vector.hpp"
#include <string>

double DipoleAmplitude::Amplitude(double xpom, double q1[2], double q2[2] )
{
    return 0; // Not defined, shouldnt be here
}

void DipoleAmplitude::InitializeTarget()
{
    // Nothing to do if not overloaded
}

std::string DipoleAmplitude::InfoStr()
{
    return "Dipole modle InfoStr not implemented";
}

double DipoleAmplitude::Amplitude(double xpom, Vec q1, Vec q2)
{
    double quark[2] = {q1.GetX(), q1.GetY() };
    double antiquark[2] = {q2.GetX(), q2.GetY() };
    return Amplitude(xpom, quark, antiquark);
}