#include "ObservateurAffichage.h"

 void ObservateurAffichage::MettreAjour( Robot& robot){
        std::cout << " Le robot s'est d�plac� � la position ("
                  << robot.getPosition().getX() << ", " << robot.getPosition().getY()
                  << ") avec la direction '" << robot.directionToString(robot.getDirectionRobot()) << "'.\n";
    }


