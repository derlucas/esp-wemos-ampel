#include <Homie.h>
#include <ArduinoOTA.h>

#define PIN_RED     D1
#define PIN_YELLOW  D2
#define PIN_GREEN   D5

long lastTickMillis;

HomieNode lightNodeRed("red", "switch");
HomieNode lightNodeYellow("yellow", "switch");
HomieNode lightNodeGreen("green", "switch");

bool nodeInputHandlerRed(const HomieRange& range, const String& value) {
  if(value == "true" || value == "false") {
    digitalWrite(PIN_RED, value == "true");
    lightNodeRed.setProperty("state").send(value);
    return true;
  }
  return false;
}

bool nodeInputHandlerYellow(const HomieRange& range, const String& value) {
  if(value == "true" || value == "false") {
    digitalWrite(PIN_YELLOW, value == "true");
    lightNodeYellow.setProperty("state").send(value);
    return true;
  }
  return false;
}

bool nodeInputHandlerGreen(const HomieRange& range, const String& value) {
  if(value == "true" || value == "false") {
    digitalWrite(PIN_GREEN, value == "true");
    lightNodeGreen.setProperty("state").send(value);
    return true;
  }
  return false;
}

void setup() {
  Serial.begin(115200);
  Serial << endl << endl;
  pinMode(PIN_RED, OUTPUT);
  pinMode(PIN_YELLOW, OUTPUT);
  pinMode(PIN_GREEN, OUTPUT);

  
  Homie_setFirmware("trafficlight", "1.0.0");

  lightNodeRed.advertise("state").settable(nodeInputHandlerRed);
  lightNodeYellow.advertise("state").settable(nodeInputHandlerYellow);
  lightNodeGreen.advertise("state").settable(nodeInputHandlerGreen);

  Homie.setup();
  Homie.getLogger() << "started" << endl;

  ArduinoOTA.setHostname(Homie.getConfiguration().deviceId);
  ArduinoOTA.begin();
  
}

void loop() {
  Homie.loop();
  ArduinoOTA.handle();
  
}

