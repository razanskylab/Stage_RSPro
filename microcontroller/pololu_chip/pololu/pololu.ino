#include "controllerboard.h"

controllerboard myCont;

void setup()
{
	myCont.identify();
}

void loop()
{
	myCont.read_command();
}