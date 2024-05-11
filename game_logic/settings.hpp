#ifndef GAME_LIFE_SETTINGS_HPP
#define GAME_LIFE_SETTINGS_HPP

#include <cstdio>
#include "my_types.hpp"

#define ABSOLUTE_MAX_ARENA_SIZE 128

#define DEFAULT_SIDE_SIZE 32
#define DEFAULT_TIME_STEP 1000
#define DEFAULT_ITERATIONS 5
#define DEFAULT_LIVING 35
#define DEFAULT_SPECIAL_CELL 5

const char VERSION_GAME[] = "0.0.0.4";
#define MAX_SIDE_SIZE 64
extern u16 __arenaSizeX;
extern u16 __arenaSizeY;

#define MIN_VALUE_TIME_STEP 1000
#define MAX_VALUE_TIME_STEP 5000
extern u16 __timeStep;

#define MIN_VALUE_ITERATIONS 5
#define MAX_VALUE_ITERATIONS 10
extern u16 __amountIterations;

#define MIN_VALUE_LIVING 10
#define MAX_VALUE_LIVING 85
extern u16 __LivingPercent;

#define MIN_VALUE_SPECIAL_CELL 1
#define MAX_VALUE_SPECIAL_CELL 15
extern u16 __WallPercent;
extern u16 __KillingPercent;
extern u16 __SupportPercent;

#endif //GAME_LIFE_SETTINGS_HPP
