#ifndef NEURALNETWORK_H
#define NEURALNETWORK_H


#include <vector>
#include <string>
#include <fstream>
#include <algorithm>
#include <iostream>
#include "makesets.h"
#include "perceptron.h"
#include "ParamParser.h"

// TEMPORARY STRUCTURE FOR TESTING ONLY
// REMOVE BEFORE SUBMISSION!!!
struct Param{
	vector<int> layers = { 5, 2, 3, 2 } ; // five inputs, 2 nodes in first h layer, 3 in second h layer, two nodes in o layer
	float learning_rate ;
	float momentum ;
	float min_error;
        string weightsFile = "FakeWeightsFile.txt";
   
} ;



using namespace std;


class neuralnetwork{


public:
	neuralnetwork(Parameters net_define);	

	void load_weights();
        bool save_weights();

	void training(vector<trainer> train, int max_iterations);

	vector<float> testing(vector<float> test_inputs);

    int get_number_o_layers();

    int get_number_o_nodes( int index );

    vector<float> get_perceptron_weights( int layerIndex, int nodeIndex );


	void print_weights(int training_iter);



private:
	vector<int> layers;
	vector<vector<Perceptron>> net ;
        int weightLayers;

	float learning;
	float momentum;
	float threshold;
        string weightsFile;

	// For training and testing
	vector<float> input ;
	vector<float> output ;

	vector<float> feed_forward();
	void adjust_weights();
	float calc_error(vector<float> estimates);
	//void load_weights();
        //void save_weights():

};

#endif

