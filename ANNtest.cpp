#include "ParamParser.h"
#include "neuralnetwork.h"
#include <fstream>
#include <iostream>

using namespace std;


/******************************************************************************
 * @authors Savoy Schuler
 *
 * @par Description:
 * This main is used for testing the ANN after it has been trained and cross
 * checked. It starts by turning the given .prm file (in argv[1]) into a string
 * and passing it to getParams() to generate a paramter struct for populating
 * parameter feilds for the ANN. It then makes function calls to load the 
 * weights file and generate a vector of floats for the testing input. The
 * function tests the ANN on the input vector and stores the results in the
 * restults vector for output. 
 *
 * @param[in]      argc - a count of the command line arguments provide in call
 * 
 * @param[in]      argv - the parameter file being used to define the ANN, read
 *                        in as a character array
 *
 * @returns 0      the function ran successfully
 *
 * @returns -1     the function ran unsuccessfully, reason printed to terminal
 *
 *****************************************************************************/

int main( int argc, char* argv[] )
{
    //string of paramater file name
    string parameterFile = "";

    //position in results vector
    int resPos; 

    //vector of floats storing input data
    vector<float> testInput

    //vector of results returned from testing
    vector<float> results

    //Params struct to hold the .prm designated parameters for ANN
    Params parameters


    //check for .prm file and excutable
    if( argc != 2 )  
    {
        cout << "ANNtest requires a parameter file as an argument" << endl;
        cout << "USAGE: test [parameter file] " << endl;
        return -1;
    }

    //Get .prm file name and store in string value
    parameterFile = argv[1];  
    
    //Call getParams to store .prm values into parameter struct for quick access 
    parameters = getParams(parameterFile);

    //The birth of the neural network
    neuralnetwork Ann = new neuralnetwork( parameters );  
  
    //load weights for the network
    Ann.load_weights();  
  
    //call function to produce input set as vector of floats
    testInput = getInputSet();

    //test network on input vector and stor 
    results = ANN.testing( testInput );

    //Terminal Output
    cout<<"Fire danger severity for year "<< "FIX THIS STEVEN "<<":"<<endl;
    for(resPos=0;resPos<results.size();resPos++)
    {
        cout<<results[resPos]<<endl;
    }

    //Return Success
    return 0;
}



    


