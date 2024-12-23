#include "ObservateurStatistique.h"
#include <fstream>
#include <iostream>
#include <sstream>
ObservateurStatistique::ObservateurStatistique(): d_totalRotations(0), d_totalDeplacements(0),
d_derniereDirection(""), d_dernierePosition(1,1)
{}
 void ObservateurStatistique::MettreAjour(Robot& robot){


         if (d_derniereDirection != robot.directionToString(robot.getDirectionRobot())) {
            d_totalRotations++;
        }
        d_derniereDirection = robot.directionToString(robot.getDirectionRobot());

        if (d_dernierePosition != robot.getPosition()){
                               d_totalDeplacements++;}
        d_dernierePosition = robot.getPosition();

        std::cout << "Statistiques mises à jour :\n"
                  << "  - Total des déplacements : " << d_totalDeplacements << "\n"
                  << "  - Total des rotations : " << d_totalRotations << "\n";
    }
    int ObservateurStatistique::getTotalDeplacements() const{
         return d_totalDeplacements;
    }


