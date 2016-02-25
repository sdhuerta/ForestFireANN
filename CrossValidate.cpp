#include "ParamParser.h"
#include "GetData.h"
#include "neuralnetwork.h"
#include "makesets.h"
#include <fstream>
#include <iostream>
#include <iomanip>
#include <stdlib.h>
#include <time.h>

using namespace std;


/******************************************************************************
 * @authors  Steven Huerta, Luke Meyer, Savoy Schuler
 *
 * @par Description: Performs the "leave one out" cross validation technique
 * upon the currently trained ANN to measure the quality of the training/testing
 * process.
 *
 *
 * @param[in] int argc - contains the number of command line arguments
 *
 * @param[in] char* argv[] - contains the command line arugments specified
 *                           by the user
 *
 * @returns 0 - cross validation process ran to completion successfully
 *          -1 - an error occured during the execution of cross validation
 *
 *****************************************************************************/

int main( int argc, char* argv[] )
{
    srand(time(NULL));

    bool isEqual = true;
    bool printFlag = false;

    vector<trainer> temp_trainer ;
    vector<float> result ;

    string parameterFile = "";
    int max_iterations = -1;
    int vectSize = -1;
    int randIndex = -1;
    int train_set_size ;
    int select ;
    int errorCount = 0;
    int processedCount = 0;
    trainer sample ;

    float meanSquareError = 0.0;
    float totalError = 0.0;

    // check to make sure user is passing a parameter file with the executable
    if( argc != 2 )
    {
        cout << "CrossValidate requires a parameter file as an argument" <<endl;
        cout << "USAGE: CrossValidate [parameter file] " << endl;
        return -1;

    }

    parameterFile = argv[1];  // get name of parameter file

    // get parameters via the parameter file
    Parameters params = getParams( parameterFile );

    // get the max number of epochs to train for
    max_iterations = params.numEpochs;

    // open the file containing training data
    ifstream fin( params.trainFile.c_str()) ;

    if( !fin )
    {

        cout << "There was an error opening the training data";
        return -1;

    }

    // get input data and put into feature vector
    vector<PDSI> fVector = pdsiFeatureVector( fin );

    reverse(fVector.begin(), fVector.end()) ;

    fin.close();

    // populate the trainer object to be passed into the neural net training process
    vector<trainer> train = createSet( fVector, params, false );


    // We're not validating on the most current year, because that is nonsense
    // We don't have the data to predict the future

    vectSize = train.size();

    train_set_size = vectSize;

    cout << "Year,  Burned,  Predicted,  Actual,  Mean Square error " << endl;

    for(int i = 0 ; i < train_set_size; i++ )
    {
        neuralnetwork ann(params);  // the birth of the neural network

        temp_trainer = train;


        // choose a sample to remove; "leave one out" cross validation
        sample = temp_trainer[i];

        temp_trainer.erase(temp_trainer.begin() + i) ;

        // get error for current training cycleHEAD
        meanSquareError = ann.training( temp_trainer, max_iterations, printFlag);

        // get error for current training cycle

        processedCount += 1;

        result = ann.testing( sample.input );  // testing process

        int z = 0;

        // check for error; assertion on expected vs actual results
        while( z < result.size() && isEqual )
        {
            if( round(result[z]) != sample.output[z] )
            {
                isEqual = false;
            }

            z += 1;
        }

        // ouput stuff to the console
        printf(" %-5d %6.0f\t[", fVector[i+1].year, fVector[i+1].rawAcresBurned);

        for(int i = 0; i < result.size(); i++)  // output actual result
            printf(" %d",(int)round(result[i])) ;

        printf(" ]  [") ;

        for(int i = 0; i < sample.output.size(); i++)  // output expected result
            printf(" %d",(int)sample.output[i]);

        printf(" ]");

        if( !isEqual )  // flag where expected result != actual result
        {
            printf("*");
            errorCount += 1;
        }

        printf("\t %6.4f\n",meanSquareError);

        isEqual = true;  // re initialize flag
    }

    // output total accuracy to console

    printf("The overall accuracy is: %-6.2f%%\n",(100 - \
            (float)errorCount/(float)processedCount * 100));



    return 0;

}


