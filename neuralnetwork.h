/*****************************************************************************/
/* @file                       neuralnetwork.h                               */
/*****************************************************************************/

//include files
#ifndef NEURALNETWORK_H
#define NEURALNETWORK_H
#include <vector>
#include <string>
#include <fstream>
#include <algorithm>
#include <iostream>
#include "makesets.h"
#include "perceptron.h"

using namespace std;


/**************************************************************************//**
 * @author Steven Huerta, Luke Meyer, Savoy Schuler
 *
 * @par Description: This object creates a back prob network consisting of
 * a number of hidden layers and perceptrons per layer defined by the
 * parameters passed to it.
 *
 ******************************************************************************/

class neuralnetwork {


public:
    /*!
    * @brief CONSTRUCTOR
    */
    neuralnetwork(Parameters net_define);

    /*!
     * @brief loads the weights from a file
     */
    void load_weights();

    /*!
     * @brief saves the weights to a file
     */
    bool save_weights();

    /*!
     * @brief trains the network on a set of input sets
     */
    float training(vector<trainer> train, int max_iterations,
                   bool print_interval);

    /*!
     * @brief returns output from inputs given to the network
     */
    vector<float> testing(vector<float> test_inputs);

    /*!
     * @brief prints the weights to the console
     */
    void print_weights(int training_iter);



private:
    /*!
     * @brief calculates the output of the network
     */
    vector<float> feed_forward();

    /*!
     * @brief adjusts the weights of the network
     */
    void adjust_weights();

    /*!
     * @brief calculates the SSE
     */
    float calc_error(vector<float> estimates);

    //private variables
    vector<int> layers; /*!< size of each network layer */
    vector<vector<Perceptron>> net ; /*!< network of perceptrons  */

    float learning; /*!< learning rate  */
    float momentum; /*!< momentum value  */
    float threshold; /*!< minimum error threshold  */
    string weightsFile; /*!< name of the weights file  */

    // For training and testing
    vector<float> input ; /*!< Inputs to the network */
    vector<float> output ; /*!< Expected outputs  */

};

#endif

