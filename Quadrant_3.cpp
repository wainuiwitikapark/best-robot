#include <stdio.h>
#include <time.h>

//loads specific methods from the ENGR101 library
extern "C" int init(int d_lev);
extern "C" int Sleep (int sec, int usec);
extern "C" int set_motor(int motor, int speed);
extern "C" int take_picture();
extern "C" char get_pixel(int row, int col, int color);\
void turn_left();
void turn_around();

int main()
{
    //This sets up the RPi hardware and ensures
    //everything is working correctly
    init(0);

    int current_error; //keeps error of one image process
    int previous_error; //holds previous error
    int error_diff; //gets the difference between the current and previous error
    int total_error = 0; //holds total error of all images
    int pixelTot = 0;

    double error_period = 0; //gets time for one image process for derivative use
    clock_t start;
    clock_t now;

    float kd = 0; //derivative constant
    int derivative_signal = 0; //used with kd and set_motor
    float ki = 0; //integral constant
    int integral_signal = 0; //used with ki and set_motor
    float kp = 0.0015; //proportional constant
    int proportional_signal = 0; //used with kp and set_motor

    int default_speed = 35;


    while(true){//line - will break when walls detected

        //clock_gettime(CLOCK_REALTIME, &start); //sets start
        start = clock();
        take_picture(); //gets a picture of the line
        current_error = 0; //reset to 0
        proportional_signal = 0; //reset to 0
        pixelTot = 0;

        for (int i = 0; i < 320; i++){ //traverses a horizontal line
            int w = get_pixel(i, 120, 3); //gets brightness at each pixel
            //handles white noise
            if (w < 100){
                w = 0;
            } else {
                w = 1;
                pixelTot += 1;
            }
            current_error += (i-160) * w; //if line in centre - current e = 0
        }

        //handles quadrant 3 cases
        if ((current_error < 500 && current_error > -500 && pixelTot > 300) || (current_error < 0 && pixelTot == 160)){
            turn_left();
        }
        else if (current_error > 0 && pixelTot == 160){
            set_motor(2, default_speed);
            set_motor(1, default_speed);
        }
        else if (pixelTot == 0){
            turn_around();
        }
        else{
            //gets the time to grab a new image
            now = clock();
            error_period = ((double)(now - start))/CLOCKS_PER_SEC;

            error_diff = current_error - previous_error;
            derivative_signal = (error_diff/error_period)*kd;

            previous_error = current_error;
            total_error += current_error; //totals all the errors calculated

            proportional_signal = current_error*kp;
            integral_signal = total_error*ki;//related to total error from all images

            //set motor speeds

            int right_motor = default_speed - proportional_signal - integral_signal + derivative_signal;
            int left_motor = default_speed + proportional_signal + integral_signal - derivative_signal;
            set_motor(2, right_motor); //right
            set_motor(1, left_motor); //left
        }
    }
    return 0;
}

void turn_left(){
    set_motor(2, 30);//left
    set_motor(1, 60);//right
    Sleep(0,800000); //time for a 90 degree left turn
    set_motor(2, 0);
    set_motor(1, 0);
    Sleep(0,500000);
    set_motor(2, -40);
    set_motor(1, -40);
    Sleep(1,000000);
    set_motor(2, 0);
    set_motor(1, 0);
    printf("left");
}


void turn_around(){
    set_motor(2, 40);
    set_motor(1, 40);
    Sleep(1, 350000); //time for a little overshoot
    set_motor(2, 40);
    set_motor(1, -40);
    Sleep(1,300000); //time for a 180 degree turn
    set_motor(2, 0);
    set_motor(1, 0);
}

void turn_around(){
    set_motor(2, 40);
    set_motor(1, 40);
    Sleep(1, 350000); //time for a little overshoot
    set_motor(2, 40);
    set_motor(1, -40);
    Sleep(1,300000); //time for a 180 degree turn
    set_motor(2, 0);
    set_motor(1, 0);
}
