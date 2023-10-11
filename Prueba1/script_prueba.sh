#!/bin/bash

echo -e " Ejecutando prueba 1...\n" 
make run fecha=2023/09/29 ciudad=Madrid temperatura=c

echo -e "\n Ejecutando prueba 2...\n" 
make run fecha=2023/10/01 ciudad=Sevilla temperatura=c

echo -e "\n Ejecutando prueba 3...\n" 
make run fecha=2023/09/29 ciudad=Gijón temperatura=c


