/*************************************************************************//**
 * @file
 *
 * @mainpage Program #1 - Fire Detection Artificial Neural Network
 *
 * @authors  Steven Huerta, Luke Meyer, Savoy Schuler
 *
 * @date  February 24, 2016
 *
 * @par Professor: Dr. John Weiss
 *
 * @par Course: CSC 447 - M001 -  9:00 am MWF
 *
 * @par Location:  McLaury - 313
 *
 * @details
 * This portion of the programming assigment consists of the methods
 * and processes relating to the training of an artificial neural network.
 * We use the general feed-forward back propogation methedology to do so, also
 * utilizing a momentum term to reach solution convergence quicker. Upon
 * executionthe training process will output, to console, the mean squared error
 * of every 10th epoch of training conducted.
 *
 *
 *
 * @section compile_section Compiling and Usage
 *
 * @par Compiling Instructions:
 *     	g++ -g -Wall -std=c++11
 *
 * @par Usage:
 * 	@verbatim
   c:\> make
   c:\> ./ANNtrain <parameters>.prm
   c:\> ./ANNtest <parameters>.prm
   c:\> ./CrossValidate <parameters>.prm
   @endverbatim
 *
 * @section todo_bugs_modification_section Todo, Bugs, and Modifications
 *
 * @bug None
 *
 * @todo None
 *
 *****************************************************************************/

#include "ParamParser.h"
#include "GetData.h"
#include "neuralnetwork.h"
#include "makesets.h"
#include <fstream>
#include <iostream>

using namespace std;

/******************************************************************************
 * @authors  Steven Huerta, Luke Meyer, Savoy Schuler
 *
 * @par Name: main
 * @par Description: this is the main function that is responsible for the
 * execution of the training process upon an artificial neural network. All
 * significant functions/methods regarding the training process are called
 * from this function.
 *
 *
 * @param[in] int argc - integer count of the number of command line arguments
 *                       that the user specified, as well as the name of the
 *                       file itself
 *
 * @param[in] char* argv[] - character array containing command line arguments
 *                           supplied by the user
 *
 * @returns 0 - training process ran to completion successfully
 *          -1 - an error occured during the execution of this program
 *
 *****************************************************************************/

int main( int argc, char* argv[] )
{
    srand(time(NULL));

    string parameterFile = "";
    int max_iterations = -1;
    vector<trainer> train ;

    // check to make sure user is passing a parameter file with the executable
    if( argc != 2 )
    {
        cout << "ANNtrain requires a parameter file as an argument" << endl;
        cout << "USAGE: ANNtrain [parameter file] " << endl;
        return -1;

    }

    parameterFile = argv[1];  // get name of parameter file

    // get params via the parameter file
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

    // Change the order to better suit our algorithm
    reverse(fVector.begin(), fVector.end()) ;

    fin.close();   // streams should be closed

    // the birth of the neural network
    neuralnetwork Ann( params );

    // populate the trainer object to be passed into the neural net training process
    train = createSet( fVector, params, false );

    // training phase of the network
    Ann.training( train, max_iterations, true );


    if( !Ann.save_weights() )  // save the weights to the file
    {
        cout << "ERROR: saving weights was unsuccessful" << endl;
        return -1;
    }


    return 0;

}

