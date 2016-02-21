

#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <ctime>
#include <algorithm>
#include "GetData.h"


using namespace std;


struct PDSI
{
	int year;
	
	float acresBurned;

	vector<float> pdsiVal;

};

void normalizePdsiData(vector<PDSI> &fVector, float maxBurned, float minBurned, float maxRating, float minRating)
{
	float denomB = maxBurned - minBurned;
	float denomR = maxRating - minRating;

	for (int i = 0; i < fVector.size(); i++)
	{
		fVector[i].acresBurned = (fVector[i].acresBurned - minBurned) / denomB;  // normalize the acres burned

		vector<float> pdsiData = fVector[i].pdsiVal;

		for (int j = 0; j < fVector[i].pdsiVal.size(); j++ )  // normalize the monthly ratings
		{
			fVector[i].pdsiVal[j] = (fVector[i].pdsiVal[j] - minRating) / denomR;
		}
	}
	
}

int getYear()
{
	time_t currentTime;

	struct tm *localTime;

	time(&currentTime);
	localTime = localtime(&currentTime); // localtime() usage will throw warning 4996. I currently have warnings disabled in my project (_CRT_SECURE_NO_WARNINGS). May need to change to a non-deprecated function call.

	int currYear = localTime->tm_year + 1900;




	return currYear;

}

vector<PDSI> pdsiFeatureVector(ifstream &fin)
{
	string temp;
	float maxBurned = -100.0;  // arbitrary initialization values
	float minBurned = 500000000;

	float maxRating = -11.0;
	float minRating = 11.0;
	bool thisYear = false;  // flag to signal when processing current year data


	/*feature vector to be used as input for training*/
	vector<PDSI> fVector;



	(getline(fin, temp, '\n'));  // skip over 2 header lines in csv
	(getline(fin, temp, '\n'));
	
	// want to get current year for looping bounds
	int currYear = getYear();

	while (getline(fin, temp, ',') && !thisYear)  // while there are still rows in the csv, read the year
	{
		PDSI feature;
		float data = 0.0;
		
		feature.year = atoi(temp.c_str()); 

		// read the acres burned for that year
		getline(fin, temp, ',');
		feature.acresBurned = atof(temp.c_str());  


		// search for max and min burn values for normalization later
		if (feature.acresBurned > maxBurned)
			maxBurned = feature.acresBurned;

		if (feature.acresBurned < minBurned)
			minBurned = feature.acresBurned;

		if (feature.year == currYear)  // make sure only to read monthly values up to and including March if reading current year's data
		{
			for (int i = 0; i < 3; i++)
			{
				getline(fin, temp, ',');

				data = atof(temp.c_str());

				feature.pdsiVal.push_back(data);

				if (data > maxRating)  // search for max and min rating value for normalization later
					maxRating = data;

				if (data < minRating)
					minRating = data;
			}

			thisYear = true; // set flag if processing current year as to not read data beyond March of the current year
		}
		else
		{
			for (int i = 0; i < 12; i++) // if it is not the current year's data, read all months
			{
				if (i != 11)
				{
					getline(fin, temp, ',');
				}
				else  // if we are reading in december rating, need to consider the end of line character present
				{
					getline(fin, temp, '\n');
				}

				data = atof(temp.c_str());

				feature.pdsiVal.push_back(data);

				if (data > maxRating)  // search for max and min rating value for normalization later
					maxRating = data;

				if (data < minRating)
					minRating = data;
			}
		}

		fVector.push_back(feature); // add feature to feature vector

	}

	// normalize acres burned and monthly pdsi ratings
	normalizePdsiData(fVector, maxBurned, minBurned, maxRating, minRating);


	return fVector;
}


//int main()
//{	


	/* Still need to code the functionality to receive input from a parameter file*/

	
//	string pdsi_bh = "PDSI_BH_1978-2015.csv";
//	string pdsi_nw = "PDSI_NW_1998_2015.csv";
//	string temp;

//	string input = pdsi_bh;

//	ifstream fin(input.c_str());

//	if (!fin)
//	{
//		std::cout << "There was an error opening the input file";
//		return -1;
//	}
	
//	vector<PDSI> fVector = pdsiFeatureVector(fin);

//	fin.close();

	

//	fVector;		


  //  return 0;
//}

