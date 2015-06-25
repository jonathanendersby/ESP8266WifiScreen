# ESP8266WifiScreen
A simple ESP8266 project that periodically updates a serial LCD screen with data pulled from a web server.

Serial is simply for debugging on the regular TX/RX pins.

Serial1 is a software serial on with the ESP's GPIO2 connected to the RX of the serial LCD screen.

This particular screen needs 5v to power up, so I'm using a 5v source with a 3v regulator to provide power to the ESP8266. The screen's VCC is connected before the regulator so it's getting the full 5v.
