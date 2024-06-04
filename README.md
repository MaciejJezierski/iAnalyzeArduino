# iAnalyze for Arduino: Turn your Arduino board into Oxygen Analyzer

Software is designed to be full developed Analyzer with one exception - the oxygen sensor is being emulated with potentiometer which is basically giving same type of output as sensor (analog output of voltage) but obviosuly not giving real oxygen values. 

Main funcions of the software are:
- Making measurment and showing the results on the screen
- Utilising BLE connection to connect to other devices - for example iPhone running iAnalyze (https://github.com/MaciejJezierski/iAnalyze)
- While connected to other device as peripherial, the host may run measurment randomly and get the results send using BLE.


## Prerequisites
- Arduino board - Arduino UNO WiFi REV2
- IDE capable of loading code to Arduino board
- LiquidCrystal.h, Button.h, ArduinoBLE.h libraries if not installed with your IDE.

## Building iAnalyze from source
Build exactly same way as any Arduino code before.
Have in mind that code was designed specifically for Arduino UNO WiFi REV2 and tested only on this device.
