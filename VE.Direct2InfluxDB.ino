/*
  © MK4001 16 Jul 2023
  Write Victron Energy MPPT fields to INfluxDB on Cloud
  based on ESP32 Wroom
*/

#include <WiFi.h>
//#include <HardwareSerial.h>
#include <InfluxDbClient.h>
#include <InfluxDbCloud.h>

// WiFi credentials
const char* ssid = "Your WiFi SSID here";
const char* password = "Your WiFi pwd here";

//Define Seria port #2 PIN 16(RX) - 17(TX - not used)
#define SERIAL_PORT Serial2

// InfluxDB Cloud Configuration
const char* influxDBUrl = "https://eu-central-1-1.aws.cloud2.influxdata.com"; //CHECK IN YOUR ACCOUT BEFORE LUNCH!!!
const char* influxDBToken = "Your InfluxDB Token (FULL ACCESS) here";
const char* influxDBOrg = "Your InfluxDB ORG ID here";
const char* influxDBBucket = "Your InfluxDB Bucket name here";

// Time zone info
#define TZ_INFO "UTC2"

InfluxDBClient influxDB(influxDBUrl, influxDBOrg, influxDBBucket, influxDBToken, InfluxDbCloud2CACert);

// Declare Data point
Point point("SmartSolar");

void setup() {
  Serial.begin(115200);

  // WiFi begin
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }

  Serial.println("Connected to WiFi");

  // Initialize ERP32 Serial2 port @19200 baud (VE.Direct port default rate)
  SERIAL_PORT.begin(19200);


  // Accurate time is necessary for certificate validation and writing in batches
  // We use the NTP servers in your area as provided by: https://www.pool.ntp.org/zone/
  // Syncing progress and the time will be printed to Serial.
  timeSync(TZ_INFO, "pool.ntp.org", "time.nis.gov");

  // Check server connection
  if (influxDB.validateConnection()) {
    Serial.print("Connected to InfluxDB: ");
    Serial.println(influxDB.getServerUrl());
  } else {
    Serial.print("InfluxDB connection failed: ");
    Serial.println(influxDB.getLastErrorMessage());
  }

  point.addTag("device", "mppt_victron");
}

void loop() {

  if (SERIAL_PORT.available()) {
    String message = SERIAL_PORT.readStringUntil('\n');

    /* DEBUG ONLY
    Serial.print("String: |");
    Serial.print(message);
    Serial.println("|");
*/
    message.trim();

    parseSerialData(message);
  }
}
