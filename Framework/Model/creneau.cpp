#include "creneau.h"

Creneau::Creneau() {}

Creneau::Creneau(std::string date, std::string heure){
    this->date=date;
    this->heure=heure;
}

std::string Creneau::getDate() const{
    return this->date;
}

std::string Creneau::getHeure() const{
    return this->heure;
}

void Creneau::setDate(std::string d){
    this->date=d;
}

void Creneau::setHeure(std::string h){
    this->heure=h;
}

bool Creneau::operator==(const Creneau& c) const {
    return (this->date == c.getDate()) && (this->heure == c.getHeure());
}


bool Creneau::operator<(const Creneau& c) const {
    if ((this->date == c.getDate()) && (this->heure < c.getHeure())) {
        return true;
    } else if (this->date < c.getDate()) {
        return true;
    } else {
        return false;
    }
}

bool Creneau::operator>(const Creneau& c) const {
    if ((this->date == c.getDate()) && (this->heure > c.getHeure())) {
        return true;
    } else if (this->date > c.getDate()) {
        return true;
    } else {
        return false;
    }
}

