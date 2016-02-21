

vector<trainer> createSet(vector<PDSI> data, Params specs)
{
	int months_left = specs.monthsPDSIData;
	int burned_left = specs.yearsBurnedAcreage;
	int end_month = specs.endMonth;
	int next_year;
	int correct_output;
	vector<trainer> train_set ;

	int sample_size = (specs.monthsPDSIData - specs.endMonth) / 12 ;

	int total_samples = data.size() - sample_size + 1;

	for(int i = 1; i < total_samples-1; i++ )
	{
		vector<float> input_set;
		vector<float> output_set(specs.numClasses, 0);
		
		// Let's load our burned data first.
		for(int j = 0; j < burned_left; j++)
			intput_set.push_back(data[i+1].acresBurned);

		// Load up our end months
		for(int j = 0; j < end_month; j++ )
		{
			input_set.push_back(data[i].pdsiVal[j]);
			months_left--;
		}

		next_year = 1 ;
		while( months_left > 0 ) 
		{
			for(int j = 0; j < 12 && months_left > 0; j++ )
			{
				input_set.push_back(data[i+next_year].pdsiVal[j])
				months_left-- ;
			}

			// increment to next year
			next_year++ ;
		}

		new_set.input = input_set ;

		if( data[i].acresBurned >= specs.lowCutoff)
			output_set[1] = 1.0 ;

		else if ( data[i].acresBurned >= specs.highCutoff)
			output_set[2] = 1.0 ;

		else
			output_set[0] = 1.0 ;

		new_set.input = output_set ;

		train_set.push_back(new_set) ;

	}


	return train_set ;
}


vector<float> createTest(vector<PDSI> data, Params specs)
{
	int months_left = specs.monthsPDSIData;
	int burned_left = specs.yearsBurnedAcreage;
	int end_month = specs.endMonth;
	vector<float> test_input ;
	int next_year = 1 ;

	for(int i = 0; i < specs.yearsBurnedAcreage )
	{
		test_input.push_back(data[i].acresBurned);
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

	return test_intput ;
}