#ifndef TEST_C_GAME_HPP
#define TEST_C_GAME_HPP

#include "./my_types.hpp"


struct Offset {
    i16 x = 0;
    i16 y = 0;
};

#define AMOUNT_DISPLACEMENT_OPTIONS 9

const Offset displacementOptions[AMOUNT_DISPLACEMENT_OPTIONS] =
        {
                {-1,  1}, {0,  1}, {1,  1},
                {-1,  0}, {0,  0}, {1,  0},
                {-1, -1}, {0, -1}, {1, -1}
        };

struct   Coords {
    u16 x = 0;
    u16 y = 0;

    bool operator==(const Coords& otherCoords) const
    {
        return (otherCoords.x == this->x)
               &&
               (otherCoords.y == this->y);
    }

    u32 operator()(const Coords& сoords) const
    {
        /*  Решение возможной колизии, повысить значимось имерения на N, где N не является 0 или 1 и в моем случае > 0. */
#define SIGNIFICANCE_COORDS_X 2

        return SIGNIFICANCE_COORDS_X * сoords.x + сoords.y;
    }

};

enum     TypeCell {
    LivingCell      = '#',
    DeadCell        = '_',
    Wall            = 'W',
    KillingCell     = 'K',
    LifeSupportCell = 'S'
};

// todo! будет в классе widget game
#define MAX_SIDE_SIZE 64

class Game
{
private:
    mapFilledCell __mapGame;

    u16 __arenaSizeX = DEFAULT_SIDE_SIZE;
    u16 __arenaSizeY = DEFAULT_SIDE_SIZE;

    u16 __timeStep = DEFAULT_TIME_STEP;

    u16 __amountIterations = DEFAULT_ITERATIONS;

    u16 __LivingPercent = DEFAULT_LIVING;

    u16 __WallPercent = DEFAULT_SPECIAL_CELL;
    u16 __KillingPercent = DEFAULT_SPECIAL_CELL;
    u16 __SupportPercent = DEFAULT_SPECIAL_CELL;

    Coords   getCoordAfterOffset(const Coords& CurrentCoords, const Offset& OffsetCoords);

    TypeCell getNewTypeCell(const Coords& CoordsCell);

    TypeCell getRandomCell();
public:
    static const short DEFAULT_SIDE_SIZE      = 32;
    static const short DEFAULT_TIME_STEP      = 1000;
    static const short DEFAULT_ITERATIONS     = 5;
    static const short DEFAULT_LIVING         = 35;
    static const short DEFAULT_SPECIAL_CELL   = 5;

    static const short MIN_VALUE_TIME_STEP    = 1000;
    static const short MAX_VALUE_TIME_STEP    = 10000;
    static const short MIN_VALUE_ITERATIONS   = 1;
    static const short MAX_VALUE_ITERATIONS   = 10;
    static const short MIN_VALUE_LIVING       = 10;
    static const short MAX_VALUE_LIVING       = 85;
    static const short MIN_VALUE_SPECIAL_CELL = 1;
    static const short MAX_VALUE_SPECIAL_CELL = 15;

    void setArenaSizeX(u16 size);
    u16 getArenaSizeX() const;
    void setArenaSizeY(u16 size);
    u16 getArenaSizeY() const;

    void setTimeStep(u16 timeStep);
    u16 getTimeStep() const;

    void setAmountIterations(u16 iterations);
    u16 getAmountIterations() const;

    void setLivingPercent(u16 percent);
    u16 getLivingPercent() const;

    void setWallPercent(u16 percent);
    u16 getWallPercent() const;
    void setKillingPercent(u16 percent);
    u16 getKillingPercent() const;
    void setSupportPercent(u16 percent);
    u16 getSupportPercent() const;

    void developmentOfLife();

    void setRandomMapGame();

    mapFilledCell getMapGame() const;
};


#endif //TEST_C_GAME_HPP
