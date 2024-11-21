#include "Robot.h"


Robot::Robot(Position position, Direction direction) : d_position(position), d_direction(direction) {}

void Robot::avancer() {
// Déplace le robot
switch (d_direction) {
case Direction::NORD: d_position.x--; break;
case Direction::EST: d_position.y++; break;
case Direction::SUD: d_position.x++; break;
case Direction::OUEST: d_position.y--; break;
}
notifierObservateurs();
}

void Robot::tournerGauche() {
direction = static_cast<Direction>((static_cast<int>(d_direction) + 3) % 4);
notifierObservateurs();
}

void Robot::tournerDroite() {
direction = static_cast<Direction>((static_cast<int>(d_direction) + 1) % 4);
notifierObservateurs();
}

void Robot::ajouterObservateur(Observateur* observateur) {
d_observateurs.push_back(observateur);
}
