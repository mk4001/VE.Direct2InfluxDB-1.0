# VE.Direct2InfluxDB
Victron Energy VE.Direct UART data output to InfluxDB.2 using Espressif ESP32

The idea of untying the Smart Solar MPPT 75/15 by Victron Energy from the BLE APP of the smartphone and being able to bring the data to the cloud on InfluxDB (even on Premise is fine anyway) led me to create this project.

The VE.Direct interface on most Victron Energy products is in fact a UART which transmits at a rate of one record per second at 19200 baud.

It is necessary to make a simple adapter cable with the help of a JST 2.0 PH 4 connector easily available both on Amazon and on Aliexpress.

Of the pins of the UART port in question, I only used PINs 1 (GND) and 3 (TX), then subsequently connected to Serial2 of a Wroom 32 ESP module (Ports GND and GPIO16).

<img width="1369" alt="Screenshot 2023-07-20 at 09 47 55" src="https://github.com/mk4001/VE.Direct2InfluxDB/assets/50479511/780e0403-754e-42f9-90fa-479fb00701fc">
