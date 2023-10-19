# CI4825 Redes de computadoras I

# José González 15-10627
# Amaranta Villegas 16-11247
# Ana Santos. 17-10602
## Instrucciones de Ejecucion

1. Abra la terminal o linea de comandos de linux o alguna de sus distribuciones
2. Navegue al directorio donde se encuentra el codigo fuente.

3. Compile el servidor y el cliente mediante los siguientes comandos:

``` g++ -o chatServer chatServer.cpp waterBottle.cpp  ```

``` g++ -o chatCliente chatCliente.cpp ```



4. Ejecute el server y el cliente mediante los siguientes comandos:

``` ./chatServer ```

``` ./chatCliente [hostname][botellaConMayorCapacidad][botellaConMenorCapacidad] ```

reemplazando [hostname] [botellaConMayorCapacidad] [botellaConMenorCapacidad] con los valores del hostname, el valor de la capacidad botella con mayor capacidad, y el valor de la capacidad de la botella con menor capacidad

5. Requisitos del Sistema


- Se requiere un compilador C++ (g++ recomendado) para compilar el código.
- Sistema operativo: Linux (puede funcionar en otros sistemas pero en este se garantiza que estos son los unicos comandos para su correcto funcionamiento).
