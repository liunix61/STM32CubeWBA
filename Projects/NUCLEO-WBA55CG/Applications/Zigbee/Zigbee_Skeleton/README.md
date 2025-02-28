## __Zigbee_Skeleton Application Description__

This application is generated by STM32CubeMX including all the libriaries required to start coding Zigbee application.

The purpose of this application is to give a starting point for the client to create his application.

### __Keywords__

Connectivity, Zigbee, Zigbee protocol, 802.15.4 protocol, STM32CubeMX


### __Application Setup__

This application only allows to initialize the LinkLayer for Zigbee applications.   
It is up to the client to add his application, calling Zigbee APIs.

### __Hardware and Software environment__

* This example runs on STM32WBA52xx devices.  

* This example has been tested with an STMicroelectronics STM32WBA52CGA_Nucleo board and can be easily tailored to any other supported device and development board.  

* On STM32WBA52CGA_Nucleo, the jumpers must be configured as described in this section. Starting from the top left position up to the bottom right position, the jumpers on the Board must be set as follows:
<br>    
**JP1:**</br>
1-2:  [ON]</br>
3-4:  [OFF]</br>
5-6:  [OFF]</br>
7-8:  [OFF]</br>
9-10: [OFF]</br>
<br>
**JP2:**</br>
1-2:  [ON]  

### __Traces__

* To get the traces you need to connect your Board to the Hyperterminal (through the STLink Virtual COM Port).  

* The UART must be configured as follows:  
<br>
BaudRate       = 115200 baud</br>
Word Length    = 8 Bits</br>
Stop Bit       = 1 bit</br>
Parity         = none</br>
Flow control   = none</br>
Terminal   "Go to the Line" : &lt;LF&gt;  

### __Note__
By default, this application runs with Zigbee PRO stack R23.
 
If you want to run this application using Zigbee PRO stack R22, you should replace ZigBeeProR23_FFD.a by ZigBeeProR22_FFD.a and ZigBeeProR23_RFD.a by ZigBeeProR22_RFD.a and ZigBeeClusters.a by ZigBeeClustersR22.a in the build environment.
 
Also, set in the project setup compilation flag CONFIG_ZB_REV=22. 