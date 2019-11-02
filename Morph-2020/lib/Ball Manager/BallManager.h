#ifndef BALLMANAGER_H
#define BALLMANAGER_H

#include <Arduino.h>
#include <Common.h>

#include <Camera.h>
#include <CoordinateManager.h>

#include <Timer.h>

class BallManager{

    public:

        /* -- Class Constructor + Init -- */
        BallManager();

        /* -- Kicks if lightgate is broken -- */
        void kickBall();

        /* -- Kicks if we are in the attacking half & roughly facing the goal -- */        
        void attackKick();

        /* -- Kicks if recharged and outside time limit -- */
        void kick();

        /* -- If ball is breaking lightgate -- */
        bool hasBall();

        bool hasKicked();

    private:

        /* -- Kicker Timers -- */
        Timer kickDischarge = Timer(KICKER_DISCHARGE_TIME);
        Timer lastKick = Timer(KICKER_LAST_TIMER);
};

extern BallManager ballManager;

#endif