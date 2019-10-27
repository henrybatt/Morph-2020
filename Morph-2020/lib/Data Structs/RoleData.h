#ifndef ROLEDATA_H
#define ROLEDATA_H

#include <Arduino.h>
#include <Define.h>
#include <Pins.h>
#include <Debug.h>
#include <Common.h>

enum Role: uint8_t{
    attack,
    defend,
    undecided

};

#endif