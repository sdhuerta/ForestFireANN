#include <iostream>
#include <sstream>
#include <vector>
#include <fstream>
#include <string>

using namespace std;

struct Params;
//typedef Params* Params;

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
};

Params ANN;
 // Define object of type Params



int main(int argc, char* argv[1])
{
    ifstream inputFile( argv[1]);
    ofstream outputFile("temp.txt");
    string line, pnd ="#",emp = "";
	vector<string> tempVals;
    while(getline(inputFile,line))
    {
     //   if( line[0]==pnd[0]||line[0]==emp[0]) 
		//{
		//}
        //else
		//{
			 outputFile<<"dog"<<"\n";   
			//outputFile << line << "\n";
		//}
	}
    ifstream inputFile2("temp.txt");

    while (getline(inputFile2,line))
    {	
		tempVals.push_back(line);
	}
 /*
	stringstream ss; 

	string token, mystring(tempVals[1]);
	while(token != mystring)
	{
		token = mystring.substr(0,mystring.find_first_of(" "));
		mystring = mystring.substr(mystring.find_first_of(" ") + 1);
		printf("%s ",token.c_str());	
	}


    ANN.weightsFile=tempVals[0];
	
	ss<<tempVals[1];
    ss>>ANN.numEpochs;
	
	ss<<tempVals[2];
    ss>>ANN.learningRate;      
    
	ss<<tempVals[3];
    ss>>ANN.momentum;

	ss<<tempVals[4];
    ss>>ANN.errorThreshold;

	ss<<tempVals[5];
    ss>>ANN.numLayers;

   	ss<<tempVals[6];
    ss>>ANN.nodesPerLayer;

   	ss<<tempVals[7];
    ss>>ANN.trainFile;

   	ss<<tempVals[8];
    ss>>ANN.yearsBurnedAcreage;

   	ss<<tempVals[9];
    ss>>ANN.monthsPDSIData;

   	ss<<tempVals[10];
    ss>>ANN.endMonth;

   	ss<<tempVals[11];
    ss>>ANN.numClasses;

   	ss<<tempVals[12];
    ss>>ANN.lowCutoff;

   	ss<<tempVals[13];
    ss>>ANN.highCutoff;
   

	cout<<ANN.weightsFile;
	cout<<ANN.numEpochs;
	cout<<ANN.learningRate;
	cout<<ANN.momentum;
	cout<<ANN.errorThreshold;
	cout<<ANN.numLayers;
	cout<<ANN.nodesPerLayer;
   	cout<<ANN.trainFile;
   	cout<<ANN.yearsBurnedAcreage;
   	cout<<ANN.monthsPDSIData;
   	cout<<ANN.endMonth;
   	cout<<ANN.numClasses;
   	cout<<ANN.lowCutoff;
   	cout<<ANN.highCutoff;*/

 //   ANN (weightsFile, numEpochs, learningRate, momentum, errorThreshold, numLayers, nodesPerLayer, trainFile, yearsBurnedAcreage, monthsPDSIData, endMonth, numClasses, lowCutoff, highCutoff);
    return 0;
}


/*
int mai() {

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
