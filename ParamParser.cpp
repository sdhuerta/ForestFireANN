#include <iostream>
#include <sstream>
#include <vector>
#include <fstream>
#include <string>
#include "GetData.h"


using namespace std;

struct Params;
//typedef Params* Params;

	// Declare Param struct type
struct Params {   
 
	//ANN PARAMETERS
	//name of ANN weights file
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


//Define ANN as an instance of struct Params
Params ANN;


int main(int argc, char* argv[1])
{
	//Open stream for input/output files
	ifstream inputFile( argv[1]);
  
	//line will be used for file reading
	//pnd and emp are comparators for skipping comments and blank lines
    string line, pnd ="#",emp = "";

	/*tempVals will store all variables read from input file as temporary 
	strings until type sorting*/
	vector<string> tempVals;

	/*Stringstream variables are used to ensure correct type casting from 
    string to proper type assignment. I hoped to avoid using so many, but if
    each instance of type casting wasn't redefined, the values were lost.*/
	stringstream s0,s1,s2,s3,s4,s5,s6,s7,s8,s9,s10,s11,s12,s13; 

	/*The while loop reads through the input file, skipping any lines that 
    begin with an empty string or a comment indicator. It stores all 
    variables as strings (which is necessary given they are followed by 
    comments) into a vector. I am aware fstreamf may have seemed like a 
    viable option for simplifying the process by g just rabbing the 
    variables, but the numNodesPerLayer variable inhibits this by having an
    unspecified number of values on a single line. Thus getline was 
    necessary.*/
    while(getline(inputFile,line))
    {
       if( line[0]==pnd[0]||line[0]==emp[0]) 
		{
		}
        else
			tempVals.push_back(line);
	}

	//Made sure to close input file.
	inputFile.close();
 
	
    /*Here I used substrings and delimiters as a method for separating 
    variables from their comments and storing the variable back as a 
    string into the tempVals vector for holding. I made a special case 
    for line numNodesPerLayer line by splitting it on the '#' to make 
    sure it captured all numerical values. */
	for (int vecPos=0;vecPos<tempVals.size();vecPos++)
	{
		if(vecPos==6)
		{
		string substring, intString=tempVals[vecPos];
		substring = intString.substr(0,intString.find_first_of("#"));
		tempVals[vecPos]=substring;
		}
		else
		{
		string substring, intString=tempVals[vecPos];
		substring = intString.substr(0,intString.find_first_of(" "));
		tempVals[vecPos]=substring;
		}	
	}

    /*Here I make use of stringstream to read the string type variables 
    out of the tempVals vectors and store them into the struct paramaters
    by using stringstream to identify type. As mentioned, either separate
    or reinitialized variables are necessary for each new value*/	
    s0<<tempVals[0];
	s0>>ANN.weightsFile;

	s1<<tempVals[1];
    s1>>ANN.numEpochs;
	
	s2<<tempVals[2];
    s2>>ANN.learningRate;      
    
	s3<<tempVals[3];
    s3>>ANN.momentum;

	s4<<tempVals[4];
    s4>>ANN.errorThreshold;

	s5<<tempVals[5];
    s5>>ANN.numLayers;

    /*Because this variable is a vector, it is necessary to set the values
    independantly by assignment using emplace, as indexing produces a seg
    fault since the system considers that referencing and cannot intialize
    new vector spaces.*/
	s6<<tempVals[6];
	while(1) 
	{
   		int vecValue;
  		s6 >> vecValue;
   		if(!s6)
      		break;
  		ANN.nodesPerLayer.push_back(vecValue);
	}

   	s7<<tempVals[7];
    s7>>ANN.trainFile;

   	s8<<tempVals[8];
    s8>>ANN.yearsBurnedAcreage;

   	s9<<tempVals[9];
    s9>>ANN.monthsPDSIData;

   	s10<<tempVals[10];
    s10>>ANN.endMonth;

   	s11<<tempVals[11];
    s11>>ANN.numClasses;

   	s12<<tempVals[12];
    s12>>ANN.lowCutoff;

   	s13<<tempVals[13];
    s13>>ANN.highCutoff;

	/*cout<< "\n\nFinal Output Set: \n\n";
	cout<<ANN.weightsFile<<endl;
	cout<<ANN.numEpochs<<endl;
	cout<<ANN.learningRate<<endl;
	cout<<ANN.momentum<<endl;
	cout<<ANN.errorThreshold<<endl;
	cout<<ANN.numLayers<<endl;
	for(int j =0; j<ANN.nodesPerLayer.size();j++)
		cout<<ANN.nodesPerLayer[j]<<" ";
   	cout<<endl<<ANN.trainFile<<endl;
   	cout<<ANN.yearsBurnedAcreage<<endl;
   	cout<<ANN.monthsPDSIData<<endl;
   	cout<<ANN.endMonth<<endl;
   	cout<<ANN.numClasses<<endl;
   	cout<<ANN.lowCutoff<<endl;
   	cout<<ANN.highCutoff<<endl;
	cout<<endl;*/

    return 0;
}
