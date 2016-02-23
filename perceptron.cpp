#include "perceptron.h"

Perceptron::Perceptron(int num_in, float learning_rate, float mtm)
{
    momentum = mtm ;

    num_inputs = num_in ;

    alpha = learning_rate ;

    float rand_init_val ;

    for(int i = 0; i < num_inputs + 1; i++)
    {
        rand_init_val = ((rand() % 201) - 100)/100.0 ;
        weights.push_back(rand_init_val) ;
    }

    old_weights.assign(weights.size(), 0) ;

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
    sum = 0;
    
    for(int i = 0; i < num_inputs; i++)
        sum += inputs[i] * weights[i] ;

    // add the bias
    sum += weights[num_inputs];
}


void Perceptron::activation()
{
    //Sigmoid function
    output = 1.0 / (1 + exp(-sum)) ;
}

// BACKPROP

// Let's start by calculating the delta

// For our hidden layer weights
void Perceptron::set_delta(int position, vector<Perceptron> next_layer)
{
    delta = 0 ;
    float next_delta;
    float next_weight;

    // FOR EVERY NODE IN THE FOLLOWING LAYER 
    // delta of that layer * connecting weight
    //REMOVE BEFORE SUBMISSION!!!!! printf("HIDDEN NODE BACKPROP\n");
    for(int i = 0; i < next_layer.size(); i++ )
    {
        next_delta = next_layer[i].get_delta(); 
        next_weight = next_layer[i].get_weights()[position] ;
        //REMOVE BEFORE SUBMISSION!!!!!printf("delta: %6.4f    weight: %6.4f\n", next_delta, next_weight);
        delta += next_delta * next_weight   ;
    }

    //REMOVE BEFORE SUBMISSION!!!!!printf("delta: %6.4f    output: %6.4f\n", delta, output);
    delta = 2.0 * delta * output * (1 - output) ;
    //printf("delta: %6.4f\n", delta);
}

// Four our output layer weights
void Perceptron::set_delta(float correct_output)
{
    delta = -2.0 * (correct_output - output) * output * (1.0 - output);
    //REMOVE BEFORE SUBMISSION!!!!!
    // printf("OUTPUT LAYER DELTA: %6.4f TARGET: %6.4f OUTPUT: %6.4f\n",delta,
    //        correct_output, output);
}


// So we can reach back for those hidden layers
float Perceptron::get_delta()
{
    return delta ;
}


// Let's adjust weights for all layers
void Perceptron::adjust_weights()
{
    float temp_momentum;

    for(int i = 0 ; i < weights.size(); i++)
    {
        temp_momentum =  momentum * (weights[i] - old_weights[i]);

        if( i < weights.size()-1)
        {
            weights[i] = weights[i] - alpha * delta * inputs[i]; // + temp_momentum;
        }
        else
            weights[i] = weights[i] - alpha * delta;// + temp_momentum;

        ////REMOVE BEFORE SUBMISSION!!!!! printf("delta: %6.4f    input: %6.4f\n", delta, inputs[i]);
    }

    old_weights = weights ;

}


void Perceptron::set_weights(vector<float> new_weights)
{
    weights = new_weights; 
}

vector<float> Perceptron::get_weights()
{
    return weights ;
}
