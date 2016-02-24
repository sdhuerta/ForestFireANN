#include "ParamParser.h"


/******************************************************************************
 * @authors Steven Huerta, Luke Meyers, Savoy Schuler
 *
 * @par Description:
 * This function's primary purpose is storing information from the .prm in a
 * Parameter struct for the Params. The function is passed the string name of
 * the .prm file by the main file, locates it and opens it from the directory.
 * iterates through it, skipping all lines that begin with a comment or empty
 * string, and stores the parameter values in a temporary string vector. After
 * closing in the input file, the function iterates through the vector reducing
 * the strings to substrings by trimming off any white space or comments. The
 * "number of nodes per layer" value has a special case handle that ensures we
 * account for that line storing mulltiple values. The function concludes by
 * iterating through the vector and storing it's values in the respective struct
 * attributes.
 *
 * @param[in]	fileName - .prm file to get data from
 *
 * @returns		returns a parameter populated ANN struct to main
 *
 *****************************************************************************/

Parameters getParams(string fileName)
{
    //Define Params as an instance of the Parameter struct
    Parameters Params;

    //Open stream for input/output files
    ifstream inputFile(fileName);

    //line will be used for file reading
    //pnd and emp are comparators for skipping comments and blank lines
    string line, pnd ="#",emp = "";

    /*tempVals will store all variables read from input file as temporary
    strings until type sorting*/
    vector<string> tempVals;

    /*Stringstream variables are used to ensure correct type casting from
    string to proper type assignment. I hoped to avoid using so many, but if
    each instance of type casting wasn't redefined, the values were lost.*/
    stringstream s0,s1,s2,s3,s4,s5,s6,s7,s8,s9,s10,s11,s12,s13;

    /*The while loop reads through the input file, skipping any lines that
    begin with an empty string or a comment indicator. It stores all
    variables as strings (which is necessary given they are followed by
    comments) into a vector. I am aware fstreamf may have seemed like a
    viable option for simplifying the process by g just rabbing the
    variables, but the numNodesPerLayer variable inhibits this by having an
    unspecified number of values on a single line. Thus getline was
    necessary.*/
    while(getline(inputFile,line))
    {
        if( line[0]==pnd[0]||line[0]==emp[0])
        {
        }
        else
            tempVals.push_back(line);
    }

    //Made sure to close input file.
    inputFile.close();


    /*Here I used substrings and delimiters as a method for separating
    variables from their comments and storing the variable back as a
    string into the tempVals vector for holding. I made a special case
    for line numNodesPerLayer line by splitting it on the '#' to make
    sure it captured all numerical values. */
    for (int vecPos=0; vecPos<tempVals.size(); vecPos++)
    {
        if(vecPos==6)
        {
            string substring, intString=tempVals[vecPos];
            substring = intString.substr(0,intString.find_first_of("#"));
            tempVals[vecPos]=substring;
        }
        else
        {
            string substring, intString=tempVals[vecPos];
            substring = intString.substr(0,intString.find_first_of(" "));
            tempVals[vecPos]=substring;
        }
    }

    /*Here I make use of stringstream to read the string type variables
    out of the tempVals vectors and store them into the struct paramaters
    by using stringstream to identify type. As mentioned, either separate
    or reinitialized variables are necessary for each new value*/
    s0<<tempVals[0];
    s0>>Params.weightsFile;

    s1<<tempVals[1];
    s1>>Params.numEpochs;

    s2<<tempVals[2];
    s2>>Params.learningRate;

    s3<<tempVals[3];
    s3>>Params.momentum;

    s4<<tempVals[4];
    s4>>Params.errorThreshold;

    s5<<tempVals[5];
    s5>>Params.numLayers;

    /*Because this variable is a vector, it is necessary to set the values
    independantly by assignment using emplace, as indexing produces a seg
    fault since the system considers that referencing and cParamsot intialize
    new vector spaces.*/
    s6<<tempVals[6];
    while(1)
    {
        int vecValue;
        s6 >> vecValue;
        if(!s6)
            break;
        Params.nodesPerLayer.push_back(vecValue);
    }

    s7<<tempVals[7];
    s7>>Params.trainFile;

    s8<<tempVals[8];
    s8>>Params.yearsBurnedAcreage;

    s9<<tempVals[9];
    s9>>Params.monthsPDSIData;

    s10<<tempVals[10];
    s10>>Params.endMonth;

    s11<<tempVals[11];
    s11>>Params.numClasses;

    s12<<tempVals[12];
    s12>>Params.lowCutoff;

    s13<<tempVals[13];
    s13>>Params.highCutoff;


    //return populated Param struct to main
    return Params;
}
