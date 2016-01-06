# DW.miniESP Firmware Support
This is official page of software support from Deaware.

#### Special thanks
* Adafruit.
* ESP8266 forum.
* [ESP8266 Arduino](https://github.com/esp8266/Arduino)

## Board information
* VCC is 3.3V
* All gpio is 3.3V
* 10 bits ADC is 0 - 1V.
* VIN is 4.5V - 12V.

![](http://128.199.176.236/dwminiesp_support/images/pinout3.png)

## How to use DW.miniESP with Arduino IDE (version >= 1.6.4)
#### 1) Connect the USB to Serial to DW.miniESP
* Directly plug USB to Serial to DW.miniESP. (Only for 6 Pin USB to Serial Arduino Programmer)

<img src="http://128.199.176.236/dwminiesp_support/images/direct_plug_ftdi3.png" height="300px"></img>

* Wiring USB2Serial to DW.miniESP following this table. (Any USB to Serial)

| USB to Serial | DW.miniESP |
| ------------- | ---------- |
|      GND      |     GND    |
|      VCC      |     VCC    |
|      TXD      |     RXD    |
|      RXD      |     TXD    |

<img src="http://128.199.176.236/dwminiesp_support/images/wiring_ftdi3.png" height="300px"></img>

#### 2) For software support, our DW.miniESP is compatible following article at [ESP8266 Arduino repository](https://github.com/esp8266/Arduino).
