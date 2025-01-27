#ifndef CALENDRIER_H
#define CALENDRIER_H

#include "creneau.h"
#include <iostream>
#include <vector>
#include <algorithm>
#include <memory> // Ajout pour std::shared_ptr


class Calendrier
{
private:
    int taille=0;
    std::vector<std::shared_ptr<Creneau>> creneaux; // Utilisation de shared_ptr

public:
    Calendrier();
    std::vector<std::shared_ptr<Creneau>> getCalendrier() const;
    int getTaille();
    void ajouteCreneau(std::shared_ptr<Creneau> c);
    void retireCreneau(std::shared_ptr<Creneau> c);
    bool estDispo(std::shared_ptr<Creneau> c);
    void triCreneau();
};

#endif // CALENDRIER_H
