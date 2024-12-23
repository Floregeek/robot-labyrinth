#ifndef OBSERVATEUR_H
#define OBSERVATEUR_H
#include "Position.h"
#include "Robot.h"
class Robot;
class Observateur
{
    public:

        virtual void MettreAjour(Robot& robot) = 0;
        virtual ~Observateur() = default;


};

#endif // OBSERVATEUR_H
