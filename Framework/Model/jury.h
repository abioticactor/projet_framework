#ifndef JURY_H
#define JURY_H

#include "enseignant.h"
#include "creneau.h"
#include <memory> // Pour std::shared_ptr

class Jury
{
private:
    std::shared_ptr<Enseignant> president;
    std::shared_ptr<Enseignant> cojury;
    std::shared_ptr<Creneau> m_creneauAttribue;


public:
    Jury();
    Jury(std::shared_ptr<Enseignant> president, std::shared_ptr<Enseignant> cojury);
    std::shared_ptr<Enseignant> getPresident() const;
    std::shared_ptr<Enseignant> getCojury() const;
    void setPresident(std::shared_ptr<Enseignant> president);
    void setCojury(std::shared_ptr<Enseignant> cojury);
    bool verifDispo();
    // NOUVEAU : Setter/Getter pour le créneau
    void setCreneauAttribue(std::shared_ptr<Creneau> c);
    std::shared_ptr<Creneau> getCreneauAttribue() const;

};

#endif // JURY_H
