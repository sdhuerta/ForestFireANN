#include "perceptron.h"


class NN_Layer{
public:
	NN_Layer(int num_nodes, double alpha, int inputs_per_node);




private:
	vector<Perceptron> nodes ;




};



void NN_Layer::NN_Layer(int num_nodes, double alpha, int inputs_per_node)
{

	for(int i = 0; i < num_nodes; i++)
	{
		nodes.push_back(Perceptron(inputs_per_node, alpha)) ;
	}
}


void NN_Layer::feed_foward(vector<double> inputs)
{
	for(int i = 0; i < nodes.size(); i++)
	{

	}
}