#include "perceptron.h"

Perceptron::Perceptron(int num_in, float learning_rate)
{

    num_inputs = num_in ;

    alpha = learning_rate ;

    int rand_init_val ;

    for(int i = 0; i < num_inputs; i++)
    {
        rand_init_val =  (rand() % 100 + 1) / 1000 ;
        weights.push_back(rand_init_val) ;
    }

}


float Perceptron::calc_output(vector <float> percept_inputs)
{
    inputs = percept_inputs ;
    // Sum up all the weights
    sum_weights();

    // Apply sigmoid to sum for this perceptron
    activation();

    return output ;
}


void Perceptron::sum_weights()
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

// Let's start by calculating the delta

// For our hidden layer weights
void Perceptron::set_delta(int position, vector<Perceptron> next_layer)
{
    float delta = 0 ;

    for(int i = 0; i < next_layer.size(); i++ )
    {
        delta += next_layer[i].get_delta(position);
    }

    delta = delta * sig_prime;

}

// Four our output layer weights
void Perceptron::set_delta(float correct_output)
{
    delta = sig_prime * (correct_output - output) ;
}


// So we can reach back for those hidden layers
float Perceptron::get_delta(int perceptron_pos)
{
    return delta * weights[perceptron_pos] ;
}


// Let's adjust weights for all layers
void Perceptron::adjust_weights()
{
    for(int i = 0 ; i < weights.size(); i++)
    {
        weights[i] = weights[i] + alpha * delta * inputs[i];
    }

}


void Perceptron::set_weights(vector<float> new_weights)
{
    weights = new_weights; 
}

vector<float> Perceptron::get_weights()
{
    return weights ;
}

 // Writing weights to file


// Setting weights to file


// 