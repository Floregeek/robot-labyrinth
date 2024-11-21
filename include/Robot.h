#ifndef ROBOT_H
#define ROBOT_H

#include <vector>


enum class Direction { NORD, EST, SUD, OUEST };
class Robot
{
    public:
        Robot(Position position, Direction direction);

        void avancer();
        void tournerGauche();
        void tournerDroite();
        bool detecterObstacle() const;

        void ajouterObservateur(Observateur* observateur);
        void notifierObservateurs();

        int getPosition() const;
        char getDirectionRobot() const;


    private:
        Position d_position;
        Direction d_direction;
        std::vector<Observateur*> d_observateurs;
};

#endif // ROBOT_H
