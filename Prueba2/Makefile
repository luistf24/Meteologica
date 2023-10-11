#################################
# MAKEFILE Prueba 2 Meteologica #
#################################


help: # Imprime mensaje con las distintas opciones del Makefile
	@grep -E '^[a-zA-Z0-9 -]+:.*#'  Makefile | sort | while read -r l; do printf "\033[1;32m$$(echo $$l | cut -f 1 -d':')\033[00m:$$(echo $$l | cut -f 2- -d'#')\n"; done

build: # Construir el proyecto
	@echo -e "Construyendo el proyecto ..."
	go build .
	mv prueba-api ./bin/

run: # Ejecuta el programa principal
	./bin/prueba-api

runScript: # Ejecuta el script con ejemplos de distintas consultas
	./script_prueba.sh

clean: # Limpia el proyecto
	@echo -e "Limpiando los binarios ..."
	rm ./bin/*
	


