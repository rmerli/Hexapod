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

void Hexapod::setGait(Gait gait)
{

}

void Hexapod::initGait()
{
    if (status == WALKING && prevStatus != status) {
        switch (gait) {
            case TRI :
                legs[0]->progress = 0;
                legs[1]->progress = 0.5;
                legs[2]->progress = 0;
                legs[3]->progress = 0.5;
                legs[4]->progress = 0;
                legs[5]->progress = 0.5;

                progressBreakpoint = 0.5;    

                break;
            case WAVE :
                legs[0]->progress = 0;
                legs[1]->progress = (1/6.0) * 5;
                legs[2]->progress = (1/6.0) * 4;
                legs[3]->progress = (1/6.0);
                legs[4]->progress = (1/6.0) * 2;
                legs[5]->progress = (1/6.0) * 3;

                progressBreakpoint = 1.0/6.0; 
                break;
        }
        for(int l = 0; l < 6; l++) {
            float t = legs[l]->progress; 
            legs[l]->firstCycle = true;
            
            if (t >= progressBreakpoint) {
                //pushing
                setControlPoints(*legs[l], firstStepPushing);
            }else {
                //lifting
                setControlPoints(*legs[l], firstStepLifting); 
            }
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

void Hexapod::planLegsPath()
{
    if (status == STANDING) {
        return;
    }

    for (int l = 0; l < 6; l++) {
        float t = legs[l]->progress;

        if (t >= progressBreakpoint) {
            if (!legs[l]->firstCycle && status != STOPPING) {
                setControlPoints(*legs[l], pushing);
            }
            legs[l]->position = GetPointOnBezierCurve(legs[l]->controlPoints, 3, mapFloat(t, progressBreakpoint, 1, 0, 1));
        }else {
            legs[l]->position = GetPointOnBezierCurve(legs[l]->controlPoints, 3, mapFloat(t,0, progressBreakpoint, 0, 1));
        }

        if ((t < progressBreakpoint && t >= progressBreakpoint - speed) && (legs[l]->firstCycle)) {
            //end first cycle for the leg
            setControlPoints(*legs[l], pushing);
            legs[l]->firstCycle = false;
        }
        
        if (legs[l]->progress < 1) {
            legs[l]->progress += speed;
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

        moveLeg(l, point, 500);
         
        // IKangles angles =  calculateIKLeg(point);
        // legs[l]->setJointsAngles(angles);
        // legs[l]->move();
    }
}

void Hexapod::checkProgress()
{
    if (status == STOPPING){
        for (int l = 0; l < 6; l++) {
            if (legs[l]->progress < 1) {
                 return;
            }
        }
        status = STANDING;
        prevStatus = STANDING;
        return;
    }
    
    for (int l = 0; l < 6; l++){
        if (legs[l]->progress > 1 && status == WALKING) {
            legs[l]->progress = 0;
            legs[l]->firstCycle = false;
            setControlPoints(*legs[l], lifting);
        }
    }
}


void Hexapod::setControlPoints(Leg& leg, Vector3 controlPoints[])
{
    for (int i = 0; i < 3; i++){
        leg.controlPoints[i] = controlPoints[i];
    }
}

void Hexapod::update()
{
    Hexapod::checkProgress();
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