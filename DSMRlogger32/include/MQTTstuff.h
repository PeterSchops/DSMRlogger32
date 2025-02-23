#ifndef MQTTSTUFF_H
#define MQTTSTUFF_H

//============ Includes ====================
#include "arduinoGlue.h"
#include "safeTimers.h"

DECLARE_TIMER_EXTERN(reconnectMQTTtimer);

enum states_of_MQTT { MQTT_STATE_INIT, MQTT_STATE_TRY_TO_CONNECT, MQTT_STATE_IS_CONNECTED, MQTT_STATE_ERROR };

#endif // MQTTSTUFF_H
