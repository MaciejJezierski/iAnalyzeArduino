#include<LiquidCrystal.h>
#include<Button.h>
#include <ArduinoBLE.h>

Button button1(7);
int Contrast = 75;
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);
BLEService iService("89a2e4f8-76cc-4bdb-81e1-14b585e66844");
BLEFloatCharacteristic OxygenCharacteristic("cde86603-7243-49cd-a02e-0fc4c663e4fa", BLERead | BLEWrite);
int sensorValue = 0;
float correctedValue = 0.0;
float finalValue = 0.0;

void setup() {
  Serial.begin(9600);
  while (!Serial);

  button1.begin();
  analogWrite(6, Contrast);
  lcd.begin(16, 2);

  if (!BLE.begin()) {
    Serial.println("starting BLE failed!");
    while (1);
  }

  BLE.setDeviceName("iAnalyze");
  BLE.setLocalName("iAnalyze");
  iService.addCharacteristic(OxygenCharacteristic);
  BLE.setAdvertisedService(iService);
  BLE.addService(iService);
  BLE.advertise();

  BLE.setEventHandler(BLEConnected, blePeripheralConnectHandler);
  BLE.setEventHandler(BLEDisconnected, blePeripheralDisconnectHandler);
  OxygenCharacteristic.setEventHandler(BLERead, switchCharacteristicRead);
  OxygenCharacteristic.setEventHandler(BLEWritten, switchCharacteristicWritten);

  OxygenCharacteristic.writeValue(finalValue);
  Serial.println("BLE set up\n");
}

void loop() {
BLE.poll();
}

void blePeripheralConnectHandler(BLEDevice central) {
  Serial.print("Connected, central: ");
  lcd.setCursor(0, 0);
  lcd.print("O2 Analyzer");
  lcd.setCursor(0, 1);
  lcd.print("Press to Analyze");
  delay(1000);
  lcd.clear();
  Serial.println(central.address());
  if (button1.released()){
    oxygenTest();
  }
}

void blePeripheralDisconnectHandler(BLEDevice central) {
  Serial.print("Disconnected, central: ");
  Serial.println(central.address());
}
void switchCharacteristicWritten(BLEDevice central, BLECharacteristic characteristic) {
  oxygenTest();
  OxygenCharacteristic.writeValue(finalValue);
  Serial.println("there");

}

void switchCharacteristicRead(BLEDevice central, BLECharacteristic characteristic) {
  // OxygenCharacteristic.writeValue(finalValue);
}


void oxygenTest() {
  Serial.println("test");
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Analyzing");
  test();
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Analyze results:");
  lcd.setCursor(0, 1);
  lcd.print(finalValue);
  Serial.println("po wyjscu");
  Serial.println(finalValue);
  delay(4000);
  lcd.clear();
}

void test() {
  finalValue = 0.0;
  for(int i=0; i<10; i++) {
    sensorValue = analogRead(A5);
    correctedValue = (float) sensorValue;
    correctedValue/=6.7;
    Serial.println(correctedValue);
    finalValue += correctedValue;
    Serial.println("-----------");
    Serial.println(finalValue);
    delay(1000);
  }
  Serial.println("-----------");
  Serial.println(" war");
  Serial.println(finalValue);
  finalValue /= 10;
  Serial.println("dziel");
  Serial.println(finalValue);

}

