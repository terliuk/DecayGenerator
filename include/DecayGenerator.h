#ifndef DECAYGENERATOR_H
#define DECAYGENERATOR_H

#include <string>
#include <iostream>
#include <tuple>

#define _USE_MATH_DEFINES
#include <math.h> 
#include <gsl/gsl_sf_result.h>
#include <gsl/gsl_sf_gamma.h>
#include <random>
#include <assert.h>

#include <Python.h>
#include <boost/python.hpp> 
#include <boost/python/tuple.hpp>
#include <boost/python/numpy.hpp>
#include <boost/python/numpy/ndarray.hpp>
#include <boost/python/suite/indexing/vector_indexing_suite.hpp>
#include "boost/multi_array.hpp"

class DecayGenerator{
    
    public: 
        
        
        DecayGenerator(std::string s= "MM", 
                      int z= 56, double q = 2457.8, uint64_t seed = 5489u);
        // 
        void initialize(std::string, int, double, uint64_t);
        void setModel(std::string);
        std::string getModel();
        void printModel(); 
        //
        void setZdaughter(int);
        int getZdaughter();
        // 
        void setQ(double);
        double getQ();
        //
        void setMax(double);
        double getMax(); 
        double findMax(std::string); 
        //
        double p(double);
        double beta(double);      
        double F(double);      
        double F(double, int);    
        //
        double rho_MM(double, double);
        boost::python::numpy::ndarray rho_MM(boost::python::numpy::ndarray,
                                             boost::python::numpy::ndarray);
        double rho_RHC(double, double); 
        boost::python::numpy::ndarray rho_RHC(boost::python::numpy::ndarray,
                                             boost::python::numpy::ndarray);

        double rho_2vbb(double, double, double); 
        boost::python::numpy::ndarray rho_2vbb(boost::python::numpy::ndarray,
                                               boost::python::numpy::ndarray,
                                               boost::python::numpy::ndarray);
        void GenerateEvents(int, double*, double*, double*);
        std::tuple<double,double,double> GenerateOneEvent();   
        boost::python::tuple GenerateOneEventPy(); 
        boost::python::numpy::ndarray GenerateEventsPy(int nev = 1);
    private:
        // variables for overloading 
        
        ///
        std::string model; // Model: MM, RHC, 2vbb etc. 
        int Z_d; // int of daughter Z
        double Q;
        double alpha; 
        double m_e;
        double maxval;
        std::mt19937_64 rng;
        std::uniform_real_distribution<double> unif; 
};

BOOST_PYTHON_MODULE(libDecayGenerator)
{
    Py_Initialize() ;
    boost::python::numpy::initialize() ;
    using namespace boost::python;
    class_<DecayGenerator>("DecayGenerator", init<optional<std::string, int, double, uint64_t> >())
      .def("setModel", &DecayGenerator::setModel)
      .def("getModel", &DecayGenerator::getModel)
      .def("printModel", &DecayGenerator::printModel)
      .def("setZdaughter",  &DecayGenerator::setZdaughter)
      .def("getZdaughter",  &DecayGenerator::getZdaughter)
      .def("setQ",  &DecayGenerator::setQ)
      .def("getQ",  &DecayGenerator::getQ)
      .def("setMax",  &DecayGenerator::setMax)
      .def("getMax",  &DecayGenerator::getMax)
      .def("findMax",  &DecayGenerator::findMax)
      .def("p", &DecayGenerator::p)
      .def("beta", &DecayGenerator::beta)
      .def<double (DecayGenerator::*)(double)>("F",&DecayGenerator::F)
      .def<double (DecayGenerator::*)(double,int)>("F",&DecayGenerator::F)
      .def<double (DecayGenerator::*)(double,double)>("rho_MM",&DecayGenerator::rho_MM)
      .def<boost::python::numpy::ndarray (DecayGenerator::*)(boost::python::numpy::ndarray,
                                                             boost::python::numpy::ndarray)>("rho_MM",&DecayGenerator::rho_MM)
      .def<double (DecayGenerator::*)(double,double)>("rho_RHC",&DecayGenerator::rho_RHC)
      .def<boost::python::numpy::ndarray (DecayGenerator::*)(boost::python::numpy::ndarray,
                                                             boost::python::numpy::ndarray)>("rho_RHC",&DecayGenerator::rho_RHC)
      .def<double (DecayGenerator::*)(double,double,double)>("rho_2vbb",&DecayGenerator::rho_2vbb)
      .def<boost::python::numpy::ndarray (DecayGenerator::*)(boost::python::numpy::ndarray,
                                                             boost::python::numpy::ndarray,
                                                             boost::python::numpy::ndarray)>("rho_2vbb",&DecayGenerator::rho_2vbb)
      .def("GenerateOneEvent", &DecayGenerator::GenerateOneEventPy)
      .def("GenerateEvents", &DecayGenerator::GenerateEventsPy)
    ;
}
#endif 
