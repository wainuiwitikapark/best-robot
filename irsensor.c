#include <stdio.h>
include <unistd.h>

extern "C" int init(int d_lev);
extern "C" int read_analog(int ch_adc);
extern "C" int set_motor(int motor, int speed);

int default_speed = 30;

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
		//Assuming front sensor is port 0, 1 is left and 2 is right
		sensor1_reading = ReadAnalog(0);
		sensor2_reading = ReadAnalog(1);
		sensor3_reading = ReadAnalog(2);
		
		
		if (check_front() == 0 && check_left() == 1 && check_right() == 1)
		{
		  forwards();
		}
		
		else if (check_front() == 1 && check_left() == 1 && check_right() == 1)
		{
		  stop();
		  turn_around();
		}

		else if (check_left() = 0 && check_right() == 1 && check_front == 1)
		{
		  stop();
		  turn_left();
		}

		else if (check_right() == 0 && check_left() == 1 && check_front == 1)
		{
		  stop();
		  turn_left();
		}
		else if (check_front() == 0 && check_left() == 0)
		{
			stop();
			turn_left();
		}
		else if (check_front() == 0)
		{
			forwards();
		}
		
	}
}

// The below code assums motor_1 is left and motor_2 is right

void stop()
{
    set_motor(2, 0);
    set_motor(1, 0);
	sleep(100;
}

void forwards(){
    set_motor(2, default_speed);
    set_motor(1, default_speed);
}

void turn_around(){
    set_motor(1, default_speed);
    set_motor(2, 0);
	sleep(2000);
}

void turn_left(int factor){
	
    int motor_1 = default_speed;
    int motor_2 = 0;

    set_motor(1, motor_1);
    set_motor(2, motor_2);
	sleep(1000);
}

void turn_right(int factor){
    int motor_1 = 0;
    int motor_2 = default_speed;

    set_motor(1, motor_1);
    set_motor(2, motor_2);
	sleep(1000);
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
