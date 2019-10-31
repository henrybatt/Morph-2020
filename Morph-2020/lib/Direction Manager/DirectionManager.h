#ifndef DIRECTIONMANAGER_H
#define DIRECTIONMANAGER_H

#include <Arduino.h>
#include <Common.h>

#include <MoveData.h>

class DirectionManager{

    public:

        /* -- Class Constructor + Init -- */
        DirectionManager();

        MoveData update();

    private:

        


};

extern DirectionManager directionManager;

#endif