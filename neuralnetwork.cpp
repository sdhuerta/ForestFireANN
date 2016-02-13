#include "neuralnetwork.h"
#include "perceptron.h"


using namespace std;




neuralnetwork::neuralnetwork(Param net_define)
{

	layers = net_define.get_layers() ;
	learning = net_define.get_learning() ;
	momentum = net_define.get_momentumd() ;
	threshold = net_define.get_threshold();

	// Skip the input layer node. The layer is n-1, so 
	// the 1st hidden layer node is layer 0.
	for(int i = 0; i < layers.size ; i++)
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


neuralnetwork::training(vector<float> train_inputs, 
						vector<float> train_ouputs, 
						int max_iterations, 
						float min_error)
{
	input = train_inputs;
	output = train_outputs;

	int iterations = 0 ;

	while(iterations++ < max_iterations)
	{
		vector<float> ff_output ;

		ff_output = feed_foward();

		error = calc_error(ff_output) ;

		if(error < min_error) 
			break ;

		// If we need to adjust the weights, lets calc the
		// deltas first
		calculate_delta(ff_output);

		adjust_weights();

		if(error < min_error) 
			break ;

	}

}


neuralnetwork::feed_foward()
{
	// Setup input layer to feed to first hidden layer
	vector<float> curr_inputs = inputs ;

	// For every layer starting with the hidden layer to the output layer
	for(int i = 0; i < layers.size(); i++)
	{
		vector<float> curr_outputs ;
		
		// For every perceptron in this current layer
		for(int j = 0; j < net[i].size(); j++)
		{
			curr_outputs.pushback(net[i][j].get_output(curr_inputs) ;
		}

		if( i != layers.size() - 1)
		{
			vector<float> curr_inputs ;
			curr_inputs = curr_outputs ;
		}

	}

	return curr_outputs ;

}


neuralnetwork::calculate_delta()
{

}


neuralnetwork::adjust_weights()
{

}



/* untested code below:
 *
vector<vector<float>> neuralnetwork::get_weights( vector<vector<Perceptron>> net )
{
    vector<vector<vector<float>>> weights;

    vector<float> = curr_weights;
         
    
    for( int i = 0; i < net.size(); i++ ) // for each layer in the net
    {
        for( int j = 0; j < net[i].size(); j++ )  // for each perceptron in current layer
        {
            net[i][j].get_weights( curr_weights );  // get them weights

            weights[i][j].push_back( curr_weights );
        }   
    }

    return weights;
} 



void neuralnetwork::set_weights( vector<vector<Perceptron>> net, vector<vector<vector<float>>> weights )
{
    for( int = 0; i < net.size(); i++ )  // for each layer in the ANN
    {
        for( int j = 0; j < net[i].size(); j++)  // for each perceptron in current layer
        {
           net[i][j].set_weights( weights[i][j]);  // set them weights

        }
        

    }


}

*/





