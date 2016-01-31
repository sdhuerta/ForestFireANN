#include <vector>
#include <time.h> // RAND


class Perceptron{
public:
    // CONSTRUCTOR
    Perceptron(int num_inputs);

    // Feed the perceptron some inputs and get some output
    float get_output(vector<float> inputs);

    float adjust_weights(); // Need to do some thought on this

private:
    void activation(); // Activation function, using sigmoid function
    void sum_weights(); // Calculate the output

    vector<float> weights;	
    
    float sum ; // sum after application of weights
    float output ; // result of sigmoid of sum

    // USED LATER WITH ADJUSTING WEIGHTS
    float sig_prime ; // the derivative of sigmoid applied to sum
    float delta; 

    int num_inputs;

    alpha = .04 ;
};


Perceptron::Perceptron(int num_inputs)
{
    num_inputs = num_inputs ;

    int rand_init_val ;

    srand(time(null));
    for(int i = 0; i < num_inputs; i++)
    {
        rand_init_val =  (rand() % 100 + 1) / 1000 ;
        weights.push_back(rand_init_val) ;
    }

}

float Perceptron::get_output(vector<float> inputs)
{
    // Sum up all the weights
    sum_weights( inputs );

    // Apply sigmoid to sum for this perceptron
    activation();

    return output ;
}

void Perceptron::sum_weights(vector<float> inputs)
{
    for(int i = 0; i < num_inputs; i++)
        sum += inputs[i] * weights[i] ;
}


void Perceptron::activation()
{
    //Sigmoid function
    output = 1.0 / (1 + exp(-sum)) ;

    // While we're here, let's calculate the sigmoid derivative for the 
    // purpose of backprop
    sig_prime = output * (1 - output);
}
