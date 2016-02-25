/*****************************************************************************/
/* @file                      ParamParser.h                                  */
/*****************************************************************************/

#ifndef PARAMPARSER_H
#define PARAMPARSER_H
#include <iostream>
#include <sstream>
#include <vector>
#include <fstream>
#include <string>

using namespace std;


/******************************************************************************
 * @authors Steven Huerta, Luke Meyer, Savoy Schuler
 *
 * @par Description:
 * This struct is desgined to hold all the parameter values defined for the
 * artificial neural network in a .prm file. It is instantiated and populated in
 * the getParams() function from which it is passed to the main for application.
 *
 *****************************************************************************/

// Define Param struct type
struct Parameters {

    //Params PARAMETERS

    string weightsFile;		/*!< name of Params weights file  */

    int numEpochs;		/*!< Number of training epochs  */

    float learningRate;		/*!< provides additional momentum to the
				gradient descent - prevents lingering in
				narrowing local mins*/

    float momentum;		/*!<  affects how aggressively the gradient
				descent performs - can cause  overshooting, but
				also increases the rate of convergence */

    float errorThreshold;	/*!< Number of training epochs  */

    int numLayers;		/*!< layers of adjustable weights
				(one less than layers of nodes)  */

    vector<int> nodesPerLayer;	/*!< how many nodes in each layer  */

    //TRAINING AND TESTING FILE

    string trainFile;		/*!< training file .prm  */

    //INPUT FEATURE VECTOR INFO

    int yearsBurnedAcreage;	/*!< num of years burned acreage  */

    int monthsPDSIData;		/*!< NO less than # input layer nodes  */

    int endMonth;		/*!< end month of current year (numerically)*/

    //OUTPUT CLASS INFO

    int numClasses;		/*!< NO LESS than of input layer nodes  */

    //FIRE SEVERITY PARAMETERS

    int lowCutoff;		/*!< high fire severity cutoffs(burned acres)*/

    int highCutoff;		/*!< low fire severity cutoffs (burned acres)*/
};


/*******************************************************************************
 *                         Function Prototypes
 ******************************************************************************/

Parameters getParams(string fileName);

#endif
