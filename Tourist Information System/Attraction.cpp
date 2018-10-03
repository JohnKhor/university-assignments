#include "Attraction.hpp"

Attraction::Attraction()
{
}

Attraction::Attraction(std::string name, int typeID, std::string address, std::string days, std::string hours, std::string contact)
: name(name), typeID(typeID), address(address), days(days), hours(hours), contact(contact)
{
}

Attraction::~Attraction()
{
}

std::string Attraction::getName() const
{
    return name;
}

int Attraction::getTypeID() const
{
    return typeID;
}

std::string Attraction::getAddress() const
{
    return address;
}

std::string Attraction::getDays() const
{
    return days;
}

std::string Attraction::getHours() const
{
    return hours;
}

std::string Attraction::getContact() const
{
    return contact;
}

void Attraction::setName(std::string name)
{
    this->name = name;
}

void Attraction::setTypeID(int typeID)
{
    this->typeID = typeID;
}

void Attraction::setAddress(std::string address)
{
    this->address = address;
}

void Attraction::setDays(std::string days)
{
    this->days = days;
}

void Attraction::setHours(std::string hours)
{
    this->hours = hours;
}

void Attraction::setContact(std::string contact)
{
    this->contact = contact;
}
