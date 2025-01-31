#include "current_velocity.h"

CurrentVelocity::CurrentVelocity(){}
CurrentVelocity::~CurrentVelocity(){}

void CurrentVelocity::setEncoder(Encoder *right_encoder_, Encoder *left_encoder_){
    right_encoder = right_encoder_;
    left_encoder  = left_encoder_;
}
