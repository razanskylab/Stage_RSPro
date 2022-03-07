#include "controllerboard.h"

controllerboard::controllerboard()
{
	Serial.begin(baudRate);
	
	// define internal LED as an output
	pinMode(LED_BUILTIN, OUTPUT);
	digitalWrite(LED_BUILTIN, LOW);
	
	// define serial led as output
	pinMode(pinLedSerial, OUTPUT);
	digitalWrite(pinLedSerial, LOW);
	
	// define led for motor as output
	pinMode(pinLedMotor, OUTPUT);
	digitalWrite(pinLedMotor, LOW);
	
	pinMode(pinLedSensor, OUTPUT);
	digitalWrite(pinLedSensor, LOW);
	
	pinMode(pinDir, OUTPUT);
	digitalWrite(pinDir, LOW);

	pinMode(pinStep, OUTPUT);
	digitalWrite(pinStep, LOW);

	pinMode(pinEnable, OUTPUT);
	digitalWrite(pinEnable, LOW);

	pinMode(pinStandby, OUTPUT);
	digitalWrite(pinStandby, HIGH);

	// start serial communication stream
	Serial.write('r');
}

void controllerboard::identify()
{
	digitalWrite(LED_BUILTIN, HIGH);
	digitalWrite(pinLedSerial, HIGH);
	digitalWrite(pinLedMotor, HIGH);
	digitalWrite(pinLedSensor, HIGH);
	delay(100);
	digitalWrite(LED_BUILTIN, LOW);
	digitalWrite(pinLedSerial, LOW);
	digitalWrite(pinLedMotor, LOW);
	digitalWrite(pinLedSensor, LOW);
	return;
}

// makes the controller wait until a certain amount of bytes arrived
void controllerboard::wait_serial(const uint16_t nSerial)
{
	digitalWrite(pinLedSerial, HIGH);
	while (Serial.available() < nSerial)
	{
		delay(1);
	}
	digitalWrite(pinLedSerial, LOW);
	return;
}

// here goes all the controll logic of the bord
void controllerboard::read_command()
{
	wait_serial(1);
	const char request = Serial.read();
	if (request == 'i') // identify device
	{
		identify();
	}
	else if (request == 'p') // return position to MATLAB
	{
		send_pos();
	}
	else if (request == 'a') // absolute move
	{
		// read target position
		const float targetPos = get_float();
		goto_pos(targetPos);
	}
	else if (request == 't') // return pitch to MATLAB
	{
		send_pitch();
	}
	else if (request == 'y') // get pitch from MATLAB
	{
		read_pitch();
	}
	else if (request == 's') // return steps per rev
	{
		send_stepsPerRev();
	}
	else if (request == 'd') // define steps per rev
	{
		read_stepsPerRev();
	} 
	else if (request == 'w') // return velocity to PC
	{
		send_vel();
	}
	else if (request == 'v') // define velocity of stage movenment
	{
		read_vel();
	}
	else if (request == 'e') // enable motor coils
	{
		enable();
	}
	else if (request == 'o')
	{
		disable();
	}
	confirm_ready();
}

// clear the serial command line
void controllerboard::clear_serial()
{
	while (Serial.available() > 0)
		Serial.read();

	return;
}

void controllerboard::confirm_ready()
{
	Serial.write('r');
}

void controllerboard::send_pos()
{
	const float pos = ((float) iStep) * get_stepsToMm();
	send_float(pos);
	return;
}

void controllerboard::goto_pos(const float goalPos)
{
	const int32_t goalSteps = round(goalPos * get_mmToSteps());
	const int32_t deltaSteps = goalSteps - iStep;
	const int32_t absSteps = abs(deltaSteps);
	if (absSteps > 0)
	{
		digitalWrite(pinLedMotor, HIGH);
		const int32_t dirStep = (deltaSteps < 0) ? 0 : 1;
		digitalWrite(pinDir, dirStep);
		const float ss = get_stepsToMm(); // step size in mm
		float vmax = stepsPerSec * ss; // mm
		const float acc = stepsPerSqSec * ss; // mm / s2
		const float deltaS = absSteps * ss;
		
		// define end point of acceleration and start point of deceleration
		float s_1 = vmax * vmax / (2 * acc);
		float s_2 = deltaS - s_1;

		if (s_1 > s_2) // if we dont even reach full speed
		{
			s_1 = deltaS / 2;
			s_2 = deltaS / 2;
			vmax = sqrt(deltaS * acc);
		}

		float vcurr = 0;
		for (int32_t incStep = 0; incStep < absSteps; incStep++)
		{
			// calculate central position of current step
			const float s = ((float) incStep + 0.5) * ss;
			
			// calculate velocity at current step
			if (s < s_1)
			{
				vcurr = sqrt(2 * s * acc);
			}
			else if (s < s_2)
			{
				vcurr = vmax;
			}
			else
			{
				vcurr = sqrt(vmax * vmax - 2 * (s - s_2) * acc);
			}

			// convert velocity to delay
			const uint32_t tDelay = round(ss / vcurr * 1e6); // in micros

			// act accordingly
			stepPolarity = !stepPolarity;
			digitalWrite(pinStep, stepPolarity);
			delayMicroseconds(tDelay);
		}
		iStep += deltaSteps;
		digitalWrite(pinLedMotor, LOW);
	}
	return;
}

void controllerboard::send_vel()
{
	send_float(stepsPerSec * get_stepsToMm());
	return;
}

void controllerboard::read_vel()
{
	stepsPerSec = get_float() * get_mmToSteps();
	return;
}

void controllerboard::send_pitch()
{
	send_float(pitch);
	return;
}

void controllerboard::read_pitch()
{
	pitch = get_float();
	return;
}

void controllerboard::send_stepsPerRev()
{
	send_float(stepsPerRev);
	return;
}

void controllerboard::read_stepsPerRev()
{
	stepsPerRev = get_float();
	return;
}

// sends a float over serial to matlab
void controllerboard::send_float(const float floatToSend)
{
	byte bytesArray[4];
	union {
    	float float_variable;
    	byte temp_array[4];
  	} u;
  	u.float_variable = floatToSend;
  	memcpy(&bytesArray[0], u.temp_array, 4);
  	Serial.write(bytesArray, 4);
	return;
}

// receives a float over serial from matlab
float controllerboard::get_float()
{
	wait_serial(4);
	union {
		float float_variable;
		byte temp_array[4];
	} u;
	Serial.readBytes(u.temp_array, 4);
	return u.float_variable;
}

// enables the coils of our stepper motor
void controllerboard::enable()
{
	if (!isEnabled)
	{
		digitalWrite(pinLedMotor, HIGH);
		digitalWrite(pinEnable, HIGH);
		isEnabled = 1;
	}
	Serial.write('e');
	return;
}

// disables the coils of our stepper motor
void controllerboard::disable()
{
	if (isEnabled)
	{
		digitalWrite(pinLedMotor, LOW);
		digitalWrite(pinEnable, LOW);
		isEnabled = 0;
	}
	Serial.write('o');
	return;
}

