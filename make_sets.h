#ifndef NEURALNETWORK_H
#define NEURALNETWORK_H

#include "GetData.h"
#include "ParamParser.h"

struct trainer{
	vector<float> input ;
	vector<float> output ;
};



vector<trainer> createSet(vector<PDSI> data, Params specs)