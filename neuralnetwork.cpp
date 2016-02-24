#include "neuralnetwork.h"


/******************************************************************************
 * @authors  Steven Huerta, Luke Meyer, Savoy Schuler
 *
 * @par Description:
 *
 *
 * @param[in]     
 *                   
 * @param[in]    
 *
 * @returns 
 *
 *****************************************************************************/

neuralnetwork::neuralnetwork(Parameters net_define)
{

	layers = net_define.nodesPerLayer ;
	learning = net_define.learningRate ;
	momentum = net_define.momentum ;
	threshold = net_define.errorThreshold;
  weightsFile = net_define.weightsFile;

	// Skip the input layer node.
	for(int i = 1; i < layers.size() ; i++)
	{
		vector<Perceptron> layer ;

		for(int j = 0; j < layers[i]; j++)
		{
			Perceptron new_node = Perceptron(layers[i-1],learning, momentum) ;
		
			layer.push_back(new_node) ;
		}

		net.push_back(layer) ;

	}

}


/******************************************************************************
 * @authors  Steven Huerta, Luke Meyer, Savoy Schuler
 *
 * @par Description:
 *
 *
 * @param[in]     
 *                   
 * @param[in]    
 *
 * @returns 
 *
 *****************************************************************************/

float neuralnetwork::training(vector<trainer> train, int max_iterations, bool print_interval)
{
	// Get the training block needed
	// Training block will be larger 
	int train_set_size = train.size() ;

	vector<int> selections;
	vector<int>::iterator list_check ;
	vector<float> calc_output ;
	int iterations = 0 ;
	float error = 0.0;
	int select ;

  //max_iterations = 10 ;

	while(iterations < max_iterations)
	{ 
		select = rand() % train_set_size ;

		list_check = find(selections.begin(), selections.end(), select);

		while( list_check != selections.end() )
		{
			select = rand() % train_set_size ;

			list_check = find(selections.begin(), selections.end(), select);	
		}

		selections.push_back(select) ;

		input = train[select].input ;
		output = train[select].output ;

		calc_output = feed_forward();

    adjust_weights();

		error += calc_error(calc_output) ;

		// One iteration means that we have trained on the entire training
		// set once. 
		if( selections.size() == train_set_size )
		{
			selections.clear();
			iterations++ ;

      if( print_interval == true  && iterations % 10 == 0)
  		  printf("Epoch: %-6d\tMSE: %6.4f\n", iterations, (error / train_set_size));

  		if( (error / train_set_size) <= threshold) 
  		{
  			return  error / train_set_size;
  		}

      if( iterations == max_iterations )
      {
        return error / train_set_size ;
      }

		  error = 0 ;
    }

    //print_weights(iterations) ;
	}
		
}


/******************************************************************************
 * @authors  Steven Huerta, Luke Meyer, Savoy Schuler
 *
 * @par Description:
 *
 *
 * @param[in]     
 *                   
 * @param[in]    
 *
 * @returns 
 *
 *****************************************************************************/

vector<float> neuralnetwork::testing(vector<float> test_inputs)
{
	input = test_inputs ;

	return feed_forward();

}


/******************************************************************************
 * @authors  Steven Huerta, Luke Meyer, Savoy Schuler
 *
 * @par Description:
 *
 *
 * @param[in]     
 *                   
 * @param[in]    
 *
 * @returns 
 *
 *****************************************************************************/

vector<float> neuralnetwork::feed_forward()
{
	vector<float> hidden_outputs;
	vector<float> hidden_inputs;

  hidden_outputs = input; 

	for(int i = 0; i < net.size(); i++)
	{
		hidden_inputs = hidden_outputs ;
		hidden_outputs.clear();

		for(int j = 0; j < net[i].size(); j++)
		{
			hidden_outputs.push_back( net[i][j].calc_output( hidden_inputs )) ;
		}

		hidden_inputs.clear();
	}
	// Return the calculated output layer outputs
	return hidden_outputs ;
}


/******************************************************************************
 * @authors  Steven Huerta, Luke Meyer, Savoy Schuler
 *
 * @par Description:
 *
 *
 * @param[in]     
 *                   
 * @param[in]    
 *
 * @returns 
 *
 *****************************************************************************/

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
  	{
  		net[i][j].adjust_weights();
  	}
}


/******************************************************************************
 * @authors  Steven Huerta, Luke Meyer, Savoy Schuler
 *
 * @par Description:
 *
 *
 * @param[in]     
 *                   
 * @param[in]    
 *
 * @returns 
 *
 *****************************************************************************/

float neuralnetwork::calc_error(vector<float> estimates)
{
	float error_sum = 0;

	for(int i = 0; i < output.size(); i++ )
	{
		error_sum += pow((output[i] - estimates[i]), 2);
	}

	return error_sum;
}


/******************************************************************************
 * @authors  Steven Huerta, Luke Meyer, Savoy Schuler
 *
 * @par Description:
 *
 *
 * @param[in]     
 *                   
 * @param[in]    
 *
 * @returns 
 *
 *****************************************************************************/

void neuralnetwork::print_weights(int training_iter)
{

	vector<float> weights ;

	printf("SIZE: %d",(int)net.size());

	for( int i = 0 ; i < net.size(); i++)
	{
		printf("TRAINING: %d LAYER: %d\n", training_iter, i);

		for(int j = 0; j < net[i].size(); j++ )
		{
			printf("NODE: %d WEIGHTS: ", j) ;

			weights = net[i][j].get_weights();

			for(int k = 0; k < weights.size(); k++ )
			{
				printf("%6.4f   ", weights[k]);
			}

			printf("\n");
			weights.clear();
		}

		printf("\n");
	}

}


/******************************************************************************
 * @authors  Steven Huerta, Luke Meyer, Savoy Schuler
 *
 * @par Description:
 *
 *
 * @param[in]     
 *                   
 * @param[in]    
 *
 * @returns 
 *
 *****************************************************************************/

void neuralnetwork::load_weights()
{
	vector<float> temp_weights;
	float next_weight;

    ifstream fin( weightsFile.c_str());

    if( !fin )
    {
        std::cout << "There was an error opening the weights file: " << weightsFile << endl;
        return;

    }

    for(int i = 0; i < net.size(); i++)
      for( int j = 0; j < net[i].size(); j++)
      {
        temp_weights.clear();

        for( int k = 0; k < layers[i] + 1; k++)
        {
          fin >> next_weight ;
          temp_weights.push_back( next_weight );
        }

        net[i][j].set_weights(temp_weights);

      }

    fin.close();
} 


/******************************************************************************
 * @authors  Steven Huerta, Luke Meyer, Savoy Schuler
 *
 * @par Description:
 *
 *
 * @param[in]     
 *                   
 * @param[in]    
 *
 * @returns 
 *
 *****************************************************************************/

bool neuralnetwork::save_weights()
{
    ofstream fout( weightsFile.c_str());
   
    
    if( !fout )
    {
        std::cout << "Could not locate the file: " << weightsFile << endl;
        return false;
    }

    for( int i = 0; i < net.size(); i++ )  // for each layer in the ANN
    {
        
        for( int j = 0; j < net[i].size(); j++)  // for each perceptron in current layer
        {
         
            vector<float> curr_weights =  net[i][j].get_weights();  // get the weights      

            
            for( int k = 0; k < curr_weights.size(); k++ )
            {
                fout << curr_weights[k] << endl;  //  write them to file

            }            
        }
    }
    fout.close();
    return true;
}
