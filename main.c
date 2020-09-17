#include <stdint.h>
#include <stdbool.h>
#include "driverlib/gpio.h"
#include "driverlib/gpio.c"
#include "driverlib/uart.h"
#include "driverlib/uart.c"
#include "driverlib/sysctl.h"
#include "driverlib/sysctl.c"
#include "driverlib/pin_map.h"
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"

/**
 * main.c
 */
#define LED_PERIPH  SYSCTL_PERIPH_GPIOF
#define LED_BASE GPIO_PORTF_BASE
#define RED_LED  GPIO_PIN_1
#define BLUE_LED  GPIO_PIN_2
#define GREEN_LED  GPIO_PIN_3


QueueHandle_t ColorHandle;
void UARTIntHandler(void){
    uint8_t color = 0;
    color = UARTCharGet(UART0_BASE);    //wait to receive char on serial
    xQueueSendFromISR(ColorHandle, (void*) &color, NULL);
    UARTIntClear(UART0_BASE, UART_INT_RX);
}



void Task_LED(void *pvParameters){
    uint8_t color = 0, state = 0;
    uint32_t pin = 0;
    TickType_t previousTime =  xTaskGetTickCount();

    while(1){
    if (xQueueReceive(ColorHandle, &color, (TickType_t)0)) {
        UARTCharPut(UART0_BASE, color); //send Char on serial
        UARTCharPut(UART0_BASE, ' ');
    }

        switch(color){
            case 'R':
            case 'r':
                state = RED_LED;
                pin = RED_LED;
                GPIOPinWrite(LED_BASE, BLUE_LED, 0);
                GPIOPinWrite(LED_BASE, GREEN_LED, 0);
                break;
            case 'B':
            case 'b':
                state = BLUE_LED;
                pin = BLUE_LED;
                GPIOPinWrite(LED_BASE, RED_LED, 0);
                GPIOPinWrite(LED_BASE, GREEN_LED, 0);
                break;

            case 'G':
            case 'g':
                state = GREEN_LED;
                pin = GREEN_LED;
                GPIOPinWrite(LED_BASE, BLUE_LED, 0);
                GPIOPinWrite(LED_BASE, RED_LED, 0);
                break;
        }
        GPIOPinWrite(LED_BASE, pin, state);
        state ^= pin;   //toggle
        color  = 0;
        vTaskDelay(500);
    }
}


int main(void)
{

    SysCtlPeripheralEnable(LED_PERIPH);     //enable the clock to PORTF (LEDs)
    while(!SysCtlPeripheralReady(LED_PERIPH));  //wait till it reaches the port

    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);    //same with PortA (UART)
    while(!SysCtlPeripheralReady(SYSCTL_PERIPH_GPIOA));
    GPIOUnlockPin(LED_BASE, RED_LED|BLUE_LED|GREEN_LED);    //unlock Pins
    GPIOPinTypeGPIOOutput(LED_BASE, RED_LED|BLUE_LED|GREEN_LED);    //set OUTPUT

    GPIOPinConfigure(GPIO_PA0_U0RX);    //configure PORTA.0 as UART receive
    GPIOPinConfigure(GPIO_PA1_U0TX);    //configure PORTA.1 as UART transmitter
    GPIOPinTypeUART(GPIO_PORTA_BASE, GPIO_PIN_0|GPIO_PIN_1);    //making sure that they set to UART function

    SysCtlPeripheralEnable(SYSCTL_PERIPH_UART0);    //enable the clock for UART peripheral
    while(!SysCtlPeripheralReady(SYSCTL_PERIPH_UART0));

    uint32_t freq = SysCtlClockGet();

    UARTIntRegister(UART0_BASE, &UARTIntHandler);
    UARTIntEnable(UART0_BASE, UART_INT_RX);
    UARTConfigSetExpClk(UART0_BASE, freq, 9600, UART_CONFIG_WLEN_8|UART_CONFIG_STOP_ONE|UART_CONFIG_PAR_NONE);
                                                //Set UART as 9600 baudrate, 8bit data, 1 stop bit, no parity
    UARTFIFODisable(UART0_BASE);

    //print out on serial The string below
    char str[] = "Enter The char of a Color R G B: ";
       uint32_t i = 0;
       while(str[i] != '\0'){
           UARTCharPut(UART0_BASE, str[i]);
           i++;
       }
       //here FreeRTOS start
       ColorHandle = xQueueCreate(2, sizeof(uint8_t));
       TaskHandle_t UARTHandle, LEDHandle;
       xTaskCreate(Task_LED, "led", 128, NULL, 1, &LEDHandle);
       vTaskStartScheduler();


    while(1);

	return 0;
}
