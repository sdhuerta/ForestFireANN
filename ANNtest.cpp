#include "ParamParser.h"
#include "neuralnetwork.h"

#include <fstream>
#include <iostream>

using namespace std;


/******************************************************************************
 * @authors Steven Huerta, Luke Meyer, Savoy Schuler
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
    vector<float> testInput ;

    //vector of results returned from testing
    vector<float> results ;

    vector<trainer> train ;

    //Params struct to hold the .prm designated params for ANN
    Parameters params ;


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
    params = getParams(parameterFile);

    ifstream fin( params.trainFile.c_str()) ;   // open the file containing training data

    if( !fin )
    {

        cout << "There was an error opening the training data";
        return -1;

    }

    vector<PDSI> fVector = pdsiFeatureVector( fin );  // get input data and put into feature vector

    // Change the order
    reverse(fVector.begin(), fVector.end()) ;

    fin.close();   // streams should be closed but never crossed!

    //The birth of the neural network
    neuralnetwork ann(params);  
  
    //load weights for the network
    ann.load_weights();  
  
    //call function to produce input set as vector of floats
    //testInput = createTest(fVector, params);

    //test network on input vector and stor 
    
    train = createSet( fVector, params );

    vector<float> correct ;

    for(int i = 0; i < train.size(); i++ )
    {

        results = ann.testing( train[i].input );
        correct = train[i].output;


        //Terminal Output
        cout<<"Fire danger severity for year "<< fVector[i+1].year <<": [ ";

        for(resPos=0;resPos<results.size();resPos++)
        {
            cout << round(results[resPos]) << "  " ;
        }

        cout << "]" << "\t[ ";

        for(int j = 0; j < correct.size(); j++ )
        {
            cout << correct[j] << "  " ; 
        }
        cout << "]" << endl; 
    }

    //Return Success
    return 0;
}



    


