#ifndef POSITION_H
#define POSITION_H

#include <iostream>
#include <cmath>

class Position {
private:
    int d_x;
    int d_y;

public:

    Position(int px = 0, int py = 0);


    int getX() const;
    int getY() const;


    void setX(int px);
    void setY(int py);


    void move(int dx, int dy);


    double distance(const Position& other) const;


    bool operator==(const Position& other) const;
    bool operator!=(const Position& other) const;


    void print(std::ostream& os) const;
};


std::ostream& operator<<(std::ostream& os, const Position& p);

#endif // POSITION_H
