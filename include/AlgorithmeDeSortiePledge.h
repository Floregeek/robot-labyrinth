#ifndef ALGORITHMEDESORTIEPLEDGE_H
#define ALGORITHMEDESORTIEPLEDGE_H

#include "Robot.h"
#include "Terrain.h"
#include "AlgorithmeDeSortie.h"

class AlgorithmeDeSortiePledge: public AlgorithmeDeSortie
{
private :
    int modetext=0;
   public:
   void executer(Robot& robot, const Terrain& terrain)override;
};

#endif
