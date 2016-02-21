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


struct PDSI
{
	int year;
	
	float acresBurned;

	vector<float> pdsiVal;

};


void normalizePdsiData( vector<PDSI> &fVector, float maxBurned, float minBurned, float maxRating, float minRating );
vector<PDSI> pdsiFeatureVector(ifstream &fin);

int getYear();


vector<PDSI> pdsiFeatureFector( ifstream &fin );



#endif
