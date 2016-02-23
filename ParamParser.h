#ifndef PARAMPARSER_H
#define PARAMPARSER_H


#include <iostream>
#include <sstream>
#include <vector>
#include <fstream>
#include <string>

using namespace std;


//struct
/******************************************************************************
 * @authors Savoy Schuler
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
	//name of Params weights file
	string weightsFile;   
	//Number of training epochs
	int numEpochs;	
	float learningRate;      
	float momentum;
	//Number of training epochs
	float errorThreshold;  
	//layers of adjustable weights (one less than layers of nodes)
	int numLayers;
	// how many nodes in each layer
	vector<int> nodesPerLayer; 

	//TRAINING AND TESTING FILE
	string trainFile;  
 
	//INPUT FEATURE VECTOR INFO
	//num of years burned acreage
	int yearsBurnedAcreage;	
	//NO less than # input layer nodes
	int monthsPDSIData;	
	//end month of current year (numerically)
	int endMonth;	

	//OUTPUT CLASS INFO
	//NO LESS than of input layer nodes
	int numClasses; 
	
	//FIRE SEVERITY PARAMETERS
	//fire severity cutoffs (burned acres) high and low
	int lowCutoff;
	int highCutoff;
};



//functions
Parameters getParams(string fileName);

#endif
