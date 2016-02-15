#include "neuralnetwork.h"


neuralnetwork::neuralnetwork(Param net_define)
{

	layers = net_define.layers ;
	learning = net_define.learning_rate ;
	momentum = net_define.momentum ;
	threshold = net_define.min_error;

	// Skip the input layer node.
	for(int i = 1; i < layers.size() ; i++)
	{
		vector<Perceptron> layer ;

		for(int j = 0; j < layers[i]; j++)
		{
			Perceptron new_node = Perceptron(layers[i-1],learning) ;
		
			layer.push_back(new_node) ;
		}

		net.push_back(layer) ;

	}

}



void neuralnetwork::training(vector<float> train_inputs, 
							 vector<float> train_ouputs, 
							 int max_iterations)
{
	// Get the training block needed
	// Training block will be larger 
	input = train_inputs;
	output = train_ouputs;

	int iterations = 0 ;

	float error ;

	while(iterations++ < max_iterations)
	{
		vector<float> ff_output ;

		ff_output = feed_forward();

		error = calc_error(ff_output) ;

		if(error < threshold) 
			break ;

		// If we need to adjust the weights, lets calc the
		// deltas first

		adjust_weights();

		if(error < threshold) 
			break ;

	}

}


vector<float> neuralnetwork::feed_forward()
{
	// Setup input layer to feed to first hidden layer
	vector<float> curr_inputs = input ;
	vector<float> curr_outputs ;

	// For every layer starting with the hidden layer to the output layer
	for(int i = 1; i < layers.size(); i++)
	{
		curr_outputs.clear() ;
		
		// For every perceptron in this current layer
		for(int j = 0; j < net[i].size(); j++)
		{
			curr_outputs.push_back(net[i][j].calc_output(curr_inputs) );
		}

		if( i != layers.size() - 1)
		{
			vector<float> curr_inputs ;
			curr_inputs = curr_outputs ;
		}

	}

	return curr_outputs ;

}

void neuralnetwork::adjust_weights()
{	

    for( int i = layers.size() - 1; i > 0; i-- )
    {  
        if( i == layers.size() - 1 )  // if we are processing the output layer
        {
            for( int j = 0; j < net[i].size(); j++ )
            { 
            	net[i][j].set_delta(output[j]);

                net[i][j].adjust_weights();
            }

        }
        else   // processing a hidden layer 
        {

            for( int j = 0; j < net[i].size(); j++)
            {

                net[i][j].set_delta(j, net[i+1]);

                net[i][j].adjust_weights();
            }
        }

    }


}

float neuralnetwork::calc_error(vector<float> estimates)
{
	float error_sum = 0;

	for(int i = 0; i < output.size(); i++ )
	{
		error_sum += pow((output[i] - estimates[i]), 2);
	}

	return error_sum;
}

/* untested code below:
 *
vector<vector<vector<float>>> neuralnetwork::get_weights()//vector<vector<Perceptron>> net )
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



void neuralnetwork::set_weights( vector<vector<vector<float>>> weights) //vector<vector<Perceptron>> net, vector<vector<vector<float>>> weights )
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





