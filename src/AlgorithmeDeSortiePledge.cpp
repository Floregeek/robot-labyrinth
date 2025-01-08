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
                    terrain.afficherTerrain(modetext, robot);
                } else {
                    robot.tournerDroite();
                    compteurAngulaire--;
                    terrain.afficherTerrain(modetext, robot);
                }
            } else {
                robot.avancer(terrain);
                terrain.afficherTerrain(modetext, robot);

                if (compteurAngulaire == 0) {
                    break;
                }
            }

            if (robot.getPosition() == sortie) {
                std ::cout<<"vous avez gagner \n";
                return;
            }
        }

        while (!robot.detecterObstacleEnFace(terrain)) {
            robot.avancer(terrain);
            terrain.afficherTerrain(modetext, robot);
            if (robot.getPosition() == sortie) {
                return;
            }
        }
    }
}
