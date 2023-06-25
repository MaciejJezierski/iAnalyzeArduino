
// Button button1(7);

// int Contrast = 75;
// LiquidCrystal lcd(12, 11, 5, 4, 3, 2);
// void setup()
// {
//    while(!Serial){}
//    Serial.begin(9600);
//    button1.begin();
//    analogWrite(6, Contrast);
//    lcd.begin(16, 2);
   
// }
// void loop()
// {
//    if (button1.released()){
//       Serial.println("test");
//       int sensorValue = analogRead(A5);
//       Serial.println(sensorValue);
//       lcd.clear();
//       lcd.setCursor(0, 0);
//       lcd.print("Analyzing");
//       delay(1000);
//       lcd.clear();
//       sensorValue = analogRead(A5);
//       Serial.println(sensorValue);

//    }
//    lcd.setCursor(0, 0);
//    lcd.print("O2 Analyzer");
//    lcd.setCursor(0, 1);
//    lcd.print("Press to Analyze");
//    delay(1000);
//    lcd.clear();
// }



#include<LiquidCrystal.h>
#include<Button.h>
#include <ArduinoBLE.h>

BLEService iService("89a2e4f8-76cc-4bdb-81e1-14b585e66844");
BLEFloatCharacteristic dataCharacteristic("cde86603-7243-49cd-a02e-0fc4c663e4fa", BLERead | BLENotify);
float dataToSend = 0.0;

void setup() {
  Serial.begin(9600);
  while (!Serial);

  if (!BLE.begin()) {
    Serial.println("starting Bluetooth® Low Energy module failed!");
    while (1);
  }

  // set advertised local name and service UUID:
  BLE.setDeviceName("iAnalyze");
  BLE.setLocalName("iAnalyze");
  iService.addCharacteristic(dataCharacteristic);
  BLE.setAdvertisedService(iService);
  BLE.addService(iService);
  // dataCharacteristic.writeValue(dataToSend);

  BLE.advertise();
  BLE.setEventHandler(BLEConnected, blePeripheralConnectHandler);
  BLE.setEventHandler(BLEDisconnected, blePeripheralDisconnectHandler);
  Serial.println("BLE LED Peripheral set up\n");
}

void loop() {
  BLEDevice central = BLE.central();
BLE.poll();
  // if (central) {
  //   Serial.print("Connected to central: ");
  //   Serial.println(central.address());


  //   // while the central is still connected to peripheral:
  //   while (central.connected()) {
  //     // if the remote device wrote to the characteristic,
  //     // use the value to control the LED:
  //     dataToSend += 0.1;
  //     // dataCharacteristic.writeValue(dataToSend);
  //     Serial.print("i was here! ");

  //     delay(1000);
  //   }

  //   Serial.print(F("Disconnected from central: "));
  //   Serial.println(central.address());
}

void blePeripheralConnectHandler(BLEDevice central) {
  // central connected event handler
  Serial.print("Connected event, central: ");
  Serial.println(central.address());
}

void blePeripheralDisconnectHandler(BLEDevice central) {
  // central disconnected event handler
  Serial.print("Disconnected event, central: ");
  Serial.println(central.address());
}
