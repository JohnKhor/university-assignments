#include "Sport.hpp"
#include <iostream>
#include "Attraction.hpp"

Sport::Sport(std::string name, int typeID, std::string address, std::string days, std::string hours, std::string contact, int ageLimit, std::string sportType)
: Attraction(name, typeID, address, days, hours, contact), ageLimit(ageLimit), sportType(sportType)
{
}

Sport::Sport()
{
}

int Sport::getAgeLimit() const
{
    return ageLimit;
}

std::string Sport::getSportType() const
{
    return sportType;
}

void Sport::setAgeLimit(int ageLimit)
{
    this->ageLimit = ageLimit;
}

void Sport::setSportType(std::string sportType)
{
    this->sportType = sportType;
}

void Sport::display() const
{
    std::cout << "1. Name: " << getName() << "\n";
    std::cout << "2. Address: " << getAddress() << "\n";
    std::cout << "3. Opening Days: " << getDays() << "\n";
    std::cout << "4. Opening Hours: " << getHours() << "\n";
    std::cout << "5. Contact No: " << getContact() << "\n";
    std::cout << "6. Age Limit: " << ageLimit << "\n";
    std::cout << "7. Sport Type: " << sportType << "\n";
}
