#ifndef OBSERVATEURSTATISTIQUE_H
#define OBSERVATEURSTATISTIQUE_H
#include "Observateur.h"
#include "Robot.h"

class ObservateurStatistique : public Observateur
{
    public:
    ObservateurStatistique();
    void MettreAjour( Robot& robot) override;
    int getTotalDeplacements() const;

    private :
      int d_totalRotations;
      int d_totalDeplacements;
      std:: string d_derniereDirection;
      Position d_dernierePosition;

};

#endif // OBSERVATEURSTATISTIQUE_H
