
#include "BLE_cons.h"
#include <string.h>

BLECharacteristic *characteristicTX; 
bool deviceConnected = false;

void sendtonotify(char *notifying){
  char txString[50];
  strncpy(txString, DEVID, sizeof(txString));
  strncat(txString, " | ", sizeof(txString));
  strncat(txString, notifying,  sizeof(txString));
  strncat(txString, "\n",  sizeof(txString));
  characteristicTX->setValue(txString); 
  characteristicTX->notify();
}

class CharacteristicCallbacks: public BLECharacteristicCallbacks {
    void onWrite(BLECharacteristic *characteristic) {
      std::string rxValue = characteristic->getValue();
      if (rxValue.length() > 0) {

        for (int i = 0; i < rxValue.length(); i++) {

        }
      }
    }
};

class ServerCallbacks: public BLEServerCallbacks {
    void onConnect(BLEServer* pServer) {
      deviceConnected = true;
    };

    void onDisconnect(BLEServer* pServer) {
      deviceConnected = false;
    }
};

void BLEInit() {
  BLEDevice::init("AREImember");                              // The name of the BLE dev that appear on your smartphone
  BLEServer *server = BLEDevice::createServer();              // Initiating the server mode for the bluetooth
  server->setCallbacks(new ServerCallbacks());                // set the callback that use to identify the connection state
  BLEService *service = server->createService(SERVICE_UUID);  // create the bluetooth service

  // create chareacteristic to send the data
  characteristicTX = service->createCharacteristic(
                       CHARACTERISTIC_UUID_TX,
                       BLECharacteristic::PROPERTY_NOTIFY
                     );

  characteristicTX->addDescriptor(new BLE2902());

  // create chareacteristic to receive the data
  BLECharacteristic *characteristic = service->createCharacteristic(
                                        CHARACTERISTIC_UUID_RX,
                                        BLECharacteristic::PROPERTY_WRITE
                                      );
  characteristic->setCallbacks(new CharacteristicCallbacks());
  // Start the service
  service->start();

  // Start advertising 
  server->getAdvertising()->start();
}
