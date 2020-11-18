/**
* Created by Kirill Dragunov on 6 nov. 2020 20:18:40
*/

#pragma once
#include "SimpleMatrix.h"

class NeuralNetwork
{
	SimpleMatrix W;
	SimpleMatrix V;
	SimpleMatrix X;
	SimpleMatrix Y;
	
	double context;
	
	double learningRate;
	double maxAllowedError;
	int maxAllowedIterations;
	int numberOfHiddenLayerNeurons;

	void learn();
public:
	NeuralNetwork(const SimpleMatrix& X,
		const SimpleMatrix& Y, 
		const double& maxAllowedError, 
		const double& learningRate, 
		const int& maxAllowedIterations, 
		const int& numberOfHiddenLayerNeurons);

	SimpleMatrix predict(const size_t &predictionsNumber);
};

