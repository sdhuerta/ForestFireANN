#include "ParamParser.h"
#include "GetData.h"
#include "neuralnetwork.h"
#include "makesets.h"
#include <fstream>
#include <iostream>
#include <stdlib.h>
#include <time.h>

using namespace std;


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

int main( int argc, char* argv[] )
{
    srand(time(NULL));

    vector<trainer> temp_trainer ;
    vector<int> selections ;
    vector<int>::iterator list_check ;
    vector<float> result ;

    string parameterFile = "";
    int max_iterations = -1;
    int vectSize = -1;
    int randIndex = -1;
    int train_set_size ;
    int select ;
    trainer sample ;

    if( argc != 2 )  // check to make sure user is passing a parameter file with the executable
    {
        cout << "CrossValidate requires a parameter file as an argument" << endl;
        cout << "USAGE: CrossValidate [parameter file] " << endl;
        return -1;

    }

    parameterFile = argv[1];  // get name of parameter file 

    
    Parameters params = getParams( parameterFile );  // get parameters via the parameter file

    max_iterations = params.numEpochs;   // get the max number of epochs to train for

    
    ifstream fin( params.trainFile.c_str()) ;   // open the file containing training data

    if( !fin )
    {

        cout << "There was an error opening the training data";
        return -1;

    }

    vector<PDSI> fVector = pdsiFeatureVector( fin );  // get input data and put into feature vector    

    reverse(fVector.begin(), fVector.end()) ;

    fin.close();   // streams should be closed but never crossed!


    vector<trainer> train = createSet( fVector, params );  // populate the trainer object to be passed into the neural net training process

    vectSize = train.size();

    train_set_size = vectSize - 1 ;

    for(int i = 0 ; i < train_set_size ; i++ )
    {
        neuralnetwork ann(params);  // the birth of the neural network

        temp_trainer = train ;

        select = rand() % train_set_size ;

        list_check = find(selections.begin(), selections.end(), select);

        while( list_check != selections.end() )
        {
            select = rand() % train_set_size ;

            list_check = find(selections.begin(), selections.end(), select);    
        }

        selections.push_back(select) ;

        sample = temp_trainer[select] ;

        temp_trainer.erase(temp_trainer.begin() + select) ;

        ann.training( temp_trainer, max_iterations);

        result = ann.testing( sample.input );

        cout << fVector[select].year << ": [" ;

        for(int i = 0; i < result.size(); i++)
            cout << round(result[i]) << " " ;

        cout << "]  [ " ;

        for(int i = 0; i < sample.output.size(); i++)
            cout << sample.output[i] << " " ;

        cout << "]" << endl ;
    }


    return 0;

}


