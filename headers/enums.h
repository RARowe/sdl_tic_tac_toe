#ifndef ENUMS_H
#define ENUMS_H
enum class SpaceState
{
    Empty,
    X,
    O
};

enum class Player
{
    One,
    Two
};

enum class WinLine
{
    Top = 0,
    HMiddle = 1,
    Bottom = 2,
    Left = 3,
    VMiddle = 4,
    Right = 5,
    BLToTR = 6,
    TLToBR = 7,
    None = 8
};
#endif
