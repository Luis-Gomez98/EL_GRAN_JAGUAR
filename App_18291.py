'''
Universidad del Valle de Guatemala
Trabajo de Graduación
Código realizado por:
Luis Ricardo Gómez Velásquez - 18291

Descripción:
Aplicación realizada en Python donde incluye la comunicación serial entre la TIVA C y la computadora.
La aplicación es capaz de recibir el código binario que originalmente manda el FPGA a la TIVA C y esta aplicación
lo codifica en decimal hasta obtener el ASCII. Incluye un sintetizador de audio digital el cúal funciona luego de que
la aplicación detecte el fin de cada texto de la FSM. 

'''

import serial
import pyttsx3
import time
import sys

BUSDATOS = ""                  # Se utiliza para almacenar datos provenientes del UART
conv_dec = 0
dato = ""
CADENA_TEXTO = []
cont = 0

engine = pyttsx3.init()
voices = engine.getProperty('voices')
engine.setProperty("rate", 180)
    
    
serialPort = serial.Serial(port = "COM3", baudrate=115200)
time.sleep(2)
serialPort.write(bytes(b'S'))
    
while(1):

    try:
    
        # Wait until there is data waiting in the serial buffer
        if(serialPort.in_waiting > 0):
            # Read data out of the buffer until a carraige return / new line is found
            BUSDATOS = serialPort.readline().decode('UTF-8')
              
            #print(BUSDATOS)
            #print(type(BUSDATOS))

            conv_dec = int(BUSDATOS,2)
            #print('El numero en decimal es: ',conv_dec)

            dato = chr(conv_dec)
            cont = cont + 1
            CADENA_TEXTO.append(dato)
            TEXTO = ''.join(CADENA_TEXTO)
            print(dato,end="")
                
            if (cont == 3539):
                    # print(TEXTO,end="")
                    serialPort.write(bytes(b'P'))
                    engine.setProperty('voice', voices[0].id) #changing index changes voices but ony 0 and 1 are working here
                    engine.say(TEXTO[3:3538])
                    engine.runAndWait()
                    serialPort.write(bytes(b'S'))
            elif (cont == 6934):
                    # print(TEXTO,end="")
                    serialPort.write(bytes(b'P'))
                    engine.setProperty('voice', voices[1].id) #changing index changes voices but ony 0 and 1 are working here
                    engine.say(TEXTO[3542:6933])
                    engine.runAndWait()
                    serialPort.write(bytes(b'S'))
                    cont = 0
    except Exception:
        print("\nInicie de nuevo la aplicación..\n")
        sys.exit()

                     

