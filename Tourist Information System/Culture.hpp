#ifndef CULTURE_HPP
#define CULTURE_HPP

#include <iostream>
#include "Attraction.hpp"

// Derived class of Attraction
class Culture: public Attraction
{
private:
    double entranceFee;
    std::string museumType;

public:
    Culture();
    Culture(std::string name, int typeID, std::string address, std::string days, std::string hours, std::string contact, double entranceFee, std::string museumType);

    double getEntranceFee() const;
    std::string getMuseumType() const;

    void setEntranceFee(double entranceFee);
    void setMuseumType(std::string museumType);

    virtual void display() const;
};

#endif // CULTURE_HPP
