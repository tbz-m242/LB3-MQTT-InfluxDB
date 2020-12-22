/** MQTT Publish von Sensordaten */
#include "mbed.h"
#include "HTS221Sensor.h"
#include "network-helper.h"
#include "MQTTNetwork.h"
#include "MQTTmbed.h"
#include "MQTTClient.h"
#include "OLEDDisplay.h"
#include "Motor.h"
#include "DHT.h"

// Sensoren wo Daten fuer Topics produzieren
static DevI2C devI2c( MBED_CONF_IOTKIT_I2C_SDA, MBED_CONF_IOTKIT_I2C_SCL );
static HTS221Sensor hum_temp(&devI2c);
AnalogIn hallSensor( MBED_CONF_IOTKIT_HALL_SENSOR );
DigitalIn button( MBED_CONF_IOTKIT_BUTTON1 );
DHT sensor( A5, DHT11 );

// Topic's
char* topicTEMP =  "iotkit";
char* topicITEMP =  "iotkit/internal/temperature";
char* topicETEMP = "iotkit/external/temperature";
char* topicIHUM = "iotkit/internal/humity";
char* topicEHUM = "iotkit/external/humity";

// MQTT Brocker
char* hostname = "192.168.1.182";
int port = 1883;
// MQTT Message
MQTT::Message message;
// I/O Buffer
char buf[100];

// UI
OLEDDisplay oled( MBED_CONF_IOTKIT_OLED_RST, MBED_CONF_IOTKIT_OLED_SDA, MBED_CONF_IOTKIT_OLED_SCL );
DigitalOut led1( MBED_CONF_IOTKIT_LED1 );
DigitalOut alert( MBED_CONF_IOTKIT_LED3 );


/** Hilfsfunktion zum Publizieren auf MQTT Broker */
void publish( MQTTNetwork &mqttNetwork, MQTT::Client<MQTTNetwork, Countdown> &client, char* topic )
{
    led1 = 1;
    printf("Connecting to %s:%d\r\n", hostname, port);
    
    int rc = mqttNetwork.connect(hostname, port);
    if (rc != 0)
        printf("rc from TCP connect is %d\r\n", rc);

    MQTTPacket_connectData data = MQTTPacket_connectData_initializer;
    data.MQTTVersion = 3;
    data.clientID.cstring = "IoTKit37";
    data.username.cstring = "testuser";
    data.password.cstring = "testpassword";
    if ((rc = client.connect(data)) != 0)
        printf("rc from MQTT connect is %d\r\n", rc);

    MQTT::Message message;    
    
    oled.cursor( 2, 0 );
    oled.printf( "Topi: %s\n", topic );
    oled.cursor( 3, 0 );    
    oled.printf( "Push: %s\n", buf );
    message.qos = MQTT::QOS0;
    message.retained = false;
    message.dup = false;
    message.payload = (void*) buf;
    message.payloadlen = strlen(buf);
    client.publish( topic, message);  
    
    // Verbindung beenden, ansonsten ist nach 4x Schluss
    if ((rc = client.disconnect()) != 0)
        printf("rc from disconnect was %d\r\n", rc);

    mqttNetwork.disconnect();
    led1 = 0;
}

/** Hauptprogramm */
int main()
{
    uint8_t id;
    int rc = 0;
    float temp, hum, h, c;
    
    oled.clear();
    oled.printf( "MQTT-LB03\r\n" );
    oled.printf( "host: %s:%s\r\n", hostname, port );

    printf("\nConnecting to %s...\n", MBED_CONF_APP_WIFI_SSID);
    oled.printf( "SSID: %s\r\n", MBED_CONF_APP_WIFI_SSID );
    // Connect to the network with the default networking interface
    // if you use WiFi: see mbed_app.json for the credentials
    NetworkInterface* wifi = connect_to_default_network_interface();
    if ( !wifi ) 
    {
        printf("Cannot connect to the network, see serial output\n");
        return 1;
    }

    // TCP/IP und MQTT initialisieren (muss in main erfolgen)
    MQTTNetwork mqttNetwork( wifi );
    MQTT::Client<MQTTNetwork, Countdown> client(mqttNetwork);
    
    /* Init all sensors with default params */
    hum_temp.init(NULL);
    hum_temp.enable();  

    while   ( 1 ) 
    {
        // Temperator und Luftfeuchtigkeit
        hum_temp.read_id(&id);
        hum_temp.get_temperature(&temp);
        hum_temp.get_humidity(&hum);
        rc = sensor.readData();         
        if ( rc == 0 )
        {
            c   = sensor.ReadTemperature(CELCIUS);
            h   = sensor.ReadHumidity();
        }
        else
            return  ( -1 );         // Fehler - Programm beenden       
        //Send Value
        //Internal Temperature
        sprintf( buf, "itemp,site=IoTKit37 value=%f", temp);        
        publish( mqttNetwork, client, topicITEMP );
        //External Temperature
        sprintf( buf, "etemp,site=IoTKit37 value=%f", c);        
        publish( mqttNetwork, client, topicETEMP );
        //Internal Humity
        sprintf( buf, "ihumity,site=IoTKit37 value=%f", hum);        
        publish( mqttNetwork, client, topicIHUM );
        //External Humity
        sprintf( buf, "ehumity,site=IoTKit37 value=%f", h);        
        publish( mqttNetwork, client, topicEHUM ); 

        wait    ( 2.0f );
    }
}
