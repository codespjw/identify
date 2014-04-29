#include <iostream>
#include <armadillo>
#include "identification.h"

using namespace std;
using namespace arma;
using namespace identification;

const unsigned int steps_number = 100;
const unsigned int input_number = 5; // number of input variables
const unsigned int input_order = 2; // for each input variable
// in total they should identify 15 coefficients, 3 for each input variable

int main(int argc, char** argv) {

  // initialize the two identificators
  identificator*  identificator_rls  = new rls(input_number, input_order);
  identificator*  identificator_nlms = new nlms(input_number, input_order);

  // define a vector of inputs and one single output
  vec inputs = zeros<vec>(input_number*input_order+input_number,1);
  double output;

  // for every computation step
  for(int i=0; i<steps_number; i++) {

    // setting new inputs to random numbers and copying old input values
    for(int j=input_number*input_order+input_number-1; j>0; j--)
      inputs(j) = inputs(j-1);
    for(int j=0;j<input_number*input_order+input_number;j=j+input_order+1)
      inputs(j) = det(randn<vec>(1,1));

    // the system behaves differently in the first half of the test and in
    // the second half, the identified parameters should reflect the last
    // change in the end, so they should be the coefficients of the second
    // part of the test
    
    if (i < (steps_number/2))
      output = +3.0*inputs(0) 
               -2.5*inputs(1) 
               +1.4*inputs(2)
               -0.1*inputs(3) 
               +0.9*inputs(4)
               +0.2*inputs(5) 
               +0.5*inputs(6)
               -3.1*inputs(7)
               +2.1*inputs(8)
               -8.1*inputs(9)
               +0.0*inputs(10)
               +0.0*inputs(11) 
               -0.5*inputs(12)
               -3.1*inputs(13)
               +2.1*inputs(14);

    else
      output = +1.0*inputs(0)
               -1.2*inputs(1)
               +3.0*inputs(2)
               +0.9*inputs(3)
               -0.1*inputs(4)
               +0.1*inputs(5)
               +0.9*inputs(6)
               -8.1*inputs(7)
               +1.1*inputs(8)
               -1.1*inputs(9)
               +0.0*inputs(10)
               +0.0*inputs(11)
               +3.5*inputs(12)
               +1.1*inputs(13)
               -1.1*inputs(14);

    // run identification procedures
    identificator_rls->step(inputs,output);
    identificator_nlms->step(inputs,output);
  }

  // print results at the end of the test both for RLS and for normalized LMS
  identificator_rls->get_weights().print("Weights RLS: ");
  identificator_nlms->get_weights().print("Weights LMS: ");
  return 0;

}
