#include "encoder_distance.h"

EncoderDistance::EncoderDistance(Encoder *rightEncoder_, Encoder *leftEncoder_) :
    rightEncoder(rightEncoder_),
    leftEncoder(leftEncoder_),
    mm(0.0)
{
    //カウンタ*1回転当たりのカウント数 = 回転数
    //回転数*2πr = 移動距離
    rightCount2Dis = WHEEL_DIAMETER * PI / RIGHT_ENC_PPR;
    leftCount2Dis  = WHEEL_DIAMETER * PI / LEFT_ENC_PPR;

}
EncoderDistance::~EncoderDistance(){}

void EncoderDistance::init(){}

void EncoderDistance::update() {
    float rDis = (float)rightEncoder->counter * rightCount2Dis;
    float lDis = (float)leftEncoder->counter  * leftCount2Dis;
    mm = (rDis+lDis)/2.0;
}

void EncoderDistance::reset() {
    mm = 0.0;
}

void EncoderDistance::dump() {
    sendMessage("Enc Distance: ");
    sendFloat(mm);
    sendMessage("[mm]");
    sendMessage("\r\n");
}
