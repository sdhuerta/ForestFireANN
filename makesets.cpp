#include "makesets.h"


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

vector<trainer> createSet(vector<PDSI> data, Parameters specs)
{
	int months_left = specs.monthsPDSIData;
	int burned_left = specs.yearsBurnedAcreage;
	int end_month = specs.endMonth;
	int next_year;
	int correct_output;
	vector<trainer> train_set ;
	int sample = 0 ;

	trainer new_set;
	vector<float> input_set;
	vector<float> output_set;

	int sample_size = (specs.monthsPDSIData - specs.endMonth) / 12 + 2;

	int total_samples = data.size() - sample_size + 1;

	while( sample < total_samples )
	{

		months_left = specs.monthsPDSIData;
		input_set.clear();
		output_set.clear();

		// Let's load our burned data first.
		for(int j = 0; j < burned_left; j++)
			input_set.push_back(data[sample+1].normAcresBurned);

		// Load up our end months
		for(int j = 0; j < end_month; j++ )
		{
			input_set.push_back(data[sample].pdsiVal[j]);
			months_left--;
		}

		next_year = 1 ;

		while( months_left > 0 ) 
		{
			for(int j = 0; j < 12 && months_left > 0; j++ )
			{
				input_set.push_back(data[sample+next_year].pdsiVal[j]);
				months_left-- ;
			}

			// increment to next year
			next_year++ ;
		}

		new_set.input = input_set ;

		output_set.assign(specs.numClasses, 0);

		if( data[sample].rawAcresBurned < specs.lowCutoff )
			output_set[0] = 1.0 ;

		else if ( data[sample].rawAcresBurned < specs.highCutoff)
			output_set[1] = 1.0 ;

		else
			output_set[2] = 1.0 ;

		new_set.output = output_set ;

		train_set.push_back(new_set) ;
     
                sample += 1;

	}

	return train_set ;
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

vector<float> createTest(vector<PDSI> data, Parameters specs)
{
	int months_left = specs.monthsPDSIData;
	int burned_left = specs.yearsBurnedAcreage;
	int end_month = specs.endMonth;
	vector<float> test_input ;
	int next_year = 1 ;

	for(int i = 0; i < burned_left; i++ )
	{
		test_input.push_back(data[i].normAcresBurned);
	}

	for(int i = 0; i < end_month; i++)
	{
		test_input.push_back(data[0].pdsiVal[i]);
		months_left-- ;
	}

	while(months_left > 0)
	{
		for(int i = 0; i < 12 && months_left > 0; i++)
		{
			test_input.push_back(data[next_year].pdsiVal[i]);
			months_left-- ;
		}

		next_year++ ;

	}

	return test_input ;
}
