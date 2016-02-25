/*****************************************************************************/
/* @file                        perceptron.h                                 */
/*****************************************************************************/
#ifndef PERCEPTRON_H
#define PERCEPTRON_H
#include <vector>
#include <math.h>
#include <time.h>
#include <stdlib.h>
#include <stdio.h>

using namespace std;

/**************************************************************************//**
 * @author Steven Huerta, Luke Meyer, Savoy Schuler
 *
 * @par Description: Perceptron is the base unit of a neural network. It is a
 * simple model of a neuron. It accumulates and sums products to produce an
 * activation signal[1,0]. This perceptron is capable of adjusting its weights
 * when in a network to better classify the inputs.
 *
 ******************************************************************************/
class Perceptron {
public:
    /*!
     * @brief CONSTRUCTOR
     */
    Perceptron(int num_in, float learning_rate, float mtm);

    /*!
     * @brief Calculates the activation signal for the perceptron
     */
    float calc_output(vector <float> inputs);

    /*!
     * @brief Returns the output signal
     */
    float get_output();

    /*!
     * @brief Returns the delta value for perceptron
     */
    float get_delta();

    /*!
     * @brief Adjusts the weights of the perceptron
     */
    void adjust_weights();

    /*!
     * @brief Sets the weights of the perceptron
     */
    void set_weights(vector<float> new_weights);

    /*!
     * @brief Returns the weights of the perceptron
     */
    vector<float> get_weights();

    /*!
     * @brief Calculates the delta for a hidden layer perceptron
     */
    void set_delta(int position, vector<Perceptron> next_layer);

    /*!
     * @brief Calculates the delta for an output layer perceptron
     */
    void set_delta(float correct_output);

private:

    /*!
     * @brief Activation function, using sigmoid function
     */
    void activation();
    /*!
     * @brief Sum the product of the inputs and the weights
     */
    void sum_weights();

    vector<float> weights;/*!< Perceptron weights  */

    vector<float> inputs;/*!<  Inputs received by the perceptron */

    vector<float> old_weights;/*!<  Perceptron weights from previous iteration*/

    float sum ; /*!< sum of products of weights and inputs  */

    float output ; /*!<  sigmoid applied to sum */

    float delta ;/*!<  gradient */

    int num_inputs;	/*!<do i need num_inputs if I'm carrying a vector of
		  	inputs??*/

    float alpha ;/*!<  learning rate */

    float momentum ;	/*!< momentum value - how strongly we want to carry our
			previous weight adjustment forward  */
};

#endif
