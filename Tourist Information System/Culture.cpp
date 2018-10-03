#include "Culture.hpp"
#include <iostream> // for std::fixed
#include <iomanip> // for std::setprecision()
#include "Attraction.hpp"

Culture::Culture()
{
}

Culture::Culture(std::string name, int typeID, std::string address, std::string days, std::string hours, std::string contact, double entranceFee, std::string museumType)
: Attraction(name, typeID, address, days, hours, contact), entranceFee(entranceFee), museumType(museumType)
{
}

double Culture::getEntranceFee() const
{
    return entranceFee;
}

std::string Culture::getMuseumType() const
{
    return museumType;
}

void Culture::setEntranceFee(double entranceFee)
{
    this->entranceFee = entranceFee;
}

void Culture::setMuseumType(std::string museumType)
{
    this->museumType = museumType;
}

void Culture::display() const
{
    std::cout << "1. Name: " << getName() << "\n";
    std::cout << "2. Address: " << getAddress() << "\n";
    std::cout << "3. Opening Days: " << getDays() << "\n";
    std::cout << "4. Opening Hours: " << getHours() << "\n";
    std::cout << "5. Contact No: " << getContact() << "\n";
    std::cout << "6. Entrance Fee: RM " << std::fixed << std::setprecision(2) << entranceFee << "\n";
    std::cout << "7. Musuem Type: " << museumType << "\n";
}
