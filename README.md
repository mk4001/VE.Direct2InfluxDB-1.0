# VE.Direct2InfluxDB
Victron Energy VE.Direct UART data output to InfluxDB.2 using Espressif ESP32 (based on Arduino platfrom)

The idea of untying the Smart Solar MPPT 75/15 by Victron Energy from the BLE APP of the smartphone and being able to bring the data to the cloud on InfluxDB (even on Premise is fine anyway) led me to create this project.

The VE.Direct interface, on most Victron Energy products, is in fact a UART which transmits at a rate of one record per second at 19200 baud.

It is necessary to make a simple adapter cable with the help of a JST 2.0 PH 4 connector easily available both on Amazon and on Aliexpress.

The pins of the UART port in question, I only used PINs 1 (GND) and 3 (TX), then connected to Serial2 of a Wroom 32 ESP module (Ports GND and GPIO16).

<img width="1369" alt="Screenshot 2023-07-20 at 09 47 55" src="https://github.com/mk4001/VE.Direct2InfluxDB/assets/50479511/780e0403-754e-42f9-90fa-479fb00701fc">

Data, flows from the UART port at the rate of 1 record/sec.

Detailed documentation of the fields, their format and content is gathered here:

https://www.victronenergy.com/upload/documents/VE.Direct-Protocol-3.33.pdf

Once the record has been captured on the ESP32, needs to parse the fields and collect the data, of what we need, before sending to InfluxDB.2

It's easy to create a free account on InfluxDB in the cloud, while for the more daring, you can download the entire suite needed for on-premise installation for a Raspberry PI for free.

You can start directly in the Cloud from here:

https://cloud2.influxdata.com/signup

Once logged into InfluxDB, you have to create a new Bucket (in short, a DB) and related Token which you then have to copy into the code attached here together with the ID of your organization. Easy.

When your Bucket is finally full of data you can decide to create a wonderful Dashboard on Grafana (always in the cloud, always free)

https://grafana.com/auth/sign-up/create-user?pg=hp&plcmt=hero-btn1&cta=create-free-account

With a little imagination and above all practice, you can even create dashboards like this:

![image1](https://github.com/mk4001/VE.Direct2InfluxDB/blob/6319bbf4189262424499b21e297fc7bacbad50cf/Screenshot%202023-11-22%20at%2013.58.06.png)

the obviously "cool" thing about this is that you can consult the data of your Victron Energy devices quickly and easily from anywhere and customize them as you like.

Inspired by: https://github.com/DocBrown101/Ve.Direct.InfluxDB.Collector
