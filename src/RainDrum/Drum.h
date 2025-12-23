#pragma once
#include <AccelStepper.h>

class Drum {
    public:
        Drum();
        void moveToPosition(int targetDrumPosition);
        void strike();
        void moveToPositionAndStrike(int position);
        void initialize();
    private:
        int currentDrumPosition = 0;
        static const int STEPS_PER_REV;
        static const int STEPS_PER_NOTE;
        static const float MAX_RPM;
        static const float MAX_ACCELERATION;
        AccelStepper stepper;
};
