#include <Arduino.h>
#include <Define.h>
#include <Common.h>


#include <Camera.h>




Camera Cam;


void setup() {


    Cam.init();



}

void loop() {
    Cam.update();

    Cam.newData();

}