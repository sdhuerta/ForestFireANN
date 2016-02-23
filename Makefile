CC = g++
CFLAGS = -c -std=c++11

# the build target executable:
TARGET = ANNtest ANNtrain GetData makesets neuralnetwork ParamParser perceptron

all: $(TARGET)


# specific targets

ANNtest.o: ANNtest.cpp ParamParser.cpp neuralnetwork.cpp
	$(CC) $(CFLAGS) ANNtest.cpp ParamParser.cpp neuralnetwork.cpp

ANNtrain.o: ANNtrain.cpp ParamParser.cpp neuralnetwork.cpp
	$(CC) $(CFLAGS) ANNtrain.cpp ParamParser.cpp neuralnetwork.cpp

GetData.o: GetData.cpp
	$(CC) $(CFLAGS) GetData.cpp

makesets.o: makesets.cpp
	$(CC) $(CFLAGS) makesets.cpp

neuralnetwork.o: neuralnetwork.cpp
	$(CC) $(CFLAGS) neuralnetwork.cpp

ParamParser.o: ParamParser.cpp
	$(CC) $(CFLAGS) ParamParser.cpp

perceptron.o: perceptron.cpp
	$(CC) $(CFLAGS) perceptron.cpp

clean: rm *o testnet
