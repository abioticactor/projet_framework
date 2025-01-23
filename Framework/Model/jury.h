#ifndef JURY_H
#define JURY_H

#include "enseignant.h"
#include <memory> // Pour std::shared_ptr

class Jury
{
private:
    std::shared_ptr<Enseignant> president;
    std::shared_ptr<Enseignant> cojury;

public:
    Jury();
    Jury(std::shared_ptr<Enseignant> president, std::shared_ptr<Enseignant> cojury);
    std::shared_ptr<Enseignant> getPresident() const;
    std::shared_ptr<Enseignant> getCojury() const;
    void setPresident(std::shared_ptr<Enseignant> president);
    void setCojury(std::shared_ptr<Enseignant> cojury);
    bool verifDispo();

};

#endif // JURY_H
