#include "position.h"



Position::Position(int px, int py) : d_x(px), d_y(py) {}


int Position::getX() const {
    return d_x;
}

int Position::getY() const {
    return d_y;
}


void Position::setX(int px) {
    d_x = px;
}

void Position::setY(int py) {
    d_y = py;
}


void Position::move(int dx, int dy) {
    d_x += dx;
    d_y += dy;
}

double Position::distance(const Position& other) const {
    int dx = d_x - other.d_x;
    int dy = d_y - other.d_y;
    return std::sqrt(dx * dx + dy * dy);
}

bool Position::operator==(const Position& other) const {
    return d_x == other.d_x && d_y == other.d_y;
}

bool Position::operator!=(const Position& other) const {
    return !(*this == other);
}


void Position::print(std::ostream& os) const {
    os << "(" << d_x << ", " << d_y << ")";
}


std::ostream& operator<<(std::ostream& os, const Position& p) {
    p.print(os);
    return os;
}
