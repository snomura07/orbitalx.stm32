#include "encoder_distance.h"

EncoderDistance::EncoderDistance(Encoder *rightEncoder_, Encoder *leftEncoder_) :
    rightEncoder(rightEncoder_),
    leftEncoder(leftEncoder_),
    mm(0.0)
{}
EncoderDistance::~EncoderDistance(){}

void EncoderDistance::init(){}

void EncoderDistance::update() {
    float rRotationCnt = (float)rightEncoder->counter / RIGHT_ENC_PPR; //カウンタ*1回転当たりのカウント数 = 回転数
    float lRotationCnt = (float)leftEncoder->counter  / LEFT_ENC_PPR;

    float rDis = rRotationCnt * WHEEL_DIAMETER * PI; //回転数*2πr = 移動距離
    float lDis = lRotationCnt * WHEEL_DIAMETER * PI;
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
