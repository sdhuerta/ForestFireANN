#include "ParamParser.h"
#include "GetData.h"
#include "neuralnetwork.h"
#include "make_sets.h"
#include <fstream>
#include <iostream>
#include <stdlib.h>
#include <time.h>



using namespace std;



int main( int argc, char* argv[] )
{
    string parameterFile = "";
    int max_iterations = -1;
    int vectSize = -1;
    int randIndex = -1;

    


    if( argc != 2 )  // check to make sure user is passing a parameter file with the executable
    {
        cout << "CrossValidate requires a parameter file as an argument" << endl;
        cout << "USAGE: CrossValidate [parameter file] " << endl;
        return -1;

    }

    parameterFile = argv[1];  // get name of parameter file 

    
    Params parameters = getParams( parameterFile );  // get parameters via the parameter file

    max_iterations = parameters.numEpochs;   // get the max number of epochs to train for

    
    ifstream fin( parameters.trainfile.c_str()) ;   // open the file containing training data

    if( !fin )
    {

        cout << "There was an error opening the training data";
        return -1;

    }

    vector<PDSI> fVector = pdsiFeatureVector( fin );  // get input data and put into feature vector    

    fin.close();   // streams should be closed but never crossed!

    
    neuralnetwork Ann = new neuralnetwork( parameters );  // the birth of the neural network

    vector<trainer> train = createSet( fVector, parameters );  // populate the trainer object to be passed into the neural net training process

    vectSize = train.size();

    srand(time(NULL));

    randIndex = rand() % vectSize = + 1; 

    if( randIndex == vectSize )  // if the random index would overstep the bounds of our vector
      { 
          randIndex -= 1;  // decrement it by one 
      }

    
    trainer outCast = train[randIndex];  // grab the entry to be left out, will be used for testing later

    train.erase( randIndex ); // remove the element from the vector

    Ann.training( train, max_iterations );  // training phase of the network

    
    vector<float> input = getInputs( train );  

    Ann.testing( input );



    // do other stuff, such as output the sweetest of results for all to see



    return 0;

}


