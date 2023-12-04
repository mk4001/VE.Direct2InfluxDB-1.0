/*
  © MK4001 16 Jul 2023
  Write Victron Energy MPPT fields to INfluxDB on Cloud
  based on ESP32 Wroom
*/

#include <WiFiManager.h>
#include <InfluxDbClient.h>
#include <InfluxDbCloud.h>

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

  //WiFiManager, Local intialization. Once its business is done, there is no need to keep it around
  WiFiManager wm;

  bool res;
  // res = wm.autoConnect(); // auto generated AP name from chipid
  // res = wm.autoConnect("AutoConnectAP"); // anonymous ap
  res = wm.autoConnect("AutoConnectAP", "password");  // password protected ap

  if (!res) {
    Serial.println("Failed to connect");
    // ESP.restart();
  } else {
    //if you get here you have connected to the WiFi
    Serial.println("connected...yeey :)");
  }

  // Initialize ERP32 Serial2 port @19200 baud (VE.Direct port default rate)
  SERIAL_PORT.begin(19200, SERIAL_8N1);


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

  if (WiFi.status() != WL_CONNECTED) {
    ESP.restart();
  }

  if (SERIAL_PORT.available()) {
    String message = SERIAL_PORT.readStringUntil('\n');  //production

    // DEBUG Only
    //Serial.print("String: |"); Serial.print(message); Serial.println("|");


    message.trim();

    parseSerialData(message);
  }
}
