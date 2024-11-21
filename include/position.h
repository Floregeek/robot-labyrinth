#ifndef POSITION_H
#define POSITION_H

#include <iostream>
#include <cmath>

class Position {
private:
    int d_x; // Coordonn�e x
    int d_y; // Coordonn�e y

public:
    // Constructeurs
    Position(int px = 0, int py = 0);

    // Accesseurs
    int getX() const;
    int getY() const;

    // Modificateurs
    void setX(int px);
    void setY(int py);

    // M�thode pour d�placer la position
    void move(int dx, int dy);

    // Calculer la distance entre deux positions
    double distance(const Position& other) const;

    // Op�rateurs
    bool operator==(const Position& other) const;
    bool operator!=(const Position& other) const;

    // M�thode d'affichage
    void print(std::ostream& os) const;
};

// Surcharge des op�rateurs d'entr�e/sortie
std::ostream& operator<<(std::ostream& os, const Position& p);

#endif // POSITION_H
