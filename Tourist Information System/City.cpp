#include "City.hpp"
#include <iostream>
#include "Sport.hpp"
#include "Culture.hpp"
#include "Shopping.hpp"
#include "LinkedList.cpp"

City::City()
{
}

City::City(int id, std::string name) : id(id), name(name)
{
}

int City::getId() const
{
    return id;
}

std::string City::getName() const
{
    return name;
}

LinkedList<Attraction*> City::getAttractions() const
{
    return attractions;
}

int City::getAttractionsLength() const
{
    return attractions.getLength();
}

Attraction* City::getAttraction(int index) const
{
    return attractions.getEntry(index);
}

void City::setId(int id)
{
    this->id = id;
}

void City::setName(std::string name)
{
    this->name = name;
}

void City::addAttraction(Attraction* attraction)
{
    attractions.insert(attractions.getLength(), attraction);
}

void City::removeAttraction(int position)
{
    attractions.remove(position);
}

City::~City()
{
    attractions.clear(); // Free memory allocated to attractions container
}
