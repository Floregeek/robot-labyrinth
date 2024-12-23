#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "Position.h"
#include "Robot.h"
#include "Terrain.h"
#include <vector>


TEST_CASE("[Robot] Test de la m�thode tournerGauche()") {
    // Test pour tourner � gauche � partir de la direction NORD
    {
        Position initialPosition(0, 0);
        Robot robot(initialPosition, Direction::NORD);
        robot.tournerGauche(); // Le robot tourne � gauche (devrait aller vers OUEST)

        REQUIRE(robot.getDirectionRobot() == Direction::OUEST); // La direction doit �tre OUEST
    }

    // Test pour tourner � gauche � partir de la direction EST
    {
        Position initialPosition(0, 0);
        Robot robot(initialPosition, Direction::EST);
        robot.tournerGauche(); // Le robot tourne � gauche (devrait aller vers NORD)

        REQUIRE(robot.getDirectionRobot() == Direction::NORD); // La direction doit �tre NORD
    }

    // Test pour tourner � gauche � partir de la direction SUD
    {
        Position initialPosition(0, 0);
        Robot robot(initialPosition, Direction::SUD);
        robot.tournerGauche(); // Le robot tourne � gauche (devrait aller vers EST)

        REQUIRE(robot.getDirectionRobot() == Direction::EST); // La direction doit �tre EST
    }

    // Test pour tourner � gauche � partir de la direction OUEST
    {
        Position initialPosition(0, 0);
        Robot robot(initialPosition, Direction::OUEST);
        robot.tournerGauche(); // Le robot tourne � gauche (devrait aller vers SUD)

        REQUIRE(robot.getDirectionRobot() == Direction::SUD); // La direction doit �tre SUD
    }
}

TEST_CASE("[Robot] Test de la m�thode tournerDroite()") {
    // Test pour tourner � droite � partir de la direction NORD
    {
        Position initialPosition(0, 0);
        Robot robot(initialPosition, Direction::NORD);
        robot.tournerDroite(); // Le robot tourne � droite (devrait aller vers EST)

        REQUIRE(robot.getDirectionRobot() == Direction::EST); // La direction doit �tre EST
    }

    // Test pour tourner � droite � partir de la direction EST
    {
        Position initialPosition(0, 0);
        Robot robot(initialPosition, Direction::EST);
        robot.tournerDroite(); // Le robot tourne � droite (devrait aller vers SUD)

        REQUIRE(robot.getDirectionRobot() == Direction::SUD); // La direction doit �tre SUD
    }

    // Test pour tourner � droite � partir de la direction SUD
    {
        Position initialPosition(0, 0);
        Robot robot(initialPosition, Direction::SUD);
        robot.tournerDroite(); // Le robot tourne � droite (devrait aller vers OUEST)

        REQUIRE(robot.getDirectionRobot() == Direction::OUEST); // La direction doit �tre OUEST
    }

    // Test pour tourner � droite � partir de la direction OUEST
    {
        Position initialPosition(0, 0);
        Robot robot(initialPosition, Direction::OUEST);
        robot.tournerDroite(); // Le robot tourne � droite (devrait aller vers NORD)

        REQUIRE(robot.getDirectionRobot() == Direction::NORD); // La direction doit �tre NORD
    }
}


TEST_CASE("[Terrain] Test de la m�thode chargerDepuisFichier") {
    // Cr�e un fichier de test temporaire
    std::ofstream fichier("test_terrain.txt");
    fichier << ".....\n"
            << "..D..\n"
            << ".....\n"
            << ".....\n"
            << "..A..\n";
    fichier.close();

    // Test du chargement du terrain depuis le fichier
    Terrain terrain("test_terrain.txt");

    // V�rifie que les positions de d�part et d'arriv�e sont bien charg�es
    REQUIRE(terrain.getPositionDepart() == Position(2, 1));  // Position 'D'
    REQUIRE(terrain.getPositionArrivee() == Position(2, 4));  // Position 'A'

    // V�rifie que la grille est correctement charg�e
    auto obstacles = terrain.obtenirObstacles();
    REQUIRE(obstacles.empty());  // Pas d'obstacles dans ce terrain

    // Nettoie le fichier apr�s test
    std::remove("test_terrain.txt");
}

TEST_CASE("[Terrain] Test de la m�thode sauvegarderDansFichier") {
    // Cr�e un terrain � sauvegarder
    Terrain terrain("test_terrain.txt");
    terrain.sauvegarderDansFichier("terrain_sauvegard�.txt");

    // Ouvre le fichier sauvegard� pour v�rification
    std::ifstream fichier("terrain_sauvegard�.txt");
    std::string contenu;
    std::string ligne;

    while (std::getline(fichier, ligne)) {
        contenu += ligne + "\n";
    }

    // V�rifie que le fichier sauvegard� correspond au terrain attendu
    REQUIRE(contenu == ".....\n..D..\n.....\n.....\n..A..\n");

    // Nettoie le fichier apr�s test
    std::remove("terrain_sauvegard�.txt");
}

TEST_CASE("[Terrain] Test de la m�thode estMur") {
    // Cr�e un terrain avec des obstacles
    std::ofstream fichier("test_terrain_mur.txt");
    fichier << ".....\n"
            << "..D..\n"
            << "..X..\n"
            << ".....\n"
            << "..A..\n";
    fichier.close();

    // Test du chargement du terrain depuis le fichier
    Terrain terrain("test_terrain_mur.txt");

    // Test des diff�rentes positions
    REQUIRE(terrain.estMur(Position(0, 0)) == false);  // Pas un mur
    REQUIRE(terrain.estMur(Position(2, 2)) == true);   // C'est un obstacle ('X')
    REQUIRE(terrain.estMur(Position(5, 4)) == true);   // Hors limites
    REQUIRE(terrain.estMur(Position(2, 1)) == false);  // Case vide, pas un mur

    // Nettoie le fichier apr�s test
    std::remove("test_terrain_mur.txt");
}
