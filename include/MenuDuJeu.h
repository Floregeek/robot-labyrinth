
#ifndef MENUDUJEU_H
#define MENUDUJEU_H
#include "Terrain.h"
#include "Robot.h"
#include "AlgorithmeDeSortieMainDroite.h"
#include "AlgorithmeDeSortiePledge.h"
#include "ObservateurAffichage.h"
#include "ObservateurStatistique.h"
#include <conio.h>
#include<fstream>
#include<limits>
class Terrain;


class MenuDuJeu {
public:

    MenuDuJeu();


    void afficherMenuPrincipal();

private:
    Terrain terrain;
    Robot* robot;
    int casesParcourues;
    int modeTexte;
    std::unique_ptr<ObservateurAffichage> observateurAffichage;
    std::unique_ptr<ObservateurStatistique> observateurStatistique;


    void choisirAlgorithmeDeSortie();
    void executerAlgorithme(AlgorithmeDeSortie& algorithme);
    void afficherCasesParcourues() const;
    void choisirModeTexte();
    void afficherTerrain();
    void incrementerCompteurDeplacement();
};


#endif // MENUDUJEU_H
