import cython
import numpy as np
cimport numpy as np

from libcpp.vector cimport vector




cdef extern from "lagrange.hpp":
    cdef cppclass Lagrange:
        Lagrange(const vector[double] &, const vector[double] &)

        int ni              # Number of interpolation points
        int ne              # Number of evaluation points
        vector[double] xi   # Interpolation points
        vector[double] xe   # Evaluation points
        vector[double] w    # Barycentric weights
        vector[double] ell  # ell(x) polynomial with roots at xi

        void bi_sum(const vector[double] &, vector[double] &)  # Evaluate sums like eq. (4.2)
        void interp(const vector[double] &, vector[double] &)  # Evaluate the interpolant
        int get_ne()
