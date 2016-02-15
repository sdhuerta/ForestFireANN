CC = g++
CFLAGS = -c -std=c++11





all: testnet

testnet: test_net.o perceptron.o neuralnetwork.o
	$(CC) $(CFLAGS) test_net.o perceptron.o neuralnetwork.o -o testnet

test_net.o: test_net.cpp
	$(CC) $(CFLAGS) test_net.cpp

perceptron.o: perceptron.cpp
	$(CC) $(CFLAGS) perceptron.cpp

neuralnetwork.o: neuralnetwork.cpp
	$(CC) $(CFLAGS) neuralnetwork.cpp

clean: rm *o testnet