#include <stdio.h>
#include <time.h>

extern "C" int init(int d_lev);
extern "C" int read_analog(int ch_adc);
extern "C" int set_motor(int motor, int speed);

int default_speed = 40;

int main()
{
	//This sets up the hardware

	init(0);

	// Calling the function to check the wall
	check_wall();
}

// The function that contains the loop which constantly runs while the robot is moving
void check_wall()
{

	while (true){
		//Assuming front sensor is port 0, 1 is left and 2 is right, and 3 is back
		sensor1_reading = ReadAnalog(0);
		sensor2_reading = ReadAnalog(1);
		sensor3_reading = ReadAnalog(2);
		sensor4_reading = ReadAnalog(3);

		if (check_front() = 1)
		{
		  stop();
		  backwards();
		}

		if (check_back() = 1)
		{	
		  stop();
		  turn_left();
		}

		if (check_left() = 1)
		{
		  stop();
		  turn_right();
		}

		if (check_right() = 1)
		{
		  stop();
		  turn_left();
		}
	}
}

// The below code assums motor_1 is left and motor_2 is right

void stop()
{
    set_motor(2, 0);
    set_motor(1, 0);
}

void forwards(){
    set_motor(2, default_speed);
    set_motor(1, default_speed);
}

void backwards(){
    set_motor(2, -(default_speed));
    set_motor(1, -(default_speed));
}

void turn_left(int factor){
    int motor_1 = default_speed * factor;
    int motor_2 = default_speed / 2;

    set_motor(1, motor_1);
    set_motor(2, motor_2);
}

void turn_right(int factor){
    int motor_1 = default_speed / 2;
    int motor_2 = default_speed * factor;

    set_motor(1, motor_1);
    set_motor(2, motor_2);
}

// 1 is true, 0 is false

int check_front()
{
	// Reads the value from the front IR sensor
	int sensor1_reading = ReadAnalog(0);

	// If the IR sensor returns below 200, it is deemed to be too close to the wall.
	int max_distance_1 = 200;

	if (sensor1_reading < max_distance_1)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

int check_left()
{
	// Reads the value from the left IR sensor
	int sensor2_reading = ReadAnalog(1);

	// If the IR sensor returns below 200, it is deemed to be too close to the wall.
	int max_distance_2 = 200;

	if (sensor2_reading < max_distance_2)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

int check_right()
{
	// Reads the value from the right IR sensor
	int sensor3_reading = ReadAnalog(2);

	// If the IR sensor returns below 200, it is deemed to be too close to the wall.
	int max_distance_3 = 200;

	if (sensor3_reading < max_distance_3)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

int check_back()
{
	// Reads the value from the back IR sensor
	int sensor4_reading = ReadAnalog(3);

	// If the IR sensor returns below 200, it is deemed to be too close to the wall.
	int max_distance_4 = 200;

	if (sensor4_reading < max_distance_4)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}