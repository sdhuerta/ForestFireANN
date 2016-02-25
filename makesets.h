/*****************************************************************************/
/* @file                        makesets.h                                   */
/*****************************************************************************/

//include files
#ifndef MAKESETS_H
#define MAKESETS_H
#include "GetData.h"
#include "ParamParser.h"

/**************************************************************************//**
 * @author Steven Huerta, Luke Meyer, Savoy Schuler
 *
 * @par Description:
 * Struct to contain the input and output for each perceptron
 ******************************************************************************/


struct trainer {
    vector<float> input ;  /*!< vector contains input data for a perepctron */
    vector<float> output ; /*!< vector contains output data from a perceptron */
};


/*******************************************************************************
 *                         Function Prototypes
 ******************************************************************************/

vector<trainer> createSet(vector<PDSI> data, Parameters specs, bool test_set) ;
vector<float> createTest(vector<PDSI> data, Parameters specs);


#endif
