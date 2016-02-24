#include "GetData.h"


/******************************************************************************
 * @authors  Steven Huerta, Luke Meyer, Savoy Schuler
 *
 * @par Description:
 *
 *
 * @param[in]
 *
 * @param[in]
 *
 * @returns
 *
 *****************************************************************************/

void normalizePdsiData(vector<PDSI> &fVector, float maxBurned, float minBurned, float maxRating, float minRating)
{
    float denomB = maxBurned - minBurned;
    float denomR = maxRating - minRating;

    for (int i = 0; i < fVector.size(); i++)
    {
        fVector[i].normAcresBurned = (fVector[i].normAcresBurned - minBurned) / denomB;  // normalize the acres burned

        vector<float> pdsiData = fVector[i].pdsiVal;

        for (int j = 0; j < fVector[i].pdsiVal.size(); j++ )  // normalize the monthly ratings
        {
            fVector[i].pdsiVal[j] = (fVector[i].pdsiVal[j] - minRating) / denomR;
        }
    }

}


/******************************************************************************
 * @authors  Steven Huerta, Luke Meyer, Savoy Schuler
 *
 * @par Description:
 *
 *
 * @param[in]
 *
 * @param[in]
 *
 * @returns
 *
 *****************************************************************************/

int getYear()
{
    time_t currentTime;

    struct tm *localTime;

    time(&currentTime);
    localTime = localtime(&currentTime); // localtime() usage will throw warning 4996. I currently have warnings disabled in my project (_CRT_SECURE_NO_WARNINGS). May need to change to a non-deprecated function call.

    int currYear = localTime->tm_year + 1900;




    return currYear;

}


/******************************************************************************
 * @authors  Steven Huerta, Luke Meyer, Savoy Schuler
 *
 * @par Description:
 *
 *
 * @param[in]
 *
 * @param[in]
 *
 * @returns
 *
 *****************************************************************************/

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
        feature.normAcresBurned = atof(temp.c_str());

        feature.rawAcresBurned = feature.normAcresBurned;  //preserve the unnormalized arcres burned data


        // search for max and min burn values for normalization later
        if (feature.rawAcresBurned > maxBurned)
            maxBurned = feature.rawAcresBurned;

        if (feature.rawAcresBurned < minBurned)
            minBurned = feature.rawAcresBurned;

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


