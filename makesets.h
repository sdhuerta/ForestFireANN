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
 * Struct for object movie
 ******************************************************************************/


struct trainer {
    vector<float> input ;		/*!<   */
    vector<float> output ;		/*!<   */
};


/*******************************************************************************
 *                         Function Prototypes
 ******************************************************************************/

vector<trainer> createSet(vector<PDSI> data, Parameters specs);
vector<float> createTest(vector<PDSI> data, Parameters specs);


#endif
