#ifndef SPORT_HPP
#define SPORT_HPP

#include <iostream>
#include "Attraction.hpp"

// Derived class of Attraction
class Sport: public Attraction
{
private:
    int ageLimit;
    std::string sportType;

public:
    Sport();
    Sport(std::string name, int typeID, std::string address, std::string days, std::string hours, std::string contact, int ageLimit, std::string sportType);

    int getAgeLimit() const;
    std::string getSportType() const;

    void setAgeLimit(int ageLimit);
    void setSportType(std::string sportType);

    virtual void display() const;
};

#endif // SPORT_HPP
