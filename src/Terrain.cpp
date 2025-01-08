#include "Terrain.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <io.h>
#include <fcntl.h>


Terrain::Terrain(const std::string& fichierTerrain) {
    chargerDepuisFichier(fichierTerrain);
}


void Terrain::chargerDepuisFichier(const std::string& fichierTerrain) {
    std::ifstream fichier(fichierTerrain);
    grille.clear();
    std::string ligne;
    int y = 0;

    while (std::getline(fichier, ligne)) {
        std::vector<char> ligneGrille(ligne.begin(), ligne.end());
        grille.push_back(ligneGrille);


        for (int x = 0; x < ligne.size(); ++x) {
            if (ligne[x] == 'D') {
                d_depart = Position(x, y);
            } else if (ligne[x] == 'A') {
                d_arrivee = Position(x, y);
            }
        }
        ++y;
    }

    fichier.close();

    // Vérifications
    if (d_depart == Position(-1, -1)) {
        std::cerr << "Erreur : la position de départ 'D' est manquante." << std::endl;
    }
    if (d_arrivee == Position(-1, -1)) {
        std::cerr << "Erreur : la position d'arrivée 'A' est manquante." << std::endl;
    }
}


void Terrain::sauvegarderDansFichier(const std::string& fichierTerrain) const {
    std::ofstream fichier(fichierTerrain);
    if (!fichier.is_open()) {
        std::cerr << "Impossible d'ouvrir le fichier terrain pour écriture : " + fichierTerrain << std::endl;
        return;
    }

    for (const auto& ligne : grille) {
        for (char c : ligne) {
            fichier << c;
        }
        fichier << '\n';
    }

    fichier.close();
}

std::vector<Position> Terrain::obtenirObstacles() const {
    std::vector<Position> obstacles;

    for (int y = 0; y < grille.size(); ++y) {
        for (int x = 0; x < grille[y].size(); ++x) {
            if (grille[y][x] == 'X') {
                Position p{x, y};
                obstacles.push_back(p);
            }
        }
    }

    return obstacles;
}


Position Terrain::getPositionDepart() const {
    return d_depart;
}


Position Terrain::getPositionArrivee() const {
    return d_arrivee;
}


bool Terrain::estMur(const Position& pos) const {
    if (pos.getX() < 0 || pos.getX() >= grille[0].size() ||
        pos.getY() < 0 || pos.getY() >= grille.size()) {
        return true;
    }
    return grille[pos.getY()][pos.getX()] == 'X';
}


void Terrain::afficherTerrain(int mode, Robot& robot) const {
    for (size_t i = 0; i < grille.size(); ++i) {
        for (size_t j = 0; j < grille[i].size(); ++j) {
            char c = grille[i][j];


            if (robot.getPosition().getX() == j && robot.getPosition().getY() == i) {
                switch (robot.getDirectionRobot()) {
                    case Direction::NORD:
                        c = '^';
                        break;
                    case Direction::EST:
                        c = '>';
                        break;
                    case Direction::SUD:
                        c = 'v';
                        break;
                    case Direction::OUEST:
                        c = '<';
                        break;
                }
            }


            switch (mode) {
                case 0:
                    std::cout << c;
                    break;
                case 1: { // Mode ASCII amélioré
          if (i == 0)
          if (j == 0) {
            std::cout << '+';
        } else if (j == grille[i].size() / 2 - 1 || j == grille[i].size() / 2) {
            std::cout << '#';
        } else if (j == grille[i].size() - 1) {
            std::cout << '+';
        } else {
            std::cout << '-';
        }
     else if (i == grille.size() - 1) {
        if (j == 0 || j == grille[i].size() - 1) {
            std::cout << '+';
        } else {
            std::cout << '-';
        }
    } else {
        if (j == 0 || j == grille[i].size() - 1) {
            std::cout << '|';
        } else if (c == 'X') {
            std::cout << '+';
        } else if (c == '.') {
            std::cout << '.';
        } else if (c == 'D' || c == 'A') {
            std::cout << c;
        } else if (robot.getPosition().getX() == j && robot.getPosition().getY() == i) {

            switch (robot.getDirectionRobot()) {
                case Direction::NORD:
                    std::cout << '^';
                    break;
                case Direction::EST:
                    std::cout << '>';
                    break;
                case Direction::SUD:
                    std::cout << 'v';
                    break;
                case Direction::OUEST:
                    std::cout << '<';
                    break;
            }
          } else {
            std::cout << ' ';
          }
         }
                break;
         }
          case 2: { // Mode Unicode avancé
                            std::vector<std::string> terrainAmeliore;

                            // Construire les bordures du haut
                            std::string bordureHaut = "┏";
                            for (size_t i = 0; i < grille[0].size(); ++i) {
                                bordureHaut += "━━";
                            }
                            bordureHaut += "┓";

                            // Construire les bordures du bas
                            std::string bordureBas = "┗";
                            for (size_t i = 0; i < grille[0].size(); ++i) {
                                bordureBas += "━━";
                            }
                            bordureBas += "┛";

                            // Construire le terrain avec les murs et bordures latérales
                            for (size_t i = 0; i < grille.size(); ++i) {
                                std::string ligneGraphique = "┃";
                                for (size_t j = 0; j < grille[i].size(); ++j) {
                                    char c = grille[i][j];

                                    // Vérifier si c'est la position du robot
                                    if (robot.getPosition().getX() == j && robot.getPosition().getY() == i) {
                                        switch (robot.getDirectionRobot()) {
                                            case Direction::NORD:
                                                ligneGraphique += " ^ ";
                                                break;
                                            case Direction::EST:
                                                ligneGraphique += " > ";
                                                break;
                                            case Direction::SUD:
                                                ligneGraphique += " v ";
                                                break;
                                            case Direction::OUEST:
                                                ligneGraphique += " < ";
                                                break;
                                        }
                                    } else {
                                        // Convertir les caractères du terrain
                                        if (c == 'X') {
                                            ligneGraphique += "┃ "; // Murs internes
                                        } else if (c == '.') {
                                            ligneGraphique += ". "; // Chemin libre
                                        }
                                        else if (c == 'D' ) {
                                        ligneGraphique += "D"; }
                                        else if (c == 'A' ) {
                                        ligneGraphique += "A"; }
                                        else {
                                            ligneGraphique += "  "; // Autres éléments
                                        }
                                    }
                                }
                                ligneGraphique += "┃";
                                terrainAmeliore.push_back(ligneGraphique);
                            }

                            // Afficher le terrain complet
                            std::cout << bordureHaut << "\n";
                            for (const auto& ligne : terrainAmeliore) {
                                std::cout << ligne << "\n";
                            }
                            std::cout << bordureBas << "\n";


                }

                default:
                    std::cerr << "Mode d'affichage non supporté." << std::endl;
                    return;
            }
        }
        std::cout << '\n';
    }

}








