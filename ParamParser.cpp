#include <iostream>
#include <sstream>
#include <vector>
#include <fstream>
using namespace std;

struct Params {   // Declare Param struct type
 
	//ANN Parameters
	string weightsFile;   //name of ANN weights file
	int numEpochs;	//Number of training epochs
	float learningRate;      
	float momentum;
	float errorThreshold;   //training cutoff - testing acceptance
	int numLayers;//layers of adjustable weights, one less than layers of nodes
	string nodesPerLayer; // how many nodes in each layer

	string trainFile; //date file for training and testing 
 
	//Input of feature vector information
	int yearsBurnedAcreage;	//num of years burned acreage
	int monthsPDSIData;	//NO less than # input layer nodes
	int endMonth;	//end month of current year (numerically)

	//Output class information
	int numClasses; //NO LESS than of input layer nodes
	
	//Do we need class names and positions (zero based)?

	//fire severity cutoffs (burned acres)
	int lowCutoff;
	int highCutoff;
}

Params ANN;   // Define object of type Params


//void getParams(string file)
//	{
//	fscanf(file, "%s %i %f %f %f %i", weightsFile, numEpochs, learningRate, momentum, 
//	}

int getParams()
{
    ifstream inputFile("nw.prm");
    ofstream outputFile("temp.txt");
    string line;
	string cmp ="#";
    while(inputFile >> line)
    {
        if( line[0]==cmp[0]) {}
        else
            outputFile << line << "\n";
    }
    ifstream inputFile("temp.txt");
    //variables    
  //  string weightsFile, trainFile;  
 //   int numEpochs, numLayers, yearsBurnedAcreage, monthsPDSIData;	
//	int endMonth, numClasses, lowCutoff, highCutoff;
//	float learningRate, momentum, errorThreshold;  
//	vector<int> nodesPerLayer; 

    while (getline(inputFile,line))
    {
        istringstream ss(line);
        ss >> 
	    ANN.weightsFile>>
	    ANN.numEpochs>>
	    ANN.learningRate>>      
        ANN.momentum>>
        ANN.errorThreshold>>
    	ANN.numLayers>>
    	ANN.nodesPerLayer>> 
    	ANN.trainFile>>
    	ANN.yearsBurnedAcreage>>
    	ANN.monthsPDSIData>>
    	ANN.endMonth>>
    	ANN.numClasses>>
    	ANN.lowCutoff>>
    	ANN.highCutoff;
    }

 //   ANN (weightsFile, numEpochs, learningRate, momentum, errorThreshold, numLayers, nodesPerLayer, trainFile, yearsBurnedAcreage, monthsPDSIData, endMonth, numClasses, lowCutoff, highCutoff);
    return 0;
}


/*
int main() {

	//Create a dynamic array to hold the values
	vector<int> numbers;

	//Create an input file stream
	ifstream in("nw.prm",ios::in);

	int number;  //Variable to hold each number as it is read
	
        //Read number using the extraction (>>) operator
        while (in >> number) {
		//Add the number to the end of the array
		numbers.push_back(number);
	}

	//Close the file stream
	in.close();

	/* 
	    Now, the vector<int> object "numbers" contains both the array of numbers, 
            and its length (the number count from the file).
	

	//Display the numbers
	cout << "Numbers:\n";
	for (int i=0; i<numbers.size(); i++) {
		cout << numbers[i] << '\n';
	}

	cin.get(); //Keep program open until "enter" is pressed
	return 0;
}
*/
