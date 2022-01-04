#ifndef controllerboard_h
#define controllerboard_h

#include <cstdint>
#include <arduino.h>

class controllerboard
{
	private:
		const uint32_t baudRate = 9600;
		const uint32_t pinLedSerial = 32;
		const uint32_t pinLedMotor = 31;
		const uint32_t pinLedSensor = 30;
		const uint32_t pinDir = 29;
		const uint32_t pinStep = 28;

		bool stepPolarity = 0; 

		// float pos = 0.1; // position of the stage [mm]
		float stepsPerSec = 1000; // velocity [steps / s]
		int32_t iStep = 0; // current step count
		float pitch = 8.0; // distance in mm / rev
		float stepsPerRev = 400.0; // number of steps / rev

	public:
		controllerboard();
		void identify();
		void wait_serial(const uint16_t nSerial);
		void read_command(); // controller decision cascade / state machine
		void clear_serial(); // flush all the serial input
		void confirm_ready(); // tell serial that we are done

		void send_pos(); // returns the position to matlab

		void goto_pos(const float goalPos); // moves to a new abs pos
		void move_steps(const int32_t nSteps); // moves the stepper by nSteps

		void send_vel(); // returns max velocity in mm/s
		void read_vel(); // read max velocity in mm/s

		void send_pitch(); // return pitch 
		void read_pitch(); // read pitch of leadscrew from matlab

		void send_stepsPerRev();
		void read_stepsPerRev();

		// input output functions
		void send_float(const float floatToSend); // send float to matlab
		float get_float(); // read float from matlab

		float get_stepsToMm() {return pitch / stepsPerRev;};
		float get_mmToSteps() {return stepsPerRev / pitch;};
};

#endif