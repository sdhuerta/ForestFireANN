#include "perceptron.h"


/******************************************************************************
 * @authors  Steven Huerta, Luke Meyer, Savoy Schuler
 *
 * @par Description: Perceptron contructor. The constructor takes in the
 * number of inputs it will receive, as well as the learning rate and
 * momentum values. It will generate a vector for weights, initializing
 * them to a random value. It will also add a bias weight.
 *
 * @param[in] num_in - the number of inputs for the perceptron
 * @param[in] learning_rate - the learning rate factor
 * @param[in] mtm - the momentum factor for the perceptron
 *
 *****************************************************************************/

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


/******************************************************************************
 * @authors  Steven Huerta, Luke Meyer, Savoy Schuler
 *
 * @par Description: This function will pass the inputs to functions to sum
 * the product of weights and inputs, it will then call the activation
 * function to calculate the output and return that output.
 *
 * @param[in] percept_inputs - a vector of input values
 *
 * @returns output - the calculated value after the perceptron fires
 *
 *****************************************************************************/

float Perceptron::calc_output(vector <float> percept_inputs)
{
    inputs = percept_inputs ;
    // Sum up all the weights
    sum_weights();

    // Apply sigmoid to sum for this perceptron
    activation();

    return output ;
}


/******************************************************************************
 * @authors  Steven Huerta, Luke Meyer, Savoy Schuler
 *
 * @par Description: This function sums the product of the weights and inputs.
 *
 *****************************************************************************/

void Perceptron::sum_weights()
{
    // reset our sum to zero before calculating our product again
    sum = 0;

    // sum up the products of the weights and inputs
    for(int i = 0; i < num_inputs; i++)
        sum += inputs[i] * weights[i] ;

    // add the bias
    sum += weights[num_inputs];
}


/******************************************************************************
 * @authors  Steven Huerta, Luke Meyer, Savoy Schuler
 *
 * @par Description: This function calculates the output by applying the
 * sigmoid function to the sum of the products.
 *****************************************************************************/

void Perceptron::activation()
{
    //Sigmoid function
    output = 1.0 / (1 + exp(-sum)) ;
}


/******************************************************************************
 * @authors  Steven Huerta, Luke Meyer, Savoy Schuler
 *
 * @par Description: This function calculates the delta for the perceptron
 * located in the hidden layer. The function grabs the weights and deltas
 * from the next layer to calculate the delta for this perceptron.
 *
 * @param[in] position - position in the current layer among other perceptrons
 * @param[in] next_layer - vector of perceptrons from the next layer of the
 *                         network.
 *****************************************************************************/

void Perceptron::set_delta(int position, vector<Perceptron> next_layer)
{
    delta = 0 ; // reset our delta to 0
    float next_delta;
    float next_weight;

    // FOR EVERY NODE IN THE FOLLOWING LAYER
    // delta of that layer * connecting weight

    // For all the nodes in the next layer ...
    for(int i = 0; i < next_layer.size(); i++ )
    {
        // ...let's grab their delta value...
        next_delta = next_layer[i].get_delta();

        //... and let's grab the weight associated between our output
        // and that next layer's node...
        next_weight = next_layer[i].get_weights()[position] ;

        //.. and then accumulate their product
        delta += next_delta * next_weight   ;
    }


    // this is the product of the delta and sigmoid prime with
    // an extra multiplier to prevent super small increments
    // This is a WAG factor
    delta = 2.0 * delta * output * (1 - output) ;
}


/******************************************************************************
 * @authors  Steven Huerta, Luke Meyer, Savoy Schuler
 *
 * @par Description: This function calculates the delta values for output
 * layer nodes.
 *
 * @param[in] correct_output - the expected output term
 *
 *****************************************************************************/

void Perceptron::set_delta(float correct_output)
{
    // calculate delta term
    // Delta term calculated as described in
    // Fundamentals of Natural Computing, Leandro Nunes de Castro
    delta = -2.0* (correct_output - output) * output * (1.0 - output);
}


/******************************************************************************
 * @authors  Steven Huerta, Luke Meyer, Savoy Schuler
 *
 * @par Description: Return the delta for this perceptron
 *
 * @returns delta - the delta term for the perceptron
 *
 *****************************************************************************/

float Perceptron::get_delta()
{
    return delta ;
}


/******************************************************************************
 * @authors  Steven Huerta, Luke Meyer, Savoy Schuler
 *
 * @par Description: This function makes a change to each of the weights
 * for the perceptron.
 *
 *****************************************************************************/

void Perceptron::adjust_weights()
{
    // To store our calculated momentum
    float temp_momentum;

    // For each of our weights...
    for(int i = 0 ; i < weights.size(); i++)
    {
        //...let's calculate the momentum...
        temp_momentum =  momentum * (weights[i] - old_weights[i]);
        //...and unless its the bias...
        if( i < weights.size()-1)
        {
            //...we'll subtract a fraction of the product of the delta and
            // and the input, then add some back(momentum)...
            weights[i] = weights[i] - alpha * delta * inputs[i] + temp_momentum;
        }
        else // adjust the bias weight
            weights[i] = weights[i] - alpha * delta + temp_momentum;
    }

    // track the current weights as old weights to later generate momentum
    old_weights = weights ;

}


/******************************************************************************
 * @authors  Steven Huerta, Luke Meyer, Savoy Schuler
 *
 * @par Description: This function sets its weights to the vector of weights
 * received.
 *
 * @param[in] new_weights vector of the weights
 *
 *****************************************************************************/

void Perceptron::set_weights(vector<float> new_weights)
{
    weights = new_weights;
}


/******************************************************************************
 * @authors  Steven Huerta, Luke Meyer, Savoy Schuler
 *
 * @par Description: This function returns a vector of weights for this
 * perceptron.
 *
 * @returns weights - vector of weights
 *
 *****************************************************************************/

vector<float> Perceptron::get_weights()
{
    return weights ;
}
