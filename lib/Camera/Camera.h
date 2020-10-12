#ifndef CAMERA_H
#define CAMERA_H

#include <Common.h>

#include <GoalData.h>
#include <Vector.h>

class Camera{

    public:

        /* -- Class Constructor + Init -- */
        Camera();

        /* -- Read Camera data and update angles and distances -- */
        void update();

        /* -- Return goal data types -- */
        GoalData getAttackGoal();
        GoalData getDefendGoal();

    private:
        /* -- Structures of goal data -- */
        GoalData attack;
        GoalData defend;
};

extern Camera camera;

#endif