#include "encoder_distance.h"

EncoderDistance::EncoderDistance(Encoder *rightEncoder_, Encoder *leftEncoder_) :
    rightEncoder(rightEncoder_),
    leftEncoder(leftEncoder_),
    mm(0.0),
    rDis(0.0),
    lDis(0.0),
    latestIndex(0),
    deltaMm(0.0)
{
    //カウンタ*1回転当たりのカウント数 = 回転数
    //回転数*2πr = 移動距離
    rightCount2Dis = WHEEL_DIAMETER * PI / RIGHT_ENC_PPR;
    leftCount2Dis  = WHEEL_DIAMETER * PI / LEFT_ENC_PPR;

    memset(preDis, 0, sizeof(preDis));
}
EncoderDistance::~EncoderDistance(){}

void EncoderDistance::init(){}

// 1msごとに処理されることを前提とする
void EncoderDistance::update() {
    rDis = (float)rightEncoder->counter * rightCount2Dis;
    lDis = (float)leftEncoder->counter  * leftCount2Dis;
    mm   = (rDis+lDis)/2.0;

    float preDis10ms = preDis[latestIndex];
    deltaMm          = mm - preDis10ms;

    latestIndex++;
    if(latestIndex == PAST_MS){
        latestIndex = 0;
    }

    int addIndex     = latestIndex==0?(PAST_MS-1):latestIndex-1;
    preDis[addIndex] = mm;
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
