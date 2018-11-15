// Title: Polynomial Arithmetic Project
// Author: David Zhu
// Description: Polynomial calculator using pointers and structures
// Updates: Nov 12: Added header file and begun on functions
//          Nov 13: Added poly_destructor, poly_coeffs, poly_val, poly_add, poly_subtract
//          Nov 14: Tested functions up to poly_val; poly_add; and poly_subtract
//
// To do: figure out whether or not to delete in init_poly
//        Test the functions. !!! check for 0 val poly.
//        Finish the other functions: DESTROY POLY CAUSES PROBLEMS
//
//=================================================================================================
#include <iostream>
#include <cmath>
#include <string>
#include <algorithm>
#include "Polynomial.h"
//=================================================================================================


//=================================================================================================
bool check_zero( poly_t const &p ){

    //Function checks for zero polynomial:
    for (int i = 0; i <= p.degree; ++i){
        if (p.a_coeffs[i] !=0 )
            return false;
    }
    std::cout<< "zero poly " << std::endl;
    return true;

}

bool set_zero( poly_t &p) {

    // Sets to zero polynomial
    double zero_array[1]{};
    init_poly(p,zero_array,0);

}
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

    // Assigns new coefficients
    for (int i = 0; i <= init_degree; ++i){
        p.a_coeffs[i] = init_coeffs[i];
    }

    p.degree = init_degree;

}

void destroy_poly( poly_t &p ){

    // Deallocates memory from the a_coeffs struct member
    delete[] p.a_coeffs;
    p.a_coeffs = nullptr;
    p.degree = 0;

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
    double y = p.a_coeffs[p.degree];

    // Horner's method to evaluating:
    for (int i = p.degree-1; i >= 0; --i){
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

        // Create new array
        poly_t new_poly{nullptr, 0};
        double *p_new_poly = new double[q.degree+1];

        // Assigns new values to p_new_poly for common terms
        for (int i = 0; i <= p.degree; ++i){
            p_new_poly[i] = p.a_coeffs[i] + q.a_coeffs[i];
        }

        // Copies over remaining terms from q.poly
        for (int i = p.degree+1; i <= q.degree; ++i){
            p_new_poly[i] = q.a_coeffs[i];
        }

        // Allocates memory for new array.
        init_poly(new_poly, p_new_poly, q.degree);


        // Deallocates memory for local array CAUSES PROBLEMS
        destroy_poly(p);

        // New polynomial
        p = new_poly;

    } else {

        // Assigns new values to current polynomial
        for (int i = 0; i <= q.degree; ++i){
            p.a_coeffs[i] += q.a_coeffs[i];
        }

        // Checks if result is 0
        if(check_zero(p))
            set_zero(p);

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

        // Create new array
        poly_t new_poly{nullptr, 0};
        double *p_new_poly = new double[q.degree+1];

        // Assigns new values to new_poly (temp var)
        for (int i = 0; i <= q.degree; ++i){
            p_new_poly[i] = p.a_coeffs[i] - q.a_coeffs[i];
        }

        // Copies over remaining terms from q.poly
        for (int i = p.degree+1; i <= q.degree; ++i){
            p_new_poly[i] = -q.a_coeffs[i];
        }

        // Allocates memory for new array.
        init_poly(new_poly, p_new_poly, q.degree);

        // Deallocates memory for local array CAUSES PROBLEMS IN MEMORY
        destroy_poly(p);

        // New polynomial
        p = new_poly;

    } else {

        // Assigns new values for current polynomial
        for (int i = 0; i <= q.degree; ++i){
            p.a_coeffs[i] -= q.a_coeffs[i];
        }

        // Checks if result is 0
        if(check_zero(p))
            set_zero(p);
    }

}

void poly_multiply( poly_t &p, poly_t const &q ){

    // Checks for poly initialization
    if (p.a_coeffs == nullptr) {
        throw 0;
    }

    // Checks for zero polynomial
    if (check_zero(p) || check_zero(q)){
        set_zero(p);
    }

}


#ifndef MARMOSET_TESTING
int main(){

    // Initialization
    poly_t test_poly{nullptr,0};
    poly_t test_poly2{nullptr,0};
    double test_coeffs[3] = {3,2,1};
    double test_coeffs2[1] = {0};
    init_poly(test_poly,test_coeffs,2);
    init_poly(test_poly2,test_coeffs2,0);

    //std::cout<< test_poly.a_coeffs[0] << test_poly.a_coeffs[1] << test_poly.a_coeffs[2];
    //double test_1 = poly_coeff(test_poly,1);
    //unsigned test_2 = poly_degree(test_poly);
    poly_multiply(test_poly,test_poly2);
    double test_3 = poly_val(test_poly, 2);

    // Test add and subtract
    for (int i = 0; i <= test_poly.degree; ++i){
        double k = poly_coeff(test_poly, i);
        std::cout << "coeff at " << i << " is " << k << std::endl;
    }

    //std::cout<< test_1 << " and " << test_2 << std::endl;
  //  std::cout << "Evaluate at x = 2: y = " << test_3;
    destroy_poly(test_poly);
    destroy_poly(test_poly2);
    return 0;
}
#endif
