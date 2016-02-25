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
 * Struct to contain the normalized .csv file data for a single year.
 * Also contains the normalized burned acreage data
 ******************************************************************************/

struct PDSI
{
    int year;		 	/*!<  year of data  */

    float normAcresBurned;	/*!<  normalized burn acreage */

    float rawAcresBurned;	/*!<  un-normalized burn acreage */

    vector<float> pdsiVal;	/*!<  normalized pdsi rating */

};


/*******************************************************************************
 *                         Function Prototypes
 ******************************************************************************/


void normalizePdsiData( vector<PDSI> &fVector, float maxBurned, float minBurned,
                        float maxRating, float minRating );

vector<PDSI> pdsiFeatureVector(ifstream &fin);

int getYear();

vector<PDSI> pdsiFeatureFector( ifstream &fin );


#endif
