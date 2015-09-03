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

	http://github.com/deaware/dwcloud_firmware_support/raw/master/package_deaware_index.json

![](http://128.199.203.210/dwminiesp_support/images/insert_board_man_url.png)

* Open **"Boards Manager"** by goto **Tools > Board > Boards Manager...**

![](http://128.199.203.210/dwminiesp_support/images/select_boards_manager.png)

* Select **ESP8266 by Deaware** then click **Install**.

![](http://128.199.203.210/dwminiesp_support/images/install_esp8266.png)

* Check **ESP8266** is available by goto **Tools > Board** and you will see **Gerneric ESP8266 Module**.

![](http://128.199.203.210/dwminiesp_support/images/dwminiesp_found.png)

#### 3) Uploading program to DW.miniESP
* Preparing your code.

![](http://128.199.203.210/dwminiesp_support/images/prepare_code.png)

* Confirm that your setting is correct.

![](http://128.199.203.210/dwminiesp_support/images/set_board.png)

* Reset your DW.miniESP into **PROG Mode** by set the **PROG/RUN switch** to **PROG Mode** position like the picture below and press **RESET**.

![](http://128.199.203.210/dwminiesp_support/images/switch_prog.png)

* Press upload button to upload.

![](http://128.199.203.210/dwminiesp_support/images/uploaded.png)

## API Documentation by [ESP8266 Arduino](https://github.com/esp8266/Arduino)

#### Basic Wiring functions ####

`pinMode`, `digitalRead`, `digitalWrite`, `analogWrite` work as usual.

Pin numbers correspond directly to the esp8266 GPIO pin numbers. To read GPIO2,
call `digitalRead(2);`

GPIO0-GPIO15 can be `INPUT`, `OUTPUT`, `INPUT_PULLUP`, and `INPUT_PULLDOWN`.
GPIO16 can be `INPUT`, `OUTPUT` or `INPUT_PULLDOWN`.

`analogRead(A0)` reads the value of the ADC channel connected to the TOUT pin.

`analogWrite(pin, value)` enables software PWM on the given pin. PWM may be used on pins 0 to 15.
Call `analogWrite(pin, 0)` to disable PWM on the pin. `value` may be in range from 0 to `PWMRANGE`, which is currently equal to 1023.

Pin interrupts are supported through `attachInterrupt`, `detachInterrupt` functions.
Interrupts may be attached to any GPIO pin, except GPIO16. Standard Arduino interrupt
types are supported: `CHANGE`, `RISING`, `FALLING`.

#### Pin Functions ####

![Pin Functions](https://raw.githubusercontent.com/Links2004/Arduino/esp8266/docs/pin_functions.png)
The most usable pin functions are mapped to the macro `SPECIAL`, so calling `pinMode(pin, SPECIAL)`
will switch that pin in the most usable FUNCTION_X. Those are UART RX/TX on pins 1 - 3, HSPI for pins 12-15 and CLK functions for pins 0, 4 and 5.

#### Timing and delays ####
`millis` and `micros` return the number of milliseconds and microseconds elapsed after reset, respectively.

`delay` pauses the sketch for a given number of milliseconds and allows WiFi and TCP/IP tasks to run.
`delayMicroseconds` pauses for a given number of microseconds.

Remember that there is a lot of code that needs to run on the chip besides the sketch
when WiFi is connected. WiFi and TCP/IP libraries get a chance to handle any pending
events each time the `loop()` function completes, OR when `delay(...)` is called.
If you have a loop somewhere in your sketch that takes a lot of time (>50ms) without
calling `delay()`, you might consider adding a call to delay function to keep the WiFi
stack running smoothly.

There is also a `yield()` function which is equivalent to `delay(0)`. The delayMicroseconds
function, on the other hand, does not yield to other tasks, so using it for delays
more than 20 milliseconds is not recommended.

#### Serial ####

`Serial` object works much the same way as on a regular Arduino. Apart from hardware FIFO (128 bytes for TX and RX) HardwareSerial has additional 256-byte TX and RX buffers. Both transmit and receive is interrupt-driven. Write and read functions only block the sketch execution when the respective FIFO/buffers are full/empty.

`Serial` uses UART0, which is mapped to pins GPIO1 (TX) and GPIO3 (RX). Serial may be remapped to GPIO15 (TX) and GPIO13 (RX) by calling `Serial.swap();` after `Serial.begin();`. Calling `swap` again maps UART0 back to GPIO1 and GPIO3.

`Serial1` uses UART1 which is a transmit-only UART. UART1 TX pin is GPIO2. To use `Serial1`, call `Serial1.begin`.

By default the diagnostic output from WiFi libraries is disabled when you call `Serial.begin`. To enable debug output again, call `Serial.setDebugOutput(true);`. To redirect debug output to `Serial1` instead, call `Serial1.setDebugOutput(true);`.

Both `Serial` and `Serial1` objects support 5, 6, 7, 8 data bits, odd (O), even (E), and no (N) parity, and 1 or 2 stop bits. To set the desired mode, call `Serial.begin(baudrate, SERIAL_8N1);`, `Serial.begin(baudrate, SERIAL_6E2);`, etc.

#### Progmem ####

The Program memory features work much the same way as on a regular Arduino; placing read only data and strings in read only memory and freeing heap for your application.
The important difference is that on the esp8266 the literal strings are not pooled.  This means that the same literal string defined inside a `F("")` and/or `PSTR("")` will take up space for each instance in the code. So you will need to manage the duplicate strings yourself.

#### WiFi(ESP8266WiFi library) ####

This is mostly similar to WiFi shield library. Differences include:

- `WiFi.mode(m)`: set mode to `WIFI_AP`, `WIFI_STA`, or `WIFI_AP_STA`.
- call `WiFi.softAP(ssid)` to set up an open network
- call `WiFi.softAP(ssid, password)` to set up a WPA2-PSK network (password should be at least 8 characters)
- `WiFi.macAddress(mac)` is for STA, `WiFi.softAPmacAddress(mac)` is for AP.
- `WiFi.localIP()` is for STA, `WiFi.softAPIP()` is for AP.
- `WiFi.RSSI()` doesn't work
- `WiFi.printDiag(Serial);` will print out some diagnostic info
- `WiFiUDP` class supports sending and receiving multicast packets on STA interface.
When sending a multicast packet, replace `udp.beginPacket(addr, port)` with
`udp.beginPacketMulticast(addr, port, WiFi.localIP())`.
When listening to multicast packets, replace `udp.begin(port)` with
`udp.beginMulticast(WiFi.localIP(), multicast_ip_addr, port)`.
You can use `udp.destinationIP()` to tell whether the packet received was
sent to the multicast or unicast address.
Also note that multicast doesn't work on softAP interface.

WiFiServer, WiFiClient, and WiFiUDP behave mostly the same way as with WiFi shield library.
Four samples are provided for this library.

#### Ticker ####

Library for calling functions repeatedly with a certain period. Two examples included.

It is currently not recommended to do blocking IO operations (network, serial, file) from Ticker
callback functions. Instead, set a flag inside the ticker callback and check for that flag inside the loop function.

#### EEPROM ####

This is a bit different from standard EEPROM class. You need to call `EEPROM.begin(size)`
before you start reading or writing, size being the number of bytes you want to use.
Size can be anywhere between 4 and 4096 bytes.

`EEPROM.write` does not write to flash immediately, instead you must call `EEPROM.commit()`
whenever you wish to save changes to flash. `EEPROM.end()` will also commit, and will
release the RAM copy of EEPROM contents.

EEPROM library uses one sector of flash located at 0x7b000 for storage.

Three examples included.

#### I2C (Wire library) ####

Wire library currently supports master mode up to approximately 450KHz.
Before using I2C, pins for SDA and SCL need to be set by calling
`Wire.begin(int sda, int scl)`, i.e. `Wire.begin(0, 2);` on ESP-01,
else they default to pins 4(SDA) and 5(SCL).

#### SPI ####

SPI library supports the entire Arduino SPI API including transactions, including setting phase (CPHA).
Setting the Clock polarity (CPOL) is not supported, yet (SPI_MODE2 and SPI_MODE3 not working).

#### ESP-specific APIs ####

APIs related to deep sleep and watchdog timer are available in the `ESP` object.

`ESP.deepSleep(microseconds, mode)` will put the chip into deep sleep. `mode` is one of `WAKE_RF_DEFAULT`, `WAKE_RFCAL`, `WAKE_NO_RFCAL`, `WAKE_RF_DISABLED`. (GPIO16 needs to be tied to RST to wake from deepSleep.)

`ESP.wdtEnable()`, `ESP.wdtDisable()`, and `ESP.wdtFeed()` provide some control over the watchdog timer.

`ESP.reset()` resets the CPU.

`ESP.getFreeHeap()` returns the free heap size.

`ESP.getChipId()` returns the ESP8266 chip ID as a 32-bit integer.

Several APIs may be used to get flash chip info:

`ESP.getFlashChipId()` returns the flash chip ID as a 32-bit integer.

`ESP.getFlashChipSize()` returns the flash chip size, in bytes, as seen by the SDK (may be less than actual size).

`ESP.getFlashChipSpeed(void)` returns the flash chip frequency, in Hz.

`ESP.getCycleCount()` returns the cpu instruction cycle count since start as an unsigned 32-bit.  This is useful for accurate timing of very short actions like bit banging.


#### OneWire (from https://www.pjrc.com/teensy/td_libs_OneWire.html) ####

Library was adapted to work with ESP8266 by including register definitions into OneWire.h
Note that if you already have OneWire library in your Arduino/libraries folder, it will be used
instead of the one that comes with this package.

#### mDNS responder (ESP8266mDNS library) ####

Allows the sketch to respond to multicast DNS queries for domain names like "foo.local".
Currently the library only works on STA interface, AP interface is not supported.
See attached example and library README file for details.

#### Other libraries (not included with the IDE)

Libraries that don't rely on low-level access to AVR registers should work well. Here are a few libraries that were verified to work:

- [aREST](https://github.com/marcoschwartz/aREST) REST API handler library.
- [PubSubClient](https://github.com/Imroy/pubsubclient) MQTT library by @Imroy.
- [DHT11](https://github.com/adafruit/DHT-sensor-library) - initialize DHT as follows: `DHT dht(DHTPIN, DHTTYPE, 15);`
- [DallasTemperature](https://github.com/milesburton/Arduino-Temperature-Control-Library.git)
- [NeoPixelBus](https://github.com/Makuna/NeoPixelBus) - Arduino NeoPixel library compatible with esp8266.
- [RTC](https://github.com/Makuna/Rtc) - Arduino Library for Ds1307 & Ds3231 compatible with esp8266.
- [Blynk](https://github.com/blynkkk/blynk-library) - easy IoT framework for Makers (check out the [Kickstarter page](http://tiny.cc/blynk-kick)).
