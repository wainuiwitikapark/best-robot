#include <stdio.h>
#include <time.h>

//loads specific methods from the ENGR101 library
extern "C" int init(int d_lev);
extern "C" int Sleep (int sec, int usec);
extern "C" int set_motor(int motor, int speed);
extern "C" int write_digital(int chan, char level);
extern "C" int read_digital(int chan, int direct);
extern "C" int select_IO(int chan, int direct);
extern "C" int read_analog(int ch_adc);
extern "C" int take_picture();
extern "C" char get_pixel(int row, int col, int color);
extern "C" int connect_to_server( char server_addr[15],int port);
extern "C" int send_to_server(char message[6]);
extern "C" int receive_from_server(char message[6]);
void gate_opening();



int main()
{
    //This sets up the RPi hardware and ensures
    //everything is working correctly
    init(0);

    //gate_opening();

    int current_error; //keeps error of one image process
    int previous_error; //holds previous error
    int error_diff; //gets the difference between the current and previous error
    int total_error = 0; //holds total error of all images
    int pixelTot = 0;

    double error_period = 0; //gets time for one image process for derivative use
    //struct timespec start;  //holds start time
    //struct timespec now; //holds end time
    clock_t start;
    clock_t now;

    float kd = 0; //derivative constant
    int derivative_signal = 0; //used with kd and set_motor
    float ki = 0; //integral constant
    int integral_signal = 0; //used with ki and set_motor
    float kp = 0.001; //proportional constant
    int proportional_signal = 0; //used with kp and set_motor




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
            if (w < 120){
                w = 0;
            } else {
                w = 1;
                pixelTot += 1;
            }
            current_error += (i-160) * w; //if line in centre - current e = 0
        }

//      if (pixelTot <5){
//          set_motor(2, -30);
//          set_motor(1, -30);
//          continue;
//      }

        //gets the time to grab a new image
        //        clock_gettime(CLOCK_REALTIME, &now); //sets now
        now = clock();
        //error_period = now.tv_sec - start.tv_sec;
        //error_period = error_period + (now.tv_nsec - start.tv_nsec)/1000000000.0;
        error_period = ((double)(now - start))/CLOCKS_PER_SEC;

        error_diff = current_error - previous_error;
        derivative_signal = (error_diff/error_period)*kd;

        previous_error = current_error;
        total_error += current_error; //totals all the errors calculated

        proportional_signal = current_error*kp;
        integral_signal = total_error*ki;//related to total error from all images

        //set motor speeds, default speed is 20
        set_motor(2, 30 - proportional_signal - integral_signal + derivative_signal); //assu$
        set_motor(1, 30 + proportional_signal + integral_signal - derivative_signal); //assu$
    }

    while (true){//maze

    }

    return 0;
}


void gate_opening()
{
    //gate closed
    connect_to_server("130.195.6.196", 1024); //connects to gate server
    send_to_server("Please");//requests password
    char message[6];//initialises variable to store password
    receive_from_server(message);//sets variable to password
    printf("Password: %s", message);
    send_to_server(message);//sends password to server
    //gate opens
}


