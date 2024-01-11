#include <hexapod.h>
#include <IK.h>

// constructor
Leg::Leg(float coaxAngle, float femoreAngle, float tibiaAngle)
{
    coaxAngle = coaxAngle;
    femoreAngle = femoreAngle;
    tibiaAngle = tibiaAngle;
}

Leg::Leg()
{
    coaxAngle = 0;
    femoreAngle = 0;
    tibiaAngle = 0;
}

void Leg::initActuators(int coaxPin, int femorePin, int tibiaPin, HardwareSerial *serial)
{
    coaxJoint = new Actuator(serial, coaxPin, 340, 2340);
    femoreJoint = new Actuator(serial, femorePin, 340, 2340);
    tibiaJoint = new Actuator(serial, tibiaPin, 340, 2340);
}

void Leg::setJointsAngles(IKangles angles)
{
    coaxAngle = angles.coax;
    femoreAngle = angles.femore;
    tibiaAngle = angles.tibia;
}

void Leg::move(int sp = 1000)
{
    coaxJoint->move(coaxAngle, 90, sp);
    femoreJoint->move(femoreAngle, 100, sp);
    tibiaJoint->move(tibiaAngle, 60, sp);
}

Hexapod::Hexapod(HardwareSerial *serial)
{
    for (int i = 0; i < 6; i++){ 
        Hexapod::legs[i] = new Leg();
        if (i > 2) {
            Hexapod::legs[i]->strideMirror = -1; 
        }

        if(i != 1 && i != 4){
            if (i == 0 || i == 5) {
                legs[i]->coaxRotated = -1;
            }
            if (i == 2 || i == 3) {
                legs[i]->coaxRotated = 1;
            }    
        }

    }

    legs[0]->initActuators(right_front_coax_pin, right_front_femore_pin, right_front_tibia_pin, serial);
    legs[1]->initActuators(right_middle_coax_pin, right_middle_femore_pin, right_middle_tibia_pin, serial);
    legs[2]->initActuators(right_back_coax_pin, right_back_femore_pin, right_back_tibia_pin, serial);
 
    legs[3]->initActuators(left_front_coax_pin, left_front_femore_pin, left_front_tibia_pin, serial);
    legs[4]->initActuators(left_middle_coax_pin, left_middle_femore_pin, left_middle_tibia_pin, serial);
    legs[5]->initActuators(left_back_coax_pin, left_back_femore_pin, left_back_tibia_pin, serial);

    moveLeg(0,standPos,2000);
    moveLeg(1,standPos,2000);
    moveLeg(2,standPos,2000);
    moveLeg(3,standPos,2000);
    moveLeg(4,standPos,2000);
    moveLeg(5,standPos,2000);
    
};

void Hexapod::walk()
{
    if (status != STANDING){
        return;
    }

    status = WALKING;
    initGait();
}

void Hexapod::stop()
{
    status = STANDING;
    moveLeg(0,standPos,2000);
    moveLeg(1,standPos,2000);
    moveLeg(2,standPos,2000);
    moveLeg(3,standPos,2000);
    moveLeg(4,standPos,2000);
    moveLeg(5,standPos,2000);
}

void Hexapod::setGait(Gait gait)
{

}

void Hexapod::initGait()
{
    if (status == WALKING && prevStatus != status) {
        switch (gait) {
            case TRI :
                legs[0]->progress = 0;
                legs[1]->progress = (cycleDuration/2) / cycleDuration;
                legs[2]->progress = 0;
                legs[3]->progress = (cycleDuration/2) / cycleDuration;
                legs[4]->progress = 0;
                legs[5]->progress = (cycleDuration/2) / cycleDuration;

                progressBreakpoint = (cycleDuration/2) / cycleDuration;    

                break;
            case WAVE :
                legs[0]->progress = 0;
                legs[1]->progress = ((cycleDuration/6.0) * 5) / cycleDuration;
                legs[2]->progress = ((cycleDuration/6.0) * 4) / cycleDuration;
                legs[3]->progress = ((cycleDuration/6.0)) / cycleDuration;
                legs[4]->progress = ((cycleDuration/6.0) * 2 ) / cycleDuration;
                legs[5]->progress = ((cycleDuration/6.0) * 3 ) / cycleDuration;

                progressBreakpoint = (cycleDuration/6.0) / cycleDuration;
                break;
        }
        Serial.println("Status walking init");
        prevStatus = status;
    }
}

void Hexapod::initStopSequence() 
{
    // if (status == STOPPING && status != prevStatus) {
    //     for (int l = 0; l < 6; l++) {
    //         legs[l]->controlPoints[0] = legs[l]->position;
    //         legs[l]->controlPoints[1] = standPos;
    //         legs[l]->controlPoints[2] = standPos;
    //         
    //         legs[l]->progress = 0.5;
    //     }
    //     prevStatus = STOPPING;
    // }
}

void Hexapod::planLegsPath() 
{
    if (status == STANDING) {
        return;
    }

    for (int l = 0; l < 6; l++) {
        float t = legs[l]->progress;
        // to extract and make it a setting
        float walkingStride = command.y;
        float steeringStride = command.x;
        
        float kWalkingStride = 0.8;
        float kSteeringStride = 0.8;

        float distance_from_ground = -220;
        float lift = 110;

        Vector3 straightControlPoints[3];
        Vector3 steeringControlPoints[3];
        Vector3 straightPoint;
        Vector3 steeringPoint;
        float weightSum = abs(command.x) + abs(command.y);

        if(weightSum == 0) {
            return;
        } 

        if (t >= progressBreakpoint) {
            //second half of the cycle aka PUSHING
            if (legs[l]->status != PUSHING) {
                setStartPoint(*legs[l]);
            }
            legs[l]->status = PUSHING;

            straightControlPoints[0] = legs[l]->startPoint;
            straightControlPoints[1] = Vector3(standPos.x, legs[l]->strideMirror  * -walkingStride * kWalkingStride, distance_from_ground);

            straightPoint = GetPointOnBezierCurve(straightControlPoints, 2, mapFloat(t, progressBreakpoint, 1, 0, 1));

            steeringControlPoints[0] = legs[l]->startPoint;
            steeringControlPoints[1] = Vector3(standPos.x + 50, 0, distance_from_ground);
            steeringControlPoints[2] = Vector3(standPos.x, steeringStride * kSteeringStride, distance_from_ground);

            steeringPoint = GetPointOnBezierCurve(steeringControlPoints, 3, mapFloat(t, progressBreakpoint, 1, 0, 1));

            legs[l]->position = ((straightPoint*abs(command.y) + steeringPoint*abs(command.x))/ weightSum);
        }else{
            //fist half of the cycle aka LIFTING
            if (legs[l]->status != LIFTING) {
                setStartPoint(*legs[l]);
            }
            legs[l]->status = LIFTING;

            straightControlPoints[0]= legs[l]->startPoint;
            straightControlPoints[1]= Vector3
                (
                    standPos.x,
                    ((legs[l]->strideMirror  * walkingStride * kWalkingStride) - legs[l]->startPoint.y)/2,
                    distance_from_ground + lift
                ); 
            straightControlPoints[2] = Vector3(standPos.x, legs[l]->strideMirror  * walkingStride * kWalkingStride, distance_from_ground);

            straightPoint = GetPointOnBezierCurve(
                straightControlPoints,
                3,
                mapFloat(t,0, progressBreakpoint, 0, 1)
            ).rotate(legs[l]->coaxOffsetAngle * legs[l]->coaxRotated, Vector2(standPos.x, 0));

            steeringControlPoints[0]= legs[l]->startPoint;
            steeringControlPoints[1]= Vector3
                (
                    standPos.x + 50,
                    0,
                    distance_from_ground + lift
                ); 
            steeringControlPoints[2] = Vector3(standPos.x, -steeringStride * kSteeringStride, distance_from_ground);

            steeringPoint = GetPointOnBezierCurve(
                steeringControlPoints,
                3,
                mapFloat(t,0, progressBreakpoint, 0, 1)
            ).rotate(legs[l]->coaxOffsetAngle * legs[l]->coaxRotated, Vector2(standPos.x, 0));

            legs[l]->position = ((straightPoint*abs(command.y) + steeringPoint*abs(command.x))/ weightSum);
        }
    }
}

void Hexapod::updateSpeed()
{
    speed = max(abs(command.y), abs(command.x)) * 2;    
    if( speed > maxSpeed) {
        speed = maxSpeed;
    }
}

void Hexapod::updateProgress()
{ 
    float currentProgress;
    for (int l = 0; l < 6; l++){
        //0.1 * 1000 = 100
        currentProgress = legs[l]->progress * cycleDuration;
        currentProgress += speed;
       
        legs[l]->progress = currentProgress / cycleDuration;
    
        if (legs[l]->progress > 1 && status == WALKING) {
            legs[l]->progress = 0;
        }
    }
}

void Hexapod::updateLegsPosition()
{
    // Vector3 center = standPos;

    for (int l = 0; l < 6; l++) {        
        // Vector3 point = {legs[l]->position.x - center.x, legs[l]->position.y - center.y, legs[l]->position.z - center.z};
        //
        // if(l != 1 && l != 4){
        //     if (l == 0 || l == 5) {
        //         point = rotatePoint(point, -coaxOffset);
        //     }
        //
        //     if (l == 2 || l == 3) {
        //         point = rotatePoint(point, coaxOffset);            
        //     }    
        // }
        //
        // point.x += center.x;
        // point.y += center.y;
        // point.z += center.z;
        // 
        moveLeg(l, legs[l]->position, 500);
    }
}

void Hexapod::setStartPoint(Leg& leg) {
    leg.startPoint = leg.position; 
}

void Hexapod::update()
{
    Hexapod::updateSpeed();
    Hexapod::updateProgress();
    Hexapod::planLegsPath();
    Hexapod::updateLegsPosition();
}

void Hexapod::setCommand(Command com) {
    if (command.x > MAX_COMMAND) com.x = MAX_COMMAND;
    if (command.x < -MAX_COMMAND) com.x = -MAX_COMMAND;
    if (command.y > MAX_COMMAND) com.y = MAX_COMMAND;
    if (command.y < -MAX_COMMAND) com.y = -MAX_COMMAND;

    if (abs(com.x) < 10) com.x = 0;
    if (abs(com.y) < 10) com.y = 0;
    command.x = com.x;
    command.y = com.y;
}

void Hexapod::moveLeg(int leg, Vector3 pos, int speed = 1000)
{
    IKangles angles =  calculateIKLeg(pos);

    legs[leg]->setJointsAngles(angles);
    legs[leg]->move();
}
