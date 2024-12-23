#ifndef ROBOT_H
#define ROBOT_H

#include <vector>
#include "Position.h"
#include "Observateur.h"
#include "Terrain.h"
#include <memory>
using std::string;
class Observateur;
class Terrain;
enum class Direction { NORD, EST, SUD, OUEST };

class Robot
{
    public:
        Robot(Position position, Direction direction);

        void avancer(const Terrain& terrain);
        void tournerGauche();
        void tournerDroite();
        bool detecterObstacleEnFace(const Terrain& terrain) const;
        bool detecterObstacleAGauche() const;
        bool detecterObstacleADroite() const;


        void notifierObservateurs();
        void enregistrerObservateur(std::unique_ptr<Observateur> observateur);

        Position getPosition() const;
        Direction getDirectionRobot() const;
        string directionToString(Direction dir)const;


    private:
        Position d_position;
        Direction d_direction;
       std::vector<std::unique_ptr<Observateur>> d_observateurs;
       std::vector<Position> obstacles;

};

#endif // ROBOT_H
