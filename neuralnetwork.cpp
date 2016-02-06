#include "neuralnetwork.h"
#include "perceptron.h"

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




vector<vector<float>> neuralnetwork::get_weights( vector<vector<Perceptron>> net )
{
    vector<vector<float>> weights;

    vector<float> = curr_weights;
         
    
    for( int i = 0; i < net.size(); i++ ) // for each layer in the net
    {
        for( int j = 0; j < net[i].size(); j++ )  // for each perceptron in current layer
        {
            net[i][j].get_weights( curr_weights );

            weights[i].push_back( curr_weights );
        }   
    }

    return weights;
} 



void neuralnetwork::set_weights( vector<vector<Perceptron>> net, vector<vector<float> weights )
{
    for( int = 0; i < net.size(); i++ )  // for each layer in the ANN
    {
        for( int j = 0; j < net[i].size(); j++)  // for each perceptron in each layer
        {
          // net[i][j].set_weights(

        }
        

    }


}






