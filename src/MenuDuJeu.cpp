#include "MenuDuJeu.h"
#include <iostream>
#include <fstream>
#include <sstream>

MenuDuJeu::MenuDuJeu() : terrain{Terrain("")}, robot(nullptr), casesParcourues(0), modeTexte(0),
      observateurStatistique(std::make_unique<ObservateurStatistique>())
{
}

void MenuDuJeu::afficherMenuPrincipal() {
    int choix;
    do {
        std::cout << "==== MENU DU JEU ====\n";
        std::cout << "1. Charger un terrain depuis un fichier\n";
        std::cout << "2. Changer le mode et afficher le terrain am�lior�\n";
        std::cout << "3. Quitter\n";
        std::cout << "Votre choix : ";
        std::cin >> choix;

        switch (choix) {


            case 1: {
                    std::cout << "Entrez le nom du fichier du terrain : ";
                    std::string nomFichier;
                    std::cin >> nomFichier;

                    try {
                        terrain = Terrain(nomFichier);
                        std::ifstream fichier(nomFichier);
                        if (!fichier.is_open()) {
                        std::cerr << "Impossible d'ouvrir le fichier terrain : " << nomFichier << "\n";
                            break;
                        }

                        std::cout << "Terrain charg� avec succ�s depuis " << nomFichier << " !\n";


                        Position depart = terrain.getPositionDepart();
                        robot = new Robot(depart, Direction::NORD);
                        observateurAffichage = std::make_unique<ObservateurAffichage>();
                        observateurStatistique = std::make_unique<ObservateurStatistique>();


                          robot->enregistrerObservateur(move(observateurAffichage));
                          robot->enregistrerObservateur(move(observateurStatistique));

                        std::cout << "Terrain initial avec le robot :\n";
                        terrain.afficherTerrain(modeTexte, *robot);

                        bool continuer = true;
                        while (continuer) {
                            std::cout << "==== OPTIONS ====\n";
                            std::cout << "1. D�placer le robot manuellement\n";
                            std::cout << "2. Ex�cuter un algorithme de sortie\n";
                            std::cout << "3. Afficher le nombre de cases parcourues par le robot\n";
                            std::cout << "4. Quitter\n";
                            std::cout << "Votre choix : ";

                            int sousChoix;
                            std::cin >> sousChoix;

                            switch (sousChoix) {
                                case 1: {
                                    char input;
                                    while (true) {


                                        std::cout << "Entrez une commande (a=avancer, g=gauche, d=droite, x=quitter): \n";

                                        input = _getch();

                                        if (input == 'x') {

                                            std::cout << "Retour au menu principal.\n";

                                            break;
                                        }

                                        switch (input) {
                                            case 'a':
                                                if (!robot->detecterObstacleEnFace(terrain)) {
                                                    robot->avancer(terrain);
                                                } else {
                                                    std::cout << "Obstacle d�tect� en face !\n";
                                                }
                                                break;

                                            case 'g':
                                                robot->tournerGauche();
                                                break;

                                            case 'd':
                                                robot->tournerDroite();
                                                break;

                                            default:
                                                std::cout << "Commande inconnue.\n";
                                                break;
                                        }


                                        terrain.afficherTerrain(modeTexte, *robot);
                                    }
                                    break;
                                }
                                case 2: {
                                    choisirAlgorithmeDeSortie();
                                    break;
                                }
                                case 3:
                                   afficherCasesParcourues();
                                                     break;
                                case 4:
                                    std::cout << "Retour au menu principal.\n";
                                    continuer = false;
                                    break;

                                default:
                                    std::cerr << "Choix invalide. Veuillez r�essayer.\n";
                            }
                        }
                    } catch (const std::exception& e) {
                        std::cerr << "Erreur : Impossible de charger le terrain : " << e.what() << "\n";
                    }
                    break;
                }






            case 2:
                choisirModeTexte();
                afficherTerrain();
                break;

            case 3:
                std::cout << "Au revoir !\n";
                break;

            default:
                std::cerr << "Choix invalide. Veuillez r�essayer.\n";
        }
    } while (choix != 3);

}

void MenuDuJeu::choisirAlgorithmeDeSortie() {
    int choix;
    std::cout << "==== CHOISIR UN ALGORITHME DE SORTIE ====\n";
    std::cout << "1. Algorithme de sortie par la main droite\n";
    std::cout << "2. Algorithme de sortie par Pledge\n";
    std::cout << "Votre choix : ";
    std::cin >> choix;

    switch (choix) {
        case 1: {
            AlgorithmeDeSortieMainDroite algorithme;
            executerAlgorithme(algorithme);
            break;
        }
        case 2: {
            AlgorithmeDeSortiePledge algorithme;
            executerAlgorithme(algorithme);
            break;
        }
        default:
            std::cerr << "Choix invalide.\n";
    }
}




void MenuDuJeu::executerAlgorithme(AlgorithmeDeSortie& algorithme) {


    algorithme.executer(*robot, terrain);

}


void MenuDuJeu::afficherCasesParcourues() const {

      if (observateurStatistique) {
        std::cout << "Nombre de cases parcourues par le robot : "
                  << observateurStatistique->getTotalDeplacements() << "\n";
    } else {
        std::cout << "Statistiques indisponibles. Le robot n'est pas initialis�.\n";
    }
}

void MenuDuJeu::choisirModeTexte() {

    int modeTexte;
    std::cout << "==== CHOISIR LE MODE TEXTE ====\n";
    std::cout << "0. Mode texte simple\n";
    std::cout << "1. Mode texte am�lior� 1\n";
    std::cout << "2. Mode texte am�lior� 2\n";
    std::cout << "Votre choix : ";
    std::cin >> modeTexte;

    switch (modeTexte) {
        case 0:
            std::cout << "Mode texte simple s�lectionn�.\n";

            break;
        case 1:
            std::cout << "Mode texte am�lior� 1 s�lectionn�.\n";

            break;
        case 2:
            std::cout << "Mode texte am�lior� 2 s�lectionn�.\n";

            break;
        default:
            std::cerr << "Choix invalide. Mode texte simple activ� par d�faut.\n";
            modeTexte = 0;
    }
}

void MenuDuJeu::afficherTerrain() {
    if (!robot) {
        std::cerr << "Erreur : Aucun robot n'a �t� plac� sur le terrain.\n";
        return;
    }
    terrain.afficherTerrain(modeTexte, *robot);
}
