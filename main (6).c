//#include <stdint.h>
//#include <stdbool.h>
//#include "inc/hw_types.h"
//#include "inc/hw_gpio.h"
//#include "driverlib/pin_map.h"
//#include "driverlib/sysctl.c"
//#include "driverlib/sysctl.h"
//#include "driverlib/gpio.c"
//#include "driverlib/gpio.h"
//#include "driverlib/uart.c"
//#include "driverlib/uart.h"
//
//#include "FreeRTOS.h"
//#include "list.h"
//#include "task.h"
//#include "queue.h"
//#include "croutine.h"
//#include "timers.h"
//#include "FreeRTOSConfig.h"
//#include "portable.h"
//#include "queue.h"
//
//#define HIGH1 0x02
//#define HIGH2 0x04
//#define LOW 0
//QueueHandle_t xQueue1;
//
//void taskA(void* ptrA)
//{
//    unsigned char data;
//    UARTCharPut(UART0_BASE, 'M');
//    xQueue1=xQueueCreate(50,sizeof(unsigned char));
//
//    while(1)
//    {
//        data=UARTCharGet(UART0_BASE);
//        UARTCharPut(UART0_BASE, data);
//       xQueueSend(xQueue1,(void*)&data,( TickType_t ) 10);
//
//        vTaskDelay(2000);
//
//    }
//
//}
//void taskB(void* ptrB)
//{
//    unsigned char data;
//    while(1)
//    {
//
//        xQueueReceive(xQueue1,(void*)&data,( TickType_t ) 10);
//        if(data=='A')
//        {
//            GPIOPinWrite(GPIO_PORTF_BASE,GPIO_PIN_2,LOW);
//            GPIOPinWrite(GPIO_PORTF_BASE,GPIO_PIN_2,HIGH2);
//            vTaskDelay(1000);
//            GPIOPinWrite(GPIO_PORTF_BASE,GPIO_PIN_2,LOW);
//        }
//        if(data=='B')
//        {
//            GPIOPinWrite(GPIO_PORTF_BASE,GPIO_PIN_1,LOW);
//            GPIOPinWrite(GPIO_PORTF_BASE,GPIO_PIN_1,HIGH1);
//            vTaskDelay(1000);
//            GPIOPinWrite(GPIO_PORTF_BASE,GPIO_PIN_1,LOW);
//        }
//        vTaskDelay(1000);
//    }
//
//}
//
//int main(void)
//{
//
//    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);
//    while(!SysCtlPeripheralReady(SYSCTL_PERIPH_GPIOA));
//    GPIOPinConfigure(GPIO_PA0_U0RX);
//    GPIOPinConfigure(GPIO_PA1_U0TX);
//    SysCtlPeripheralEnable(SYSCTL_PERIPH_UART0);
//    while(!SysCtlPeripheralReady(SYSCTL_PERIPH_UART0));
//    UARTConfigSetExpClk(UART0_BASE, SysCtlClockGet(),9600,(UART_CONFIG_WLEN_8 | UART_CONFIG_STOP_ONE |UART_CONFIG_PAR_NONE));
//    GPIOPinTypeUART(GPIO_PORTA_BASE,GPIO_PIN_0|GPIO_PIN_1);
//    UARTClockSourceSet(UART0_BASE,UART_CLOCK_PIOSC);
//
//
//
//    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);
//    while(!SysCtlPeripheralReady(SYSCTL_PERIPH_GPIOF));
//
//    GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE,GPIO_PIN_1|GPIO_PIN_2);
//    GPIOUnlockPin(GPIO_PORTF_BASE,GPIO_PIN_4|GPIO_PIN_1|GPIO_PIN_2);
//    xTaskCreate(taskA,NULL,100,NULL,2,NULL);
//    xTaskCreate(taskB,NULL,100,NULL,1,NULL);
//    vTaskStartScheduler();
//    return 0;
//}
