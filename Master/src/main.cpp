// #include <Common.h>

// // IMU
// #include <Camera.h>
// // Bluetooth
// #include <Avoidance.h>

// #include <MotorArray.h>



// #include <BallData.h>
// #include <LineData.h>
// #include <Vector.h>
// #include <MoveData.h>


// float heading;
// BallData ball;
// Vector robot;




// BallData recieve(){

//     BallData ballData = BallData();

//     while(SLAVE_SERIAL.available() >= SLAVE_PACKET_SIZE){
//         if (SLAVE_SERIAL.read() == SLAVE_START_BYTE && SLAVE_SERIAL.peek() == SLAVE_START_BYTE){
//             uint8_t dataBuffer[SLAVE_PACKET_SIZE - 2] = {0};

//             for (uint8_t i = 0; i < SLAVE_PACKET_SIZE - 2; i++) {
//                 dataBuffer[i] = SLAVE_SERIAL.read();
//             }

//             ballData = BallData(word(dataBuffer[0], dataBuffer[1]),
//                                 word(dataBuffer[2], dataBuffer[3]));

//             avoid.data(ballData, LineData(word(dataBuffer[4], dataBuffer[5]),
//                                           word(dataBuffer[6], dataBuffer[7]) / 100));
//         }
//     }

//     return ballData;
// }


// MoveData moveToCoord(Vector target){

//     if (camera.attack.visible() || camera.defend.visible()){
//         // Calculate Movement towards target coords
//         Vector diff = target - robot;

//         if (diff.mag >= COORD_THRESHOLD_DISTANCE){
//             // Calculate direction towards coords
//             return MoveData(floatMod(diff.arg - heading, 360.0f), abs(coordPID.update(diff.mag, 0.0f)));
//         }
//     }

//     // Cannot calculate movement or at coord, stop
//     return MoveData();

// }




// MoveData calculateOrbit(){
//     MoveData move = MoveData();

//     move.angle = floatMod(ball.angle + ball.orbitAngle(), 360.0f);

//     // If ball is close and infront of capture zone, surge forwards and try to kick, else move at normal speed
//     if (ball.strength > ATTACK_SURGE_STRENGTH && angleIsInside(360-ATTACK_CAPTURE_ANGLE, ATTACK_CAPTURE_ANGLE, ball.angle)){
//         move.speed = ORBIT_SURGE_SPEED;
//         //* Try to kick

//     } else {
//         move.speed = ORBIT_SLOW_SPEED + (ORBIT_FAST_SPEED - ORBIT_SLOW_SPEED) * (1.0f - abs(ball.orbitAddition) / 90.0f);
//     }

//     #if DEBUG_ORBIT
//         Serial.printf("Orbit Data:\tAngle: %i,\t Speed: %i,\t Angle Addition: %f \n", move.angle, move.speed, ball.orbitAddition);
//     #endif

//     return move;


// }


// MoveData calculateAttack(){

//     if (ball.visible()){
//         return MoveData(calculateOrbit(), (camera.attack.visible() ? -attackGoalTrackPID.update((floatMod(camera.attack.angle + 180.0f, 360.f) - 180.0f), 0.0f) : NO_CORRECTION));
    
//     } else {
//         return moveToCoord(Vector(NO_BALL_COORD_I, NO_BALL_COORD_J));
//     }

// }


// MoveData calculateDefense(){

//     if (ball.visible()){

//         if (angleIsInside(360.0f-DEFEND_CAPTURE_ANGLE, DEFEND_CAPTURE_ANGLE, ball.angle) && ball.strength > DEFEND_SURGE_STRENGTH && robot.j < DEFEND_SURGE_J){
//             //* switch BT
//             return MoveData(calculateOrbit(), camera.defend.visible() ? (-defendGoalTrackPID.update((floatMod(camera.defend.angle + 180.0f, 360.0f) - 180.0f), 180.0f)) : NO_CORRECTION);
        
//         } else if (!angleIsInside(270.0f, 90.0f, ball.angle)){
//             return calculateOrbit();
            
//         } else {
//             float iMove = -iPID.update((ball.angle > 180.0f ? ball.angle - 360.0f : ball.angle), 0.0f);
//             float jMove = camera.defend.visible() ? jPID.update(camera.defend.calculateCentimeter(), DEFEND_DISTANCE_CM) : -15;
//             return MoveData(floatMod(toDegrees(atan2(jMove, iMove)), 360.0f), sqrtf(jMove * jMove + iMove + iMove),
//                             camera.defend.visible() ? (-defendGoalTrackPID.update((floatMod(camera.defend.angle + 180.0f, 360.0f) - 180.0f), 180.0f)) : NO_CORRECTION);
//         }
//     } else {
//         return moveToCoord(Vector(0.0f, DEFEND_GOAL_J + DEFEND_DISTANCE_CM));
//     }
// }






// void setup(){ SLAVE_SERIAL.begin(TEENSY_BAUD); }


// void loop(){

//     ball = recieve();
//     // IMU Data

//     robot = camera.update(heading);

//     // #if SWITCHING
//     //     // Role role = 
//     // #endif

//     MoveData movement = avoid.update(MoveData(), heading);

//     if (movement.correction == NO_CORRECTION) { movement.correction = roundf(imuPID.update((floatMod(heading + 180.0f, 360.0f) - 180.0f), 0.0f)); }

//     motors.update(movement);

//     int arr[10] = {0};

//     memset(arr, 100, sizeof(arr));

// }


#include <Arduino.h>
#include "Common.h"


#include "States.h"

#include "TSSPArray.h"
#include "MotorArray.h"
#include "MPU.h"
#include "LightArray.h"
#include "Camera.h"

StateMachine sm;
RobotState robotState;

void setup(){
    Serial.begin(9600);
    Serial.println("Setup Complete");

    sm = StateMachine(&States::Attack::orbit);

    pinMode(LED_BUILTIN, OUTPUT);
    digitalWrite(LED_BUILTIN, LOW);

}

bool ledon = false;

#include "StatesMovement.h"

void loop(){

    for (int i = 0; i < 300; i++){
        tssp.read();
    }

    // Update Data
    tssp.update();
    mpu.update();
    lightArray.update();
    camera.update();

    // Reset Outputs
    robotState.movement = MoveData();
    robotState.canSwitch = false;

    // Update SM Data
    robotState.ball = tssp.getData();
    robotState.heading = mpu.getHeading();
    robotState.line = lightArray.getData();
    robotState.attackGoal = camera.getAttackGoal();
    robotState.defendGoal = camera.getDefendGoal();
    // robotState.robot = ;

    // Update SM
    sm.update();

    // Avoidance
    States::Movement::avoidance();

    // Move Motors
    motors.update(robotState.movement);


}



// /* - Calculate Robot Position - */
//             if (attack.visible() || defend.visible()) {
//                 uint16_t angle = floatMod((attack.distance < defend.distance ? attack.angle : defend.angle) + heading, 360.0f);
//                 float distance = fminf(attack.calculateCentimeter(), defend.calculateCentimeter());

//                 int8_t i = constrain(distance * -sinf(toRadians(angle)), (-FIELD_WIDTH_CM / 2), (FIELD_WIDTH_CM / 2));
//                 int8_t j = constrain(FIELD_LENGTH_WITH_GOAL * (attack.distance < defend.distance ? 1 : -1) + (distance * -cosf(toRadians(angle))), (-FIELD_LENGTH_CM / 2), (FIELD_LENGTH_CM / 2));
//                 robotPosition = Vector(i, j);
//             } else {
//                 robotPosition = Vector();
//             }
//         }
//     }
//     return robotPosition;