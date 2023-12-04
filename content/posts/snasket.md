+++
title =  "raylib + pure data + mysql"
tags = ["vydia","programacion", "c"]
date = "2023-12-03"
+++

## Introducción
Hace un mes publiqué en [github](https://github.com/feivaoco/snasket/releases/tag/v2.0) e [itchio](https://feivvydiadev.itch.io/snasket) un jueguito clon del Snake, el chiste es que se puede subir tu puntuación a tabla de puntuaciones que se comparte con todos, no parece mucho pero desde la perspectiva de que lo hice todo en C desde cero y sin tutoriales, para mí es bastante, jeje ( ´ ω ` ).
El nombre de Snasket nace de que estaba escuchando [Caskets](https://www.youtube.com/watch?v=_BJzCJy8-As) mientras estaba probando por primera vez la librería de libpd, y el proyecto de prueba se llamaba [Casket](https://github.com/feivaoco/casket_sonido), entonces combiné Casket y Snake para que naciera Snasket, muy ingenioso la verdad.

## Desarollo

### Librerías

Raylib, todos lo aman, todos lo adoran, yo no, y aun así no me rendí cuando batallé para juntarlo junto con la librería de libmysql -- en unos parrafos más se explica porqué -- (`ー´). Esta librería permite graficar de manera muy sencilla y sin tanto rollo, el creador lo sigue promocionando como una librería para aprender pero realmente si se puede llegar a hacer un producto que se pueda publicar en tiendas de jueguitos. 

LibPD, en el título dice Pure Data pero en realidad lo que se usa es libpd, ya que con esta librería se pueden usar parches de pure data sin necesidad de una interfaz grafica, de esta forma se puede hacer sintesis en tiempo real y tener la versatilidad de diseñar tu propio sonido, una ventaja más de usar esta librería es que no ocupo estar cambiando algún archivo de sonido cada vez que quisiera cambiar algo del sonido, ya que solamente podría recargar el archivo con una simple función y sería suficiente para aplicar los cambios -- algo que no hice y pues lo que estuve haciendo fue recargar por completo el programa cada que cambiaba el sonido, jeje, --, igualmente para probar el sonido también se puede hacer mediante Pure Data ya que ahí es donde se diseña.

LibMySQL, tardé y tardé muchísimo para siquiera empezar a usarlo, pues los argumentos que se debían de poner a la hora de compilar no salían en la documentación oficial ni en el tutorial más famoso de usar libmysql. Donde encontré la solución a mi problema fue en un foro que su útlima actualización fue hace 10 o 15 años, así de pasado de lanza está la gente de que no usa libmysql en windows en este futuro tan arraigado en herramientas que proporcionan todo a la mano.

### Usando las librerías

La estructura con la que hice el proyecto es la siguiente:
```c 
proyecto
|-- bin
|-- include
|-- lib
|-- src
|-- assets
|-- Makefile
```
De ésta manera puedo comprender más qué es lo que hay en mi proyecto, igualmente ya en código hago un if con macros de la siguiente manera:
```c
#ifdef RELEASE_
libpd_openfile("sonidos.pd", "assets");
#endif //RELEASE_

#ifdef DEVELOPMENT_
libpd_openfile("sonidos.pd", "../pd");
#endif //DEVELOPMENT_
```
Si defino un macro llamado RELEASE_ entonces va suceder lo que hay en el bloque de RELEASE_, lo mismo en el bloque de DEVELOPMENT_, ¿y qué sucede si defino RELEASE_ y DEVELOPMENT_? Un error, la función va decir que no encontró el archivo en alguno de los dos bloques. ¿Hay alguna manera de evitar esto? Solamente no se definen los dos si se va usar alguno, obviamente esto no es para nada seguro y muy poco profesional, pero es práctico para mi objetivo con el proyecto. 

Raylib cuenta con un gran conflicto con windows.h, esto sucede gracias a libmysql, especificamente con mysql.h, ya que este llama al archivo con el conflicto. No había manera simple de resolverlo... HASTA QUE TUVE QUE LEER CÓDIGO FUENTE -- **SE ASUSTA** --. Era un simple #define que coloqué en el mysql.h.
```c
#define MYSQL_ABI_CHECK
```
Ya que en el siguiente código se encuentra el conflicto:
```c
#ifndef my_socket_defined
#define my_socket_defined
#if defined(_WIN32) && !defined(MYSQL_ABI_CHECK)
#include <windows.h>
#ifdef WIN32_LEAN_AND_MEAN
#include <winsock2.h>
#endif
#define my_socket SOCKET
#else
typedef int my_socket;
#endif /* _WIN32 && ! MYSQL_ABI_CHECK */
#endif /* my_socket_defined */
```
Dice que si se define _WIN32 y no se define MYSQL_ABI_CHECK entonces se va a llamar windows.h, por lo que con el define anterior de MYSQL_ABI_CHECK resolví el conflicto entre Raylib y libmysql ┐(︶▽︶)┌. Por eso es bueno leer código fuente de lo qué se usa jeje. 

La librería de libpd no viene con su manera de llevar sonido a los dispositivos de salida ni de entrada, y te avisa, la manera en que libpd puede obtener y llevar sonidos es con [portaudio](https://github.com/PortAudio/portaudio), este lo tuve que compilar, al igual que libpd. Las únicas librerías que no compilé fue Raylib, MySQL y msf_gif, este último nomás es un header pero lo cuento como librería, portaudio y libpd los tuve que compilar y lo hice mediante gcc con el devkit de [w64devkit](https://github.com/skeeto/w64devkit), de hecho todo el proyecto fue compilado utilizando el gcc perteneciente a ese devkit. 

Los argumentos utilizados en la compilación fueron los siguientes:
```makefile
CFLAGS = -O1	\
		-Iinclude -Llib \
		-lmysql -lws2_32 -lwsock32 -lsecur32 \
		-lraylib -lopengl32 -lgdi32 -lwinmm \
		-llibpd -lportaudio \
		-mwindows 
```
No me gusta para nada cmake por eso tuve que saber qué argumentos colocar en la compilación, odio mucho cmake ٩(ఠ益ఠ)۶. 

## Reflexiones
La manera en que estructure el programa fue en máquina de estados, ya que de esta forma se me hacía más sencillo saber en qué parte del código me encontraba a la hora de ejecutar el programa. Esto no es recomendable ya en algún proyecto grande por su poca eficiencia a la hora de que vaya fluido el programa pero por el momento todo bien porque no es un proyecto pesadote.

También algo que me faltó hacer bien fue que quería optimizar la colisión de la serpiente, pues hago un chequeo de colisión por cada nodo que se tiene la serpiente, entonces por ejemplo, si la serpiente llega a tener 5000 nodos se harían 5000 chequeos, es sí es algo malo porque puede llegar a pasar, pero lo deje así por falta de interes más que nada. Igualmente si planeé la optimización, la manera en que se haría el chequeo de colisión es que se haría un rectangulo por cada cambio de dirección de la cola de la serpiente, por ejemplo, si la serpiente de momento está recta entonces se haría un sólo rectangulo y por lo tanto un chequeo, pero si de repente la serpiente cambia de dirección entonces se generaría otro rectangulo para hacer el chequeo.

Demostración grafica (￣▽￣)ノ:
![optimizacion de colisiones en snake](/img/optimi.png "grafica")

Me gusto mucho poder hacer la demostración de concepto de usar raylib y mysql, al igual que porfin usar pure data en un jueguito, no creo usarlos de nuevo pero está bien, comprendí que debo saber cómo se usan librerías en proyectos y aprendí a buscar soluciones a problemas que no había topado haciendo otros proyectos. 

[Otra vez el link del código fuente del jueguito ( ~* - *)~](https://github.com/feivaoco/snasket) 