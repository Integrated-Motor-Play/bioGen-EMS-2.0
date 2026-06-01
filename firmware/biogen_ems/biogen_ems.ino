/*
 * bioGen-EMS 2.0 — Seeed XIAO nRF52840
 * Auto-Paizo compatible EMS channel control + EMG telemetry
 */

#include <ArduinoBLE.h>
#include "config.h"

BLEService biogenService(BIOGEN_SERVICE_UUID);
BLEByteCharacteristic cmdCharacteristic(BIOGEN_CMD_CHAR_UUID, BLEWrite | BLERead);
BLEIntCharacteristic emgCharacteristic(BIOGEN_EMG_CHAR_UUID, BLENotify);

const int selPins[4] = {PIN_SEL_A, PIN_SEL_B, PIN_SEL_C, PIN_SEL_D};
int activeChannel = 0;  // 0 = none, 1-4 = demux channel

// EMG smoothing state
int emgMax = 300;
int emgMin = 100;
int emgLevel = 0;
int emgHistory[6];
int smoothHistory[6];
uint8_t historyLen = 0;
unsigned long lastEmgMs = 0;

int readEmgAveraged() {
  long sum = 0;
  for (int i = 0; i < 32; i++) {
    sum += analogRead(EMG_PIN);
  }
  int val = (int)(sum >> 5);
  if (val > emgMax) emgMax = val;
  if (val < emgMin) emgMin = val;
  return val;
}

bool isMonotonic(int* arr, int len) {
  if (len < 2) return true;
  bool inc = true, dec = true;
  for (int i = 1; i < len; i++) {
    if (arr[i] < arr[i - 1]) inc = false;
    if (arr[i] > arr[i - 1]) dec = false;
  }
  return inc || dec;
}

int smoothness(int* arr, int len) {
  if (len < 5) return 0;
  int hi = arr[0], lo = arr[0];
  for (int i = 1; i < len; i++) {
    if (arr[i] > hi) hi = arr[i];
    if (arr[i] < lo) lo = arr[i];
  }
  if (isMonotonic(arr, len)) return 0;
  return hi - lo;
}

int average(int* arr, int len) {
  if (len == 0) return 0;
  long sum = 0;
  for (int i = 0; i < len; i++) sum += arr[i];
  return (int)(sum / len);
}

void shiftPush(int* arr, int len, int value) {
  for (int i = 0; i < len - 1; i++) {
    arr[i] = arr[i + 1];
  }
  arr[len - 1] = value;
}

void applyChannel(int channel) {
  for (int i = 0; i < 4; i++) {
    digitalWrite(selPins[i], (channel == i + 1) ? HIGH : LOW);
  }
  activeChannel = channel;
}

void resetAllChannels() {
  applyChannel(0);
}

void handleCommand(char c) {
  switch (c) {
    case 'A': applyChannel(1); break;
    case 'a': if (activeChannel == 1) resetAllChannels(); break;
    case 'B': applyChannel(2); break;
    case 'b': if (activeChannel == 2) resetAllChannels(); break;
    case 'C': applyChannel(3); break;
    case 'c': if (activeChannel == 3) resetAllChannels(); break;
    case 'D': applyChannel(4); break;
    case 'd': if (activeChannel == 4) resetAllChannels(); break;
    case 'E':
    case 'e':
      resetAllChannels();
      break;
    case 'r':
    case 'R':
      resetAllChannels();
      break;
    default:
      break;
  }
}

void onCmdWritten(BLEDevice central, BLECharacteristic characteristic) {
  if (cmdCharacteristic.written()) {
    uint8_t value = cmdCharacteristic.value();
    handleCommand((char)value);
  }
}

void updateEmg() {
  unsigned long now = millis();
  if (now - lastEmgMs < EMG_SAMPLE_INTERVAL_MS) return;
  lastEmgMs = now;

  int raw = readEmgAveraged();
  if (historyLen < 6) {
    emgHistory[historyLen] = raw;
    smoothHistory[historyLen] = 0;
    historyLen++;
    return;
  }
  shiftPush(emgHistory, 6, raw);
  int s = smoothness(emgHistory, 5);
  shiftPush(smoothHistory, 6, s);
  int target = average(smoothHistory, 5) * 100;
  emgLevel += (int)((target - emgLevel) * 0.1f);

  emgCharacteristic.writeValue(emgLevel);

#if EMG_DEBUG_SERIAL
  Serial.print(raw);
  Serial.print(',');
  Serial.print(target);
  Serial.print(',');
  Serial.println(emgLevel);
#endif
}

void setup() {
  for (int i = 0; i < 4; i++) {
    pinMode(selPins[i], OUTPUT);
    digitalWrite(selPins[i], LOW);
  }
  pinMode(LED_BUILTIN, OUTPUT);

  Serial.begin(SERIAL_BAUD);
  while (!Serial && millis() < 3000) {
    ;  // wait for USB serial (timeout for battery use)
  }

  if (!BLE.begin()) {
    Serial.println("BLE init failed");
    while (1) {
      digitalWrite(LED_BUILTIN, !digitalRead(LED_BUILTIN));
      delay(200);
    }
  }

  BLE.setLocalName(BLE_DEVICE_NAME);
  BLE.setDeviceName(BLE_DEVICE_NAME);
  biogenService.addCharacteristic(cmdCharacteristic);
  biogenService.addCharacteristic(emgCharacteristic);
  BLE.addService(biogenService);
  cmdCharacteristic.setEventHandler(BLEWritten, onCmdWritten);
  emgCharacteristic.writeValue(0);

  BLE.advertise();
  Serial.println("bioGen-EMS ready");
}

void loop() {
  BLE.poll();

  while (Serial.available()) {
    char c = Serial.read();
    if (c == '\n' || c == '\r') continue;
    handleCommand(c);
  }

  updateEmg();
}
