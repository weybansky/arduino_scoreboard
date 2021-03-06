#include <IRremote.h>

#include <PinChangeInt.h>

int RECV_PIN = A0;
IRrecv irrecv(RECV_PIN);
decode_results results;

const int a = 5;
const int b = 6;
const int c = 7;
const int d = 8;
const int e = 9;
const int f = 10;
const int g = 11;
const int dot = 12;

const int common1 = A1;
const int common2 = A2;
const int common3 = A3;
const int common4 = A4;

const int delayy = 5;
// const int delayy_btn = 450;

String number_to_be_displayed = "0000";
String charOne, charTwo, charThree, charFour;
volatile int charA, charB, charC, charD;

#define buttonA A5
#define buttonB 2
#define buttonC 3
#define buttonD 4

void setup()
{
	pinMode(a, OUTPUT);
	pinMode(b, OUTPUT);
	pinMode(c, OUTPUT);
	pinMode(d, OUTPUT);
	pinMode(e, OUTPUT);
	pinMode(f, OUTPUT);
	pinMode(g, OUTPUT);
	pinMode(dot, OUTPUT);
	pinMode(common1, OUTPUT);
	pinMode(common2, OUTPUT);
	pinMode(common3, OUTPUT);
	pinMode(common4, OUTPUT);

	charOne = number_to_be_displayed.charAt(0);
	charTwo = number_to_be_displayed.charAt(1);
	charThree = number_to_be_displayed.charAt(2);
	charFour = number_to_be_displayed.charAt(3);
	charA = charOne.toInt();
	charB = charTwo.toInt();
	charC = charThree.toInt();
	charD = charFour.toInt();

	pinMode(buttonA, INPUT_PULLUP);
	attachPinChangeInterrupt(buttonA, button_press, RISING); // library

	// interrupts();
	pinMode(buttonB, INPUT_PULLUP);
	attachInterrupt(digitalPinToInterrupt(buttonB), button_press, RISING);

	pinMode(buttonC, INPUT_PULLUP);
	attachInterrupt(digitalPinToInterrupt(buttonC), button_press, RISING);

	pinMode(buttonD, INPUT_PULLUP);
	attachPinChangeInterrupt(buttonD, button_press, RISING); //library

	Serial.begin(115200);
	// In case the interrupt driver crashes on setup, give a clue
	// to the user what's going on.
	Serial.println("Enabling IRin");
	irrecv.enableIRIn(); // Start the receiver
	Serial.println("Enabled IRin");
}

void loop()
{
	noInterrupts();
	remote_press();
	// button_press();
	interrupts();
	write_num_to_segment('a', charA);
	delay(delayy);
	write_num_to_segment('b', charB);
	delay(delayy);
	write_num_to_segment('c', charC);
	delay(delayy);
	write_num_to_segment('d', charD);
	delay(delayy);
	Serial.print(charA);
	Serial.print(charB);
	Serial.print(charC);
	Serial.println(charD);
}

void button_press_B()
{
	// if (digitalRead(buttonB) == HIGH)
	// {
		charB++;
		if (charB > 10)
		{
			charB = 0;
		}
	// }
}

void button_press()
{
	if (digitalRead(buttonA) == HIGH)
	{
		charA++;
		if (charA > 10)
		{
			charA = 0;
		}
	}
	if (digitalRead(buttonB) == HIGH)
	{
		charB++;
		if (charB > 10)
		{
			charB = 0;
		}
	}
	if (digitalRead(buttonC) == HIGH)
	{
		charC++;
		if (charC > 10)
		{
			charC = 0;
		}
	}
	if (digitalRead(buttonD) == HIGH)
	{
		charD++;
		if (charD > 10)
		{
			charD = 0;
		}
	}
}

void remote_press()
{
	if (irrecv.decode(&results))
	{
		Serial.println(results.value, HEX);
		digitalWrite(13, HIGH); //indicate remote press
		switch (results.value)
		{
		case 0xFF30CF:
			charA++;
			if (charA > 10)
			{
				charA = 0;
			}
			Serial.println("ADD TO A");
			break;
		case 0xFF18E7:
			charB++;
			if (charB > 10)
			{
				charB = 0;
			}
			Serial.println("ADD TO B");
			break;
		case 0xFF7A85:
			charC++;
			if (charC > 10)
			{
				charC = 0;
			}
			Serial.println("ADD TO C");
			break;
		case 0xFF10EF:
			charD++;
			if (charD > 10)
			{
				charD = 0;
			}
			Serial.println("ADD TO D");
			break;
		}
		digitalWrite(13, LOW); //indicate remote press
		irrecv.resume();	   // Receive the next value
	}
}

void write_num_to_segment(char segment, int digit)
{
	display_segment(segment);
	display_digit(digit);
}

void display_segment(char segment)
{
	switch (segment)
	{
	case 'a':
		digitalWrite(common1, LOW);
		digitalWrite(common2, HIGH);
		digitalWrite(common3, HIGH);
		digitalWrite(common4, HIGH);
		break;
	case 'b':
		digitalWrite(common1, HIGH);
		digitalWrite(common2, LOW);
		digitalWrite(common3, HIGH);
		digitalWrite(common4, HIGH);
		break;
	case 'c':
		digitalWrite(common1, HIGH);
		digitalWrite(common2, HIGH);
		digitalWrite(common3, LOW);
		digitalWrite(common4, HIGH);
		break;
	case 'd':
		digitalWrite(common1, HIGH);
		digitalWrite(common2, HIGH);
		digitalWrite(common3, HIGH);
		digitalWrite(common4, LOW);
		break;
	}
}

void display_digit(int digit)
{
	switch (digit)
	{
	case 0:
		digit0();
		break;
	case 1:
		digit1();
		break;
	case 2:
		digit2();
		break;
	case 3:
		digit3();
		break;
	case 4:
		digit4();
		break;
	case 5:
		digit5();
		break;
	case 6:
		digit6();
		break;
	case 7:
		digit7();
		break;
	case 8:
		digit8();
		break;
	case 9:
		digit9();
		break;
	case 10:
		digitoff();
		break;
	}
}

void digit0()
{
	digitalWrite(a, HIGH);
	digitalWrite(b, HIGH);
	digitalWrite(c, HIGH);
	digitalWrite(d, HIGH);
	digitalWrite(e, HIGH);
	digitalWrite(f, HIGH);
	digitalWrite(g, LOW);
}

void digit1()
{
	digitalWrite(a, LOW);
	digitalWrite(b, HIGH);
	digitalWrite(c, HIGH);
	digitalWrite(d, LOW);
	digitalWrite(e, LOW);
	digitalWrite(f, LOW);
	digitalWrite(g, LOW);
}

void digit2()
{
	digitalWrite(a, HIGH);
	digitalWrite(b, HIGH);
	digitalWrite(c, LOW);
	digitalWrite(d, HIGH);
	digitalWrite(e, HIGH);
	digitalWrite(f, LOW);
	digitalWrite(g, HIGH);
}

void digit3()
{
	digitalWrite(a, HIGH);
	digitalWrite(b, HIGH);
	digitalWrite(c, HIGH);
	digitalWrite(d, HIGH);
	digitalWrite(e, LOW);
	digitalWrite(f, LOW);
	digitalWrite(g, HIGH);
}

void digit4()
{
	digitalWrite(a, LOW);
	digitalWrite(b, HIGH);
	digitalWrite(c, HIGH);
	digitalWrite(d, LOW);
	digitalWrite(e, LOW);
	digitalWrite(f, HIGH);
	digitalWrite(g, HIGH);
}

void digit5()
{
	digitalWrite(a, HIGH);
	digitalWrite(b, LOW);
	digitalWrite(c, HIGH);
	digitalWrite(d, HIGH);
	digitalWrite(e, LOW);
	digitalWrite(f, HIGH);
	digitalWrite(g, HIGH);
}

void digit6()
{
	digitalWrite(a, HIGH);
	digitalWrite(b, LOW);
	digitalWrite(c, HIGH);
	digitalWrite(d, HIGH);
	digitalWrite(e, HIGH);
	digitalWrite(f, HIGH);
	digitalWrite(g, HIGH);
}

void digit7()
{
	digitalWrite(a, HIGH);
	digitalWrite(b, HIGH);
	digitalWrite(c, HIGH);
	digitalWrite(d, LOW);
	digitalWrite(e, LOW);
	digitalWrite(f, LOW);
	digitalWrite(g, LOW);
}

void digit8()
{
	digitalWrite(a, HIGH);
	digitalWrite(b, HIGH);
	digitalWrite(c, HIGH);
	digitalWrite(d, HIGH);
	digitalWrite(e, HIGH);
	digitalWrite(f, HIGH);
	digitalWrite(g, HIGH);
}

void digit9()
{
	digitalWrite(a, HIGH);
	digitalWrite(b, HIGH);
	digitalWrite(c, HIGH);
	digitalWrite(d, HIGH);
	digitalWrite(e, LOW);
	digitalWrite(f, HIGH);
	digitalWrite(g, HIGH);
}

void digitdot()
{
	digitalWrite(a, LOW);
	digitalWrite(b, LOW);
	digitalWrite(c, LOW);
	digitalWrite(d, LOW);
	digitalWrite(e, LOW);
	digitalWrite(f, LOW);
	digitalWrite(g, LOW);
	digitalWrite(dot, HIGH);
}

void digitoff()
{
	digitalWrite(a, LOW);
	digitalWrite(b, LOW);
	digitalWrite(c, LOW);
	digitalWrite(d, LOW);
	digitalWrite(e, LOW);
	digitalWrite(f, LOW);
	digitalWrite(g, LOW);
	digitalWrite(dot, LOW);
}
