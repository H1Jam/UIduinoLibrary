#include "BluetoothSerial.h"
#include "Bind.hpp"

BluetoothSerial SerialBT;
Bind bind;
BindAttitudeIndicator attitudeIndicator;
BindHeadingIndicator headingIndicator;
BindHeadingIndicator headingIndicator2;

int counter = 0;
float rollC = 0;
float pitchC = 0;

float rollDelta = 2;
float pitchDelta = 1;

float headingC = 0;

void onConnection(int16_t w, int16_t h) {
  Serial.println("Screen setup started!");
  drawAttitudeIndicator();
  addHeadingIndicator();
  Serial.println("Screen setup done!");
}

void drawAttitudeIndicator() {
  attitudeIndicator.x = 30;
  attitudeIndicator.y = 70;
  attitudeIndicator.cmdId = BIND_ADD_OR_REFRESH_CMD;
  attitudeIndicator.dimSize = 200;

  // Specify the initial roll and pitch values.
  attitudeIndicator.roll = 0.0f;
  attitudeIndicator.pitch = 0.0f;

  // Synchronize the attitudeIndicator object with BindCanvas.
  bind.sync(&attitudeIndicator);
}

void addHeadingIndicator() {
  headingIndicator.x = 30;
  headingIndicator.y = 70;
  headingIndicator.cmdId = BIND_ADD_OR_REFRESH_CMD;
  headingIndicator.dimSize = 200;

  // Specify the initial heading value.
  headingIndicator.heading = 0.0f;

  // Synchronize the headingIndicator object with BindCanvas.
  bind.sync(&headingIndicator);
}

void setup() {
  Serial.begin(115200);
  String devName = "BindOnESP32";
  SerialBT.begin(devName);

  bind.init(&SerialBT, &onConnection);
  
  Serial.println("The Bluetooth device started, now you can pair the phone with Bluetooth!");
  Serial.println("devName:");
  Serial.println(devName);
}

void loop() {
  bind.sync();
  delay(10);
  counter++;
  if (counter > 20) {
    counter = 0;
    rollC += rollDelta;
    pitchC += pitchDelta;
    headingC += 5;

    if (rollC > 20 || rollC < -20) {
      rollDelta = -1 * rollDelta;
    }

    if (pitchC > 20 || pitchC < -20) {
      pitchDelta = -1 * pitchDelta;
    }

    if (headingC > 360) {
      headingC = 0.0f;
    }
    _setAttitudeIndicator(rollC, pitchC);
    _setHeadingIndicator(headingC);
  }
}

void _setAttitudeIndicator(float roll, float pitch) {
  attitudeIndicator.cmdId = BIND_DATA_ONLY_CMD;
  attitudeIndicator.roll = roll;
  attitudeIndicator.pitch = pitch;
  bind.sync(&attitudeIndicator);
}

void _setHeadingIndicator(float heading) {
  headingIndicator.cmdId = BIND_DATA_ONLY_CMD;
  headingIndicator.heading = heading;
  bind.sync(&headingIndicator);
}
