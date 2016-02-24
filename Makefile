LINK = g++
CFLAGS = -Wall -O -g
CXXFLAGS = $(CFLAGS) -std=c++11

TARGET = ANNtest ANNtrain 

all:	$(TARGET)

ANNtest: ANNtest.o neuralnetwork.o ParamParser.o perceptron.o GetData.o makesets.o 
	$(LINK) $(CFLAGS) -o $@ $^

ANNtrain: ANNtrain.o neuralnetwork.o ParamParser.o perceptron.o GetData.o makesets.o 
	$(LINK) $(CFLAGS) -o $@ $^

clean:
	rm -f *.o *~ core 

cleanall:
	rm -f *.o *~ core $(TARGET)
