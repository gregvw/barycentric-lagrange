#include <iostream>
#include <iomanip>
#include <cmath>
#include "lagrange.hpp"

// Validate that the C++ code works before testing with Cython

int main(int argc, char *argv[]) {

    double pi = 2.0*acos(0);

    int ni = 9;
    int ne = 21;

    dvec xi(ni,0);
    dvec xe(ne,0);
   

    // Chebyshev-Gauss-Lobatto 
    for(int i=0;i<ni;++i) {
        xi[i] = -cos((pi*i)/(ni-1));
    } 
 
    // Uniform 
    for(int e=0;e<ne;++e) {
        xe[e] = 2*double(e)/(ne-1)-1;
    } 

    Lagrange lagrange(xi,xe);


    // Evaluate some function on the grid
    dvec func(ni,0);
    
    for(int i=0;i<ni;++i) {
        func[i] = exp(xi[i]);
    }

    // Polynomial
    dvec poly(ne,0);
   
    lagrange.interp(func,poly);

    for(int e=0;e<ne;++e) {
        std::cout << std::setw(12) << xe[e] 
                  << std::setw(12) << poly[e] << std::endl;
    }


}
