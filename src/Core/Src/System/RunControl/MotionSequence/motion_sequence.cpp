#include "motion_sequence.h"

namespace RunControl
{
MotionSequence::MotionSequence():
    currMotion(MotionKind::STOP),
    nextMotion(MotionKind::STOP){

}

MotionSequence::~MotionSequence(){}

void MotionSequence::init(){
}

void MotionSequence::update(){
    // start condition: STRAIGHT
    // end condition

    if(endCheck()){
        currMotion = nextMotion;

    }
}

bool MotionSequence::endCheck(){
    switch (currMotion)
    {
        case MotionKind::STRAIGHT:
        // end condition: 直進距離が一定以上
        break;

        case MotionKind::TURN_LEFT:
        // end condition: 左旋回角度が一定以上
        break;

        case MotionKind::TURN_RIGHT:
        // end condition: 右旋回角度が一定以上
        break;

        case MotionKind::STOP:
        // end condition: 停止時間が一定以上
        break;

        default:
        break;
    }

    return true;
}


void MotionSequence::pushNextMotion(MotionKind motion){
    nextMotion = motion;
}













}
