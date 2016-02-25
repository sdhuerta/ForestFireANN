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
    float error_sum = 0;
    float total_error = 0;
    float mse;
    bool flag ;
    int num_correct = 0 ;

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

    //open the file containing training data
    ifstream fin( params.trainFile.c_str()) ;

    if( !fin )
    {

        cout << "There was an error opening the training data";
        return -1;

    }

    // get input data and put into feature vector
    vector<PDSI> fVector = pdsiFeatureVector( fin );

    // Change the order
    reverse(fVector.begin(), fVector.end()) ;

    fin.close();   // streams should be closed but never crossed!

    //The birth of the neural network
    neuralnetwork ann(params);

    //load weights for the network
    ann.load_weights();

    //call function to produce input set as vector of floats

    //test network on input vector and stor

    train = createSet( fVector, params, true );

    vector<float> correct ;

    printf("Parameter File: %s\n", parameterFile.c_str());
    printf("Data File: %s\n\n", params.trainFile.c_str());

    printf(" YEAR\t RESULT\t\t CORRECT OUTPUT\n");

    // This is the output loop to print our comparisons
    for(int i = 0; i < train.size(); i++ )
    {
        error_sum = 0 ;

        results = ann.testing( train[i].input );
        correct = train[i].output;

        flag = true ;

        printf(" %-7d [",fVector[i].year);

        for(int j = 0; j < results.size(); j++)
        {
            error_sum += pow((correct[j] - results[j]), 2);

            printf(" %d ",(int) round(results[j]));

            if( round(results[j]) != correct[j] )
                flag = false ;
        }

        // Special casing so that we are not comparing
        // expected output when we don't have any
        // This would not generalize to other files than
        // those provided.
        if( i != 0 )
        {
            printf("]\t [");

            for(int j = 0; j < correct.size(); j++)
                printf(" %d ",(int) round(correct[j]));

            printf("]");

            if(flag == false)
                printf("*");
            else
                num_correct++;

            printf("\n");
        }

        else
        {
            printf("]\t WAIT AND SEE \n");
        }


        total_error += error_sum ;
    }

    mse = total_error / train.size() ;

    printf("\nMSE: %6.4f\n", mse);
    printf("Accuracy: %4.2f%%\n", (num_correct/(float)train.size() * 100) ) ;
    //Return Success
    return 0;
}






