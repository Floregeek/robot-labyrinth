#include "ObservateurAffichage.h"

 void ObservateurAffichage::MettreAjour( Robot& robot){
        std::cout << " Le robot s'est déplacé à la position ("
                  << robot.getPosition().getX() << ", " << robot.getPosition().getY()
                  << ") avec la direction '" << robot.directionToString(robot.getDirectionRobot()) << "'.\n";
    }


