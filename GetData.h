#ifndef GETDATA_H
#define GETDATA_H

#include <fstream>
#include <vector>



struct PDSI;

void normalizePdsiData( vector<PDSI> &fVector, float maxBurned, float minBurned, float maxRating, float minRating );


int getYear();


vector<PDSI> pdsiFeatureFector( ifstream &fin );



#endif
