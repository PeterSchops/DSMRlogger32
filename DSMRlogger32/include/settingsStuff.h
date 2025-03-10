#ifndef SETTINGSSTUFF_H
#define SETTINGSSTUFF_H

//============ Includes ====================
#include "arduinoGlue.h"
#include "Shield32.h"


DECLARE_TIMER_EXTERN(publishMQTTtimer);
DECLARE_TIMER_EXTERN(reconnectMQTTtimer);
DECLARE_TIMER_EXTERN(nextTelegram);
DECLARE_TIMER_EXTERN(oledSleepTimer);

void showDevSettings();   
void showShieldSettings();   

#endif // SETTINGSSTUFF_H
