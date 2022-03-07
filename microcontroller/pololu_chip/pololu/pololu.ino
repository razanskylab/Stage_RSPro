/*
	File: pololu.ino
	Author: Urs Hofmann
	Mail: mail@hofmannu.org
	Date: 08.03.2022
*/

#include "controllerboard.h"

void setup()
{

}

void loop()
{
	controllerboard myCont;
	while (1)
	{
		myCont.read_command();
	}
}