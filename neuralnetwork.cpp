#include "neuralnetwork.h"


/******************************************************************************
 * @authors  Steven Huerta, Luke Meyer, Savoy Schuler
 *
 * @par Description: This function is the constructor of the neural network
 * It takes in the parameters and generates the network layers, sets the
 * learning and momentum values. It also sets the error threshold. It also
 * creates the needed perceptrons for each layer.
 *
 * @param[in] net_define - Structure containing the definitions of the network
 *
 *****************************************************************************/

neuralnetwork::neuralnetwork(Parameters net_define)
{
    layers = net_define.nodesPerLayer ; // set nodes per layer
    learning = net_define.learningRate ; // set the learning rate
    momentum = net_define.momentum ; // set the momentum for learning
    threshold = net_define.errorThreshold; // set the threshold for error
    weightsFile = net_define.weightsFile; // set the file to save/load from

    // Create every layer after the input layer.
    for(int i = 1; i < layers.size() ; i++)
    {
        // create a container for our layer of perceptrons
        vector<Perceptron> layer ;

        // for each layer...
        for(int j = 0; j < layers[i]; j++)
        {
            // ...Let's create another node feeding the number of inputs
            // , learning, and the momentum.
            Perceptron new_node(layers[i-1],learning, momentum) ;

            // We push it into our layer container
            layer.push_back(new_node) ;
        }

        // push each layer into our network container
        net.push_back(layer) ;
    }
}


/******************************************************************************
 * @authors  Steven Huerta, Luke Meyer, Savoy Schuler
 *
 * @par Description:
 *
 *
 * @param[in] train - vector containing a set of inputs and associated outputs
 * @param[in] max_iterations - the maximum number of iterations
 * @param[in] print_interval - a bool that turns on/off training console
 *                             output
 *
 * @returns error - the MSE of the last epoch of training
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
    float last_error = 0;
    float error = 0;
    int select ;
    int stuck = 0;

    //max_iterations = 5 ;

    // While we haven't reach our iteration limit
    while(iterations < max_iterations)
    {
        // take a sample from our sample set
        select = rand() % train_set_size ;

        list_check = find(selections.begin(), selections.end(), select);

        // if the sample has been selected before, grab another!
        while( list_check != selections.end() )
        {
            select = rand() % train_set_size ;

            list_check = find(selections.begin(), selections.end(), select);
        }

        // add this selection to our list of selected samples
        selections.push_back(select) ;

        // get the inputs of the sample
        input = train[select].input ;

        // get the outputs of the sample
        output = train[select].output ;

        // calculate the outputs from first pass through network
        calc_output = feed_forward();

        // adjust the weights
        adjust_weights();

        error += calc_error(calc_output) ;

        // One iteration means that we have trained on the entire training
        // set once.
        if( selections.size() == train_set_size )
        {
            // clear our list and increment our epochs by 1
            selections.clear();
            iterations++ ;

            // calculate MSE
            error  = error / (float)train_set_size ;

            if( print_interval == true  && iterations % 10 == 0)
                printf("Epoch: %-6d\tMSE: %6.4f\n", iterations, error);

            // If we have trained sufficiently let's stop training
            if( error <= threshold)
                return  error;

            // insufficient error change
            if( abs(last_error - error) < .005)
            {
                stuck++ ;

                if(stuck > 50)
                    return error ;
            } 
            else
                stuck = 0 ;

            // if we have trained the max number of iterations specified, exit
            
            if( iterations == max_iterations )
                return error;

            last_error = error ;

            error = 0 ;
        }
    }

}


/******************************************************************************
 * @authors  Steven Huerta, Luke Meyer, Savoy Schuler
 *
 * @par Description: This function feeds the inputs through the network layers
 * generating an output(classification)
 *
 * @param[in] test_inputs - vector containing the normalized inputs
 *
 * @returns output - vector of floats containing output from the network
 *
 *****************************************************************************/

vector<float> neuralnetwork::testing(vector<float> test_inputs)
{
    // save this input to the class for use in the feed forward
    input = test_inputs ;

    // return the outputs
    return feed_forward();
}


/******************************************************************************
 * @authors  Steven Huerta, Luke Meyer, Savoy Schuler
 *
 * @par Description: This function is responsible for carrying the outputs of
 * the previous layer to be fed into the inputs of the next layer until the
 * entire network is traversed.
 *
 * @returns hidden_outputs - vector of floats from the output layer
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
