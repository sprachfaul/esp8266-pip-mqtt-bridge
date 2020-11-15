# esp8266-pip-mqtt-bridge
Connect famous PIP 5048GK with RS232 (SUB D) over ESP8266 to an mqtt

# Hardware
* d1_mini board
* rs232 Adapter board
* PIP 5048 GK

# External resources
I was inspired by following threads / projects / tutorials
* https://forum.arduino.cc/index.php?topic=625629.0
* https://bitbucket.org/twvtec/esp8266-pip-serial2wlan-server/src/master/
* https://www.photovoltaikforum.com/core/attachment/7135-protocol-pdf/  ==> pdf with communication protocol

# Getting started

`include/secrets.h.template` needed to be copied to `include/secrets.h` and filled with values that suite your environment (wifi + mqtt).

