# Sensor-CO2-IoT
## Proyecto IoT para la medición de CO2 en el ambiente 
Este proyecto se presentó en mayo del 2022 para acreditar la materia de Taller de Investigación.

El proyecto consiste en un dispositivo que nos ayuda a monitorear qué tan seguro es estar en un aula de clases mediante mediante la medición de la calidad del aire para que, en caso de no ser los parámetros deseables, emitir una alerta que avise a las personas que pueden estar vulnerables, también se incluye una página web que muestra los valores de CO2 captados por el sensor.
## Circuito
### Dispositivos utilizados
+ Arduino Nano 33 IoT
+ Módulo MQ-135
+ Modulo Fuente Micro Usb 5v
+ Elevador De Voltaje Mt3608
+ Tira Led Ws2812b
+ Cargador 5V 2A
+ Buzzer Activo 5V
### Diagrama del circuito
![image](https://user-images.githubusercontent.com/89102286/211431749-c5a819a0-f257-4917-b037-9452393ebdea.png)
## Interfaz web.
![Captura de pantalla_20230109_013954](https://user-images.githubusercontent.com/89102286/211431896-39f5b976-837c-4251-a7bf-e6d977f27959.png)
## Funcionamiento
El back-end del sitio está conformado por dos archivos php: getCO2 y setCO2, estos dos archivos funcionan como las API's del proyecto.
+ El archivo setC02 genera un archivo de texto que guarda en formato JSON el valor recibido.
+ El archivo getCO2 hace un echo del contenido del archivo generado anteriormente.

El front-end hace uso de la API getCO2 para arctualizar el valor del gráfico, generado con la API Charts de Google.

El diospositivo electrónico realiza la medición del CO2 y envía el valor medido a la API getCO2 a través de internet, además tiene una tira led y un buzz activo para indicar los niveles de CO2 sin la necesidad de acceder al sitio web.
