#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

struct Params {   // Declare Param struct type
 
	//ANN Parameters
	string weightsFile;   //name of ANN weights file
    int numEpochs;	//Number of training epochs
	float learningRate;      
	float momentum;
	float errorThreshold   //training cutoff - testing acceptance
	int numLayers;//layers of adjustable weights, one less than layers of nodes
	vecotr<int> nodesPerLayer; // how many nodes in each layer

	string trainFile; //date file for training and testing 
 
	//Input of feature vector information
	int yearsBurnedAcreage;	//num of years burned acreage
	int	monthsPDSIData;	//NO less than # input layer nodes
	int endMonth;	//end month of current year (numerically)

	//Output class information
	int numClasses; //NO LESS than of input layer nodes
	
	//Do we need class names and positions (zero based)?

	//fire severity cutoffs (burned acres)
	int	lowCutoff;
	int highCutoff;


} ANN;   // Define object of type Params










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
	*/

	//Display the numbers
	cout << "Numbers:\n";
	for (int i=0; i<numbers.size(); i++) {
		cout << numbers[i] << '\n';
	}

	cin.get(); //Keep program open until "enter" is pressed
	return 0;
}
