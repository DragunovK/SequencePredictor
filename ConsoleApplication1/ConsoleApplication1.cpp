/**
* Created by Kirill Dragunov on 6 nov. 2020 19:57:44
*/

#include "NeuralNetwork.h"
#include "Configuration.h"
#include <iostream>
#include <math.h>

void formXandY(const SimpleMatrix& sequence, SimpleMatrix& X, SimpleMatrix& Y, const size_t& Xcolumns)
{
	for (size_t i = 0; i < sequence.colsNumber() - Xcolumns; i++)
	{
		X.pushBackRow(sequence.getSubRow(0, i, i + Xcolumns));
		Y.pushBackRow(sequence.getSubRow(0, i + Xcolumns, i + Xcolumns + 1));
	}
}

void generateSequenceAndReference(const size_t& option, const size_t &sequenceSize, SimpleMatrix& sequence, SimpleMatrix& reference, const size_t& predictionsNumber)
{
	SimpleMatrix S(1, sequenceSize + predictionsNumber);

	switch (option)
	{
	case 1: //Fibonacci sequence
		for (size_t i = 1; i <= sequenceSize + predictionsNumber; i++)
			if (i == 1 || i == 2)
				S.setElement(0, i - 1, 0.001);
			else 
				S.setElement(0, i - 1, (S.at(0, i - 2) + S.at(0, i - 3)));
		break;
	case 2: //Factorial function
		for (size_t i = 0; i < sequenceSize + predictionsNumber; i++)
			S.setElement(0, i, tgamma(i + 1) / 10000000);
		break;
	case 3: //Periodic function
		for (size_t i = 0; i < sequenceSize + predictionsNumber; i++)
			S.setElement(0, i, (1 + sin(2 * i)) / 10);
		break;
	case 4: //Power function
		for (size_t i = 1; i <= sequenceSize + predictionsNumber; i++)
			S.setElement(0, i - 1, (i * i) / 1000000);
		break;
	case 5: //Linear function
		for (size_t i = 1; i <= sequenceSize + predictionsNumber; i++)
			S.setElement(0, i - 1, ((double)i + 4) / 100);
		break;
	default:
		break;
	}

	sequence = S.getSubRow(0, 0, sequenceSize);
	reference = S.getSubRow(0, sequenceSize, S.colsNumber());
}

int main()
{
	SimpleMatrix sequence;
	SimpleMatrix reference;
	generateSequenceAndReference(3, 10, sequence, reference, 5);
	std::cout << "Sequence" << sequence.toString() << std::endl;

	SimpleMatrix X;
	SimpleMatrix Y;
	formXandY(sequence, X, Y, Configuration::learning_matrix_columns);
	std::cout << "X" << X.toString() << "\n";
	std::cout << "Y" << Y.toString() << "\n";

	NeuralNetwork JordanNetwork(
		X, Y, 
		Configuration::max_error,
		Configuration::learning_rate, 
		Configuration::max_allowed_iterations, 
		Configuration::number_of_hidden_layer_neurons
	);

	SimpleMatrix predictions = JordanNetwork.predict(Configuration::number_of_predictions);
	std::cout << "Predictions" << predictions.toString() << std::endl;
	std::cout << "Reference" << reference.toString() << std::endl;

	return 0;
}

