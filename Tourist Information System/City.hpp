#ifndef CITY_HPP
#define CITY_HPP

#include "Attraction.hpp"
#include <iostream>
#include "LinkedList.cpp"

class City
{
private:
    int id;
    std::string name;
    LinkedList<Attraction*> attractions; // Container to store attractions data

public:
    City();
    City(int id, std::string name);

    int getId() const;
    std::string getName() const;
    LinkedList<Attraction*> getAttractions() const;
    int getAttractionsLength() const;
    Attraction* getAttraction(int index) const;

    void setId(int id);
    void setName(std::string name);
    void addAttraction(Attraction* attraction);
    void removeAttraction(int position);

    ~City(); // Free memory allocated to attractions container
};

#endif // CITY_HPP
