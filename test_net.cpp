#include <vector>
#include <stdio.h>
#include "neuralnetwork.h"

using namespace std;


	/* 5x4 maps of characters using 1 or 0
	* Example:
	*
	* 1 1 1 1
	* 1 0 0 1
	* 1 1 1 1
	* 1 0 0 1
	* 1 0 0 1
	*
	* Represents 'A'
	*/


const vector<float> A = {0, 1, 1, 0,
					   1, 0, 0, 1,
					   1, 0, 0, 1, 
					   1, 1, 1, 1,
					   1, 0, 0, 1,
					   1, 0, 0, 1 };

const vector<float> B = {1, 1, 1, 0,
					   1, 0, 0, 1,
					   1, 1, 1, 0, 
					   1, 0, 0, 1,
					   1, 0, 0, 1,
					   1, 1, 1, 0 } ;

const vector<float> C = {0, 1, 1, 1,
					   1, 0, 0, 0,
					   1, 0, 0, 0, 
					   1, 0, 0, 0,
					   1, 0, 0, 0,
					   0, 1, 1, 1 } ;


const vector<float> D = {1, 1, 1, 0,
					   1, 0, 0, 1,
					   1, 0, 0, 1, 
					   1, 0, 0, 1,
					   1, 0, 0, 1,
					   1, 1, 1, 0 } ;


const vector<float> E = {1, 1, 1, 1,
					   1, 0, 0, 0,
					   1, 1, 1, 0, 
					   1, 0, 0, 0,
					   1, 0, 0, 0,
					   1, 1, 1, 1 } ;


const vector<float> F = {1, 1, 1, 1,
					   1, 0, 0, 0,
					   1, 1, 1, 0, 
					   1, 0, 0, 0,
					   1, 0, 0, 0,
					   1, 0, 0, 0 } ;


const vector<float> One =  {0, 1, 0, 0,
					      1, 1, 0, 0,
					      0, 1, 0, 0, 
					      0, 1, 0, 0,
					      0, 1, 0, 0,
					      1, 1, 1, 0 } ;


const vector<float> Nine = {0, 0, 1, 1,
					      0, 1, 0, 1,
					      0, 0, 1, 1, 
					      0, 0, 0, 1,
					      0, 0, 0, 1,
					      0, 0, 0, 1 } ;


const vector<vector<float>> answers = {{1,0,0,0,0,0,0,0},
								     {0,1,0,0,0,0,0,0},
								     {0,0,1,0,0,0,0,0},
								     {0,0,0,1,0,0,0,0},
								     {0,0,0,0,1,0,0,0},
								     {0,0,0,0,0,1,0,0},
								     {0,0,0,0,0,0,1,0},
								     {0,0,0,0,0,0,0,1}};




int main(int argc, char* argv[])
{

    Param definitions;

    /* Se}up layers
    * intput = 20
    * hidden = 14
    * output = 8
    */
    definitions.layers = {20,14,8} ;

    definitions.learning_rate = 0.5;
    definitions.momentum = 1 ;
    definitions.min_error = .05 ;

    neuralnetwork testnet = neuralnetwork(definitions) ;

    vector<vector<float>> test_data = {A,B,C,D,E,F,One,Nine} ;

    testnet.training(test_data, answers, 100);

    vector<float> response ;

    response = testnet.testing(D);

    printf("RESPONSE: ");

   	for(int i = 0; i < response.size(); i++ )
   		printf("%.3f\t", response[i]);

   	printf("\n");

	return 0;
}



