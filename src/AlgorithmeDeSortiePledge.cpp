#include "AlgorithmeDeSortiePledge.h"

void AlgorithmeDeSortiePledge::executer(Robot &robot, const Terrain &terrain) {
    int compteur = 0;
    bool sortieAtteinte = false;
    Position sortie = terrain.getPositionArrivee();
    while (!sortieAtteinte) {

        while (!robot.detecterObstacleEnFace(terrain)) {
            robot.avancer(terrain);
        }


        do {
            if (!robot.detecterObstacleADroite()) {
                robot.tournerDroite();
                compteur--;
            } else if (!robot.detecterObstacleEnFace(terrain)) {
                robot.avancer(terrain);
            } else {
                robot.tournerGauche();
                compteur++;
            }
            if (robot.getPosition() == sortie) {
                sortieAtteinte = true;
                break;
            }
        } while (compteur != 0);
    }
}
