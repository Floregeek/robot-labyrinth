#include "AlgorithmeDeSortiePledge.h"

void AlgorithmeDeSortiePledge::executer(Robot &robot, const Terrain &terrain) {
    Position sortie = terrain.getPositionArrivee();
    int compteurAngulaire = 0;

    while (robot.getPosition() != sortie) {
        while (compteurAngulaire != 0 || robot.detecterObstacleEnFace(terrain)) {
            if (robot.detecterObstacleEnFace(terrain)) {
                if (!robot.detecterObstacleAGauche(terrain)) {
                    robot.tournerGauche();
                    compteurAngulaire++;
                }
                else {
                    robot.tournerDroite();
                    compteurAngulaire--;
                }
            }
            else {
                robot.avancer(terrain);

                if (compteurAngulaire == 0) {
                    break;
                }
            }

            if (robot.getPosition() == sortie) {
                return;
            }
        }

        while (!robot.detecterObstacleEnFace(terrain)) {
            robot.avancer(terrain);

            if (robot.getPosition() == sortie) {
                return;
            }
        }
    }
}
