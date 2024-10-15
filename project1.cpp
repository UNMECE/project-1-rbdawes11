#include <iostream>
#include <cmath>

struct _capacitor
{
	double *time;
	double *voltage;
	double *current;
	double C;           
};
typedef struct _capacitor Capacitor;

#define TIMESTEPS 50000
#define R 1000
#define dt 1e-10
//change in time is 1e-10 s
//final time to be measured is 5e-6 s

void getCurrent(Capacitor *c)
{
	for(int i = 1; i < TIMESTEPS; i++)
	{
		c->current[i] = c->current[i-1] - (((double)dt * c->current[i-1]) / ((double)R * c->C));
	}
}

void getVoltage(Capacitor *c)
{
	for(int i = 1; i < TIMESTEPS; i++)
	{
		c->voltage[i] = c->voltage[i-1] + ((c->current[i-1] * (double)dt) / c->C);
	}
}

void outputValues(Capacitor *c)
{
	std::cout<< "Printing the voltages and currents:\n";
	for(int i = 0; i < TIMESTEPS; i+=200)
	{
		std::cout << "Time step " << (i/200)+1 << ":  Voltage: " << c->voltage[i] << "  Current: " << c->current[i] << std::endl;
	}

}

int main()
{
	Capacitor *capacitor = (Capacitor *) malloc(sizeof(Capacitor));
	capacitor->time = (double *) malloc(sizeof(double) * TIMESTEPS);
	capacitor->voltage = (double *) malloc(sizeof(double) * TIMESTEPS);
	capacitor->current = (double *) malloc(sizeof(double) * TIMESTEPS);
	capacitor->C = 1e-10;
	capacitor->voltage[0] = 0;
	capacitor->current[0] = 10/(double)R;
	getCurrent(capacitor);
	getVoltage(capacitor);
	outputValues(capacitor);



	return 0;
}
