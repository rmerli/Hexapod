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

void Leg::initActuators(int coaxPin, int femorePin, int tibiaPin)
{
    coaxJoint = new Actuator(coaxPin, 340, 2340);
    femoreJoint = new Actuator(femorePin, 340, 2340);
    tibiaJoint = new Actuator(tibiaPin, 340, 2340);
}

void Leg::setJointsAngles(IKangles angles)
{
    coaxAngle = angles.coax;
    femoreAngle = angles.femore;
    tibiaAngle = angles.tibia;
}

void Leg::move(int speed = 1000)
{
    coaxJoint->move(coaxAngle, 90, speed);
    femoreJoint->move(femoreAngle, 100, speed);
    tibiaJoint->move(tibiaAngle, 60, speed);
}

Hexapod::Hexapod()
{
    for (int i = 0; i < 6; i++)
    {
        Hexapod::legs[i] = new Leg();
    }

    legs[0]->initActuators(right_front_coax_pin, right_front_femore_pin, right_front_tibia_pin);
    legs[1]->initActuators(right_middle_coax_pin, right_middle_femore_pin, right_middle_tibia_pin);
    legs[2]->initActuators(right_back_coax_pin, right_back_femore_pin, right_back_tibia_pin);
 
    legs[3]->initActuators(left_front_coax_pin, left_front_femore_pin, left_front_tibia_pin);
    legs[4]->initActuators(left_middle_coax_pin, left_middle_femore_pin, left_middle_tibia_pin);
    legs[5]->initActuators(left_back_coax_pin, left_back_femore_pin, left_back_tibia_pin);

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
    if (status == STOPPING && status != prevStatus) {
        for (int l = 0; l < 6; l++) {
            legs[l]->controlPoints[0] = legs[l]->position;
            legs[l]->controlPoints[1] = standPos;
            legs[l]->controlPoints[2] = standPos;
            
            legs[l]->progress = 0.5;
        }
        prevStatus = STOPPING;
    }

}

void Hexapod::planLegsPath() {
    if (status == STANDING) {
        return;
    }

    for (int l = 0; l < 6; l++) {
        float t = legs[l]->progress;
        // to extract and make it a setting
        float stride = 50;
        float distance_from_ground = -200;
        float lift = 75;


        if (t >= progressBreakpoint) {
            //second half of the cycle aka PUSHING
            if (legs[l]->status != PUSHING) {
                setStartPoint(*legs[l]);
            }
            legs[l]->status = PUSHING;

            legs[l]->controlPoints[0] = legs[l]->startPoint;
            legs[l]->controlPoints[1] = legs[l]->startPoint;
            legs[l]->controlPoints[2] = Vector3(legs[l]->startPoint.x, -direction * stride, distance_from_ground);

            legs[l]->position = GetPointOnBezierCurve(legs[l]->controlPoints, 3, mapFloat(t, progressBreakpoint, 1, 0, 1));

        }else{
            //fist half of the cycle aka LIFTING
            if (legs[l]->status != LIFTING) {
                setStartPoint(*legs[l]);
            }

            legs[l]->controlPoints[0] = legs[l]->startPoint;
            legs[l]->controlPoints[1] = Vector3
                (
                    legs[l]->startPoint.x,
                    ((direction * stride) - legs[l]->startPoint.y)/2,
                    distance_from_ground + lift
                ); 
            legs[l]->controlPoints[2] = Vector3(legs[l]->startPoint.x, direction * stride, distance_from_ground);

            legs[l]->status = LIFTING;
            legs[l]->position = GetPointOnBezierCurve(legs[l]->controlPoints, 3, mapFloat(t,0, progressBreakpoint, 0, 1));
        }
    }
}
void Hexapod::updateSpeed()
{
    if (carCommand.y >= 0) direction = 1;
    else direction = -1;

    speed = abs(carCommand.y);    
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
    Vector3 center = standPos;

    for (int l = 0; l < 6; l++) {        
        Vector3 point = {legs[l]->position.x - center.x, legs[l]->position.y - center.y, legs[l]->position.z - center.z};
        
        if(l != 1 && l != 4){
            float rotationMatrix[3][3];
            if (l == 0 || l == 3) {
                makeRotationZMatrix(degToRad(-45), rotationMatrix);
            }

            if (l == 2 || l == 5) {
                makeRotationZMatrix(degToRad(45), rotationMatrix);
            }    
            point = mulMatrixVector(rotationMatrix, point);
        }
        
        point.x += center.x;
        point.y += center.y;
        point.z += center.z;

        moveLeg(l, point, 1000);
    }
}

void Hexapod::setControlPoints(Leg& leg, Vector3 controlPoints[])
{
    for (int i = 0; i < 3; i++){
        leg.controlPoints[i] = controlPoints[i];
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

void Hexapod::moveLeg(int leg, Vector3 pos, int speed = 1000)
{
    IKangles angles =  calculateIKLeg(pos);

    if (leg > 2) {
        angles.coax *= -1;
    }

    legs[leg]->setJointsAngles(angles);
    legs[leg]->move();
}
