#include <vector>
#include <stdio.h>
#include <string> 
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
 

void print_response(neuralnetwork net, vector<float> character);

int main(int argc, char* argv[])
{

    Parameters definitions;

    /* Se}up layers
    * intput = 20
    * hidden = 14
    * output = 8
    */
    definitions.nodesPerLayer = {24,14,8} ;
    definitions.learningRate = 0.4;
    definitions.momentum = .6 ;
    definitions.errorThreshold = .01 ;
    definitions.weightsFile = "test_weights.txt" ;


    neuralnetwork testnet = neuralnetwork(definitions) ;

    vector<trainer> train;

    trainer a;
    trainer b;
    trainer c;
    trainer d;
    trainer e;
    trainer f;
    trainer one;
    trainer nine;

    a.input = A;
    b.input = B;
    c.input = C;
    d.input = D;
    e.input = E;
    f.input = F;
    one.input = One;
    nine.input = Nine;

    a.output = answers[0];
    b.output = answers[1];
    c.output = answers[2];
    d.output = answers[3];
    e.output = answers[4];
    f.output = answers[5];
    one.output = answers[6];
    nine.output = answers[7];

    train.push_back(a);
    train.push_back(b);
    train.push_back(c);
    train.push_back(d);
    train.push_back(e);
    train.push_back(f);
    train.push_back(one);
    train.push_back(nine);

    //vector<vector<float>> test_data = {A,B,C,D,E,F,One,Nine} ;

    testnet.training(train, 10000);

    vector<float> response ;

    print_response(testnet, A);
    print_response(testnet, B);
    print_response(testnet, C);
    print_response(testnet, D);
    print_response(testnet, E);
    print_response(testnet, F);
    print_response(testnet, One);
    print_response(testnet, Nine);

	return 0;
}


void print_response(neuralnetwork net, vector<float> character)
{
    vector<float> response ;
    response = net.testing(character);

    printf("RESPONSE: ");

    for(int i = 0; i < response.size(); i++ )
        printf("%.3f\t", response[i]);

    printf("\n");
}



