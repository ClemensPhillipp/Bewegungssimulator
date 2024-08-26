#include <Servo.h>

Servo s1;  // up 'n' down
Servo s2;  // left 'n' right
Servo s3;  // door

int rounds = 50;

int default_position1 = 90;
int default_position2 = 110;
int default_position3 = 0;

int pos1 = default_position1;
int pos2 = default_position2;

void setup() {
  Serial.begin(9600);
  s1.attach(10);
  s2.attach(11);
  s3.attach(12);
  s1.write(default_position1);
  s2.write(default_position2);
  s3.write(default_position3);
}

void loop() {
  if (rounds >= 50) {
    goHome();
    openDoor();
    Serial.println("Pause");
    delay(10000);
    rounds = 0;
    closeDoor();
    delay(5000);
    Serial.println("weiter gehts");
  } else {
    tilt(random(default_position1, default_position1 + 20), 20);
    rotate(random(default_position2 - 30, default_position2 + 30), 20);
    delay(300);
    rounds++;
  }
}

void openDoor() {
  Serial.println("rotateRight");
  for (int pos3 = default_position3; pos3 <= default_position3 + 45; pos3 += 1) {
    s3.write(pos3);
    delay(100);
  }
}

void closeDoor() {
  for (int pos3 = default_position3 + 45; pos3 >= 0; pos3 -= 1) {
    s3.write(pos3);
    delay(100);
  }
}

void rotate(int pos, int speed) {
  if (pos < pos2) {
    rotateRight(pos, speed);
  } else if (pos > pos2) {
    rotateLeft(pos, speed);
  }
  pos2 = pos;
}

void rotateLeft(int pos, int speed) {
  for (pos2; pos2 <= pos; pos2 += 1) {
    s2.write(pos2);
    delay(speed);
  }
}

void rotateRight(int pos, int speed) {
  for (pos2; pos2 >= pos; pos2 -= 1) {
    s2.write(pos2);
    delay(speed);
  }
}

void tilt(int pos, int speed) {
  if (pos < pos1) {
    down(pos, speed);
  } else if (pos > pos1) {
    up(pos, speed);
  }
  pos1 = pos;
}

void up(int pos, int speed) {
  for (pos1; pos1 <= pos; pos1 += 1) {
    s1.write(pos1);
    delay(speed);
  }
}

void down(int pos, int speed) {
  for (pos1; pos1 >= pos; pos1 -= 1) {
    s1.write(pos1);
    delay(speed);
  }
}

void goHome() {
  tilt(default_position1, 50);
  rotate(default_position2, 50);
}
