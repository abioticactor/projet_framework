#include "creneau.h"

Creneau::Creneau() {}

Creneau::Creneau(std::string date, std::string heure){
    this->date=date;
    this->heure=heure;
}

std::string Creneau::getDate(){
    return this->date;
}

std::string Creneau::getHeure(){
    return this->heure;
}

void Creneau::setDate(std::string d){
    this->date=d;
}

void Creneau::setHeure(std::string h){
    this->heure=h;
}

bool Creneau::operator == (Creneau& c){
    return (this->date==c.getDate())&(this->heure==c.getHeure());
}

bool Creneau::operator < (Creneau& c){
    if ((this->date==c.getDate())&(this->heure<c.getHeure())){
        return true;
    }
    else if (this->date<c.getDate()){
        return true;
    }
    else{
        return false;
    }
}

bool Creneau::operator > (Creneau& c){
    if ((this->date==c.getDate())&(this->heure>c.getHeure())){
        return true;
    }
    else if (this->date>c.getDate()){
        return true;
    }
    else{
        return false;
    }
}
