#ifndef NEURALNETWORK_H
#define NEURALNETWORK_H


class neuralnetwork{


public:
	neuralnetwork(Param net_define);



private:
vector<int> layers;
vector<vector<Perceptron>> net ;
float learning;
float momentum;
float threshold;

vector<vector<float>> get_weights( vector<vector<Perceptron>> net );

void set_weights( vector<vector<Perceptron>> net, vector<vector<vector<float>>> weights);

// For training and testing
vector<float> input ;
vector<float> output ;



};

#endif
