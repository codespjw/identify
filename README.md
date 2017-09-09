identify
========

C++ library for identification prodedures
[![Build Status](https://travis-ci.org/martinamaggio/identify.png)](https://travis-ci.org/martinamaggio/identify)


Requirements
--
The library requires Armadillo, the C++ linear algebra library that can be downloaded [here](http://arma.sourceforge.net/).
On debian-like systems, Armadillo can be installed typing:
```
sudo apt-get install libarmadillo-dev
```

Recursive Least Square Estimator Usage
--
To define and use an [RLS estimator](http://en.wikipedia.org/wiki/Recursive_least_squares_filter), only three lines of code are necessary.
```
identificator*  identificator_rls  = new rls(input_number, input_order);
identificator_rls->step(inputs, output);
identificator_rls->get_weights();
```
The first line initializes the estimator, receiving as parameters the number of inputs and their order (the number of past values considered for the identification procedure). It should be called only in the initialization phase.

The second line calls the estimation step. The estimator should receive a vector of input values and the corresponding measured output. The vector of input values should have a size that is equal to the number of input variables times the input order augmented by one (for each input it will also receive the current value). The input vector is an Armadillo vector with the values ordered for each input.
```
vec inputs = zeros<vec>(input_number*input_order+input_number, 1);
// in1(k), in1(k-1) ... in1(k-_n_order), in2(k), ... in2(k-_n_order) ...
```

The third line retrieves the coefficients of the variables after the estimation procedure is completed. It can be called after every "step" or in any other moment to retrieve the current estimated coefficients.

Normalized Least Mean Squares
--
To define and use a normalized [LMS estimator](http://en.wikipedia.org/wiki/Least_mean_squares_filter), only three lines of code are necessary.
```
identificator*  identificator_nlms = new nlms(input_number, input_order);
identificator_nlms->step(inputs, output);
identificator_nlms->get_weights();
```
The usage is the same as for the RLS estimator.


