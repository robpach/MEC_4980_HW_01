#include <Arduino.h>

// All button definitions
const int button_1 = A0;
const int button_2 = A1;
const int button_3 = A2;
const int button_4 = A3;

// All LED definitions
const int led_1 = 5;
const int led_2 = 6;
const int led_3 = 9;
const int led_4 = 10;

int phase = 0;
int state1;
int state2;
int state3;
int state4;
const long loading_duration = 3000;
const long detonation_duration = 5000;
long start;
const int resetDelay = 300;

void setup()
{
  Serial.begin(115200);

  pinMode(button_1, INPUT_PULLUP);
  pinMode(button_2, INPUT_PULLUP);
  pinMode(button_3, INPUT_PULLUP);
  pinMode(button_4, INPUT_PULLUP);

  pinMode(led_1, OUTPUT);
  pinMode(led_2, OUTPUT);
  pinMode(led_3, OUTPUT);
  pinMode(led_4, OUTPUT);
}

void loop()
{
  // REMINDER: Low state on INPUT_PULLUP means button pressed
  if (phase == 0)
  {

    Serial.println("Unloaded");
    digitalWrite(led_1, LOW);
    digitalWrite(led_2, LOW);
    digitalWrite(led_3, LOW);
    digitalWrite(led_4, LOW);
    delay(100);
    state1 = digitalRead(button_1);

    if (state1 == LOW)
    {
      Serial.println("Loading...");
      digitalWrite(led_1, HIGH);
      start = millis();
      while (millis() - start < loading_duration)
      {
        state1 = digitalRead(button_1);
        if (state1 == LOW)
        {
          delay(resetDelay);
          phase = 0;
        }
      }
      Serial.println("Loaded");
      phase = 1;
    }
  }

  if (phase == 1)
  {

    state1 = digitalRead(button_1);
    if (state1 == LOW)
    {
      delay(resetDelay);
      phase = 0;
    }
    state2 = digitalRead(button_2);
    if (state2 == LOW)
    {
      Serial.println("Material Inserted");
      digitalWrite(led_2, HIGH);
      phase = 2;
    }
  }

  if (phase == 2)
  {
    state1 = digitalRead(button_1);
    if (state1 == LOW)
    {
      delay(resetDelay);
      phase = 0;
    }

    state3 = digitalRead(button_3);
    if (state3 == LOW)
    {
      Serial.println("Starting Detonation...");
      start = millis();
      while (millis() - start < detonation_duration)
      {
        state1 = digitalRead(button_1);
        if (state1 == LOW)
        {
          delay(resetDelay);
          phase = 0;
        }
        digitalWrite(led_3, HIGH);
        delay(100);
        digitalWrite(led_3, LOW);
        delay(100);
      }

      Serial.println("BOOM!");
      digitalWrite(led_3, HIGH);
      digitalWrite(led_4, HIGH);
      phase = 3;
    }
  }

  if (phase == 3)
  {
    state1 = digitalRead(button_1);
    if (state1 == LOW)
    {
      delay(resetDelay);
      phase = 0;
    }

    state4 = digitalRead(button_4);
    if (state4 == LOW)
    {
      Serial.println("Energy Placed into Vehicle.");
      for (int i = 0; i <= 2; i++)
      {
        digitalWrite(led_1, LOW);
        digitalWrite(led_2, LOW);
        digitalWrite(led_3, LOW);
        digitalWrite(led_4, LOW);
        delay(100);
        digitalWrite(led_1, HIGH);
        digitalWrite(led_2, HIGH);
        digitalWrite(led_3, HIGH);
        digitalWrite(led_4, HIGH);
        delay(100);
      }
      phase = 0;
    }
  }
}
