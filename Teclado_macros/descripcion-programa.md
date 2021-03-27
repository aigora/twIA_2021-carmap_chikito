## Programa del teclado
    _aún estoy decidiendo cómo distribuir los botones y el joystick en el teclado_
    _todo lo que tengo ahora mismo son esquemas_
### Objetivo:
- desarrollar un programa que asocie el teclado auxiliar de ocho teclas
con el programa de Carmap; cada tecla ejerce una función dentro del programa.
El programa permite ejecutar lo que serían comandos complejos del teclado con
pulsar un botón del teclado auxiliar.
##Menús manejables con el teclado:
- Opción 1: Control remoto de Carmap
    El teclado tiene un joystick para mover el Carmap y un "panel de control" con teclas
    que realizan funciones relativas al movimiento y la gráfica que se va generando.
    - Una tecla para detenerse y pausar la marcha; puede reanudarse pulsando la misma
    - Una tecla que al pulsarla genera un punto de control
        La gráfica de trayectoria del robot se generará con splines o algún método similar, de modo que las curvas de su trayectoria quedarán definidas por la posición de un número reducido de puntos.
        El usuario podrá ir generando manualmente la curva punto por punto, o configurar los ajustes de la misma en caso de que se vayan a generar los puntos automáticamente
    - Una tecla para guardar o importar la gráfica generada
       El comando equivale a detener la grabación de la trayectoria y guardar la curva obtenida con un nombre genérico, o pedirle al usuario que la nombre en el momento de guardar. Todas las gráficas podrán ser visualizadas y manejadas con el mismo programa.
    - Una tecla de "grabar" para iniciar lo que sería la grabación de la trayectoria
    - Una tecla para terminar la grabación de la trayectoria
    - Una tecla para regresar sobre sus pasos; en este caso el robot seguiría la trayectoria marcada por los puntos de control de las curvas, pero los recorre en el orden contrario.
- La tecla SWITCH es la misma; sirve para cambiar el perfil del teclado. Sólo se podrá pulsar mientras no esté siendo grabada una gráfica.
### Especificaciones del programa
- 
### Requisitos del programa
#### Obligatorio
- Código bien estructurado
- Tener un diseño mínimamente cómodo para poder ser utilizado sin dolor en la mano.
- Mínima consistencia en el modelo como para que no se rompa demasiado fácilmente y no se desprendan partes.
- Que las teclas estén colocadas de manera que no haya confusión o
riesgo de pulsar alguna por accidente.
#### Opcional
- Buena presentación.
- Incorporar el logo al diseño del teclado para mayor cohesión.

---

__27 de Marzo de 2021__
Trabajando en esta solución: _Amélie Nader Prieto_