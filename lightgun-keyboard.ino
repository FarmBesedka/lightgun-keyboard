#define EB_NO_FOR
#define EB_NO_CALLBACK
#define EB_NO_COUNTER
#define EB_NO_BUFFER
#define EB_HOLD_TIME 50

#include <EncButton.h>
#include <Keyboard.h>

#define SHOT_PIN 2
#define HIT_PIN 3

Button shotBtn(SHOT_PIN, INPUT_PULLUP, HIGH);
Button hitBtn(HIT_PIN);

unsigned long shotTime = 0;
int shotDuration = 100;
bool isShot = false;

void setup() {
  Keyboard.begin();
  Serial.begin(115200);
}

void loop() {
  shotBtn.tick();
  hitBtn.tick();
  handleShot();
  handleHit();
  if (shotBtn.press() && !isShot) {
    isShot = true;
    shotTime = millis() + shotDuration;
  }
}

void handleShot() {
  if (isShot) {
    Keyboard.press(KEY_F23);
    if (millis() > shotTime) {
      Keyboard.release(KEY_F23);
      isShot = false;
    }
  }
}

void handleHit() {
  hitBtn.pressing() ? Keyboard.press(KEY_F24) : Keyboard.release(KEY_F24);
}
