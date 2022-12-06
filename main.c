/**
 * Universidad del Valle de Guatemala
 * Programa de la electrónica externa. Automatización de la máquina de estados finitos
 * y Ring Oscilator.
 *
 * Realizado por:
 * Luis Ricardo Gómez Velásquez - 18291
 */

//Liberías Utilizadas

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "inc/hw_ints.h"
#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
#include "driverlib/debug.h"
#include "driverlib/fpu.h"
#include "driverlib/gpio.h"
#include "driverlib/pin_map.h"
#include "driverlib/rom.h"
#include "driverlib/sysctl.h"
#include "driverlib/uart.h"
#include "utils/uartstdio.h"


//****************************** Creación de las funciones delay ***********************************************

void delayMs(uint32_t ui32Ms) {

    // 1 clock cycle = 1 / SysCtlClockGet() second
    // 1 SysCtlDelay = 3 clock cycle = 3 / SysCtlClockGet() second
    // 1 second = SysCtlClockGet() / 3
    // 0.001 second = 1 ms = SysCtlClockGet() / 3 / 1000

    SysCtlDelay(ui32Ms * (SysCtlClockGet() / 3 / 1000));
}

void delayUs(uint32_t ui32Us) {
    SysCtlDelay(ui32Us * (SysCtlClockGet() / 3 / 1000000));
}

//********************************* Función para la configuración de UART ***************************************************************************

void
InitConsole(void)
{
    // Enable GPIO port A which is used for UART0 pins.
    // TODO: change this to whichever GPIO port you are using.
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);

    // Configure the pin muxing for UART0 functions on port A0 and A1.
    // This step is not necessary if your part does not support pin muxing.
    // TODO: change this to select the port/pin you are using.
    GPIOPinConfigure(GPIO_PA0_U0RX);
    GPIOPinConfigure(GPIO_PA1_U0TX);

    // Enable UART0 so that we can configure the clock.
    SysCtlPeripheralEnable(SYSCTL_PERIPH_UART0);

    // Use the internal 16MHz oscillator as the UART clock source.
    UARTClockSourceSet(UART0_BASE, UART_CLOCK_PIOSC);

    // Select the alternate (UART) function for these pins.
    // TODO: change this to select the port/pin you are using.
    GPIOPinTypeUART(GPIO_PORTA_BASE, GPIO_PIN_0 | GPIO_PIN_1);

    // Initialize the UART for console I/O.
    UARTStdioConfig(0, 115200, 16000000);
}
//************************************************** Main **********************************************************

int main(void)
{
    //Declaración Variables
    bool BUSDATOS[8];
    int x = 0;
    char str;

    SysCtlClockSet(SYSCTL_SYSDIV_2_5 | SYSCTL_USE_PLL | SYSCTL_OSC_MAIN |
                   SYSCTL_XTAL_16MHZ); // 80 MHz

    InitConsole(); //Llamando a la función de configuración de UART

    //Habilitación de los puertos
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOB);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOD);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOE);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);

    //Configuración de Entradas
    //Bus de 8 bits
    GPIOPinTypeGPIOInput(GPIO_PORTA_BASE, GPIO_PIN_5 | GPIO_PIN_6 | GPIO_PIN_7); //q_out[2,1,0]
    GPIOPinTypeGPIOInput(GPIO_PORTB_BASE, GPIO_PIN_0 | GPIO_PIN_1 |GPIO_PIN_4); //q_out[7,6,3]
    GPIOPinTypeGPIOInput(GPIO_PORTE_BASE, GPIO_PIN_4 | GPIO_PIN_5); //q_out[5,4]
    GPIOPinTypeGPIOInput(GPIO_PORTF_BASE, GPIO_PIN_1); //CLK_S

    //Configuración de Salidas
    GPIOPinTypeGPIOOutput(GPIO_PORTD_BASE, GPIO_PIN_2 |GPIO_PIN_3); //clk y EN
    GPIOPinTypeGPIOOutput(GPIO_PORTE_BASE, GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3); //Reset y Select[1];Select[0]

    while(1)
    {
        while(UARTCharsAvail(UART0_BASE)){
                    str = UARTCharGet(UART0_BASE);  //str recibe los datos mediante el UART0
                    }

        if ((str == 'S')){ //Inicia la automatización
            GPIOPinWrite(GPIO_PORTD_BASE, GPIO_PIN_3, 255); //EN en 1 cuando se reciba el carácter 'S'

            if (x == 0){ //Si el contador es cero
                UARTprintf("00001010\n"); //Saltos de línea
                UARTprintf("00001010\n");
                GPIOPinWrite(GPIO_PORTE_BASE, GPIO_PIN_1, 255); //Reset en 1
                delayUs(1);
                GPIOPinWrite(GPIO_PORTE_BASE, GPIO_PIN_1, 0); //Reset en 0
                GPIOPinWrite(GPIO_PORTE_BASE, GPIO_PIN_2, 0); //Select en 00
                GPIOPinWrite(GPIO_PORTE_BASE, GPIO_PIN_3, 0);
            }else if (x == 3537){ //Cuando termine de desplegar el primer texto, se activa un reset y el select cambia a 1
                UARTprintf("00001010\n"); //Saltos de línea
                UARTprintf("00001010\n");
                GPIOPinWrite(GPIO_PORTE_BASE, GPIO_PIN_1, 255); //Reset en 1
                delayUs(1);
                GPIOPinWrite(GPIO_PORTE_BASE, GPIO_PIN_1, 0); //Reset en 0
                GPIOPinWrite(GPIO_PORTE_BASE, GPIO_PIN_2, 0); //Select en 01
                GPIOPinWrite(GPIO_PORTE_BASE, GPIO_PIN_3, 255);
            }else if (x == 6930){ //Cuando termine de desplegar ambos textos, se activa un reset y el select cambia a 0
                UARTprintf("00001010\n"); //Saltos de línea
                UARTprintf("00001010\n");
                GPIOPinWrite(GPIO_PORTE_BASE, GPIO_PIN_1, 255); //Reset en 1
                delayUs(1);
                GPIOPinWrite(GPIO_PORTE_BASE, GPIO_PIN_1, 0); //Reset en 0
                GPIOPinWrite(GPIO_PORTE_BASE, GPIO_PIN_2, 0); //Select en 00
                GPIOPinWrite(GPIO_PORTE_BASE, GPIO_PIN_3, 0);
                x = 0; //Se reinicia el contador para volver a desplegar el primer texto
            }


            //Lectura de datos transmitidos por el FPGA
            BUSDATOS[0] = GPIOPinRead(GPIO_PORTA_BASE, GPIO_PIN_7);
            BUSDATOS[1] = GPIOPinRead(GPIO_PORTA_BASE, GPIO_PIN_6);
            BUSDATOS[2] = GPIOPinRead(GPIO_PORTA_BASE, GPIO_PIN_5);
            BUSDATOS[3] = GPIOPinRead(GPIO_PORTB_BASE, GPIO_PIN_4);
            BUSDATOS[4] = GPIOPinRead(GPIO_PORTE_BASE, GPIO_PIN_5);
            BUSDATOS[5] = GPIOPinRead(GPIO_PORTE_BASE, GPIO_PIN_4);
            BUSDATOS[6] = GPIOPinRead(GPIO_PORTB_BASE, GPIO_PIN_1);
            BUSDATOS[7] = GPIOPinRead(GPIO_PORTB_BASE, GPIO_PIN_0);

            UARTprintf("%i%i%i%i%i%i%i%i\n", BUSDATOS[7],BUSDATOS[6],BUSDATOS[5],BUSDATOS[4],BUSDATOS[3],BUSDATOS[2],BUSDATOS[1],BUSDATOS[0]);
            //Envío de datos por UART

            GPIOPinWrite(GPIO_PORTD_BASE, GPIO_PIN_2, 0); //CLK que entra al FPGA cada 7 ms
            delayMs(7);
            GPIOPinWrite(GPIO_PORTD_BASE, GPIO_PIN_2, 255);
            delayMs(7);

            x++; //Incrementa el contador
        }else if ((str == 'P')){
            GPIOPinWrite(GPIO_PORTD_BASE, GPIO_PIN_2, 0);
            GPIOPinWrite(GPIO_PORTD_BASE, GPIO_PIN_3, 0); //EN en 0 cuando se reciba el carácter 'P'
        }else{
            GPIOPinWrite(GPIO_PORTD_BASE, GPIO_PIN_2, 0); //CLK que entra al FPGA
            GPIOPinWrite(GPIO_PORTE_BASE, GPIO_PIN_1, 0); //Reset en 0
            GPIOPinWrite(GPIO_PORTE_BASE, GPIO_PIN_2, 0); //Select en 00
            GPIOPinWrite(GPIO_PORTE_BASE, GPIO_PIN_3, 0);
            GPIOPinWrite(GPIO_PORTD_BASE, GPIO_PIN_3, 0); //EN
            x = 0; //Inicia en 0 el contador
        }
    }
}
