#ifndef UTIL_HPP
#define UTIL_HPP

#include <iostream>
#include "City.hpp"
#include "Attraction.hpp"
#include "LinkedList.cpp"

// Utility functions used in TourismSystem
namespace util
{
    int getIntInputWithin(int range);
    int getIntInput();
    double getDoubleInput();
    std::string getStrInput();

    int strToInt(std::string str);
    double strToDouble(std::string str);

    void toUpperCase(char& letter);

    void clearScreen();
    void pauseScreen();

    void printCitiesName(const LinkedList<City*> cities);
    void printAttractionsName(const LinkedList<Attraction*> attractions);
}

#endif // UTIL_HPP
