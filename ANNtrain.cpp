#include "ParamParser.h"
#include "GetData.h"
#include "neuralnetwork.h"
#include "makesets.h"
#include <fstream>
#include <iostream>



using namespace std;



int main( int argc, char* argv[] )
{
    string parameterFile = "";
    int max_iterations = -1;
    vector<trainer> train ;


    if( argc != 2 )  // check to make sure user is passing a parameter file with the executable
    {
        cout << "ANNtrain requires a parameter file as an argument" << endl;
        cout << "USAGE: ANNtrain [parameter file] " << endl;
        return -1;

    }

    parameterFile = argv[1];  // get name of parameter file 

    
    Parameters params = getParams( parameterFile );  // get params via the parameter file

    max_iterations = params.numEpochs;   // get the max number of epochs to train for

    
    ifstream fin( params.trainFile.c_str()) ;   // open the file containing training data

    if( !fin )
    {

        cout << "There was an error opening the training data";
        return -1;

    }

    vector<PDSI> fVector = pdsiFeatureVector( fin );  // get input data and put into feature vector

    fin.close();   // streams should be closed but never crossed!

    
    neuralnetwork Ann( params );  // the birth of the neural network

    train = createSet( fVector, params );  // populate the trainer object to be passed into the neural net training process


    Ann.training( train, max_iterations );  // training phase of the network


    if( !Ann.save_weights() )  // save the weights to the file
    {
        cout << "ERROR: saving weights was unsuccessful" << endl;
        return -1;
    }



    return 0;

}

