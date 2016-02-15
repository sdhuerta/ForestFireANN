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

	remove("temp.txt");
	
    ifstream inputFile( argv[1]);
    ofstream outputFile("temp.txt");
    string line, pnd ="#",emp = "";
	vector<string> tempVals;
    while(getline(inputFile,line))
    {
       if( line[0]==pnd[0]||line[0]==emp[0]) 
		{
		}
        else
		{
			outputFile << line << "\n";
		}
	}
	inputFile.close();
 	outputFile.close();	
    ifstream inputFile2("temp.txt");

    while (getline(inputFile2,line))
    {		
		tempVals.push_back(line);
	}


	cout<< "Starting output: "<<endl;
	for (int vecPos=0;vecPos<tempVals.size();vecPos++)
	{
		if(vecPos==6)
		{
		string token, mystring=tempVals[vecPos];
		token = mystring.substr(0,mystring.find_first_of("#"));
		//mystring = mystring.substr(mystring.find_first_of(" ") + 1);
		tempVals[vecPos]=token;

		}
		else
		{
		string token, mystring=tempVals[vecPos];
		token = mystring.substr(0,mystring.find_first_of(" "));
		tempVals[vecPos]=token;
		}	
	}

	for (int vecPos=0;vecPos<tempVals.size();vecPos++)
	{
	 	cout<<endl<<tempVals[vecPos];
	}
	cout<<endl;


	stringstream s0,s1,s2,s3,s4,s5,s6,s7,s8,s9,s10,s11,s12,s13,s14; 

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

   	s6<<tempVals[6];
    s6>>ANN.nodesPerLayer;

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

	cout<< "\n\nFinal Output Set: \n\n";


	cout<<ANN.weightsFile<<endl;
	cout<<ANN.numEpochs<<endl;
	cout<<ANN.learningRate<<endl;
	cout<<ANN.momentum<<endl;
	cout<<ANN.errorThreshold<<endl;
	cout<<ANN.numLayers<<endl;
	cout<<ANN.nodesPerLayer<<endl;
   	cout<<ANN.trainFile<<endl;
   	cout<<ANN.yearsBurnedAcreage<<endl;
   	cout<<ANN.monthsPDSIData<<endl;
   	cout<<ANN.endMonth<<endl;
   	cout<<ANN.numClasses<<endl;
   	cout<<ANN.lowCutoff<<endl;
   	cout<<ANN.highCutoff<<endl;


	cout<<endl;

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
