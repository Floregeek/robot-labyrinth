#include <iostream>
#include <fstream>
#include "Terrain.h"
#include "Robot.h"
#include "MenuDuJeu.h"
#include <locale>
#include <conio.h>
#include "ObservateurAffichage.h"
#include "ObservateurStatistique.h"
#include "Position.h"
#include <io.h>
#include <fcntl.h>
#include <windows.h>

#include <memory>
using namespace std;

int main() {
    //setlocale(LC_ALL, "");
    SetConsoleOutputCP(65001);
 try {
        std::cout << "Bienvenue dans le jeu du robot labyrinthe !\n";
        MenuDuJeu menu;
        menu.afficherMenuPrincipal();
    } catch (const std::exception& e) {
        std::cerr << "Erreur inattendue : " << e.what() << "\n";
    } catch (...) {
        std::cerr << "Une erreur inconnue est survenue.\n";
    }
    return 0;
}

