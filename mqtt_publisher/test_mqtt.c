#include <stdio.h>
#include <mosquitto.h>


int main(void)
{
    struct mosquitto *mosqt;
    int rc;

    mosquitto_lib_init();

    mosqt = mosquitto_new("test_mqtt", true, NULL);

    rc = mosquitto_connect(mosqt, "localhost", 1883, 60);

    if (rc != 0)
    {
        printf("Client could not connect to broker ! Error code: %d\n", rc);
        mosquitto_destroy(mosqt);
        return -1;
    }

    printf("Client connected to broker !\n");

    mosquitto_publish(mosqt, NULL, "test", 10, "Hello MQTT", 0, false);

    mosquitto_disconnect(mosqt);
    mosquitto_destroy(mosqt);
    mosquitto_lib_cleanup();

    return 0;
}