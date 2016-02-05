#ifndef PERCEPTRON_H
#define PERCEPTRON_H

#include <vector>
#include <time.h> // RAND


class Perceptron{
public:
    // CONSTRUCTOR
    Perceptron(int num_inputs, double learning_rate);

    // Feed the perceptron some inputs and get some output
    double get_output(vector <double> inputs);

    // Getting the error from the previous weights
    double get_error(int perceptron_pos);
    void adjust_weights(); //may make this a private function

    void Perceptron::set_error(int position, vector<Perceptron> next_layer);
    void Perceptron::set_error(double correct_output);

    double Perceptron::get_error(int perceptron_pos);

private:
    void activation(); // Activation function, using sigmoid function
    void sum_weights(); // Calculate the output

    // Store our weights and inputs between previous and current layer
    vector<double> weights;
    vector<double> inputs ;	
    
    double sum ; // sum after application of weights
    double output ; // result of sigmoid of sum

    // USED LATER WITH ADJUSTING WEIGHTS
    double sig_prime ; // the derivative of sigmoid applied to sum
    double error ;

    int num_inputs; // do i need num_inputs if I'm carrying a vector of inputs??

    float alpha ;
};

#endif
