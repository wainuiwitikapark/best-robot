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
extern "C" int send_to_server(char message[24]);
extern "C" int receive_from_server(char message[24]);
void move_straight();
void turn_left();
void turn_right();
void gate_opening();



int main()
{
    //This sets up the RPi hardware and ensures
    //everything is working correctly
    init(0);

    gate_opening();

//    while(true){//line - will break when walls detected
//        take_picture();
//        int error = 0;
//        for (int i = 0; i < 320; i++){
//            int w = get_pixel(120, i, 3);
//            //handles white noise
//            if (w < 200){
//                w = 0;
//            } else {
//                w = 1;
//            }
//            error += (i-160) * w;
//        }
//        if (error > 10){//error margin not going to be exactly 0 ever
//            turn_right();
//        } else if (error < 10){
//            turn_left();
//        } else{
//            move_straight();
//        }
//    }

//    while (true){//maze
//
//    }

    return 0;
}



void move_straight()
{
    set_motor(1, 255); //right wheel
    set_motor(2, 255); //left wheel

}

void turn_right()
{
    set_motor(1, -255); //right backwards
    set_motor(2, 255); //left forwards

}

void turn_left()
{
    set_motor(1, 255);//right forwards
    set_motor(2, -255);//left backwards

}

void gate_opening()
{
    //gate closed
    connect_to_server("130.195.6.196", 1024); //connects to gate server
    send_to_server("Please");//requests password
    char message[6];//initialises variable to store password
    receive_from_server(message);//sets variable to password
    send_to_server(message);//sends password to server
    //gate opens
}

