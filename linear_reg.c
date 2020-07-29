#include <stdio.h>
#include <math.h>


float LinearReg(int train_x[], int x_size, int train_y[], int test_size, int test_x[], int test_y[]);
float MSE(float x, float y_pred, float y_actual, int size);


int main()
{
	int train_x[] = {2, 4, 6, 7, 9, 10, 13, 17, 25, 30};
	int train_x_size = sizeof(train_x)/sizeof(train_x[0]);
	int train_y[] = {4, 7, 12, 15, 18, 23, 27, 34, 50, 60};
	
	int test_x[] = {22, 45, 28};
	int test_y[] = {44, 90, 56};
	int test_size = sizeof(test_x)/sizeof(test_x[0]);
	
	LinearReg(train_x, train_x_size, train_y, test_size, test_x, test_y);
	
}

float LinearReg(int train_x[], int x_size, int train_y[], int test_size, int test_x[], int test_y[])
{
	//training params
	int epoch = 10;
	float lr = 0.01;
	//model vars
	float y_pred = 0;
	float bias = 0;
	float slope = 0;
	float slope_der = 0;
	float bias_der = 0;
	//loop vars
	int i, j;
	//eval
	float acc = 0;
	float preds[] = {};
	float r0 = 0;
	float r1 = 0;
	float test_y_mean = 0;
	
	for(i=0; i<epoch; i++)
	{
		for(j=0; j<x_size; j++)
		{
			y_pred = slope*train_x[j] + bias;
			//losses
			slope_der = MSE(train_x[j], y_pred, train_y[j], x_size);
			bias_der = MSE(train_x[j], y_pred, train_y[j], x_size)/train_x[j];
			//gradient descent
			slope-= lr*slope_der;
			bias-= lr*bias_der;
		}
	}
	
	for(i=0; i<test_size; i++)
	{
		printf("For input %d prediction is: %f\n", test_x[i], (test_x[i]*slope + bias));
		preds[i] = test_x[i]*slope + bias;
	}
	
	//y_test_mean
	for(i=0; i<test_size; i++)
	{
		test_y_mean+=test_y[i]/test_size;
	}
	//mean absolute error
	for(i=0; i<test_size; i++)
	{
		r0+= pow((preds[i] - test_y[i]), 2);
		r1+= pow((test_y[i] - test_y_mean), 2);
	}
	acc = 1-(r0/r1);
	printf("Accuracy: %f", acc);
}

float MSE(float x, float y_pred, float y_actual, int size)
{
	//derivative of MSE. By chain rule for Gradient Descent:
	float mse_der = (2*x*(y_pred - y_actual))/size;
	return mse_der;
}


