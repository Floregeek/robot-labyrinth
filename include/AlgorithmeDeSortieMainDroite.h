#ifndef ALGORITHMEDESORTIEMAINDROITE_H
#define ALGORITHMEDESORTIEMAINDROITE_H

#include<iostream>
#include "Robot.h"
#include "Terrain.h"
#include "AlgorithmeDeSortie.h"

class AlgorithmeDeSortieMainDroite: public AlgorithmeDeSortie
{
public:
void executer(Robot& robot, const Terrain& terrain)override;
};

#endif // ALGORITHMEDESORTIEMAINDROITE_H