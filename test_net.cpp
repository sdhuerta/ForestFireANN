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


const vector<int> A = {0, 1, 1, 0,
					   1, 0, 0, 1,
					   1, 0, 0, 1, 
					   1, 1, 1, 1,
					   1, 0, 0, 1,
					   1, 0, 0, 1 };

const vector<int> B = {1, 1, 1, 0,
					   1, 0, 0, 1,
					   1, 1, 1, 0, 
					   1, 0, 0, 1,
					   1, 0, 0, 1,
					   1, 1, 1, 0 } ;

const vector<int> C = {0, 1, 1, 1,
					   1, 0, 0, 0,
					   1, 0, 0, 0, 
					   1, 0, 0, 0,
					   1, 0, 0, 0,
					   0, 1, 1, 1 } ;


const vector<int> D = {1, 1, 1, 0,
					   1, 0, 0, 1,
					   1, 0, 0, 1, 
					   1, 0, 0, 1,
					   1, 0, 0, 1,
					   1, 1, 1, 0 } ;


const vector<int> E = {1, 1, 1, 1,
					   1, 0, 0, 0,
					   1, 1, 1, 0, 
					   1, 0, 0, 0,
					   1, 0, 0, 0,
					   1, 1, 1, 1 } ;


const vector<int> F = {1, 1, 1, 1,
					   1, 0, 0, 0,
					   1, 1, 1, 0, 
					   1, 0, 0, 0,
					   1, 0, 0, 0,
					   1, 0, 0, 0 } ;


const vector<int> One =  {0, 1, 0, 0,
					      1, 1, 0, 0,
					      0, 1, 0, 0, 
					      0, 1, 0, 0,
					      0, 1, 0, 0,
					      1, 1, 1, 0 } ;


const vector<int> Nine = {0, 0, 1, 1,
					      0, 1, 0, 1,
					      0, 0, 1, 1, 
					      0, 0, 0, 1,
					      0, 0, 0, 1,
					      0, 0, 0, 1 } ;



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
















	return 0;
}



