#################################
# MAKEFILE Prueba 1 Meteologica #
#################################


help: # Imprime mensaje con las distintas opciones del Makefile
	@grep -E '^[a-zA-Z0-9 -]+:.*#'  Makefile | sort | while read -r l; do printf "\033[1;32m$$(echo $$l | cut -f 1 -d':')\033[00m:$$(echo $$l | cut -f 2- -d'#')\n"; done

build: # Construir el proyecto
	@echo -e "Construyendo el proyecto ..."
	g++ ./src/main.cpp ./src/tiempo.cpp  -o ./bin/prueba -O3 -I ./include

run: # Ejecuta el programa principal. Un ejemplo sería: make run fecha=2023/09/29 ciudad=Madrid temperatura=C
	./bin/prueba ${fecha} ${ciudad} ${temperatura}

runScript: # Ejecuta el script de pruebas.
	./script_prueba.sh

clean: # Limpia el proyecto
	@echo -e "Limpiando los binarios ..."
	rm ./bin/*
	


