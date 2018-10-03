#ifndef TOURISM_SYSTEM_HPP
#define TOURISM_SYSTEM_HPP

#include "City.hpp"
#include "LinkedList.cpp"
#include "AdjacencyMatrix.hpp"

// The main class
class TourismSystem
{
private:
    LinkedList<City*> cities; // Container to store cities data
    AdjacencyMatrix* flightMap; // Container to store flight information

public:
    void run(); // Main function to run the system

private:
    bool loadData(); // Load data from a text file
    bool saveData(); // Save data to a text file

    void menu(); // Main menu. Ask for identity

    void selectCity(); // User select a city to either view its attractions or flight information
    void viewFlightInfo(int position); // User view flight information
    void selectType(const City& city); // User select a type of attraction
    void selectAttraction(const City& city, int type); // User select an attraction
    void viewAttractionInfo(const City& city, int position, int type); // User view an attraction

    void adminPanel(); // Support for administrator
    void addNewCity(); // Admin add a new city
    void addNewAttraction(); // Admin add a new attraction
    void addNewFlight(); // Admin a new flight between two cities
    void removeCity(); // Admin remove an existing city
    void removeAttraction(); // Admin remove an existing attraction
    void removeFlight(); // Admin remove an existing flight between two cities
    void editCity(); // Admin edit an existing city
    void editAttraction(); // Admin edit an existing attraction

public:
    ~TourismSystem(); // Release memory allocated to the containers
};

#endif // TOURISM_SYSTEM_HPP
