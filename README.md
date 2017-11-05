# ESP8266-Environmental-Monitor
ESP8266 with DHT22/11 for Environmental Monitoring with data logging to remote web server (PHP) and database (MySQL)

This is a repository sharing code used on a series of ESP8266 microcontrollers with DHT22/11 temperature and humidity sensors, analog sensors and/or distance sensors which then connect over WiFi to your PHP server and inserts the data into your MySQL server.

Some more detail on how I used this for fun projects around the house here:
https://www.freelearner.how/2017/09/24/environmental-monitoring-cheap-esp8266-temperature-humidity-etc/

A note on security with this project - in the example code I use HTTP Get variables and connect unsecured over HTTP.  While this might be okay for a small environment over a secure network it's NOT a good plan for an enterprise solution!  The process to re-use this code for an enterprise solution would be to leverage HTTPS, and use variables that are easier to secure (i.e. Post rather than Get).
