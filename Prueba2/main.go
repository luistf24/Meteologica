package main

import (
	"encoding/csv"
	"net/http"
	"fmt"
	"os"
	"strconv"
	"strings"
	"github.com/gin-gonic/gin"
)


var datos = obtenerDatos()

// Estructura usada para codificar la información en formato JSON
type tiempo struct {
	Nombre			string `json:"nombre"`
	Fecha			string `json:"fecha"`
	Temp_max		float32 `json:"temperatura máxima"`
	Temp_min		float32 `json:"temperatura mínima"`
	Precipitacion	float32 `json:"precipitacion"`
	Nubosidad		int `json:"nubosidad"`
}


/*	
	Función usada para obtener toda la información del archivo .csv.
 	Como en este caso, al contrario que la prueba 1, he supuesto que el programa principal
	se va a ejecutar indefinidamente respondiendo a las distintas consultas. Por ello he decido
	que la información del archivo se almacene en memoria del dispositivo ya que así solo hacemos 
	una lectura del archivo aumentando la velocidad del programa principal.
*/ 
func obtenerDatos()[][]string {
	file, err := os.Open("./data/Meteologica_vacante_Backend_developer_Prueba_Datos_20230927.csv")
	
	if err != nil {
		fmt.Println("Error abriendo el archivo")
	}

	defer file.Close()

	reader := csv.NewReader(file)
	reader.Comma = ';'
	reader.FieldsPerRecord = -1

	records, err := reader.ReadAll()

	if err != nil {
		fmt.Println(err)
	}

	return records
}

/*
	Función utilizada para obtener la solicitud pedida por una consulta a la API. Para ello 
	se leen los datos previamente cargados en memoria, se realiza la misma operación que en la 
	prueba 1 para obtener la información requerida y se devuelve una lista de "tiempos".
*/
func obtenerConsulta(lista [][]string, peticion []string)[]tiempo {
	ciudad_encontrada	:= false
	ciudad_recorrida	:= false
	fecha_correcta		:= false

	var salida []tiempo

	for i:=0; i<len(lista) && !ciudad_recorrida; i++ {
		if peticion[1] == lista[i][1] {
			ciudad_encontrada = true
		} else if ciudad_encontrada {
			ciudad_recorrida = true
		}

		if peticion[1] == lista[i][1] && !fecha_correcta && peticion[0] == lista[i][0] {
			fecha_correcta = true
		}

		if peticion[1] == lista[i][1] && fecha_correcta {
			temp_max, _			:= strconv.ParseFloat(strings.Replace(lista[i][2], ",", ".", 1), 64)
			temp_min, _			:= strconv.ParseFloat(strings.Replace(lista[i][3], ",", ".", 1), 64)
			precipitacion, _	:= strconv.ParseFloat(strings.Replace(lista[i][4], ",", ".", 1), 64)
			nubosidad, _		:= strconv.Atoi(lista[i][5])

			if peticion[2] == "F" {
				temp_max = temp_max*1.8+32
				temp_min = temp_min*1.8+32
			}

			temp := tiempo { 	Nombre: peticion[1], 
								Fecha: lista[i][0], 
								Temp_max: float32(temp_max), 
								Temp_min: float32(temp_min), 
								Precipitacion: float32(precipitacion), 
								Nubosidad: nubosidad }
			
			salida = append(salida, temp)
		}

	}

	return salida
}

// Función usada para obtener toda la información del archivo .csv mediante la API
func getTiempo(c *gin.Context) {
	c.IndentedJSON(http.StatusOK, datos)
}

/*
	Función usada para responder las llamadas a la API pidiendo la información del tiempo 
	y precipitaciones de un lugar determinado y una fecha determinada. La temperatura se 
	devuelve en grados Celsius o Fahrenheit. Se ha seguido el mismo procedimiento que en 
	la prueba 1, es decir, se devuelve la información del día pedido y la de los próximos 
	días.
*/
func getTiempoProximo(c *gin.Context) {
	año		:= c.Param("año")
	mes		:= c.Param("mes")
	dia		:= c.Param("dia")
	fecha	:= año + "/" + mes + "/" + dia

	ciudad	:= c.Param("ciudad")
	temp	:= c.Param("temp")

	peticion := obtenerConsulta(datos, []string{fecha, ciudad, temp})

	c.IndentedJSON(http.StatusOK, peticion)
}


func main() {

	router :=gin.Default()
	router.GET("/", getTiempo)
	router.GET("/:año/:mes/:dia/:ciudad/:temp", getTiempoProximo)

	router.Run("localhost:3333")

}
