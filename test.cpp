#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "Position.h"
#include "AlgorithmeDeSortieMainDroite.h"
#include "AlgorithmeDeSortiePledge.h"
#include "Robot.h"
#include "Terrain.h"
#include <vector>


TEST_CASE("[Robot] Test de la méthode tournerGauche()") {
    {
        Position initialPosition(0, 0);
        Robot robot(initialPosition, Direction::NORD);
        robot.tournerGauche();
        REQUIRE(robot.getDirectionRobot() == Direction::OUEST);
    }

    {
        Position initialPosition(0, 0);
        Robot robot(initialPosition, Direction::EST);
        robot.tournerGauche();
        REQUIRE(robot.getDirectionRobot() == Direction::NORD);
    }

    {
        Position initialPosition(0, 0);
        Robot robot(initialPosition, Direction::SUD);
        robot.tournerGauche();
        REQUIRE(robot.getDirectionRobot() == Direction::EST);
    }

    {
        Position initialPosition(0, 0);
        Robot robot(initialPosition, Direction::OUEST);
        robot.tournerGauche();
        REQUIRE(robot.getDirectionRobot() == Direction::SUD);
    }
}

TEST_CASE("[Robot] Test de la méthode tournerDroite()") {
    {
        Position initialPosition(0, 0);
        Robot robot(initialPosition, Direction::NORD);
        robot.tournerDroite();
        REQUIRE(robot.getDirectionRobot() == Direction::EST);
    }

    {
        Position initialPosition(0, 0);
        Robot robot(initialPosition, Direction::EST);
        robot.tournerDroite();
        REQUIRE(robot.getDirectionRobot() == Direction::SUD);
    }

    {
        Position initialPosition(0, 0);
        Robot robot(initialPosition, Direction::SUD);
        robot.tournerDroite();
        REQUIRE(robot.getDirectionRobot() == Direction::OUEST);
    }

    {
        Position initialPosition(0, 0);
        Robot robot(initialPosition, Direction::OUEST);
        robot.tournerDroite();
        REQUIRE(robot.getDirectionRobot() == Direction::NORD);
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

    REQUIRE(terrain.getPositionDepart() == Position(2, 1));
    REQUIRE(terrain.getPositionArrivee() == Position(2, 4));

    auto obstacles = terrain.obtenirObstacles();
    REQUIRE(obstacles.empty());

    std::remove("test_terrain.txt");
}

TEST_CASE("Sauvegarde du terrain dans un fichier") {
    Terrain terrain("test_terrain_valid.txt");
    std::string fichierSauvegarde = "test_terrain_save.txt";

    terrain.sauvegarderDansFichier(fichierSauvegarde);

    Terrain terrainCharge(fichierSauvegarde);
    REQUIRE(terrainCharge.getPositionDepart() == terrain.getPositionDepart());
    REQUIRE(terrainCharge.getPositionArrivee() == terrain.getPositionArrivee());
    REQUIRE(terrainCharge.obtenirObstacles() == terrain.obtenirObstacles());
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

    REQUIRE(terrain.estMur(Position(0, 0)) == false);
    REQUIRE(terrain.estMur(Position(2, 2)) == true);
    REQUIRE(terrain.estMur(Position(5, 4)) == true);
    REQUIRE(terrain.estMur(Position(2, 1)) == false);

    std::remove("test_terrain_mur.txt");
}

TEST_CASE("Affichage du terrain") {
    Terrain terrain("test_terrain_valid.txt");
    Robot robot(Position(1, 1), Direction::EST);

    SUBCASE("Affichage brut") {
        REQUIRE_NOTHROW(terrain.afficherTerrain(0, robot));
    }

    SUBCASE("Affichage ASCII") {
        REQUIRE_NOTHROW(terrain.afficherTerrain(1, robot));
    }

    SUBCASE("Affichage Unicode") {
        REQUIRE_NOTHROW(terrain.afficherTerrain(2, robot));
    }
}

TEST_CASE("Test de la méthode avancer") {
    Terrain terrain("terrain.txt");
    Robot robot(Position(2, 1), Direction::EST);

    robot.avancer(terrain);

    REQUIRE(robot.getPosition() == Position(3, 1));
}

TEST_CASE("Test de la méthode tournerGauche") {
    Robot robot(Position(2, 1), Direction::EST);

    robot.tournerGauche();
    REQUIRE(robot.getDirectionRobot() == Direction::NORD);

    robot.tournerGauche();
    REQUIRE(robot.getDirectionRobot() == Direction::OUEST);

    robot.tournerGauche();
    REQUIRE(robot.getDirectionRobot() == Direction::SUD);

    robot.tournerGauche();
    REQUIRE(robot.getDirectionRobot() == Direction::EST);
}

TEST_CASE("Test de la méthode tournerDroite") {
    Robot robot(Position(2, 1), Direction::EST);

    robot.tournerDroite();
    REQUIRE(robot.getDirectionRobot() == Direction::SUD);

    robot.tournerDroite();
    REQUIRE(robot.getDirectionRobot() == Direction::OUEST);

    robot.tournerDroite();
    REQUIRE(robot.getDirectionRobot() == Direction::NORD);

    robot.tournerDroite();
    REQUIRE(robot.getDirectionRobot() == Direction::EST);
}

TEST_CASE("Test de getPosition()") {
    Position positionInitiale(5, 10);
    Robot robot(positionInitiale, Direction::NORD);

    REQUIRE(robot.getPosition().getX() == 5);
    REQUIRE(robot.getPosition().getY() == 10);
}

TEST_CASE("Test de getDirectionRobot()") {
    Robot robot(Position(0, 0), Direction::SUD);

    REQUIRE(robot.getDirectionRobot() == Direction::SUD);
}

TEST_CASE("Test de directionToString()") {
    Robot robot(Position(0, 0), Direction::EST);

    REQUIRE(robot.directionToString(Direction::NORD) == "NORD");
    REQUIRE(robot.directionToString(Direction::EST) == "EST");
    REQUIRE(robot.directionToString(Direction::SUD) == "SUD");
    REQUIRE(robot.directionToString(Direction::OUEST) == "OUEST");
}
TEST_CASE("Test de l'algorithme de sortie Pledge") {
    Terrain terrain("terrain_description");

    Position positionDepart(0, 0);
    Robot robot(positionDepart, Direction::NORD);

    AlgorithmeDeSortiePledge algo;
    algo.executer(robot, terrain);

    REQUIRE(robot.getPosition() == terrain.getPositionArrivee());
}
TEST_CASE("Test de l'algorithme de sortie Main Droite") {
    Terrain terrain("terrain.txt");

    Position positionDepart(0, 0);
    Robot robot(positionDepart, Direction::NORD);

    AlgorithmeDeSortieMainDroite algo;
    algo.executer(robot, terrain);

    REQUIRE(robot.getPosition() == terrain.getPositionArrivee());
}



