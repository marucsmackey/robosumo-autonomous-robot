//
// filename: RoboSumoJuri 7.0
// author: Marcus Mackey
// date: 03/12/25
//

int state = 12; // start by driving forward to find edge

// motor pins
const int LEFT_FWD  = 5;
const int LEFT_REV  = 3;
const int RIGHT_FWD = 6;
const int RIGHT_REV = 9;

void setup()
{
  pinMode(LEFT_FWD, OUTPUT);
  pinMode(LEFT_REV, OUTPUT);
  pinMode(RIGHT_FWD, OUTPUT);
  pinMode(RIGHT_REV, OUTPUT);
}

void loop()
{
  int fls, frs;

  int ed = 512; // edge detection threshold

  // timing values
  unsigned long start_turn_time = 27830;
  unsigned long go_to_centre_time = 28695;
  unsigned long stop_at_centre_time = 28000;

  fls = analogRead(1);
  frs = analogRead(0);

  if (state == 12) // drive forward to find edge
  {
    motors(255, 235);

    if (fls > ed) state = 13;
    if (frs > ed) state = 14;
  }

  else if (state == 13) // reverse then turn right
  {
    motors(-255, -255);
    delay(150);

    motors(255, -255);
    delay(150);

    state = 2;
  }

  else if (state == 14) // reverse then turn left
  {
    motors(-255, -255);
    delay(150);

    motors(-255, 255);
    delay(150);

    state = 3;
  }

  else if (state == 2) // turn back onto black from left edge
  {
    motors(255, -255);

    if (fls < ed) state = 4;
  }

  else if (state == 3) // turn back onto black from right edge
  {
    motors(-255, 255);

    if (frs < ed) state = 11;
  }

  else if (state == 4) // follow edge from left side
  {
    motors(255, 255);

    if (fls > ed) state = 5;
    if (millis() > start_turn_time) state = 7;
    if (frs > ed) state = 3;
  }

  else if (state == 11) // follow edge from right side
  {
    motors(255, 255);

    if (frs > ed) state = 6;
    if (millis() > start_turn_time) state = 8;
    if (fls > ed) state = 2;
  }

  else if (state == 5) // correct left edge without reversing
  {
    motors(255, 0);

    if (fls < ed) state = 4;
    if (millis() > start_turn_time) state = 7;
    if (frs > ed) state = 3;
  }

  else if (state == 6) // correct right edge without reversing
  {
    motors(0, 255);

    if (frs < ed) state = 11;
    if (millis() > start_turn_time) state = 8;
    if (fls > ed) state = 2;
  }

  else if (state == 7) // turn right towards centre
  {
    motors(255, 0);

    if (millis() > go_to_centre_time) state = 9;
  }

  else if (state == 8) // turn left towards centre
  {
    motors(0, 255);

    if (millis() > go_to_centre_time) state = 9;
  }

  else if (state == 9) // drive towards centre
  {
    motors(255, 255);

    if (millis() > stop_at_centre_time) state = 10;
    if (fls < ed) state = 15;
    if (frs < ed) state = 16;
  }

  else if (state == 10) // stop in centre
  {
    motors(0, 0);
  }

  else if (state == 15) // realign from left
  {
    motors(0, 255);

    if (fls < ed && frs < ed) state = 17;
  }

  else if (state == 16) // realign from right
  {
    motors(255, 0);

    if (fls < ed && frs < ed) state = 17;
  }

  else if (state == 17) // reverse towards centre
  {
    motors(-255, -255);

    if (millis() > stop_at_centre_time) state = 10;
  }
}

// positive speed = forward
// negative speed = reverse
void motors(int left_speed, int right_speed)
{
  if (left_speed > 0)
  {
    analogWrite(LEFT_FWD, left_speed);
    digitalWrite(LEFT_REV, LOW);
  }

  else if (left_speed < 0)
  {
    analogWrite(LEFT_FWD, 0);
    analogWrite(LEFT_REV, -left_speed);
  }

  else
  {
    analogWrite(LEFT_FWD, 0);
    analogWrite(LEFT_REV, 0);
  }

  if (right_speed > 0)
  {
    analogWrite(RIGHT_FWD, right_speed);
    digitalWrite(RIGHT_REV, LOW);
  }

  else if (right_speed < 0)
  {
    analogWrite(RIGHT_FWD, 0);
    analogWrite(RIGHT_REV, -right_speed);
  }

  else
  {
    analogWrite(RIGHT_FWD, 0);
    analogWrite(RIGHT_REV, 0);
  }
}
