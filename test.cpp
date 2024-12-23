#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "Position.h"
#include "Robot.h"
#include "Terrain.h"
#include <vector>


TEST_CASE("[Robot] Test de la méthode tournerGauche()") {
   
    {
        Position initialPosition(0, 0);
        Robot robot(initialPosition, Direction::NORD);
        robot.tournerGauche(); // Le robot tourne à gauche (devrait aller vers OUEST)

        REQUIRE(robot.getDirectionRobot() == Direction::OUEST); // La direction doit être OUEST
    }

   
    {
        Position initialPosition(0, 0);
        Robot robot(initialPosition, Direction::EST);
        robot.tournerGauche(); // Le robot tourne à gauche (devrait aller vers NORD)

        REQUIRE(robot.getDirectionRobot() == Direction::NORD); // La direction doit être NORD
    }

    {
        Position initialPosition(0, 0);
        Robot robot(initialPosition, Direction::SUD);
        robot.tournerGauche(); // Le robot tourne à gauche (devrait aller vers EST)

        REQUIRE(robot.getDirectionRobot() == Direction::EST); // La direction doit être EST
    }

   
    {
        Position initialPosition(0, 0);
        Robot robot(initialPosition, Direction::OUEST);
        robot.tournerGauche(); // Le robot tourne à gauche (devrait aller vers SUD)

        REQUIRE(robot.getDirectionRobot() == Direction::SUD); // La direction doit être SUD
    }
}

TEST_CASE("[Robot] Test de la méthode tournerDroite()") {
    
    {
        Position initialPosition(0, 0);
        Robot robot(initialPosition, Direction::NORD);
        robot.tournerDroite(); // Le robot tourne à droite (devrait aller vers EST)

        REQUIRE(robot.getDirectionRobot() == Direction::EST); // La direction doit être EST
    }

  
    {
        Position initialPosition(0, 0);
        Robot robot(initialPosition, Direction::EST);
        robot.tournerDroite(); // Le robot tourne à droite (devrait aller vers SUD)

        REQUIRE(robot.getDirectionRobot() == Direction::SUD); // La direction doit être SUD
    }


    {
        Position initialPosition(0, 0);
        Robot robot(initialPosition, Direction::SUD);
        robot.tournerDroite(); // Le robot tourne à droite (devrait aller vers OUEST)

        REQUIRE(robot.getDirectionRobot() == Direction::OUEST); // La direction doit être OUEST
    }

    
    {
        Position initialPosition(0, 0);
        Robot robot(initialPosition, Direction::OUEST);
        robot.tournerDroite(); // Le robot tourne à droite (devrait aller vers NORD)

        REQUIRE(robot.getDirectionRobot() == Direction::NORD); // La direction doit être NORD
    }
}


TEST_CASE("[Terrain] Test de la méthode chargerDepuisFichier") {
   
    std::ofstream fichier("test_terrain.txt");
    fichier << ".....\n"
            << "..D..\n"
            << ".....\n"
            << ".....\n"
            << "..A..\n";
    fichier.close();

    
    Terrain terrain("test_terrain.txt");

    
    REQUIRE(terrain.getPositionDepart() == Position(2, 1));  // Position 'D'
    REQUIRE(terrain.getPositionArrivee() == Position(2, 4));  // Position 'A'

    
    auto obstacles = terrain.obtenirObstacles();
    REQUIRE(obstacles.empty());  // Pas d'obstacles dans ce terrain

  
    std::remove("test_terrain.txt");
}

TEST_CASE("[Terrain] Test de la méthode sauvegarderDansFichier") {
   
    Terrain terrain("test_terrain.txt");
    terrain.sauvegarderDansFichier("terrain_sauvegardé.txt");

  
    std::ifstream fichier("terrain_sauvegardé.txt");
    std::string contenu;
    std::string ligne;

    while (std::getline(fichier, ligne)) {
        contenu += ligne + "\n";
    }

   
    REQUIRE(contenu == ".....\n..D..\n.....\n.....\n..A..\n");

    
    std::remove("terrain_sauvegardé.txt");
}

TEST_CASE("[Terrain] Test de la méthode estMur") {
   
    std::ofstream fichier("test_terrain_mur.txt");
    fichier << ".....\n"
            << "..D..\n"
            << "..X..\n"
            << ".....\n"
            << "..A..\n";
    fichier.close();

   
    Terrain terrain("test_terrain_mur.txt");

    
    REQUIRE(terrain.estMur(Position(0, 0)) == false);  // Pas un mur
    REQUIRE(terrain.estMur(Position(2, 2)) == true);   // C'est un obstacle ('X')
    REQUIRE(terrain.estMur(Position(5, 4)) == true);   // Hors limites
    REQUIRE(terrain.estMur(Position(2, 1)) == false);  // Case vide, pas un mur

    
    std::remove("test_terrain_mur.txt");
}
