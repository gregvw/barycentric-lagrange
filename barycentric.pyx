# distutils: language = c++
# distutils: sources = lagrange.cpp

cimport c_barycentric
from c_barycentric cimport Lagrange
from libcpp.vector cimport vector
import numpy as np
cimport numpy as np

cdef class Barycentric:
    cdef Lagrange *thisptr
  

    def __init__(self,const vector[double] &xi,
                      const vector[double] &xe):
        self.thisptr  = new Lagrange(xi,xe)

    def __dealloc__(self):
        del self.thisptr 

    def bi_sum(self,const vector[double] &f,
                          vector[double] &y):
        self.thisptr.bi_sum(f,y)

    def interp(self, const vector[double] &func):
             


        cdef np.ndarray[np.float64_t,ndim=1] poly
        poly = np.zeros(self.thisptr.get_ne(),np.float64)
 
        # Modify poly in place
        self.thisptr.interp(func, poly)

        return poly
