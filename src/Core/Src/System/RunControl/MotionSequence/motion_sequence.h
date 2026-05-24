#ifndef RUN_CONTROL_MOTION_SEQUENCE_H
#define RUN_CONTROL_MOTION_SEQUENCE_H

namespace RunControl
{
class MotionSequence {
public:
    enum MotionKind
    {
        STRAIGHT,
        TURN_LEFT,
        TURN_RIGHT,
        STOP
    };

public:
    MotionSequence();
    ~MotionSequence();
    void init();
    void update();
    void pushNextMotion(MotionKind motion);

private:
    void start();
    bool endCheck();

private:
    MotionKind currMotion;
    MotionKind nextMotion;

};
}

#endif
