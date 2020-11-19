#pragma once

/**
* Defines if the context on 2nd and following learning iterations will be set to zero.
* To disable comment the define out.
*/
#define set_learning_context_to_zero

/**
* Defines if the context will be set to zero before predicting.
* To disable comment the define out.
*/
#define set_predicting_context_to_zero

/**
* Defines if threshold will be used. If defined, threshold will be updated.
* To disable comment the define out.
*/
#define threshold

/**
* Defines if each iteration's mse and weights will be displayed.
* To disable comment the define out.
*/
//#define learning_debug

struct Configuration
{
	static inline const double max_error = 0.0001;
	static inline const double learning_rate = 0.05;
	static inline const size_t number_of_hidden_layer_neurons = 5;
	static inline const size_t max_allowed_iterations = 1000000;
	static inline const size_t number_of_predictions = 5;
	static inline const size_t learning_matrix_columns = 3;
};

