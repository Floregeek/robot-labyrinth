#ifndef TERRAIN_H
#define TERRAIN_H


#include <vector>
#include <string>
#include "Position.h"
#include "Robot.h"
class Robot;
class Terrain {
public:
    Terrain(const std::string& fichierTerrain);

    void chargerDepuisFichier(const std::string& fichierTerrain);
    void sauvegarderDansFichier(const std::string& fichierTerrain) const;

    Position getPositionDepart() const;
    Position getPositionArrivee() const;

    bool estMur(const Position& mur) const;
    void afficherTerrain(int mode ,Robot& robot) const;
    std::vector<Position> obtenirObstacles() const;

private:
    std::vector<std::vector<char>> grille;
    Position d_depart;
    Position d_arrivee;

};

#endif // TERRAIN_H
