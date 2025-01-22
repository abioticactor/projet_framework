#ifndef JURY_H
#define JURY_H

#include "enseignant.h"

class Jury
{
private:
    Enseignant* president;
    Enseignant* cojury;

public:
    Jury();
    Jury(Enseignant* president, Enseignant* cojury);
    Enseignant getPresident();
    Enseignant getCojury();
    void setPresident(Enseignant* president);
    void setCojury(Enseignant* cojury);
    bool verifDispo();

};

#endif // JURY_H
