class neuralnetwork
{
public:
	neuralnetwork(Param net_define);



private:
vector<int> layers;
vector<vector<Perceptron>> net ;
float learning;
float momentum;
float threshold;

// For training and testing
vector<float> input ;
vector<float> output ;

};


neuralnetwork::neuralnetwork(Param net_define)
{

	layers = net_define.get_layers() ;
	learning = net_define.get_learning() ;
	momentum = net_define.get_momentumd() ;
	threshold = net_define.get_threshold();

	// Skip the input layer node
	for(int i = 1; i < layers.size ; i++)
	{
		vector<Perceptron> layer ;

		for(int j = 0; j < layers[i]; j++)
		{
			Perceptron new_node = Perceptron(layers[i])
		
			layer.push_back(new_node) ;
		}

		net.push_back(layer) ;

	}

}


neuralnetwork::training(vector<float> inputs)
{
	vector<float> outputs

	for(int i = 0; i < layers.size(); i++)
	{
		for(int j = 0; j < layers[i].size(); j++)
		{
			

		}
	}




}