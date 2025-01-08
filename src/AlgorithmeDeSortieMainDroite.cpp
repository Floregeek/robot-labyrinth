#include "AlgorithmeDeSortieMainDroite.h"
#include <unordered_set>
#include <sstream>

void AlgorithmeDeSortieMainDroite::executer(Robot &robot, const Terrain &terrain) {
    Position sortie = terrain.getPositionArrivee();
    std::unordered_set<std::string> positionsVisitees;
    int compteurBoucles = 0;

    // �tape 1 : Avancer tout droit jusqu'� rencontrer un mur � droite
    while (!robot.detecterObstacleADroite(terrain)) {
        if (!robot.detecterObstacleEnFace(terrain)) {
            robot.avancer(terrain);
        } else {
            robot.tournerGauche(); // Si bloqu�, tourner � gauche pour chercher une sortie
        }
    }

    // �tape 2 : Appliquer la r�gle de la main droite
    while (robot.getPosition() != sortie) {
        std::ostringstream oss;
        oss << robot.getPosition().getX() << "," << robot.getPosition().getY();
        std::string positionActuelle = oss.str();

        if (positionsVisitees.find(positionActuelle) != positionsVisitees.end()) {
            compteurBoucles++;
            if (compteurBoucles > 3) {
                // G�rer la situation de boucle ici, par exemple en faisant demi-tour
                robot.tournerGauche();
                continue;
            }
        } else {
            compteurBoucles = 0;
            positionsVisitees.insert(positionActuelle);
        }

        terrain.afficherTerrain(0, robot);
        std::cout << std::endl;

        // R�gle de la main droite
        if (!robot.detecterObstacleADroite(terrain)) {
            robot.tournerDroite();
            robot.avancer(terrain);
        } else if (!robot.detecterObstacleEnFace(terrain)) {
            robot.avancer(terrain);
        } else {
            robot.tournerGauche();
        }
    }

    terrain.afficherTerrain(modetext, robot);
    std::cout << "Le robot a atteint la sortie !" << std::endl;
}
