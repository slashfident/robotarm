#include <Servo.h>

Servo servo_1;
Servo servo_2;
Servo servo_3;

byte const x_in = A6;
byte const y_in = A7;
byte const z_in = A3;

word x_read = 0;
word y_read = 0;
word z_read = 0;

word x_base = 0;
word y_base = 0;
word z_base = 0;

int x = 90;
int y = 90;
int z = 90;

unsigned long prev_millis = 0;

void setup() {
	servo_1.attach(10);
	servo_2.attach(7);
	servo_3.attach(3);

	pinMode(x_in, INPUT);
	pinMode(y_in, INPUT);
	pinMode(z_in, INPUT_PULLUP);

	for (unsigned i = 0; i < 20; ++i) {
		delay(5);
		x_base += analogRead(x_in);
		y_base += analogRead(y_in);
		z_base += analogRead(z_in);
	}

	x_base /= 20;
	y_base /= 20;
	z_base /= 20;

	x_read = x_base;
	y_read = y_base;
	z_read = z_base;

	Serial.begin(9600);
}

void loop() {
	if (millis() - prev_millis > 50) {
		prev_millis = millis();

		x_read = analogRead(x_in);
		if (x_read > x_base*1.2)
			x = min(x + 3, 180);
		else if (x_read < x_base*0.8)
		  x = max(x - 3, 0);
		Serial.print(x); Serial.print(", ");

		y_read = analogRead(y_in);
		if (y_read > y_base*1.2)
			y = min(y + 3, 180);
		else if (y_read < y_base*0.8)
		  y = max(y - 3, 0);
		Serial.print(y); Serial.print(", ");

		z_read = analogRead(z_in);
		if (z_read > z_base*1.2)
			z = min(z + 3, 180);
		else if (z_read < z_base*0.8)
		  z = max(z - 3, 0);
		Serial.println(z);

		servo_1.write(z);
		servo_2.write(y);
		servo_3.write(x);
	}
		
	delay(2);
}
