#include"lagrange.hpp"

// Constructor
Lagrange::Lagrange(const dvec &xInterp, const dvec &xEval) : 
    ni(xInterp.size()), ne(xEval.size()), xi(xInterp), xe(xEval), 
    w(dvec(xInterp.size(),0)), ell(dvec(xEval.size(),0)) {

    /* Compute the weights using as slightly modified version of the 
       algorithm on page 504 in the Trefethen & Berrut paper */
    
    w[0] = 1.0;
    
    // I think this loop can not be parallelized
    for(int j=1;j<ni;++j)
    {
        w[j] = 1;

        for(int k=0;k<j;++k)
        {
            double d = xi[k]-xi[j];
            w[k] *= d;
            w[j] *= -d;
        }
    }

    for(int j=0;j<ni;++j)
    {
        w[j] = 1.0/w[j];
    }
  
    dvec ones(ni,1.0);          // Create vector of ones
  
    this->bi_sum(ones,ell);    // Compute the ell(x) polynomial

    for(int j=0;j<ne;++j)
    {
        ell[j] = 1.0/ell[j];
    }
}


Lagrange::~Lagrange(){
}

void Lagrange::bi_sum(const dvec &f, dvec &y){
    /* This routine evaluates sums of the form shown in equation (4.2) in 
       the paper by J-P Berrut and L.N. Trefethen */

    for(int j=0;j<ne;++j)
    {
        y[j] = 0;
        for(int k=0;k<ni;++k)
        {
            if(xe[j] == xi[k])
            {
                y[j] = f[j];
                break;
            }
            else
            {
                y[j] += w[k]*f[k]/(xe[j]-xi[k]);
            }
        }    
    }    
}


void Lagrange::interp(const dvec &func, dvec &poly){

    this->bi_sum(func,poly);

    for(int j=0;j<ne;++j)
    {
        poly[j] *= ell[j];
    }    
}


int Lagrange::get_ne(void) { 
    return ne;
}
