#ifndef MAKESETS_H
#define MAKESETS_H

#include "GetData.h"
#include "ParamParser.h"

struct trainer {
    vector<float> input ;
    vector<float> output ;
};



vector<trainer> createSet(vector<PDSI> data, Parameters specs);
vector<float> createTest(vector<PDSI> data, Parameters specs);


#endif
