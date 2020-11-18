/**
* Created by Kirill Dragunov on 6 nov. 2020 20:18:43
*/

#include "NeuralNetwork.h"
#include "Configuration.h"
#include <iostream>

std::function<double(double)> sigmoid = [](const double& arg) {
	return 1 / (1 + exp(-arg));
};

void NeuralNetwork::learn()
{
	for (size_t learningIteration = 1; learningIteration <= maxAllowedIterations; learningIteration++)
	{
		
#ifdef set_learning_context_to_zero
		context = 0;
#endif // set_context_to_zero

		// Updating weights
		for (size_t xIndex = 0; xIndex < X.rowsNumber(); xIndex++)
		{
			auto Xi = X.getRow(xIndex);  // Input layer
			Xi.pushBack(context, false); // Insert context into input layer
			
			auto Hi = (Xi * W).function(sigmoid); // Hidden layer
			auto Yi = (Hi * V).function(sigmoid); // Output layer (single neuron)
			
			context = Yi.at(0, 0);
			auto delta = context - Y.at(xIndex, 0);

			auto Hit = Hi.transpose();
			W -= learningRate * delta * (V.elementwiseMult(Hit.elementwiseMult(1 - Hit)) * Xi).transpose();
			V -= learningRate * delta * Hi.transpose();
		}

#ifdef set_learning_context_to_zero
		context = 0;
#endif // set_context_to_zero

		double totalMSE = 0.0;
		
		// Counting error
		for (size_t xIndex = 0; xIndex < X.rowsNumber(); xIndex++)
		{
			auto Xi = X.getRow(xIndex);
			Xi.pushBack(context, false);

			auto Hi = (Xi * W).function(sigmoid);
			auto Yi = (Hi * V).function(sigmoid);

			context = Yi.at(0, 0);
			auto delta = context - Y.at(xIndex, 0);

			totalMSE += delta * delta / 2;
		}

#ifdef learning_debug
		std::cout << "On learning iteration " + std::to_string(learningIteration) + " total MSE = " + std::to_string(totalMSE) + ".\n";
		std::cout << "Weights:\n" << "W " << W.toString() << "\nV " << V.toString() << std::endl;
#endif // learning_debug

		if (totalMSE <= maxAllowedError)
		{
			std::cout << "Training complete within " << std::to_string(learningIteration) << " iterations. Final MSE: " + std::to_string(totalMSE) << std::endl;
			break;
		}
	}
}

NeuralNetwork::NeuralNetwork(const SimpleMatrix& X, 
	const SimpleMatrix& Y, 
	const double& maxAllowedError, 
	const double& learningRate, 
	const int& maxAllowedIterations, 
	const int& numberOfHiddenLayerNeurons)
{
	this->X = X;
	this->Y = Y;
	this->maxAllowedError = maxAllowedError;
	this->learningRate = learningRate;
	this->maxAllowedIterations = maxAllowedIterations;
	this->numberOfHiddenLayerNeurons = numberOfHiddenLayerNeurons;
	this->context = 0;

	W = SimpleMatrix(X.colsNumber() + 1, numberOfHiddenLayerNeurons, -1, 1);
	V = SimpleMatrix(numberOfHiddenLayerNeurons, 1, -1, 1);

	learn();
}

SimpleMatrix NeuralNetwork::predict(const size_t& predictionsNumber)
{
	SimpleMatrix predictions(1, predictionsNumber + 1);
	SimpleMatrix X_ = X.getRow(X.rowsNumber() - 1);

#ifdef set_predicting_context_to_zero
	context = 0;
#endif // set_predicting_context_to_zero

	for (size_t i = 0; i < predictionsNumber + 1; i++)
	{
		auto Xi = X_.getSubRow(0, i, X_.colsNumber());
		Xi.pushBack(context, false);

		auto Hi = (Xi * W).function(sigmoid);
		auto Yi = (Hi * V).function(sigmoid);

		context = Yi.at(0, 0);
		predictions.setElement(0, i, context);

		X_.pushBack(context, false);
	}

	return predictions.getSubRow(0, 1, predictions.colsNumber());
}

