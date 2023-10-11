#include "../include/tiempo.h"

using namespace std;

Tiempo::Tiempo()
{

}

Tiempo::~Tiempo()
{

}

Tiempo::Tiempo(string n, string f, float tM, float tm, float p, int nb)
{
	nombre			= n;
	fecha			= f;
	temp_max		= tM;
	temp_min		= tm;
	precipitacion	= p;
	nubosidad		= nb;
}

