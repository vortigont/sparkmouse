#include <Arduino.h>
// my mouse mover
// to prevent stuped screenlocks

// Based on https://www.shadowandy.net/2015/01/digispark-random-mouse-move-anti-screensaver.htm
// Digispark Random Mouse Move for anti-screensaver
// Author: shadowandy (shadowandy[dot]sg[at]gmail[dot]com)
// Web: www.shadowandy.net

#include "DigiMouse.h"
//#include "main.h"

// Configurations for Random Mouse Move
#define MOUSE_MOVE_L 1		// Number of pixels to move (min)
#define MOUSE_MOVE_H 10		// Number of pixels to move (max)
#define MOUSE_DELAY_L 30000	// Interval (milliseconds) to move the mouse (min)
#define MOUSE_DELAY_H 120000	// Interval (milliseconds) to move the mouse (max)

#define DELAY_TIME	50
#define MAX_BRT	255		// max brightness for led
#define LED_PIN	1		// 1 - LED on Model A; 0 - LED on Model B

// You really should not change anything below

#define MOUSE_UP 1
#define MOUSE_DN 2
#define MOUSE_LT 3
#define MOUSE_RT 4

unsigned int mouse_move_amount = 1;
unsigned int mouse_current = MOUSE_UP;
unsigned long mouse_time_current;
unsigned long mouse_time_movement;

uint8_t brt = MAX_BRT;

void setup() {
  pinMode(LED_PIN, OUTPUT);
  DigiMouse.begin(); //start or reenumerate USB
  //ledToggle();
  analogWrite(LED_PIN, brt);
  mouse_time_movement = millis() + random(MOUSE_DELAY_L, MOUSE_DELAY_H);
  mouse_move_amount = random(MOUSE_MOVE_L, MOUSE_MOVE_H);
}

void loop() {
  //DigiMouse.update(); // DigiMouse.update() at least every 50ms
  if (millis() > mouse_time_movement) {
    switch (mouse_current) {
        case MOUSE_UP :
          DigiMouse.moveY(-mouse_move_amount);
          break;
        case MOUSE_DN :
          DigiMouse.moveY(mouse_move_amount);
          break;
        case MOUSE_LT :
          DigiMouse.moveX(-mouse_move_amount);
          break;
        case MOUSE_RT :
          DigiMouse.moveX(mouse_move_amount);
          break;
        default :
          mouse_current = 1;
    }
    //ledToggle();
    mouse_current = random(1,4);
    mouse_time_movement = millis() + random(MOUSE_DELAY_L, MOUSE_DELAY_H);
    mouse_move_amount = random(MOUSE_MOVE_L, MOUSE_MOVE_H);
    brt = MAX_BRT;
  }

  if (brt) analogWrite(LED_PIN, --brt);
  DigiMouse.delay(DELAY_TIME);
}