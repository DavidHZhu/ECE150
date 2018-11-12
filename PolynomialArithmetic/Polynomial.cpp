// Title: Polynomial Arithmetic Project
// Author: David Zhu
// Description: Polynomial calculator using pointers and structures
// Updates: Nov 12: Added header file and begun on functions
// To do: figure out whether or not to delete in init_poly
//
//
//
//=================================================================================================
#include <iostream>
#include <cmath>
#include <string>
#include <algorithm>
#include "Polynomial.h"
//=================================================================================================


int main(){

    return 0;
}

void init_poly( poly_t &p, double const init_coeffs[], unsigned int const init_degree ){

    // Checks if the previous array was deallocated:
    if (p.a_coeffs != nullptr){
        delete p.a_coeffs;
    }

    // Allocates memory dynamically for new array:
    double *new_poly = new double[init_degree+1];
    for (int i = 0; i <= init_degree; ++i){
        new_poly[i] = init_coeffs[i];
    }
    p.a_coeffs = new_poly;

}