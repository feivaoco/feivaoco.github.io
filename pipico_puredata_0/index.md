# Pure Data Pi Pico
## Bienvenido a mi primer proyecto involucrando a la Pi Pico y el programa Pure Data.

- [Pure Data Pi Pico](#pure-data-pi-pico)
  - [Bienvenido a mi primer proyecto involucrando a la Pi Pico y el programa Pure Data.](#bienvenido-a-mi-primer-proyecto-involucrando-a-la-pi-pico-y-el-programa-pure-data)
  - [Resumen](#resumen)
  - [Introducción](#introducción)
  - [Desarrollo](#desarrollo)
    - [Diagrama del circuito](#diagrama-del-circuito)
    - [Parche del Pure Data](#parche-del-pure-data)
    - [Arduino IDE y la Pi Pico](#arduino-ide-y-la-pi-pico)
    - [Circuito con la Pi Pico](#circuito-con-la-pi-pico)
  - [Resultados](#resultados)
  - [Conclusiones](#conclusiones)
  - [Descargar proyecto](#descargar-proyecto)
  - [Enlaces](#enlaces)

## Resumen
Este proyecto es un piano sintetizador con el que los sonidos se generan a través del programa Pure Data y este es controlado con la Pi Pico.

## Introducción
Pure Data es un programa con el Procesamiento de Señales Digitales, DSP, por lo que permite realizar pianos synths, como el de éste proyecto. Y la Raspberry Pi Pico es un minicontrolador que cuenta con 26 pins gpios y SÓLO 3 pins análogos, por lo que éste minicontrolador como que no me sirve para lo que quiero hacer; ya pedí una Mega 2560, esa madre sí tiene muchisímos pins análogos.

## Desarrollo

### Diagrama del circuito
La verdad esto fue lo útlimo que se realizó pero para que se vea un algún resultado de una vez mejor la pongo aquí al principio, jeje.
![diagrama del circuito](/pipico_puredata_0/proyecto/diagrama_pipicopiano.png) El diagrama fue hecho en [draw.io](https://app.diagrams.net/ "Página de draw.io"), la verdad es que es un programa muy bueno e intuitivo para realizar esquemas y diagramas como éste, la primera vez que lo usé fue para hacer un diagrama de flujo.

### Parche del Pure Data
Bueno, nunca hice ni un boceto ni nada parecido, ni una planeación escrita, el programa fue realizándoce pero con varios errores. El bojetivo final ya se tenía claro antes de empezar el codígo de Pure Data o de la programación para la Pi Pico, así que el enfoque no se perdía; pero había errores que de los que no se tenía noción como que un método para enviar datos con el Pure Data no me servía y lo hice de una forma que tendré que cambiar a futuro porque es sólo manda un dato a la seríal, y para algún futuro proyecto necesitaría mandar más de un solo dato a la Serial para comunicarse con el aparato conectado a la Serial. Las librerías utilizadas en este parche son [comport], que es el que permite comunicarse con la Serial, y la librería [cyclone], que emula los objetos que se encuentran en el programa para DSP que se llama Max MSP, este programa es de costo y la verdad no sé cómo funcione, cuenta con una comunidad más grande, lo más seguro que por la interfaz de usuario que cuenta por defecto y por su mayor cantidad de escritos que proporcionan una mejor comprensión del programa, bueno, siguiendo con mi proyecto, jeje. El parche es muy dependiente de cómo programes a la Pi Pico, por eso incluyo sketch del Arduino IDE en el 7z que se encuentra en la descarga; mi parche no es muy descriptivo por lo que sería necesario saber cómo funciona Pure Data por si ocurre un error al intentar encender el modo DSP, ya que se debe prender el programa del parche ya teniendo conectada la Pi Pico a la computadora. También hice una interfaz de usuario que se encuentra a la mera izquierda del parche, en sí, no funciona para que toques el piano ahí, las teclas de piano solo sirven para recibir datos y no para mandar datos; los únicos que sirven para enviar datos y que se deben utilizar ya con el mouse, son los Multipliers y el Volumen, de ahí en fuera todo es controlado con la Pi Pico (por eso quiero que ya llegue otro minicontrolador con más pins análogos 😠). Y creo que sería todo de parte del parche.

### Arduino IDE y la Pi Pico
La Pi Pico aunque no pertenezca a la familia de Arduino puede ser programada en su IDE, instalando los datos necesarios para eso (dejaré todos los videos y páginas que me ayudaron a realizar el proyecto así que no pondré tutorial aquí, jeje), al igual que otros minicontroladores como la LGT8F328P. La IDE de Arduino proporciona un programa que se comunica con la serial en la misma IDE, por lo que revisar si cada botón y potenciometro funciona es muy sencillo y no hay necesidad de utilizar otro programa para verificar. Al igual, se puede utilizar otro minicontrolador u aparato que se comunique mediante la serial, no hay que limitarse a la Pi Pico, así como yo no me limite a usar un Arduino (también porque no tengo uno hasta el momento, jeje); sólo es cuestión de comprender cómo funciona el aparato que vas a utilizar para cambiar el código del sketch y del parche de Pure Data.  El dato que se lee en la Serial es para encender los cuatro Leds que indican la escala del tono, también se puede ver en la interfaz del parche pero es que quería aprender a mandar información a la Serial con el parche, jeje. El sketch cuenta con unas funciones para no hacer tan largo el código. Y no he visto que se iniciliacen los pins análogos en algunos sketchs que vi al investigar, por lo que eso es una mala costumbre que llegue a costar caro, por lo que se hacen las inicializaciones correctas en la función setup.

### Circuito con la Pi Pico
Las primeras conexiones fueron los potenciometros, ya que lo que quería hacer desde el principio era usar los potenciometros para modificar valores de un sintetizador, ya lo segundo fue la conexión de los botones. Y la idea de cambiar el tono con unos botones nació de no tener más pins análogos, por lo que los botones hacen varias de 20hz a 7902hz, que son los hertz de las notas de C0 a B8, y como siempre se cuenta con algo para indicar la escala entonces hice que el parche mande información a la Serial para que la Pi Pico encienda los leds que están arriba de los botónes. Los pins de ADC_VREF y AGND la neta no entendí si en realidad se deben utilizar o no, pienso que la documentación de la Pi Pico dice algo como que se deben utilizar para tener una mayor precisión de los datos pero no comprendí muy bien a lo que se refieren con: "If the ADC is not used or ADC performance is not critical, this pin can be connected to digital
ground."; OOoo, creo que ya entendí hasta ahorita, jeje.

## Resultados
Como ya vieron el diagrama del circuito no necesito ponerlo dos veces aquí, por lo que solamente pondré mi video utilizando el primer synth y ya construído como piano así bien pasado de lanza. Y tambíen pondré una captura de la espectacular interfaz del parche.
![interfaz del parche](/pipico_puredata_0/cap_interfaz.png)
[Aquí el video del primer intento con la Pi Pico y Pure Data](https://www.youtube.com/watch?v=5JeAMMj4OdM&t) <br>
[Y aquí el video utilizando ya el producto de este proyecto](https://www.youtube.com/watch?v=BOR75bgEKAA)


## Conclusiones
Bueno, eso sería todo. Me gustó mucho realizar el proyecto ya quería usar un sintetizador en hardware, y para mí esto ya cuenta como ello. También gracias a este proyecto comprendí más a la Pi Pico y darme cuenta que no me sirve de mucho para los sintetizadores casi casi, todo se podía arreglar comprando unos modulos que añaden más pins análogos pero prefiero mejor otro minicontrolador con más pins análogos porque sale más barato a la larga, entonces me esperaré a tenerlo para hacer un proyecto incluyendo un minicontrolador que controle un parche de Pure Data, por el momento encontré un curso completo del Pure Data que me ayudará mucho y también el libro hecho por el mismo autor de Pure Data servirá mucho.

## Descargar proyecto
Archivo:  [pipico_puredata_0.7z](pipico_puredata_0.7z) <br> Contiene dos imagenes del diagrama del circuito, una en png y otra svg para mayor calidad, también contiene el sketch del IDE de Arduino y el parche de Pure Data, el cómo utilizar este proyecto la verda no lo expliqué porque no lo tenía pensado, de todas formas dejo un contacto para que me manden un mensaje por Discord: _invu42069#6865.
 
## Enlaces
Sin descripción para que vean cada uno de ellos y vean de qué tratan.
- [https://www.youtube.com/watch?v=WPj-clNbvfk](https://www.youtube.com/watch?v=WPj-clNbvfk)
- [https://www.youtube.com/watch?v=eVW0FD9g_Sk](https://www.youtube.com/watch?v=eVW0FD9g_Sk)
- [https://www.youtube.com/watch?v=1cCTdezDBxM&t](https://www.youtube.com/watch?v=1cCTdezDBxM&t)
- [https://www.youtube.com/watch?v=B61ywfEbK5M&t](https://www.youtube.com/watch?v=B61ywfEbK5M&t)