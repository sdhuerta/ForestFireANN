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



			// TESTING!!!!
		// vector<float> weights ;
		// for( int i = 0 ; i < net.size(); i++)
		// {
		// 	printf("LAYER: %d\n", i);

		// 	for(int j = 0; j < net[i].size(); j++ )
		// 	{
		// 		printf("NODE: %d WEIGHTS: ", j) ;

		// 		weights = net[i][j].get_weights();

		// 		for(int k = 0; k < weights.size(); k++ )
		// 		{
		// 			printf("%6.4f", weights[k]);
		// 		}

		// 		printf("\n");
		// 		weights.clear();
		// 	}
		// 	printf("\n");
		// }





}



void neuralnetwork::training(vector<vector<float>> train_inputs, 
							 vector<vector<float>> train_ouputs, 
							 int max_iterations)
{
	// Get the training block needed
	// Training block will be larger 
	int train_set_size = train_inputs.size() ;
	vector<int> selections;
	vector<int>::iterator list_check ;
	vector<float> calc_output ;
	int iterations = 0 ;
	float error ;
	int select ;

	while(iterations++ < max_iterations)
	{
		if( selections.size() == train_set_size )
			selections.clear();

		select = rand() % train_set_size ;

		list_check = find(selections.begin(), selections.end(), select);

		if( list_check != selections.end() )
		{
			select = rand() % train_set_size ;

			list_check = find(selections.begin(), selections.end(), select);	
		}

		input = train_inputs[select] ;
		output = train_ouputs[select] ;

		calc_output = feed_forward();

		error = calc_error(calc_output) ;

		// TESTING!!!
		printf("error: %f\n", error);

		if(error < threshold) 
			break ;

		adjust_weights();

		// TESTING!!!!
		// vector<float> weights ;
		// for( int i = 0 ; i < net.size(); i++)
		// {
		// 	printf("TRAINING: %d LAYER: %d\n", (iterations + 1), i);

		// 	for(int j = 0; j < net[i].size(); j++ )
		// 	{
		// 		printf("NODE: %d WEIGHTS: ", j) ;

		// 		weights = net[i][j].get_weights();

		// 		for(int k = 0; k < weights.size(); k++ )
		// 		{
		// 			printf("%6.4f", weights[k]);
		// 		}

		// 		printf("\n");
		// 		weights.clear();
		// 	}
		// 	printf("\n");
		// }

	}

}


vector<float> neuralnetwork::testing(vector<float> test_inputs)
{
	input = test_inputs ;

	return feed_forward();

}


vector<float> neuralnetwork::feed_forward()
{
	vector<float> hidden_outputs;
	vector<float> hidden_inputs;

	//Start with input layer to hidden layer
	for(int i = 0; i < net[0].size(); i++ )
	{
		hidden_inputs.push_back( net[0][i].calc_output( input ));
	}


	// NOW, for the hidden layers leading up to the output layer
	// Start with 1 since we have taken care of the first hidden layer,
	// subtract 1 from the size of the layers as we are not dealing with 
	// the input layer
	for(int i = 1; i < layers.size()-1; i++)
	{
		hidden_outputs.clear();
		hidden_outputs = hidden_inputs ;
		hidden_inputs.clear();

		for(int j = 0; j < net[i].size(); j++)
		{
			hidden_inputs.push_back( net[i][j].calc_output( hidden_outputs )) ;
		}
	}


	// Return the calculated output layer outputs
	return hidden_inputs ;
}



void neuralnetwork::adjust_weights()
{	

    for( int i = net.size()-1; i > -1; i-- )
    {  
    	
        if( i == net.size()-1 )  // if we are processing the output layer
        {

            for( int j = 0; j < net[i].size(); j++ )
            { 
            	net[i][j].set_delta(output[j]);
            }

        }
        else   // processing a hidden layer 
        {

            for( int j = 0; j < net[i].size(); j++)
            {

                net[i][j].set_delta(j, net[i+1]);
            }
        }

    }

    for( int i = 0; i < net.size(); i++ )
    	for(int j = 0; j < net[i].size(); j++)
    		net[i][j].adjust_weights();
}


float neuralnetwork::calc_error(vector<float> estimates)
{
	float error_sum = 0;

	for(int i = 0; i < output.size(); i++ )
	{
		error_sum += 0.5 * pow((output[i] - estimates[i]), 2);
	}

	return error_sum;
}
