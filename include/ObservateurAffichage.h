#ifndef OBSERVATEURAFFICHAGE_H
#define OBSERVATEURAFFICHAGE_H
#include "Robot.h"
#include "Observateur.h"
class ObservateurAffichage : public Observateur
{
    public:

  void MettreAjour( Robot& robot) override;

};

#endif // OBSERVATEURAFFICHAGE_H
