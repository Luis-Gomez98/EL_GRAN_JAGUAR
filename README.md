# EL_GRAN_JAGUAR
Archivo README donde se encuentran videos, códigos, diagrama de conexión y librerías requeridas para el completo funcionamiento de la máquina de estados finito.

## Instalación Python 3:

Se recomienda NO utilizar la versión más reciente porque suelen ser versiones de prueba.

- __[Instalar Python](https://www.python.org/downloads/)__ - Link de instalación. 

## Librerías requeridas:

Instalación de las librerías utilizadas en Python 3 para `Windows 11` y Distribuciones de `Linux`:

Windows 11:

    pip3 install pyserial
    pip3 install pyttsx3
    pip3 install python-time
    pip3 install os-sys

Distribuciones de Linux:

    sudo pip3 install pyserial
    sudo pip3 install pyttsx3
    sudo pip3 install python-time
    sudo pip3 install os-sys
    
## Diagrama de conexión de la electrónica externa y el FPGA:

![Diagrama de conexión](https://github.com/Luis-Gomez98/EL_GRAN_JAGUAR/blob/main/Diagramas%20de%20Conexi%C3%B3n/CONEXION%20FPGA%20TIVA%20C.png)

## Códigos:

Código de la electrónica externa (TIVA C):

- __[main](https://github.com/Luis-Gomez98/EL_GRAN_JAGUAR/blob/main/main.c)__ - Código principal realizado en Code Composer Studio.

Código de la aplicación y sintetizador digital (Python 3): 

- __[App_18291](https://github.com/Luis-Gomez98/EL_GRAN_JAGUAR/blob/main/App_18291.py)__ - Código para la aplicación de consola en Python 3. (IMPORTANTE INSTALAR LAS LIBRERÍAS)

## Videos:

- __[Explicación de creación de Blackboxes](https://youtu.be/-3zbbkzytVc)__ - Video 1.

- __[Creación de programa en ISE Design Suite 14.7](https://youtu.be/HMclKwUTCZg)__ - Video 2.

- __[Importación archivo UCF a ISE Design Suite 14.7](https://youtu.be/HMclKwUTCZg)__ - Video 3.

- __[Proceso de Sintetización y montaje del archivo verilog al FPGA Digilent Genesys Board](https://youtu.be/ttubQtCyglY)__ - Video 4.

- __[Simulación en ISIM.](https://youtu.be/HMclKwUTCZg)(https://youtu.be/42cC32TNNTo)__ - Video 5.

- __[Explicación de la electrónica externa.](https://youtu.be/I-KUMfvtae4)__ - Video 6.

- __[Explicación aplicación de consola en Python 3.](https://youtu.be/klTiH55PLWs)__ - Video 7.

- __[Funcionamiento de El Gran Jaguar.](https://youtu.be/QU9_QRYPk8c)__ - Video 8.



