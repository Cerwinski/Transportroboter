# Projekt Transportroboter in Vertiefung Programmierung SS23

## Table of Contents
1. [General Info](#general-info)
2. [Technologies](#technologies)
3. [Installation](#installation)

### General Info
***
Ein Roboter der Objekte von A nach B bringt.
Er soll das Objekt auf der Strecke greifen, mit dem Linearantrieb hochheben und anhand der Linien auf dem Boden zu dem Entladeort fahren, der rot markiert ist. 
Am Entladeort soll er das Objekt entladen und fährt dann autonom weiter zum Zielort (blau) wo sein Prozess zu Ende ist und er stehn bleibt.
Beim Be- und Entladen leuchtet außerdem die LED auf um zu signalisieren, dass er es Be- und Entlädt.

## Technologies
***
A list of technologies used within the project:
* [Makeblock Library](https://github.com/Makeblock-official/Makeblock-Libraries): Version 3.27
* [mBot Ranger](https://www.makeblock.com/pages/mbot-ranger-robot-building-kit): Version 1
* [Me Color Sensor](http://docs.makeblock.com/diy-platform/en/electronic-modules/sensors/me-color-sensor-v1.html): Version 1
* [Me Line Follower](https://education.makeblock.com/help/me-line-follower/): Version 2
* [Me Ultrasonic Sensor](https://education.makeblock.com/help/me-ultrasonic-sensor/): Version 1
* [SG90 9g Micro Servomotor](https://www.roboter-bausatz.de/p/sg90-9g-micro-servomotor): Version 1
* [Arduino IDE](https://www.arduino.cc/en/software): Version 2.1.1

## Installation
***
A little intro about the installation. 
```
$ git clone https://github.com/Cerwinski/mbot-ranger.git

In den Ordner mbot-ranger gehen. Dann den Code_Abgabe_Vertiefung_Prog.ino über die Arduino IDE öffnen. Dann den mBot Ranger mit COM5 verbinden am Gerät. 
Als Board das Arduino Mega or Mega 2560 auswählen und als Port COM5/6. Den Code hochladen, wenn fertig, dann Verbindung zum mBot trennen.
Jetzt ist der mBot Ranger startbereit und man kann den Anschaltknopf drücken. Vorher den Roboter mit dem Linienfolgersensor auf die Strecke legen. Fertig.

