# DW.miniESP Firmware Support
This is official page of software support from Deaware.

#### Special thank.

## Board information
* VCC is 3.3V
* All gpio is 3.3V
* 10 bits ADC is 0 - 1V.
* VIN is 4.5V - 12V.

![](http://128.199.203.210/dwminiesp_support/images/pinout.png)

## How to use DW.miniESP with Arduino IDE (version >= 1.6.4)
#### 1) Connect the USB to Serial to DW.miniESP
* Directly plug USB to Serial to DW.miniESP. (Only for 6 Pin USB to Serial Arduino Programmer)

<img src="http://128.199.203.210/dwminiesp_support/images/direct_plug_ftdi.png" height="300px"></img>

* Wiring USB2Serial to DW.miniESP following this table. (Any USB to Serial)

| USB to Serial | DW.miniESP |
| ------------- | ---------- |
|      GND      |     GND    |
|      VCC      |     VCC    |
|      TXD      |     RXD    |
|      RXD      |     TXD    |

<img src="http://128.199.203.210/dwminiesp_support/images/wiring_ftdi.png" height="300px"></img>

#### 2) Preparing Arudino IDE (version >= 1.6.4)
* If you don't have Arduino IDE (version >= 1.6.4) or you have Arduino IDE version < 1.6.4, you can download directly from this [link](http://www.arduino.cc/en/Main/Software)
* Firstly, **Add Board Manager URLs** by goto **File > Preferences** and fill **Add Board Manager URLs** with the following link.
````
http://github.com/deaware/dwcloud_firmware_support/raw/master/package_deaware_index.json
````
![](http://128.199.203.210/dwminiesp_support/images/insert_board_man_url.png)

* Open **"Boards Manager"** by goto **Tools > Board > Boards Manager...**
![](http://128.199.203.210/dwminiesp_support/images/select_boards_manager.png)

* Select **ESP8266 by Deaware** and click **Install**.
![](http://128.199.203.210/dwminiesp_support/images/install_esp8266.png)

* Check **ESP8266** is available by goto **Tools > Board** and you will see **DW.miniESP**.
![](http://128.199.203.210/dwminiesp_support/images/dwminiesp_found.png)
