#include "rapidjson/document.h"
#include "rapidjson/writer.h"
#include "rapidjson/stringbuffer.h"


using namespace std;

/*
	Clase en la cual se almacenará la información del tiempo pedida en la prueba
	para poder formatearla en JSON de manera cómoda.
*/
class Tiempo
{
	public:
		string nombre;
		string fecha;
		float temp_max;
		float temp_min;
		float precipitacion;
		int nubosidad;
	
		Tiempo();
		Tiempo(string, string, float, float, float, int);
		~Tiempo();

		template<typename Writer>
		void Serialize(Writer & writer) const // Función para serializar la información de la clase.
		{
			writer.SetMaxDecimalPlaces(3);
			writer.StartObject();
			writer.String("nombre");
			writer.String(nombre.c_str());
			writer.String("fecha");
			writer.String(fecha.c_str());
			writer.String("temperatura max");
			writer.Double(temp_max);
			writer.String("temperatura min");
			writer.Double(temp_min);
			writer.String("precipitacion");
			writer.Double(precipitacion);
			writer.String("nubosidad");
			writer.Uint(nubosidad);
			writer.EndObject();
		}

		string serialize() // Función para serializar la información de la clase en JSON, 
		{				   // usa la función Serialize para ello.
			rapidjson::StringBuffer s;
			rapidjson::Writer<rapidjson::StringBuffer> writer(s);
			Serialize(writer);
			return s.GetString();
		}

};
