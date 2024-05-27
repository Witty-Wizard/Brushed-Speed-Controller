#include <Arduino.h>

#define deadtime 2 // us
#define motor1_PMOS 6
#define motor1_NMOS 5
enum output_state
{
  OUTPUT_HIGH = 1,
  OUTPUT_LOW = 2,
  OUTPUT_NEUTRAL = 0
};

output_state motor1 = OUTPUT_NEUTRAL;

void output_fsm(output_state desired_state);

void setup()
{
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(motor1_PMOS, OUTPUT);
  pinMode(motor1_NMOS, OUTPUT);

  output_fsm(OUTPUT_NEUTRAL);
}

void loop()
{
  // put your main code here, to run repeatedly:
  while (Serial.available() > 0)
  {

    char c = Serial.read();
    if (c == '1')
    {
      output_fsm(OUTPUT_HIGH);
    }
    else if (c == '0')
    {
      output_fsm(OUTPUT_LOW);
    }
    else if (c == 'z')
    {
      output_fsm(OUTPUT_NEUTRAL);
    }
  }
}

void output_fsm(output_state desired_state)
{
  if (motor1 == OUTPUT_NEUTRAL)
  {
    if (desired_state == OUTPUT_NEUTRAL)
    {
// turn both MOS OFF
#ifndef INVERTED_OUTPUTS
      digitalWrite(motor1_PMOS, HIGH);
      digitalWrite(motor1_NMOS, LOW);
#else
      digitalWrite(motor1_PMOS, LOW);
      digitalWrite(motor1_NMOS, HIGH);
#endif

      motor1 = OUTPUT_NEUTRAL;
    }
    else if (desired_state == OUTPUT_HIGH)
    {
// turn pmos on
#ifndef INVERTED_OUTPUTS
      digitalWrite(motor1_PMOS, LOW);
      digitalWrite(motor1_NMOS, LOW);
#else
      digitalWrite(motor1_PMOS, HIGH);
      digitalWrite(motor1_NMOS, HIGH);
#endif
      motor1 = OUTPUT_HIGH;
    }
    else if (desired_state == OUTPUT_LOW)
    {
// turn nmos on
#ifndef INVERTED_OUTPUTS
      digitalWrite(motor1_PMOS, HIGH);
      digitalWrite(motor1_NMOS, HIGH);
#else
      digitalWrite(motor1_PMOS, LOW);
      digitalWrite(motor1_NMOS, LOW);
#endif
      motor1 = OUTPUT_LOW;
    }
    else
    {
#ifndef INVERTED_OUTPUTS
      digitalWrite(motor1_PMOS, HIGH);
      digitalWrite(motor1_NMOS, LOW);
#else
      digitalWrite(motor1_PMOS, LOW);
      digitalWrite(motor1_NMOS, HIGH);
#endif
      motor1 = OUTPUT_NEUTRAL;
    }
  }
  else if (motor1 == OUTPUT_HIGH)
  {
    if (desired_state == OUTPUT_NEUTRAL)
    {
// turn both mos OFF
#ifndef INVERTED_OUTPUTS
      digitalWrite(motor1_PMOS, HIGH);
      digitalWrite(motor1_NMOS, LOW);
#else
      digitalWrite(motor1_PMOS, LOW);
      digitalWrite(motor1_NMOS, HIGH);
#endif
      delayMicroseconds(deadtime);
      motor1 = OUTPUT_NEUTRAL;
    }
    else if (desired_state == OUTPUT_HIGH)
    {
// turn pmos on
#ifndef INVERTED_OUTPUTS
      digitalWrite(motor1_PMOS, LOW);
      digitalWrite(motor1_NMOS, LOW);
#else
      digitalWrite(motor1_PMOS, HIGH);
      digitalWrite(motor1_NMOS, HIGH);
#endif
      motor1 = OUTPUT_HIGH;
    }
    else if (desired_state == OUTPUT_LOW)
    {
// turn pmos off
#ifndef INVERTED_OUTPUTS
      digitalWrite(motor1_PMOS, HIGH);
      digitalWrite(motor1_NMOS, LOW);
#else
      digitalWrite(motor1_PMOS, LOW);
      digitalWrite(motor1_NMOS, HIGH);
#endif
      delayMicroseconds(deadtime);
      motor1 = OUTPUT_NEUTRAL;

      // now turn on the mos
      output_fsm(OUTPUT_LOW);
    }
    else
    {
#ifndef INVERTED_OUTPUTS
      digitalWrite(motor1_PMOS, HIGH);
      digitalWrite(motor1_NMOS, LOW);
#else
      digitalWrite(motor1_PMOS, LOW);
      digitalWrite(motor1_NMOS, HIGH);
#endif
      motor1 = OUTPUT_NEUTRAL;
    }
  }
  else if (motor1 == OUTPUT_LOW)
  {
    if (desired_state == OUTPUT_NEUTRAL)
    {
// turn both MOS OFF
#ifndef INVERTED_OUTPUTS
      digitalWrite(motor1_PMOS, HIGH);
      digitalWrite(motor1_NMOS, LOW);
#else
      digitalWrite(motor1_PMOS, LOW);
      digitalWrite(motor1_NMOS, HIGH);
#endif
      delayMicroseconds(deadtime);
      motor1 = OUTPUT_NEUTRAL;
    }
    else if (desired_state == OUTPUT_HIGH)
    {
// turn nmos off
#ifndef INVERTED_OUTPUTS
      digitalWrite(motor1_PMOS, HIGH);
      digitalWrite(motor1_NMOS, LOW);
#else
      digitalWrite(motor1_PMOS, LOW);
      digitalWrite(motor1_NMOS, HIGH);
#endif
      delayMicroseconds(deadtime);
      motor1 = OUTPUT_NEUTRAL;

      output_fsm(OUTPUT_HIGH);
    }
    else if (desired_state == OUTPUT_LOW)
    {
// turn nmos on
#ifndef INVERTED_OUTPUTS
      digitalWrite(motor1_PMOS, HIGH);
      digitalWrite(motor1_NMOS, HIGH);
#else
      digitalWrite(motor1_PMOS, LOW);
      digitalWrite(motor1_NMOS, LOW);
#endif
      motor1 = OUTPUT_LOW;
    }
    else
    {
#ifndef INVERTED_OUTPUTS
      digitalWrite(motor1_PMOS, HIGH);
      digitalWrite(motor1_NMOS, LOW);
#else
      digitalWrite(motor1_PMOS, LOW);
      digitalWrite(motor1_NMOS, HIGH);
#endif
      motor1 = OUTPUT_NEUTRAL;
    }
  }
  else
  {
#ifndef INVERTED_OUTPUTS
    digitalWrite(motor1_PMOS, HIGH);
    digitalWrite(motor1_NMOS, LOW);
#else
    digitalWrite(motor1_PMOS, LOW);
    digitalWrite(motor1_NMOS, HIGH);
#endif
    motor1 = OUTPUT_NEUTRAL;
  }
}
