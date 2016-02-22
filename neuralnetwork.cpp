#include "neuralnetwork.h"


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



void neuralnetwork::training(vector<trainer> train, int max_iterations)
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

  //max_iterations = 5 ;

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

		error += calc_error(calc_output) ;

		// One iteration means that we have trained on the entire training
		// set once. 
		if( selections.size() == train_set_size )
		{
			selections.clear();
			iterations++ ;

      if(iterations % 10 == 0)
  		   printf("Epoch: %d  error: %.4f\n", iterations, (error / train_set_size));

  		if( (error / train_set_size) < threshold) 
  		{
        printf("Epoch: %d  error: %.4f\n", iterations, (error / train_set_size));
  			//printf("NUM ITERATIONS: %d\n", iterations);
  			return ;
  		}

		  error = 0 ;
    }

    adjust_weights();
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
		hidden_outputs.push_back( net[0][i].calc_output( input ));
	}


	// NOW, for the hidden layers leading up to the output layer
	// Start with 1 since we have taken care of the first hidden layer,
	// subtract 1 from the size of the layers as we are not dealing with 
	// the input layer
	for(int i = 1; i < net.size(); i++)
	{
		hidden_inputs = hidden_outputs ;
		hidden_outputs.clear();

		//printf("%d\n",i);

		for(int j = 0; j < net[i].size(); j++)
		{
			hidden_outputs.push_back( net[i][j].calc_output( hidden_inputs )) ;
		}

		hidden_inputs.clear();
	}


	// Return the calculated output layer outputs
	return hidden_outputs ;
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
    	{
    		//printf("Adjusting Layer: %d Node %d\n", i, j) ;
    		net[i][j].adjust_weights();
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

void neuralnetwork::load_weights()
{
  vector<float> temp_weights;
  float next_weight;
  /*
    int inputNum = -10;
    vector<int> hNodes;
    vector<float> curr_weights;
    float temp = -1.0;


    int oNodes = -10;

    // get important info regarding the network layers i.e. number of hidden layers, number of ouput nodes, number of inputs to first hidden layer
    

    for( int i = 0; i < layers.size(); i++ )
    {
        if( i == 0 )
        {
            inputNum = layers[i];
        }
        else if( i == ( layers.size() - 1 ) )   
        {
            oNodes = layers[i];

        }
        else
        {
            hNodes.push_back( layers[i] );
        }

    }


    int numWeightsTotal = -1;  //will hold the expected number of weights to be loaded
    int weightCount = 0;   // will track actual number of weights that were loaded in
    */

    /*
    // calculate the expected total number of weights
    for( int i = 0; i < hNodes.size(); i++ )
    {
        if( i == 0 )
        {
            numWeightsTotal += ( inputNum * hNodes[i] );

            cout << numWeightsTotal << endl;
        } 
        else  if( i == hNodes.size() - 1 )
        {
            numWeightsTotal += ( oNodes * hNodes[i] );
            numWeightsTotal += ( hNodes[i - 1] * hNodes[i] );

        }
        else
        {
            numWeightsTotal += ( hNodes[i] * hNodes[ i + 1 ] );

        }       

    }

  // The above code produces an expected value that is 1 less than the actual value. Needs fixing or maybe we just discard the actual vs. expected check
  */

   
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

   /*

    // load weights for all hidden layer nodes
    for( int i = 0; i < net.size(); i++ )  // for each of the hidden layers
    {
        cout << "The number of hidden layers is: " << hNodes.size() << endl;

        if( i == 0 )  // if we are at the first hidden layer, load those particular weights
        {
            for( int j = 0; j < hNodes[i]; j++ )  // fill all nodes in first hidden layer
            {

                for( int k = 0; k < inputNum; k++ )
                {
                    fin >> temp;
                    curr_weights.push_back( temp );
                    weightCount += 1;

                }
                
                net[i][j].set_weights( curr_weights );

                curr_weights.clear();
            }
 
         }
         else  // we are somewhere in the midst of hidden layers, load the remainder of the weights
         {

             for( int j = 0; j < hNodes[i]; j++ )
             {
                 for( int k = 0; k < hNodes[ i - 1 ]; k++ )
                 {
                     fin >> temp;
                      
                     curr_weights.push_back( temp );
                     
                     weightCount += 1;

                 }
                 
                 net[i][j].set_weights( curr_weights );

                 curr_weights.clear();

             }

         }
         
     }

     
     int lastPos = hNodes.size();  // useful for indexing the last layer in hNodes
     
     // load weights for output layer nodes
     for( int i =0; i < oNodes; i++ )
     {
         for( int j = 0; j < hNodes[lastPos - 1]; j++ )
         {
             fin >> temp;

             curr_weights.push_back( temp );

             weightCount += 1;

         }

         net[lastPos][i].set_weights( curr_weights );

         curr_weights.clear();

     }
     */

    fin.close();

    /* This is the sister code to the actual vs. expected check mentioned above
    if( weightCount != numWeightsTotal )
    {
        std::cout << "The expected number of weights was " << numWeightsTotal << endl;
        std::cout << "The actual number of weights was " << weightCount << endl;

        return;

    }
    */
} 



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

// return number of layers in the network - used for debugging
int neuralnetwork::get_number_o_layers()
{
    return net.size();
}


// return the number of nodes in the indexed layer - used for debugging
int neuralnetwork::get_number_o_nodes( int index )
{

    return net[index].size();

}

// returns the vector of weights for the indexed perceptron - used for debugging
vector<float> neuralnetwork::get_perceptron_weights( int layerIndex, int nodeIndex )
{
    return net[ layerIndex ][ nodeIndex ].get_weights();

}

