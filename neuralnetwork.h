#ifndef NEURALNETWORK_H
#define NEURALNETWORK_H


#include <vector>
#include "perceptron.h"


using namespace std;


class neuralnetwork{


public:
	neuralnetwork(Param net_define);



private:
vector<int> layers;
vector<vector<Perceptron>> net ;
float learning;
float momentum;
float threshold;

vector<vector<float>> get_weights( vector<vector<Perceptron>> );

void set_weights( vector<vector<Perceptron>>, vector<vector<vector<float>>>);

// For training and testing
vector<float> input ;
vector<float> output ;




};

#endif
