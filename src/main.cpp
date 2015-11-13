/*
 * Diffraction at sub-nucleon scale
 * Heikki Mäntysaari <mantysaari@bnl.gov>, 2015
 */

#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <iomanip>

#include <tools/tools.hpp>

#include "dipole.hpp"
#include "smooth_ws_nuke.hpp"
#include "diffraction.hpp"
#include "gauss_boost.hpp"
#include "ipsat_nucleons.hpp"
#include "vector.hpp"
#include "subnucleon_config.hpp"
#include "ipglasma.hpp"

using namespace std;

string InfoStr();

DipoleAmplitude *amp;

int main(int argc, char* argv[])
{
    double Qsqr=0;
    double t=0.1;
    double xpom=0.001;
    PROCESS p = COHERENT;
    bool print_nucleus = false;
    
    cout << "# SubNucleon Diffraction by H. Mäntysaari <mantysaari@bnl.gov>, 2015" << endl;
    
    if (string(argv[1])=="-help")
    {
        cout << "-real, -imag: set real/imaginary part" << endl;
        cout << "-dipole [ipsat,ipnonsat,ipglasma] [ipglasmafile, ipsat_radius_fluctuation_fraction]" << endl;
        cout << "-mcintpoints points" << endl;
        return 0;
    }
        
    
    for (int i=1; i<argc; i++)
    {
        if (string(argv[i])=="-coherent")
            p = COHERENT;
        else if (string(argv[i])=="-incoherent")
            p = INCOHERENT;
        else if (string(argv[i])=="-mcintpoints")
            MCINTPOINTS = StrToReal(argv[i+1]);
        else if (string(argv[i])=="-real")
            REAL_PART = true;
        else if (string(argv[i])=="-imag")
            REAL_PART = false;
        else if (string(argv[i])=="-dipole")
        {
            if (string(argv[i+1])=="ipsat" or string(argv[i+1])=="ipnonsat")
            {
                amp = new Ipsat_Nucleons;
                if (string(argv[i+1])=="ipsat")
                    ((Ipsat_Nucleons*)amp)->SetSaturation(true);
                else
                    ((Ipsat_Nucleons*)amp)->SetSaturation(false);
                ((Ipsat_Nucleons*)amp)->SetFluctuatingNucleonSize(StrToReal(argv[i+2]));
                
            }
            else if (string(argv[i+1])=="ipglasma")
                amp = new IPGlasma(argv[i+2]);
            else
            {
                cerr << "Unknown dipole " << argv[i+1] << endl;
                return -1;
            }
        }
        else if (string(argv[i])=="-print_nucleus")
        {
            print_nucleus = true;
        }
    }
    
    
    //
    //IPGlasma glasma("data/V.dat");
    
    //double origin[2]={0,0};
    
    /*
    for (double y=-11.5; y < 11.5; y+=0.05)
    {
        for (double x=-11.5; x < 11.5; x+=0.05)
        {
            double p[2] = {x,y};
            cout << y << " " << x << " " << glasma.Amplitude(0.01, origin, p) << endl;
        }
        cout << endl;
        
    }*/
   
    
    
    BoostedGauss wavef("gauss-boosted.dat");
    
    amp->InitializeTarget();
    

    Diffraction diff(*amp, wavef);
    
    
    cout << "# " << InfoStr() << endl;
    cout << "# " << wavef << endl;
    
    
    if (print_nucleus)
    {
        // Print ipsat nucleus, todo: ipglasma
        std::vector<Vec> positions = ((Ipsat_Nucleons*)amp)->GetNucleons();
        std::vector<double> Bps = ((Ipsat_Nucleons*)amp)->GetB_ps() ;
        cout << "# x   y    radius   [GeV^-1]" << endl;
        for (int i=0; i<positions.size(); i++)
        {
            cout << positions[i].GetX() << " " << positions[i].GetY() << " " << std::sqrt(2.0*Bps[i]) << endl;
        }
        return 0;
        
    }
    
    if (p == INCOHERENT)
        cout << "# t    dsigma/dt [GeV^4] " << endl;
    if (p == COHERENT)
        cout << "# t    Re A [GeV^2] " << endl;
    for (t=0.0; t<=0.61; t+=0.005)
    {
        double res = 0;
        cout.precision(5);
        if (p == INCOHERENT)
            res =diff.TotalCrossSection(xpom, Qsqr, t);
        else if (p == COHERENT)
            res = diff.CoherentCrossSection(xpom, Qsqr, t);
        cout << t << " ";
        cout.precision(10);
        cout << res  << endl;

    }
    


    
    delete amp;
    
}


string InfoStr()
{
    stringstream info;
    
    info << "Parameters: MCINTPOINTS: " << MCINTPOINTS << " ZINT_INTERVALS " << ZINT_INTERVALS << " MCINTACCURACY " << MCINTACCURACY << " ZINT _RELACCURACY " << ZINT_RELACCURACY;
    info << ". Integration method ";
    if (MCINT == MISER)
        info << "MISER";
    else if (MCINT == VEGAS)
        info << "VEGAS";
    else
        info << "unknown!";
    
    info << " Dipole: " << amp->InfoStr();

    
    if (REAL_PART) info << ". Real part";
    else info << ". Imaginary part";
    
    return info.str();

}