/*
Project: Ocean
Author:  DEISS Olivier
License: This software is offered under the GPL license. See COPYING for more information.
*/

#include <cmath>
#include <iostream>

#include "Philipps.hpp"

/*
Initializes the variables.
*/
Philipps::Philipps(const double p_lx, const double p_ly, const int p_nx, const int p_ny, const double p_wind_speed, const int p_wind_alignment, const double p_min_wave_size, const double p_A) :
    lx(p_lx),
    ly(p_ly),
    nx(p_nx),
    ny(p_ny),
    wind_speed(p_wind_speed),
    wind_alignment(p_wind_alignment),
    min_wave_size(p_min_wave_size),
    A(p_A) {
}

/*
This function initializes the variables to the right values before
a series of calls to the functor.
*/
void Philipps::init_fonctor(int i) {
    x = i - nx/2;
    y = -ny/2;
}

/*
Philipps spectrum fonctor. See J. Tessendorf's paper for more information
and the mathematical formula.
*/
double Philipps::operator()() {
    double g    = 9.81;
    double kx   = (2*M_PI*x)/lx;
    double ky   = (2*M_PI*y)/ly;
    double k_sq = kx*kx + ky*ky;
    double L_sq = pow((wind_speed*wind_speed)/g, 2);
    y++;
    if(k_sq==0) {
        return 0;
    }
    else {
        double var;
        var =  A*exp((-1/(k_sq*L_sq)));
        var *= exp(-k_sq*pow(min_wave_size, 2));
        var *= pow((kx*kx)/k_sq, wind_alignment);
        var /= k_sq*k_sq;
        return var;
    }
}