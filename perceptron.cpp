#include "perceptron.h"

Perceptron::Perceptron(int num_inputs, float learning_rate)
{
    num_inputs = num_inputs ;

    alpha = learning_rate ;

    int rand_init_val ;

    srand(time(null));
    for(int i = 0; i < num_inputs; i++)
    {
        rand_init_val =  (rand() % 100 + 1) / 1000 ;
        weights.push_back(rand_init_val) ;
    }

}


 float Perceptron::get_output(vector <float> inputs)
{
    inputs = inputs ;
    // Sum up all the weights
    sum_weights( inputs );

    // Apply sigmoid to sum for this perceptron
    activation();

    return output ;
}


void Perceptron::sum_weights(vector <float> inputs)
{
    for(int i = 0; i < num_inputs; i++)
        sum += inputs[i] * weights[i] ;
}


void Perceptron::activation()
{
    //Sigmoid function
    output = 1.0 / (1 + exp(-sum)) ;

    // While we're here, let's calculate the sigmoid derivative for the 
    // purpose of backprop
    sig_prime = output * (1 - output);
}

// BACKPROP

// Let's start by calculating the error

// For our hidden layer weights
void Perceptron::set_error(int position, vector<Perceptron> next_layer)
{
    float error = 0 ;

    for(int i = 0; i < next_layer.size(); i++ )
    {
        error += next_layer[i].get_error(position)
    }

    error = error * sig_prime;

}

// Four our output layer weights
void Perceptron::set_error(float correct_output)
{
    error = sig_prime * (correct_output - output) ;
}


// So we can reach back for those hidden layers
float Perceptron::get_error(int perceptron_pos)
{
    return error * weights[perceptron_pos] ;
}


// Let's adjust weights for all layers
void Perceptron::adjust_weights()
{
    for(int i = 0 ; i < weights.size(); i++)
    {
        weights[i] = weights[i] + alpha * error * inputs[i];
    }

}


void Perceptron::set_weights(vector<float> new_weights)
{
    for(int i = 0; i < new_weights.size(); i++)
        weights[i] = new_weights[i] ;
}

void Perceptron::get_weights()
{
    return weights ;
}

 // Writing weights to file


// Setting weights to file


// 