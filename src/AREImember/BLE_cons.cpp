
#include "BLE_cons.h"
#include "RFID_cons.h"
#include <string.h>

BLECharacteristic *characteristicTX;
bool deviceConnected = false;
BLEMode blemode = nulltag;

void sendtonotify(char *notifying) {
  char txString[50];
  //strncpy(txString, DEVID, sizeof(txString));
  //strncat(txString, " | ", sizeof(txString));
  //strncat(txString, notifying,  sizeof(txString));
  //strncat(txString, "\n",  sizeof(txString));
  characteristicTX->setValue(notifying);
  characteristicTX->notify();
}

class CharacteristicCallbacks: public BLECharacteristicCallbacks {
    void onWrite(BLECharacteristic *characteristic) {
      std::string rxValue = characteristic->getValue();
      if (rxValue.length() > 0) {
//        for (int i = 0; i < rxValue.length(); i++) {
//          Serial.print(rxValue[i]);
//        }
        if (rxValue.find("WEN|") != -1) {
          blemode = writetag;
          sendtonotify("Now tag your card");
          char *item = GetItem(rxValue, 4);
          if ( !WritetoTag(item)) {
            sendtonotify("Writing card failed");
          }
          else {
            sendtonotify("Writing card success");
          }
          delete[] item;
          blemode = nulltag;
        }
        else if (rxValue.find("REN") != -1) {
          //Serial.println("Membaca Kartu");
          //sendtonotify("Read Tag");
          blemode = readtag;
        }
        else if (rxValue.find("B1") != -1) {
          sendtonotify("B1");
        }
        else if (rxValue.find("B0") != -1) {
          sendtonotify("B0");
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

char *GetItem( std::string str, int from) {

  char * writable = new char[str.size() + 1];
  std::copy(str.begin() + from, str.end(), writable);
  writable[str.size()] = '\0';
  return writable;
}

void BLEInit() {
  BLEDevice::init("AREImember");                              // The name of the BLE dev that appear on your smartphone
  BLEServer *server = BLEDevice::createServer();              // Initiating the server mode for the bluetooth
  server->setCallbacks(new ServerCallbacks());                // set the callback that use to identify the connection state
  BLEService *service = server->createService(SERVICE_UUID);  // create the bluetooth service

  // create chareacteristic to send the data
  characteristicTX = service->createCharacteristic(
                       CHARACTERISTIC_UUID_TX,
                       BLECharacteristic::PROPERTY_READ
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
  BLEAdvertising *pAdvertising = BLEDevice::getAdvertising();
  pAdvertising->addServiceUUID(SERVICE_UUID);
  pAdvertising->setScanResponse(true);
  pAdvertising->setMinPreferred(0x06); 
  pAdvertising->setMinPreferred(0x12);
  BLEDevice::startAdvertising();

  // Start advertising
  //server->getAdvertising()->start();
}
