#include "Util.hpp"
#include <iostream>
#include <sstream> // for std::stringstream()
#include <cstdlib> // for atoi(), atof(), system("CLS")
#include <limits> // for std::numeric_limits<std::streamsize>::max()
#include "City.hpp"
#include "Attraction.hpp"
#include "LinkedList.cpp"

namespace util
{
    int getIntInputWithin(int range)
    {
        std::cout << "Selection: ";
        std::string strInput;
        int intInput;
        while(true)
        {
            std::getline(std::cin, strInput);
            if (!(std::stringstream(strInput) >> intInput))
            {
                std::cout << strInput << " is not an integer. Valid input is from 1 to " << range << ". Please try again.\n\n";
                std::cout << "Selection: ";
            }
            else if (!(intInput >= 1 && intInput <= range))
            {
                std::cout << intInput << " is out of bounds. Valid input is from 1 to " << range << ". Please try again.\n\n";
                std::cout << "Selection: ";
            }
            else
                break;
        }
        std::cout << "\n";
        return intInput;
    }

    int getIntInput()
    {
        std::cout << "==> ";
        std::string strInput;
        int intInput;
        while(true)
        {
            std::getline(std::cin, strInput);
            if (std::stringstream(strInput) >> intInput)
                break;
            else
            {
                std::cout << strInput << " is not an integer. Please try again.\n\n";
                std::cout << "==> ";
            }
        }
        std::cout << "\n";
        return intInput;
    }

    double getDoubleInput()
    {
        std::cout << "==> ";
        std::string strInput;
        double doubleInput;
        while(true)
        {
            std::getline(std::cin, strInput);
            if (std::stringstream(strInput) >> doubleInput)
                break;
            else
            {
                std::cout << strInput << " is not a double. Please try again.\n\n";
                std::cout << "==> ";
            }
        }
        std::cout << "\n";
        return doubleInput;
    }

    std::string getStrInput()
    {
        std::cout << "==> ";
        std::string strInput;
        std::getline(std::cin, strInput);
        std::cout << "\n";
        return strInput;
    }

    int strToInt(std::string str)
    {
        return atoi(str.c_str());
    }

    double strToDouble(std::string str)
    {
        return atof(str.c_str());
    }

    void toUpperCase(char& letter)
    {
        if (islower(letter))
            letter = toupper(letter);
    }

    void clearScreen()
    {
        system("CLS");
    }

    void pauseScreen()
    {
        std::cout << "Press ENTER to continue...\n";
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
        std::cout << "\n";
    }

    void printCitiesName(const LinkedList<City*> cities)
    {
        int citiesLength = cities.getLength();
        for (int i = 0; i < citiesLength; i++)
            std::cout << "(" << i + 1 << ") " << cities.getEntry(i)->getName() << "\n";
    }

    void printAttractionsName(const LinkedList<Attraction*> attractions)
    {
        int attractionsLength = attractions.getLength();
        for (int i = 0; i < attractionsLength; i++)
            std::cout << "(" << i + 1 << ") " << attractions.getEntry(i)->getName() << "\n";
    }
}
