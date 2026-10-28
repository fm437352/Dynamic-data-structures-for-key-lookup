# Dynamic-Data-Structures-for-Key-Lookup
Integrantes: Francisca Muñoz(aka fm437352), Dalma Redoles(aka vennusss), Néstor Sepúlveda(aka nachoswi).

Resumen del trabajo 


En este trabajo hacemos un arreglo dinamico y una lista circular doblemente enlazada, donde les agregamos dos diccionarios
con el diccionaro uno hacemos la busqueda de las dos estructuras y con el segundo diccionario hacemos la insercion y la eliminacion
de forma intercalada para los dos métodos se miden y comparan los tiempos de ejecución en la insercion, busqueda y eliminacion, asi como 
el consumo de memoria dinamica en cada estructura.


Para poder acceder al archivo principal:
```bash
# bash

# Compila las dos soluciones con distintos valores de K y REP (ejemplo K=64 y REP=200):
make run_all K=64 REP=200 

# Ejecuta automáticamente los experimentos con K=32 y REP=100
make run_all 

# Para ejecutar las soluciones independientemente
# Para arreglo dinámico:
make run1

# Para lista circular doblemente enlazada con distintos valores de K y REP: (ejemplo K=64 y REP=200):
make run2 K=64 REP=200

# Para lista circular doblemente enlazada con valores por defecto:
make run2


funcionalidad del codigo 

solución 1: la solución se basa en crear un arreglo dinámico usando métodos vistos en clase y la STL, usar el diccionario que nos dieron para el mismo, con las funciones de eliminación e inserción seleccionar cierto numero de palabras que añadimos a nuestro arreglo dinámico con el fin de luego buscar dentro del arreglo si se encuentran unas palabras seleccionadas dentro y medir el tiempo que se tarda en hacer todo este proceso desde la creación del arreglo hasta si se encuentran las palabras en el arreglo, haciendo la búsqueda con el comando de la STL binary search.

solución 2: la solución se basa en crear una lista circular doblemente enlazada usando la STL y métodos vistos en clase, usar el diccionario que nos dieron para el mismo, con las funciones de eliminación e inserción seleccionar cierto numero de palabras que añadimos a nuestra lista circular doblemente enlazada con el fin de luego buscar dentro de la lista si se encuentran unas palabras seleccionadas entre las de la lista y medir el tiempo que se tarda en todo este proceso desde la creación de la lista hasta si se encuentran las palabras en el dentro de ella, con la diferencia de que aquí la lista se recorre usando un puntero.


justificaciones de la stl

Se utilizaron  las operaciones de STL debido mayoritariamente a la función de cada una, debido a que realizaban un comando específico que nos ahorraba el tiempo de hacer el código personalmente cada vez que se necesitará, reduciendo el tiempo de demora, mejorando el rendimiento del código y no dejando cabida a errores dando más tiempo a pulir detalles y en general a hacer el código principal y la solución envés de demorarse en instrucciones que son para dar paso a las soluciones realizadas, el uso de la STL es beneficioso en general para la optimalidad de los códigos en los que se permite usar esta.

