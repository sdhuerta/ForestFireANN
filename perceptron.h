#ifndef PERCEPTRON_H
#define PERCEPTRON_H

#include <vector>
#include <math.h>
#include <time.h> 
#include <stdlib.h>
#include <stdio.h>

using namespace std;



class Perceptron{
public:
    // CONSTRUCTOR
    Perceptron(int num_in, float learning_rate);

    // Feed the perceptron some inputs and get some output
    float calc_output(vector <float> inputs);
    float get_output(); // grab what has been calculated

    // Getting the delta from the previous weights
    float get_delta();
    void adjust_weights(); //may make this a private function

    // Setters and getters
    void set_weights(vector<float> new_weights);
    vector<float> get_weights();

    void set_delta(int position, vector<Perceptron> next_layer);
    void set_delta(float correct_output);


private:
    void activation(); // Activation function, using sigmoid function
    void sum_weights(); // Calculate the output

    // Store our weights and inputs between previous and current layer
    vector<float> weights;
    vector<float> inputs;
    
    float sum ; // sum after application of weights
    float output ; // result of sigmoid of sum

    // USED LATER WITH ADJUSTING WEIGHTS
    float sig_prime ; // the derivative of sigmoid applied to sum
    float delta ;

    int num_inputs; // do i need num_inputs if I'm carrying a vector of inputs??

    float alpha ;
};

#endif
