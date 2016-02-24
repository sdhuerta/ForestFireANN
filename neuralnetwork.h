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
 * @par Description: 
 * 
 ******************************************************************************/

class neuralnetwork {


public:
    //public function prototypes
    neuralnetwork(Parameters net_define);

    void load_weights();
    bool save_weights();

    float training(vector<trainer> train, int max_iterations, bool print_interval);

    vector<float> testing(vector<float> test_inputs);

    int get_number_o_layers();

    int get_number_o_nodes( int index );

    vector<float> get_perceptron_weights( int layerIndex, int nodeIndex );


    void print_weights(int training_iter);



private:
    //private variables
    vector<int> layers;
    vector<vector<Perceptron>> net ;
    int weightLayers;

    //
    float learning;
    float momentum;
    float threshold;
    string weightsFile;

    // For training and testing
    vector<float> input ;
    vector<float> output ;

    //
    vector<float> feed_forward();
    void adjust_weights();
    float calc_error(vector<float> estimates);


};

#endif

