#include "stm32f4xx.h"

#include "pid.h"

void PID_Init(PID_PIDConfig *config)
{
	config->errorSum = 0.0F;
	config->errorOld = 0.0F;

	return;
}

float PID_Control(float ist, float soll, PID_PIDConfig *config)
{
	float error = soll - ist;

	//Fehler aufsummieren
	config->errorSum += error;
	//if(config->errorSum >= 100)
	//	config->errorSum = 100;
	//if(config->errorSum <= -100)
	//		config->errorSum = -100;

	//Regleranteile berechnen
	float K = config->K*error;
	float I = config->I*config->errorSum*config->samplingTime;
	float D = config->D*(error - config->errorOld)/config->samplingTime;

	//Stellwert berechnen
	float stellwert = K + I + D;

	//Alten Fehler für den D-Anteil speichern
	config->errorOld = error;

	//Limitierung des Stellwertes
	if(config->activateLimit > 0)
	{
		if(config->upperLimit < stellwert)
		{
			stellwert = config->upperLimit;
		}
		if(config->lowerLimit > stellwert)
		{
			stellwert = config->lowerLimit;
		}
	}

	return stellwert;
}
