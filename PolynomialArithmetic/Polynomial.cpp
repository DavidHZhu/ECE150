// Title: Polynomial Arithmetic Project
// Author: David Zhu
// Description: Polynomial calculator using pointers and structures
// Updates: Nov 12: Added header file and begun on functions
//          Nov 13: Added poly_destructor, poly_coeffs, poly_val, poly_add, poly_subtract
//          Nov 14:
//
// To do: figure out whether or not to delete in init_poly
//        Test the functions.
//        Finish the other functions
//
//=================================================================================================
#include <iostream>
#include <cmath>
#include <string>
#include <algorithm>
#include "Polynomial.h"
//=================================================================================================
#ifndef MARMOSET_TESTING
int main();
#endif

#ifndef MARMOSET_TESTING
int main(){

    return 0;
}
#endif

//=================================================================================================
void init_poly( poly_t &p, double const init_coeffs[], unsigned int const init_degree ){

    // Checks if the previous array was deallocated:
    if (p.a_coeffs != nullptr){
        delete[] p.a_coeffs;
        p.a_coeffs = nullptr;
    }

    // Allocates memory dynamically for new array:
    p.a_coeffs = new double[init_degree+1];

    // Special case for the Zero polynomial
    if (init_degree == 0){
        p.a_coeffs[0] = 0;
    }

    for (int i = 0; i <= init_degree; ++i){
        p.a_coeffs[i] = init_coeffs[i];
    }

    p.degree = init_degree;

}

void destroy_poly( poly_t &p ){

    // Deallocates memory from the a_coeffs struct member
    delete[] p.a_coeffs;
    p.a_coeffs = nullptr;

}

unsigned int poly_degree( poly_t const &p ){

    // Returns the degree of the polynomial if it is initialized:
    if (p.a_coeffs == nullptr){
        throw 0;
    } else {
        return p.degree;
    }
}

double poly_coeff( poly_t const &p, unsigned int n ){

    // Returns the degree of the polynomial if it is initialized:
    if (p.a_coeffs == nullptr){
        throw 0;
    } else {
        return p.a_coeffs[n];
    }

}

double poly_val( poly_t const &p, double const x){

    // Checks for poly initialization
    if (p.a_coeffs == nullptr){
        throw 0;
    }

    // Initial Y value from x:
    double y = p.a_coeffs[0];

    // Horner's method to evaluating:
    for (int i = 0; i <= p.degree; ++i){
        y = y*x + p.a_coeffs[i];
    }

    return y;
}

// Note: the second polynomial is const
void poly_add( poly_t &p, poly_t const &q){

    // Checks for poly initialization
    if (p.a_coeffs == nullptr) {
        throw 0;
    }

    // Compares sizes of polynomials
    if (p.degree < q.degree){

        // Allocates memory
        double *new_poly = new double[q.degree+1];

        // Assigns new values to new_poly for common terms
        for (int i = 0; i <= p.degree; ++i){
            new_poly[i] = q.a_coeffs[i] + p.a_coeffs[i];
        }

        // Copies over remaining terms from q.poly
        for (int i = p.degree+1; i <= q.degree; ++i){
            new_poly[i] = q.a_coeffs[i];
        }

        // Destroys local var and assigns nullptr
        destroy_poly(p);

        // New polynomial
        p.a_coeffs = new_poly;
        p.degree = q.degree+1;

    } else {

        // Assigns new values to current polynomial
        for (int i = 0; i <= q.degree; ++i){
            p.a_coeffs[i] += q.a_coeffs[i];
        }

    }
}

// Note: the second polynomial is const
void poly_subtract( poly_t &p, poly_t const &q){

    // Checks for poly initialization
    if (p.a_coeffs == nullptr) {
        throw 0;
    }

    // Compares sizes of polynomials
    if (p.degree < q.degree){

        // Allocates memory
        double *new_poly = new double[q.degree+1];

        // Assigns new values to new_poly (temp var)
        for (int i = 0; i <= q.degree; ++i){
            new_poly[i] = q.a_coeffs[i] - p.a_coeffs[i];
        }

        // Copies over remaining terms from q.poly
        for (int i = p.degree+1; i <= q.degree; ++i){
            new_poly[i] = q.a_coeffs[i];
        }

        // Destroys local var and assigns nullptr
        destroy_poly(p);

        // New polynomial
        p.a_coeffs = new_poly;
        p.degree = q.degree+1;

    } else {

        // Assigns new values for current polynomial
        for (int i = 0; i <= q.degree; ++i){
            p.a_coeffs[i] -= q.a_coeffs[i];
        }
    }

}