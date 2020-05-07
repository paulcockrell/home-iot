# Home IOT

Publish sensor metrics from independent Espruino Nano sensors over HC12 433Mhz radio to the 'hub' ESP8266 which publishes the message on to Google IOT cloud, where it is processed of a MQTT queue by a cloud function and stored in a database

## Development
Developed with [platformio](https://platformio.org/) integrated into VS Code

## Google IOT

Under the cloud folder you will find the serverless functions to process the queue to store in a DB and a web site to view the data in graphs.

## View SPA to view graphs
```
https://home-iot-20200429.web.app/
```
# References

```
https://github.com/GoogleCloudPlatform/google-cloud-iot-arduino/tree/master/examples/Esp8266-lwmqtt
```