#ifndef ALGORITHMEDESORTIE_H
#define ALGORITHMEDESORTIE_H

#include "Robot.h"
#include "Terrain.h"
class AlgorithmeDeSortie
{
public:
virtual ~AlgorithmeDeSortie()= default;
virtual void executer(Robot& robot, const Terrain& terrain) = 0;
};



#endif // ALGORITHMEDESORTIE_H
