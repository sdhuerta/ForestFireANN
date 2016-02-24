# Makefile for Program #1 Artificial Neural Network

# Author: Savoy Schuler
# Class:  CSC447 Artificial Intelligence
# Date:   Spring 2016

# Usage:  make target1 target2 ...

#===============================================================================

# GNU C/C++ compiler and linker:
LINK = g++

# Preprocessor and compiler flags
#CFLAGS = -Wall -O -g
CXXFLAGS = $(CFLAGS) -std=c++11

#===============================================================================

# Targets
TARGET = ANNtest ANNtrain CrossValidate

#Build Everything

all:	$(TARGET)

#Dependencies 
ANNtest: ANNtest.o neuralnetwork.o ParamParser.o perceptron.o GetData.o makesets.o 
	$(LINK) $(CFLAGS) -o $@ $^

ANNtrain: ANNtrain.o neuralnetwork.o ParamParser.o perceptron.o GetData.o makesets.o 
	$(LINK) $(CFLAGS) -o $@ $^

CrossValidate: CrossValidate.o neuralnetwork.o ParamParser.o perceptron.o GetData.o makesets.o 
	$(LINK) $(CFLAGS) -o $@ $^

#===============================================================================

#Include option for clean sweep of objects and executables
clean:
	rm -f *.o *~ core $(TARGET)


