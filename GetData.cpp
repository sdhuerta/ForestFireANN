#include "GetData.h"


/******************************************************************************
 * @authors  Steven Huerta, Luke Meyer, Savoy Schuler
 *
 * @par Description:
 * Normalizes the .csv data to better suit this particular application of an ANN
 *
 *
 * @param[in/out] vector<PDSI> fVector - feature vector containing raw .csv data
 *                                  to be normalized
 *
 * @param[in] float maxBurned - contains the largest value of burned acres
 *                              across all of the data read in from the .csv
 *
 * @param[in] float minBurned - contains the smallest value of burned acres
 *                              across all of the data read in from the .csv
 *
 * @param[in] float maxRating - contains the largest PDSI value across all data
 *                              read from the .csv
 *
 * @params[in] float minRating - contains the smallest PDSI value across all
 *                               data read from the .csv
 *
 * @returns void
 *
 *****************************************************************************/

void normalizePdsiData(vector<PDSI> &fVector, float maxBurned, float minBurned,
                       float maxRating, float minRating)
{
    float denomB = maxBurned - minBurned;
    float denomR = maxRating - minRating;

    for (int i = 0; i < fVector.size(); i++)
    {
        // normalize the acres burned
        fVector[i].normAcresBurned =
            (fVector[i].normAcresBurned - minBurned) / denomB;

        vector<float> pdsiData = fVector[i].pdsiVal;

        for (int j = 0; j < fVector[i].pdsiVal.size(); j++ )
        {
            // normalize the monthly ratings
            fVector[i].pdsiVal[j] = (fVector[i].pdsiVal[j] - minRating) /denomR;
        }
    }

}


/******************************************************************************
 * @authors  Steven Huerta, Luke Meyer, Savoy Schuler
 *
 * @par Description:
 * Returns the current calendar year
 *
 *
 * @param[in] - none
 *
 *
 * @returns currYear - integer value representing the current year
 *
 *****************************************************************************/

int getYear()
{
    time_t currentTime;

    struct tm *localTime;

    time(&currentTime);
    localTime = localtime(&currentTime);

    int currYear = localTime->tm_year + 1900;

    return currYear;

}


/******************************************************************************
 * @authors  Steven Huerta, Luke Meyer, Savoy Schuler
 *
 * @par Description: This function facilitates the parsing of a .csv file
 *containing yearly burn data and also populates a feature vector with said
 *data to be used as input for the neural network during the training phase.
 *
 *
 * @param[in] ifstream fin - input file stream for .csv data
 *
 *
 * @returns vector<PDSI> - returns a populated feature vector
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

    // while there are still rows in the csv, read the year
    while (getline(fin, temp, ',') && !thisYear)
    {
        PDSI feature;
        float data = 0.0;

        feature.year = atoi(temp.c_str());

        // read the acres burned for that year
        getline(fin, temp, ',');
        feature.normAcresBurned = atof(temp.c_str());

        //preserve the unnormalized arcres burned data
        feature.rawAcresBurned = feature.normAcresBurned;


        // search for max and min burn values for normalization later
        if (feature.rawAcresBurned > maxBurned)
            maxBurned = feature.rawAcresBurned;

        if (feature.rawAcresBurned < minBurned)
            minBurned = feature.rawAcresBurned;

        if (feature.year == currYear)  /* make sure only to read monthly values
		 up to and including March if reading current year's data*/
        {
            for (int i = 0; i < 3; i++)
            {
                getline(fin, temp, ',');

                data = atof(temp.c_str());

                feature.pdsiVal.push_back(data);
                // search for max and min rating value for normalization later
                if (data > maxRating)
                    maxRating = data;

                if (data < minRating)
                    minRating = data;
            }

            thisYear = true; /* set flag if processing current year as to not
				read data beyond March of the current year */
        }
        else
        {
            // if it is not the current year's data, read all months
            for (int i = 0; i < 12; i++)
            {
                if (i != 11)
                {
                    getline(fin, temp, ',');
                }
                else  /* if we are reading in december rating, need to consider
			 the end of line character present */
                {
                    getline(fin, temp, '\n');
                }

                data = atof(temp.c_str());

                feature.pdsiVal.push_back(data);

                // search for max and min rating value for normalization later
                if (data > maxRating)
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


