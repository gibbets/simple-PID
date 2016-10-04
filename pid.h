
/*
 * Guard
 */
#ifndef PID_H_DEF
#define PID_H_DEF

typedef struct
{
	float K; //K-Anteil
	float I; //I-Anteil
	float D; //D-Anteil

	float errorSum; //Integrierter Fehler
	float errorOld; //Abgeleiteter Fehler

	uint8_t activateLimit; //Obere und untere Grenzwerte aktivieren
	int32_t upperLimit; //Oberer Grenzwert
	int32_t lowerLimit; //Unterer Grenzert
	int32_t vorsteuerung;

	float samplingTime; //Abtastzeit in ms

	//Input, Outputscale?
}PID_PIDConfig;

/*
 * Initialisiert eine PID_PIDConfig-Struktur um sie anschlieﬂend zu verwenden.
 */
void PID_Init(PID_PIDConfig *config);

/*
 * Berechnet aus einem Ist- und einem Sollwert den Stellwert anhand eines in
 * config definierten PID-Reglers.
 */
float PID_Control(float ist, float soll, PID_PIDConfig *config);

#endif
