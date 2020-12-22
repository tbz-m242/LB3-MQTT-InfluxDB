# 1. Testprotokoll
Damit ein Projekt richtig funktioniert, muss getestet werden.
Folgend finden Sie das Testprotokoll vom Lb03 Projekt.

## 1.1 Vagrant installation
| Testfall: 001     | Vagrant installation                                                                                                                                |
| ----------------- | --------------------------------------------------------------------------------------------------------------------------------------------------- |
| Ziel:             | Die Umgebung kann mit Vagrant Deployed werden.                                                                                                      |
| Beschreibung:     | Klonen Sie das git und wechseln sie ins lb03 Verzeichnis. Jetzt können sie ganz einfach vagrant up ausführen. Die VMs sollen jetzt erstellt werden. |
| Soll-Wert:        | Es werden 3 VMs erstellt                                                                                                                            |
| Ist-Wert:         | Es gibt eine mosquitto, grafana und influxdb VM.                                                                                                    |
| Analyse:          | Alles wie geplant.                                                                                                                                  |
| Weitere Schritte: | -                                                                                                                                                   |

## 1.2 MQTT Mosquitto
| Testfall: 002     | MQTT Mosquitto                                                                                                      |
| ----------------- | ------------------------------------------------------------------------------------------------------------------- |
| Ziel:             | Der Server wurde richtig aufgesetzt und kann MQTT-Topics empfangen und verteilen.                                   |
| Beschreibung:     | Mit dem Programm [MQTT.fx](https://mqttfx.jensd.de/) kann man Daten vom MQTT-Server auslesen und Topics subscriben. |
| Soll-Wert:        | Daten können angezeigt werden.                                                                                      |
| Ist-Wert:         | Man kann Topics folgen und Daten an den Server senden.                                                              |
| Analyse:          | Funktioniert wie geplant.                                                                                           |
| Weitere Schritte: | -                                                                                                                   |

## 1.3 Telegraf Konfiguration
| Testfall: 003     | Telegraf Konfiguration                                                                                                                                  |
| ----------------- | ------------------------------------------------------------------------------------------------------------------------------------------------------- |
| Ziel:             | Der Telegraf hat die benötigten Berechtigungen und kann in die Datenbank nach InfluxDB Konzept schreiben.                                               |
| Beschreibung:     | Der Telegraf folgt dem Topic iotkit/#. Mit dem Programm [MQTT.fx](https://mqttfx.jensd.de/) kann man Daten an das Topic schreiben, diese werden danach in die Datenbank geschriben. |
| Soll-Wert:        | Es gibt folgende Tabellen/Messwerte: enhumity, inhumity, entemperature und intemperature.                                                               |
| Ist-Wert:         | Es gibt folgende Tabellen/Messwerte: enhumity, inhumity, entemperature und intemperature.                                                               |
| Analyse:          | Funktioniert wie geplant.                                                                                                                               |
| Weitere Schritte: | -                                                                                                                                                       |

## 1.4 InfluxDB Konfiguration
| Testfall: 004     | InfluxDB Konfiguration                                                              |
| ----------------- | ----------------------------------------------------------------------------------- |
| Ziel:             | Die InfluxDB ist richtig konfiguriert, so dass die Daten gespeichert werden können. |
| Beschreibung:     | Einloggen auf der InfluxDB und ein Select Statement ausführen.                      |
| Soll-Wert:        | Daten können herausgelesen werden.                                                  |
| Ist-Wert:         | Daten können mit "use m242; select * from itemperature" herausgelesen werden.       |
| Analyse:          | Funktioniert wie geplant.                                                            |
| Weitere Schritte: | -                                                                                   |

## 1.5 Grafana InfluxDB connection
| Testfall: 005     | Grafana InfluxDB connection                                    |
| ----------------- | -------------------------------------------------------------- |
| Ziel:             | Grafana kann mit der Datenbank verbunden werden                |
| Beschreibung:     | Nach dem einlogen auf Grafana kann man die InfluxDB einbinden. |
| Soll-Wert:        | Eine Verbindung zur InfluxDB kann aufgebaut werden.            |
| Ist-Wert:         | InfluxDB kann mit Grafana verknüpft werden.                    |
| Analyse:          | Funktioniert wie geplant.                                      |
| Weitere Schritte: | -                                                              |

## 1.6 Grafana Konfiguration
| Testfall: 006     | Grafana Konfiguration                                                               |
| ----------------- | ----------------------------------------------------------------------------------- |
| Ziel:             | Man kann sich auf das Grafana Interface einloggen.                                  |
| Beschreibung:     | In einem Webbrowser auf Localhost:3000 zugreifen und mit den credentials einloggen. |
| Soll-Wert:        | Das Login funktioniert. Man siegt das Grafana Dashboard                             |
| Ist-Wert:         | Das Login auf das Dashboard funktioniert.                                           |
| Analyse:          | Funktioniert wie geplant.                                                           |
| Weitere Schritte: | -                                                                                   |

## 1.7 IOT-Kit MQTT Daten versand
| Testfall: 007     | IOT-Kit MQTT Daten versand                                                                                                   |
| ----------------- | ---------------------------------------------------------------------------------------------------------------------------- |
| Ziel:             | Das IOTKit kann die Daten über MQTT an den Broker schicken.                                                                  |
| Beschreibung:     | Die Kompilierte Datei muss auf das IotKit hochgeladen. Nach einem Neustart des Board fängt dieses an die Daten zu senden. |
| Soll-Wert:        | Es gibt keine Error beim senden.                                                                                             |
| Ist-Wert:         | Die Daten werden verteilt und nach InfluxDB Konzept verteilt.                                                                |
| Analyse:          | Funktioniert wie geplant.                                                                                                    |
| Weitere Schritte: | -                                                                                                                            |
