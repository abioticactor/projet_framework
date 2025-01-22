#ifndef CALENDRIER_H
#define CALENDRIER_H

#include "creneau.h"
#include <iostream>
#include <vector>
#include <algorithm>

class Calendrier
{
private:
    int taille=0;
    std::vector<Creneau*> creneaux;

public:
    Calendrier();
    std::vector<Creneau*> getCalendrier() const;
    int getTaille();
    void ajouteCreneau(Creneau* c);
    void retireCreneau(Creneau* c);
    bool estDispo(Creneau* c);
    void triCreneau();
};

#endif // CALENDRIER_H
