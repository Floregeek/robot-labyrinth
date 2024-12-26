#include "Robot.h"


Robot::Robot(Position position, Direction direction) : d_position{position}, d_direction{direction} {}

void Robot::avancer(const Terrain& terrain) {
    if (detecterObstacleEnFace(terrain)) {
        std::cout << "Obstacle détecté en face. Le robot ne peut pas avancer." << std::endl;
        return;
    }


    switch (d_direction) {
        case Direction::NORD:
            d_position.move(0, -1);
            break;
        case Direction::SUD:
            d_position.move(0, 1);
            break;
        case Direction::EST:
            d_position.move(1, 0);
            break;
        case Direction::OUEST:
            d_position.move(-1, 0);
            break;
    }


     notifierObservateurs();
}


void Robot::tournerGauche() {
d_direction = static_cast<Direction>((static_cast<int>(d_direction) + 3) % 4);
notifierObservateurs();
}

void Robot::tournerDroite() {
d_direction = static_cast<Direction>((static_cast<int>(d_direction) + 1) % 4);
notifierObservateurs();
}

bool Robot::detecterObstacleEnFace(const Terrain& terrain) const {
    Position positionEnFace = d_position;


    switch (d_direction) {
        case Direction::NORD:
            positionEnFace.move(0, -1);
            break;
        case Direction::SUD:
            positionEnFace.move(0, 1);
            break;
        case Direction::EST:
            positionEnFace.move(1, 0);
            break;
        case Direction::OUEST:
            positionEnFace.move(-1, 0);
            break;
    }


    return terrain.estMur(positionEnFace);
}


bool Robot::detecterObstacleAGauche(const Terrain& terrain) const {
    Position positionAGauche = d_position;

    switch (d_direction) {
        case Direction::NORD:
            positionAGauche.move(-1, 0);
            break;
        case Direction::EST:
            positionAGauche.move(0, -1);
            break;
        case Direction::SUD:
            positionAGauche.move(1, 0);
            break;
        case Direction::OUEST:
            positionAGauche.move(0, 1);
            break;
    }

    if (terrain.estMur(positionAGauche)) {
        return true;
    }

    for (const Position& obstacle : terrain.obtenirObstacles()) {
        if (obstacle == positionAGauche) {
            return true;
        }
    }

    return false;
}



bool Robot::detecterObstacleADroite(const Terrain& terrain) const {
    Position positionADroite = d_position;

    switch (d_direction) {
        case Direction::NORD:
            positionADroite.move(1, 0);
            break;
        case Direction::EST:
            positionADroite.move(0, 1);
            break;
        case Direction::SUD:
            positionADroite.move(-1, 0);
            break;
        case Direction::OUEST:
            positionADroite.move(0, -1);
            break;
    }

    if (terrain.estMur(positionADroite)) {
        return true;
    }

    for (const Position& obstacle : terrain.obtenirObstacles()) {
        if (obstacle == positionADroite) {
            return true;
        }
    }

    return false;
}


void Robot::notifierObservateurs(){
    for (const auto& observateur : d_observateurs) {
            observateur->MettreAjour(*this);
        }
}
 void Robot::enregistrerObservateur(std::unique_ptr<Observateur> observateur) {
        d_observateurs.push_back(std::move(observateur));
    }

Position Robot::getPosition() const{
    return d_position;
}

Direction Robot::getDirectionRobot() const
{
    return d_direction;
}
string Robot::directionToString(Direction dir) const {
    switch (dir) {
        case Direction::NORD: return "NORD";
        case Direction::EST: return "EST";
        case Direction::SUD: return "SUD";
        case Direction::OUEST: return "OUEST";
        default: return "INCONNUE";
    }
}
