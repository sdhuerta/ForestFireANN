/*****************************************************************************/
/* @file                         GetData.h                                   */
/*****************************************************************************/

//include files
#ifndef GETDATA_H
#define GETDATA_H
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <ctime>
#include <algorithm>
#include <fstream>

using namespace std;


/**************************************************************************//** 
 * @author Steven Huerta, Luke Meyer, Savoy Schuler
 * 
 * @par Description: 
 * Struct for object movie
 ******************************************************************************/

struct PDSI
{
    int year;		 	/*!<   */

    float normAcresBurned;	/*!<   */

    float rawAcresBurned;	/*!<   */

    vector<float> pdsiVal;	/*!<   */

};


/*******************************************************************************
 *                         Function Prototypes
 ******************************************************************************/


void normalizePdsiData( vector<PDSI> &fVector, float maxBurned, float minBurned, float maxRating, float minRating );
vector<PDSI> pdsiFeatureVector(ifstream &fin);

int getYear();

vector<PDSI> pdsiFeatureFector( ifstream &fin );


#endif
