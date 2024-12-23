#include "AlgorithmeDeSortieMainDroite.h"

void AlgorithmeDeSortieMainDroite::executer(Robot& robot, const Terrain& terrain)
{
    while (robot.getPosition()!= terrain.getPositionArrivee()) {
        if (!robot.detecterObstacleADroite()) {
            robot.tournerDroite();
            robot.avancer(terrain);
        } else if (!robot.detecterObstacleEnFace(terrain)) {
            robot.avancer(terrain);
        } else {
            robot.tournerGauche();
        }

    }
    std::cout<< "Le robot est sorti du labyrinthe!"<<std::endl;

}
