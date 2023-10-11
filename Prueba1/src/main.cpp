#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <algorithm>

#include "rapidjson/document.h"
#include "rapidjson/writer.h"
#include "rapidjson/stringbuffer.h"

#include "../include/tiempo.h"


using namespace std;

char delimitador = ';';

/*
	Función utilizada para obtener una lista de "Tiempos" a partir de una fecha y una ciudad obteniendo
	así los datos de temperatura y precipitación de un día y de los siguientes.
	Como he supuesto que el programa una vez que se ejecuta una vez por cada petición, he considerado 
	que no es necesario almacenar todo la información de archivo .csv en memoria ya que como está ordenado
	con solo recorrer el archivo entero, en el peor de los casos, bastaría para obtener toda la información 
	necesaria.
*/
vector<Tiempo> obtenerDatos(string Ciudad, string Fecha, string Temperatura)
{
	ifstream csv("./data/Meteologica_vacante_Backend_developer_Prueba_Datos_20230927.csv");

	vector<Tiempo> salida;


	string linea, temp;
	stringstream stream;
	string fecha, ciudad, temporal;
	float temp_max, temp_min, precipitacion;
	int nubosidad;

	getline(csv, linea);

	bool ciudad_encontrada	= false;
	bool ciudad_recorrida	= false;
	bool fecha_correcta		= false;

	while(getline(csv, linea) && !ciudad_recorrida) // Recorremos el archivo secuencialmente.
	{
		stream << linea;

		getline(stream, fecha, delimitador);
		getline(stream, ciudad, delimitador);

		getline(stream, temporal, delimitador);
		replace(temporal.begin(), temporal.end(), ',', '.'); // Como en el .csv de pruebas hay decimales con , 
															 // los cambiamos por .
		temp_max = stof(temporal);

		getline(stream, temporal, delimitador);
		replace(temporal.begin(), temporal.end(), ',', '.');
		temp_min = stof(temporal);

		getline(stream, temporal, delimitador);
		replace(temporal.begin(), temporal.end(), ',', '.');
		precipitacion = stof(temporal);

		getline(stream, temporal, delimitador);
		nubosidad = stoi(temporal);

		if(ciudad == Ciudad)
			ciudad_encontrada = true;
		else if(ciudad_encontrada)
			ciudad_recorrida = true;

		if(ciudad == Ciudad && !fecha_correcta && fecha == Fecha)
			fecha_correcta = true;

		if(ciudad == Ciudad && fecha_correcta) // Si es la ciudad que buscamos y la fecha es correcta(igual o mayor)
		{									   // almacenamos el tiempo.
			if(Temperatura == "F")
			{
				temp_max = temp_max*1.8+32;
				temp_min = temp_min*1.8+32;
			}
		
			Tiempo tiempo(ciudad, fecha, temp_max, temp_min, precipitacion, nubosidad);	
			salida.push_back(tiempo);

		}

		stream.clear();
	}

	return salida; // Devolvemos una lista con todos los tiempos del día y los días próximos.
}


int main(int argc, char *argv[])
{
	if(argc != 4)
	{
		cout << "Tienes que introducir 3 argumentos. El primero será la fecha en formato yyyy/mm/dd, el segundo es la ciudad y el tercero la temperatura en grados Celsius o Fahrenheit (C|F) " << endl;
		return -1;
	}

	vector<Tiempo> solucion = obtenerDatos(argv[2], argv[1], argv[3]);
	rapidjson::StringBuffer buffer;
	rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);

	for(int i=0; i<solucion.size(); i++)
		cout << solucion[i].serialize() << endl;

}
