#ifndef NEURALNETWORK_H
#define NEURALNETWORK_H


#include <vector>
#include <algorithm>
#include <string>
#include <fstream>
#include "perceptron.h"

// TEMPORARY STRUCTURE FOR TESTING ONLY
// REMOVE BEFORE SUBMISSION!!!
struct Param{
	vector<int> layers ;
	float learning_rate ;
	float momentum ;
	float min_error;
} ;



using namespace std;


class neuralnetwork{


public:
	neuralnetwork(Param net_define);

	bool load_weights(string filename);
	bool save_weights(string filename);

    void training(vector<vector<float>> train_inputs, 
				  vector<vector<float>> train_ouputs, 
				  int max_iterations);

	vector<float> testing(vector<float> test_inputs);


	void print_weights(int training_iter);



private:
	vector<int> layers;
	vector<vector<Perceptron>> net ;

	float learning;
	float momentum;
	float threshold;

	// For training and testing
	vector<float> input ;
	vector<float> output ;

	vector<float> feed_forward();
	void adjust_weights();
	float calc_error(vector<float> estimates);

};

#endif
