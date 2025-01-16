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
    std::string getDate();
    std::string getHeure();
    void setDate(std::string d);
    void setHeure(std::string h);
    bool operator < (Creneau& c);
    bool operator > (Creneau& c);
    bool operator == (Creneau& c);
};

#endif // CRENEAU_H
