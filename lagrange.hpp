// lagrange.hpp

#include<vector>

typedef std::vector<double> dvec;

class Lagrange{
    public:
        Lagrange(const dvec&, const dvec&);
        ~Lagrange();

        // Interpolate from the interpolation to the evaluation points
        void interp(const dvec&, dvec&);

        /* Implement sum formulas as found in equation 4.2 of Trefethen 
           and Berrut SIAM Review, Vol. 46, No. 3, pp.501-517 */
        void bi_sum(const dvec&, dvec &);

        int get_ne();
    private:
        // Number of interpolation points
        int ni;

        int ne;

        // Number of evaluation points

        // Values of interpolation points  
        dvec xi; 

        // Values of evaluation points
        dvec xe;

        // Interpolation weights
        dvec w;

        // Barycentric multiplicative polynomial
        dvec ell;

};
