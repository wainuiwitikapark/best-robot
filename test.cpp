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
void move_straight();



int main()
{
    //This sets up the RPi hardware and ensures
    //everything is working correctly
    init(0);
    move_straight();
//    while(true){
//        take_picture();
//        int error = 0;
//        for (int i = 0; i < 320; i++){
//            int w = get_pixel(120, i, 3);
//            if (w < 200){
//                w = 0;
//            } else {
//                w = 1;
//            }
//            error += (i-160) * w;
//        }
//        if (error > 0){
//            turn_left();
//        } else if (error < 0){
//            turn_right();
//        } else{
//            move_straight();
//        }
//    }

    return 0;
}

void move_straight()
{
    set_motor(1, 255);
    set_motor(2, 255);
    Sleep(2, 000000);
    set_motor(1, 0);
    set_motor(2, 0);
}

