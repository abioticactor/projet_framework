#ifndef CRENEAU_H
#define CRENEAU_H

#include <iostream>

class Creneau
{
private:
    std::string date;
    std::string heure;

public:
    Creneau();
    Creneau(std::string date,std::string heure);
    std::string getDate() const;
    std::string getHeure() const;
    void setDate(std::string d);
    void setHeure(std::string h);
    bool operator < (const Creneau& c) const;
    bool operator > (const Creneau& c) const;
    bool operator == (const Creneau& c) const;
};

#endif // CRENEAU_H
