
#ifndef _BLE_CONS_H__
#define _BLE_CONS_H__

#include <BLEDevice.h>
#include <BLEServer.h>
#include <BLEUtils.h>
#include <BLE2902.h>

extern bool deviceConnected;
#define SERVICE_UUID            "ab0828b1-198e-4351-b779-901fa0e0371e"
#define CHARACTERISTIC_UUID_RX  "4ac8a682-9736-4e5d-932b-e9b31405049c"
#define CHARACTERISTIC_UUID_TX  "0972EF8C-7613-4075-AD52-756F33D4DA91"
#define DEVID                   "3310-3340-12908"

void sendtonotify(char *notifying);
void BLEInit(void);

 #endif
