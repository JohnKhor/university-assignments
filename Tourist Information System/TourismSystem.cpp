#include "TourismSystem.hpp"
#include <iostream>
#include <iomanip> // std::setprecision()
#include <fstream> // std::ifstream, std::ofstream
#include "City.hpp"
#include "Attraction.hpp"
#include "Sport.hpp"
#include "Culture.hpp"
#include "Shopping.hpp"
#include "Util.hpp"
#include "LinkedList.cpp"
#include "AdjacencyMatrix.hpp"

// Main function to run the system
void TourismSystem::run()
{
    // Load data into the system and display main menu
    if(loadData())
        menu();
    else
        std::cout << "Fail to load data, terminating program. \n";
}

// Comparison used in LinkedList's sort() function
bool operator<(const City& city1, const City& city2)
{
    return (city1.getName() < city2.getName());
}

// Overloaded insertion operator for City used in loadData()
std::istream& operator>>(std::istream& in, City& city)
{
    std::string strData;

    std::getline(in, strData);
    int intData = util::strToInt(strData);
    city.setId(intData);

    std::getline(in, strData);
    city.setName(strData);

    return in;
}

// Overloaded insertion operator for Sport used in loadData()
std::istream& operator>>(std::istream& in, Sport& sport)
{
    std::string strData;
    int intData;

    std::getline(in, strData);
    intData = util::strToInt(strData);
    sport.setTypeID(intData);

    std::getline(in, strData);
    sport.setName(strData);

    std::getline(in, strData);
    sport.setAddress(strData);

    std::getline(in, strData);
    sport.setDays(strData);

    std::getline(in, strData);
    sport.setHours(strData);

    std::getline(in, strData);
    sport.setContact(strData);

    std::getline(in, strData);
    intData = util::strToInt(strData);
    sport.setAgeLimit(intData);

    std::getline(in, strData);
    sport.setSportType(strData);

    return in;
}

// Overloaded insertion operator for Culture used in loadData()
std::istream& operator>>(std::istream& in, Culture& culture)
{
    std::string strData;

    std::getline(in, strData);
    int intData = util::strToInt(strData);
    culture.setTypeID(intData);

    std::getline(in, strData);
    culture.setName(strData);

    std::getline(in, strData);
    culture.setAddress(strData);

    std::getline(in, strData);
    culture.setDays(strData);

    std::getline(in, strData);
    culture.setHours(strData);

    std::getline(in, strData);
    culture.setContact(strData);

    std::getline(in, strData);
    double doubleData = util::strToDouble(strData);
    culture.setEntranceFee(doubleData);

    std::getline(in, strData);
    culture.setMuseumType(strData);

    return in;
}

// Overloaded insertion operator for Shopping used in loadData()
std::istream& operator>>(std::istream& in, Shopping& shopping)
{
    std::string strData;
    int intData;

    std::getline(in, strData);
    intData = util::strToInt(strData);
    shopping.setTypeID(intData);

    std::getline(in, strData);
    shopping.setName(strData);

    std::getline(in, strData);
    shopping.setAddress(strData);

    std::getline(in, strData);
    shopping.setDays(strData);

    std::getline(in, strData);
    shopping.setHours(strData);

    std::getline(in, strData);
    shopping.setContact(strData);

    std::getline(in, strData);
    intData = util::strToInt(strData);
    shopping.setDiscount(intData);

    std::getline(in, strData);
    int mallsSize = util::strToInt(strData);

    for (int index = 0; index < mallsSize; index++){
        std::getline(in, strData);
        shopping.addMall(strData);
    }

    return in;
}

// Load data from a text file
bool TourismSystem::loadData()
{
    std::ifstream inputFile("db.txt");

    if (inputFile.fail()) return false;

    std::string data;

    // Load number of cities
    std::getline(inputFile, data);
    int citiesLength = util::strToInt(data);

    int attractionsLength;

    // Load cities data
    for (int i = 0; i < citiesLength; i++){
        City* city = new City();
        inputFile >> *city;
        cities.insert(i, city);

        // Load number of attractions of a city
        std::getline(inputFile, data);
        attractionsLength = util::strToInt(data);

        // Load attractions data of a city
        for (int j = 0; j < attractionsLength; j++){
            std::getline(inputFile, data);
            // Downcast to access derived classes' overloaded insertion operator
            if (data == "Sport"){
                Sport* sport = new Sport();
                inputFile >> *sport;
                cities.getEntry(i)->addAttraction(sport);
            }
            else if (data == "Culture"){
                Culture* culture = new Culture();
                inputFile >> *culture;
                cities.getEntry(i)->addAttraction(culture);
            }
            else if (data == "Shopping"){
                Shopping* shopping = new Shopping();
                inputFile >> *shopping;
                cities.getEntry(i)->addAttraction(shopping);
            }
        }
    }
    cities.sort(); // Sort cities alphabetically

    // Load size of flight map
    std::getline(inputFile, data);
    int flightMapSize = util::strToInt(data);

    // Load flight information data
    int** matrix = new int*[flightMapSize]; // Temp matrix to be passed into AdjacencyMatrix's constructor
    for (int row = 0; row < flightMapSize; row++){
        matrix[row] = new int[flightMapSize];
        for (int col = 0; col < flightMapSize; col++)
            inputFile >> matrix[row][col];
        std::getline(inputFile, data); // Discard newline after each row
    }
    flightMap = new AdjacencyMatrix(matrix, flightMapSize);

    std::getline(inputFile, data); // Discard newline at the end
    inputFile.close();
    return true;
}

// Overloaded extraction operator for City used in saveData()
std::ostream& operator<<(std::ostream& out, const City& city)
{
    out << city.getId() << "\n" << city.getName() << "\n";
    return out;
}

// Overloaded extraction operator for Sport used in saveData()
std::ostream& operator<<(std::ostream& out, const Sport& sport)
{
    out << sport.getTypeID() << "\n" << sport.getName() << "\n" << sport.getAddress() << "\n" << sport.getDays() << "\n"
    << sport.getHours() << "\n" << sport.getContact() << "\n" << sport.getAgeLimit() << "\n" << sport.getSportType() << "\n";
    return out;
}

// Overloaded extraction operator for Culture used in saveData()
std::ostream& operator<<(std::ostream& out, const Culture& culture)
{
    out << culture.getTypeID() << "\n" << culture.getName() << "\n" << culture.getAddress() << "\n" << culture.getDays() << "\n"
    << culture.getHours() << "\n" << culture.getContact() << "\n" << std::fixed << std::setprecision(2) << culture.getEntranceFee()
    << "\n" << culture.getMuseumType() << "\n";
    return out;
}

// Overloaded extraction operator for Shopping used in saveData()
std::ostream& operator<<(std::ostream& out, const Shopping& shopping)
{
    out << shopping.getTypeID() << "\n" << shopping.getName() << "\n" << shopping.getAddress() << "\n" << shopping.getDays()
    << "\n" << shopping.getHours() << "\n" << shopping.getContact() << "\n" << shopping.getDiscount() << "\n";
    LinkedList<std::string> malls = shopping.getMalls();
    int mallsSize = malls.getLength();
    out << mallsSize << "\n";
    for (int i = 0; i < mallsSize; i++)
        out << malls.getEntry(i) << "\n";
    return out;
}

// Save data to a text file
bool TourismSystem::saveData()
{
    std::ofstream outputFile("db.txt");

    if (outputFile.fail()) return false;

    // Save number of cities
    int citiesLength = cities.getLength();
    outputFile << citiesLength << "\n";

    int attractionsLength;

    // Save cities data
    for (int i = 0; i < citiesLength; i++){
        outputFile << *cities.getEntry(i);
        LinkedList<Attraction*> attractions = cities.getEntry(i)->getAttractions();

        // Save number of attractions of a city
        attractionsLength = attractions.getLength();
        outputFile << attractionsLength << "\n";

        // Save attractions data of a city
        for (int j = 0; j < attractionsLength; j++){
            // Downcast to access derived classes' overloaded extraction operator
            if (attractions.getEntry(j)->getTypeID() == 1){
                outputFile << "Sport\n";
                Sport* sport = dynamic_cast<Sport*>(attractions.getEntry(j));
                outputFile << *sport;
            }
            else if (attractions.getEntry(j)->getTypeID() == 2){
                outputFile << "Culture\n";
                Culture* culture = dynamic_cast<Culture*>(attractions.getEntry(j));
                outputFile << *culture;
            }
            else if (attractions.getEntry(j)->getTypeID() == 3){
                outputFile << "Shopping\n";
                Shopping* shopping = dynamic_cast<Shopping*>(attractions.getEntry(j));
                outputFile << *shopping;
            }
        }
    }

    // Save size of flight map
    int flightMapSize = flightMap->getSize();
    outputFile << flightMapSize << "\n";

    // Save flight information data
    for (int row = 0; row < flightMapSize; row++){
        for (int col = 0; col < flightMapSize; col++)
            outputFile << flightMap->getEdge(row, col) << " ";
        outputFile << "\n";
    }

    outputFile.close();
    return true;
}

// Main menu. Ask for identity
void TourismSystem::menu()
{
    // The main loop
    bool exit = false;
    while(!exit){
        util::clearScreen();
        std::cout << "************************************** \n";
        std::cout << "#                                    # \n";
        std::cout << "#     TOURIST INFORMATION SYSTEM     # \n";
        std::cout << "#                                    # \n";
        std::cout << "************************************** \n\n";

        std::cout << "Welcome, are you a user or an admin? \n";
        std::cout << "(1) User \n";
        std::cout << "(2) Admin \n";
        std::cout << "(3) Exit \n";

        int select = util::getIntInputWithin(3);
        switch(select){
            case 1: selectCity(); break;
            case 2: adminPanel(); break;
            case 3: exit = true; break;
        }
    }
}

// User select a city to either view its attractions or flight information
void TourismSystem::selectCity()
{
    util::clearScreen();
    std::cout << "Please select a city to view its attractions and flight information: \n";
    util::printCitiesName(cities);
    int options = cities.getLength();
    std::cout << "(" << options + 1 << ") Back to menu \n";

    int citySelect = util::getIntInputWithin(options + 1);
    if (citySelect == options + 1) return;

    std::cout << "Please select an option to proceed: \n";
    std::cout << "(1) Select type of attraction \n";
    std::cout << "(2) View flight information \n";
    std::cout << "(3) Back to menu \n";

    int select = util::getIntInputWithin(3);
    if (select == 1) selectType(*cities.getEntry(citySelect - 1));
    else if (select == 2) viewFlightInfo(citySelect - 1);
    else if (select == 3) return;
}

/***** CITY CONNECTION *****
    Johor
    Direct flight - Malacca
    Indirect flight - Kuala Lumpur, Penang

    Kuala Lumpur
    Direct flight - Malacca, Penang
    Indirect flight - Johor

    Malacca
    Direct flight - Johor, Kuala Lumpur, Penang
    Indirect flight - N/A

    Penang
    Direct flight - Kuala Lumpur, Malacca
    Indirect flight - Johor
*/
// User view flight information
void TourismSystem::viewFlightInfo(int position)
{
    bool repeat = true;
    while(repeat){
        util::clearScreen();
        std::cout << "You have chosen " << cities.getEntry(position)->getName() << ". \n";
        std::cout << "Please select the destination city: \n";
        util::printCitiesName(cities);
        int options = cities.getLength();
        std::cout << "(" << options + 1 << ") Back to select city \n";
        std::cout << "(" << options + 2 << ") Return to menu \n";

        int select = util::getIntInputWithin(options + 2);
        if (select >= 1 && select <= options){
            if (position == select - 1)
                std::cout << "No flight is available between the same city. \n";
            else{
                std::cout << "Departed from: " << cities.getEntry(position)->getName() << ". \n";
                std::cout << "Arrival at: " << cities.getEntry(select - 1)->getName() << ". \n\n";

                int originId = cities.getEntry(position)->getId();
                int destId = cities.getEntry(select - 1)->getId();

                // Direct flight is available when there's an edge between chosen cities
                std::cout << "Direct flight is ";
                if (flightMap->isEdge(originId - 1, destId - 1)) std::cout << "available. \n";
                else std::cout << "not available. \n";

                // Indirect flight is available when there's a path between chosen cities
                // Edge between chosen cities is not counted as a path
                std::cout << "Indirect flight is ";
                if (flightMap->isPath(originId - 1, destId - 1)) std::cout << "available. \n";
                else std::cout << "not available. \n";
            }
            util::pauseScreen();
        }
        else if (select == options + 1){
            repeat = false;
            selectCity();
        }
        else if (select == options + 2) return;
    }
}

// User select a type of attraction
void TourismSystem::selectType(const City& city)
{
    util::clearScreen();
    std::cout << "You have chosen " << city.getName() << ". \n";
    std::cout << "Please select a type of attraction: \n";
    std::cout << "(1) Sport \n";
    std::cout << "(2) Culture \n";
    std::cout << "(3) Shopping \n";
    std::cout << "(4) All types \n";
    std::cout << "(5) Back to select city \n";
    std::cout << "(6) Return to menu \n";

    int select = util::getIntInputWithin(6);
    if (select >= 1 && select <= 4) selectAttraction(city, select);
    else if (select == 5) selectCity();
    else if (select == 6) return;
}

// User select an attraction
void TourismSystem::selectAttraction(const City& city, int type)
{
    util::clearScreen();
    std::cout << "You have chosen ";
    if (type == 1) std::cout << "Sport. \n";
    else if (type == 2) std::cout << "Culture. \n";
    else if (type == 3) std::cout << "Shopping. \n";
    else if (type == 4) std::cout << "All types. \n";

    std::cout << "Please select an attraction: \n";
    int options = 1;
    LinkedList<int> positions; // Store positions of objects of a particular type of attraction
    int attractionsLength = city.getAttractionsLength();
    for (int i = 0; i < attractionsLength; i++) // Display attractions' name based on the type that user had chosen
        if (city.getAttraction(i)->getTypeID() == type || type == 4){
            std::cout << "(" << options << ") " << city.getAttraction(i)->getName() << "\n";
            positions.insert(positions.getLength(), i);
            options++;
        }
    std::cout << "(" << options << ") Back to select type of attraction \n";
    std::cout << "(" << options + 1 << ") Return to select city \n";
    std::cout << "(" << options + 2 << ") Return to menu \n";

    int select = util::getIntInputWithin(options + 2);
    if (select >= 1 && select <= options - 1) viewAttractionInfo(city, positions.getEntry(select - 1), type);
    else if (select == options) selectType(city);
    else if (select == options + 1) selectCity();
    else if (select == options + 2) return;
}

// User view an attraction
void TourismSystem::viewAttractionInfo(const City& city, int position, int type)
{
    util::clearScreen();
    Attraction* attraction = city.getAttraction(position);
    std::cout << "You have chosen " << attraction->getName() << ". \n";
    std::cout << "Attraction's details: \n";
    attraction->display();
    std::cout << "Please select an option to continue: \n";
    std::cout << "(1) Back to select attraction \n";
    std::cout << "(2) Return to select type of attraction \n";
    std::cout << "(3) Return to select city \n";
    std::cout << "(4) Return to menu \n";

    int select = util::getIntInputWithin(4);
    if (select == 1) selectAttraction(city, type);
    else if (select == 2) selectType(city);
    else if (select == 3) selectCity();
    else if (select == 4) return;
}

// Support for administrator
void TourismSystem::adminPanel()
{
    bool done = false;
    while(!done){
        util::clearScreen();
        std::cout << "Welcome to the admin panel. \n";
        std::cout << "Please select an option to proceed: \n";
        std::cout << "(1) Add a new city \n";
        std::cout << "(2) Add a new attraction \n";
        std::cout << "(3) Add a new flight information \n";
        std::cout << "(4) Remove an existing city \n";
        std::cout << "(5) Remove an existing attraction \n";
        std::cout << "(6) Remove an existing flight information \n";
        std::cout << "(7) Edit an existing city \n";
        std::cout << "(8) Edit an existing attraction \n";
        std::cout << "(9) Save current data \n";
        std::cout << "(10) Return to menu \n";

        int select = util::getIntInputWithin(10);
        switch(select){
            case 1: addNewCity(); break;
            case 2: addNewAttraction(); break;
            case 3: addNewFlight(); break;
            case 4: removeCity(); break;
            case 5: removeAttraction(); break;
            case 6: removeFlight(); break;
            case 7: editCity(); break;
            case 8: editAttraction(); break;
            case 9: if(saveData()) std::cout << "Current data is saved successfully. \n";
                    else std::cout << "Fail to save data. \n";
                    util::pauseScreen(); break;
            case 10: done = true; break;
        }
    }
    return;
}

// Admin add a new city
void TourismSystem::addNewCity()
{
    util::clearScreen();
    std::cout << "Please type the name of new city. \n";
    std::cout << "(1) Back to admin panel \n";

    std::string newName = util::getStrInput();
    if (newName == "1") return;

    util::toUpperCase(newName[0]); // Ensure first letter of city name is upper case
    cities.insert(cities.getLength(), new City(cities.getLength() + 1, newName));
    cities.sort(); // Sort cities alphabetically

    flightMap->appendZeros(); // Append and initialise new row and column indicating new city to zero

    std::cout << "New city is added successfully. \n";
    util::pauseScreen();
    return;
}

// Admin add a new attraction
void TourismSystem::addNewAttraction()
{
    util::clearScreen();
    std::cout << "Please select the city to add new attraction: \n";
    util::printCitiesName(cities);
    int options = cities.getLength();
    std::cout << "(" << options + 1 << ") Back to admin panel \n";

    int citySelect = util::getIntInputWithin(options + 1);
    util::clearScreen();
    if (citySelect == options + 1) return;

    City* chosenCity = cities.getEntry(citySelect - 1);
    std::cout << "You have chosen " << chosenCity->getName() << ". \n";
    std::cout << "Please select the type of attraction: \n";
    std::cout << "(1) Sport \n";
    std::cout << "(2) Culture \n";
    std::cout << "(3) Shopping \n";
    std::cout << "(4) Back to admin panel \n";

    int typeSelect = util::getIntInputWithin(4);
    util::clearScreen();
    if (typeSelect == 4) return;

    std::cout << "You have chosen ";
    if (typeSelect == 1) std::cout << "Sport. \n";
    else if (typeSelect == 2) std::cout << "Culture. \n";
    else if (typeSelect == 3) std::cout << "Shopping. \n";

    std::cout << "Please type the name of new attraction. \n";
    std::string addName = util::getStrInput();
    std::cout << "Please type the address of new attraction. \n";
    std::string addAddress = util::getStrInput();
    std::cout << "Please type the opening days of new attraction, e.g. Mon - Thu. \n";
    std::string addDays = util::getStrInput();
    std::cout << "Please type the opening hours of new attraction, e.g. 09:00 - 18:00. \n";
    std::string addHours = util::getStrInput();
    std::cout << "Please type the contact number of new attraction, e.g. 01-222 3333. \n";
    std::string addContact = util::getStrInput();

    if (typeSelect == 1){
        std::cout << "Please type the age limit of new sport attraction. \n";
        int addAgeLimit = util::getIntInput();
        std::cout << "Please type the sport type of new sport attraction. \n";
        std::string addSportType = util::getStrInput();
        chosenCity->addAttraction(new Sport(addName, typeSelect, addAddress, addDays, addHours, addContact, addAgeLimit, addSportType));
    }
    else if (typeSelect == 2){
        std::cout << "Please type the entrance fee of new culture attraction. \n";
        double addEntranceFee = util::getDoubleInput();
        std::cout << "Please type the museum type of new culture attraction. \n";
        std::string addMuseumType = util::getStrInput();
        chosenCity->addAttraction(new Culture(addName, typeSelect, addAddress, addDays, addHours, addContact, addEntranceFee, addMuseumType));
    }
    else if (typeSelect == 3){
        std::cout << "Please type the discount of new shopping attraction. Note: % is not required. \n";
        int addDiscount = util::getIntInput();
        std::cout << "Please type the number of malls in new shopping attraction. \n";
        int mallsLength = util::getIntInput();
        LinkedList<std::string> addMalls;
        for (int j = 0; j < mallsLength; j++){
            std::cout << "Please type the name of mall #" << j + 1 << " in new shopping attraction. \n";
            std::string addMall = util::getStrInput();
            addMalls.insert(j, addMall);
        }
        chosenCity->addAttraction(new Shopping(addName, typeSelect, addAddress, addDays, addHours, addContact, addDiscount, addMalls));
    }

    std::cout << "New attraction is added successfully. \n";
    util::pauseScreen();
    return;
}

// Admin a new flight between two cities
void TourismSystem::addNewFlight()
{
    while(true){
        util::clearScreen();
        std::cout << "Please select the origin city: \n";
        util::printCitiesName(cities);
        int options = cities.getLength();
        std::cout << "(" << options + 1 << ") Back to admin panel \n";

        int origin = util::getIntInputWithin(options + 1);
        if (origin == options + 1) return;

        std::cout << "Please select the destination city: \n";
        util::printCitiesName(cities);
        std::cout << "(" << options + 1 << ") Back to admin panel \n";

        int dest = util::getIntInputWithin(options + 1);
        if (dest == options + 1) return;

        if (origin == dest) std::cout << "You cannot add a flight between the same city. Please try again. \n";
        else{
            int originId = cities.getEntry(origin - 1)->getId();
            int destId = cities.getEntry(dest - 1)->getId();
            flightMap->addEdge(originId - 1, destId - 1); // Add edge between two cities to indicate direct flight

            std::cout << "A flight from " << cities.getEntry(origin - 1)->getName() << " to "
            << cities.getEntry(dest - 1)->getName() << " and vice versa are added successfully. \n";
        }
        util::pauseScreen();
    }
}

// Admin remove an existing city
void TourismSystem::removeCity()
{
    util::clearScreen();
    std::cout << "Please select the city to remove: \n";
    util::printCitiesName(cities);
    int options = cities.getLength();
    std::cout << "(" << options + 1 << ") Back to admin panel \n";

    int removeSelect = util::getIntInputWithin(options + 1);
    if (removeSelect == options + 1) return;

    int index = cities.getEntry(removeSelect - 1)->getId() - 1;
    flightMap->removeRowColAt(index); // Remove row and column corresponded to removed city

    int citiesLength = cities.getLength();
    for (int i = 0; i < citiesLength; i++){ // Decrement id of cities having id larger than removed city's id
        int id = cities.getEntry(i)->getId();
        if (cities.getEntry(i)->getId() > cities.getEntry(removeSelect - 1)->getId()){
            cities.getEntry(i)->setId(--id);
        }
    }

    cities.remove(removeSelect - 1);
    std::cout << "Existing city is removed successfully. \n";
    util::pauseScreen();
    return;
}

// Admin remove an existing attraction
void TourismSystem::removeAttraction()
{
    util::clearScreen();
    std::cout << "Please select a city to remove one of its attractions: \n";
    util::printCitiesName(cities);
    int options = cities.getLength();
    std::cout << "(" << options + 1 << ") Back to admin panel \n";

    int citySelect = util::getIntInputWithin(options + 1);
    util::clearScreen();
    if (citySelect == options + 1) return;

    City* chosenCity = cities.getEntry(citySelect - 1);
    std::cout << "You have chosen " << chosenCity->getName() << " \n";
    std::cout << "Please select an attraction to remove. \n";
    util::printAttractionsName(chosenCity->getAttractions());
    int optionCount = chosenCity->getAttractionsLength();
    std::cout << "(" << optionCount + 1 << ") Back to admin panel \n";

    int attractionSelect = util::getIntInputWithin(optionCount + 1);
    if (attractionSelect == optionCount + 1) return;

    chosenCity->removeAttraction(attractionSelect - 1);
    std::cout << "Existing attraction is removed successfully. \n";
    util::pauseScreen();
    return;
}

// Admin remove an existing flight between two cities
void TourismSystem::removeFlight()
{
    while(true){
        util::clearScreen();
        std::cout << "Please select the origin city: \n";
        util::printCitiesName(cities);
        int options = cities.getLength();
        std::cout << "(" << options + 1 << ") Back to admin panel \n";

        int origin = util::getIntInputWithin(options + 1);
        if (origin ==  options + 1) return;

        std::cout << "Please select the destination city: \n";
        util::printCitiesName(cities);
        std::cout << "(" << options + 1 << ") Back to admin panel \n";

        int dest = util::getIntInputWithin(options + 1);
        if (dest == options + 1) return;

        if (origin == dest) std::cout << "You cannot remove a flight between the same city. Please try again. \n";
        else{
            int originId = cities.getEntry(origin - 1)->getId();
            int destId = cities.getEntry(dest - 1)->getId();
            flightMap->removeEdge(originId - 1, destId - 1); // Remove edge between two cities to indicate no direct flight

            std::cout << "A flight from " << cities.getEntry(origin - 1)->getName() << " to "
            << cities.getEntry(dest - 1)->getName() << " and vice versa are removed successfully. \n";
        }
        util::pauseScreen();
    }
}

// Admin edit an existing city
void TourismSystem::editCity()
{
    util::clearScreen();
    std::cout << "Please select a city to edit. \n";
    util::printCitiesName(cities);
    int options = cities.getLength();
    std::cout << "(" << options + 1 << ") Back to admin panel \n";

    int citySelect = util::getIntInputWithin(options + 1);
    util::clearScreen();
    if (citySelect == options + 1) return;

    City* chosenCity = cities.getEntry(citySelect - 1);
    std::cout << "You have chosen " << chosenCity->getName() << ". \n";
    std::cout << "Please type the new name of chosen city. \n";
    std::string editName = util::getStrInput();

    util::toUpperCase(editName[0]); // Ensure first letter of city name is upper case
    chosenCity->setName(editName);
    cities.sort(); // Sort cities alphabetically

    std::cout << "Existing city is edited successfully. \n";
    util::pauseScreen();
    return;
}

// Admin edit an existing attraction
void TourismSystem::editAttraction()
{
    util::clearScreen();
    std::cout << "Please select the city to edit one of its attractions: \n";
    util::printCitiesName(cities);
    int options = cities.getLength();
    std::cout << "(" << options + 1 << ") Back to admin panel \n";

    int citySelect = util::getIntInputWithin(options + 1);
    util::clearScreen();
    if (citySelect == options + 1) return;

    City* chosenCity = cities.getEntry(citySelect - 1);
    std::cout << "You have chosen " << chosenCity->getName() << ". \n";
    std::cout << "Please select an attraction to edit: \n";
    util::printAttractionsName(chosenCity->getAttractions());
    int optionCount = chosenCity->getAttractionsLength();
    std::cout << "(" << optionCount + 1 << ") Back to admin panel \n";

    int attractionSelect = util::getIntInputWithin(optionCount + 1);
    if (attractionSelect == optionCount + 1) return;

    Attraction* chosenAttraction = chosenCity->getAttraction(attractionSelect - 1);
    // Downcast to access derived classes' setters
    Sport* sportAttraction = dynamic_cast<Sport*>(chosenAttraction);
    Culture* cultureAttraction = dynamic_cast<Culture*>(chosenAttraction);
    Shopping* shoppingAttraction = dynamic_cast<Shopping*>(chosenAttraction);

    int typeSelect = chosenAttraction->getTypeID();
    while(true){
        util::clearScreen();
        std::cout << "You have chosen " << chosenAttraction->getName() << ". \n";
        std::cout << "Please select the attribute to edit: \n";
        std::cout << "(1) Name \n";
        std::cout << "(2) Address \n";
        std::cout << "(3) Days \n";
        std::cout << "(4) Hours \n";
        std::cout << "(5) Contact \n";
        if (typeSelect == 1){
            std::cout << "(6) Age Limit \n";
            std::cout << "(7) Sport Type \n";
        }
        else if (typeSelect == 2){
            std::cout << "(6) Entrance Fee \n";
            std::cout << "(7) Museum Type \n";
        }
        else if (typeSelect == 3){
            std::cout << "(6) Discount \n";
            std::cout << "(7) Mall \n";
        }
        std::cout << "(8) Back to admin panel \n";

        int attributeSelect = util::getIntInputWithin(8);
        if (attributeSelect == 1){
            std::cout << "Please type the new name of chosen attraction. \n";
            std::string editName = util::getStrInput();
            chosenAttraction->setName(editName);
        }
        else if (attributeSelect == 2){
            std::cout << "Please type the new address of chosen attraction. \n";
            std::string editAddress = util::getStrInput();
            chosenAttraction->setAddress(editAddress);
        }
        else if (attributeSelect == 3){
            std::cout << "Please type the new opening days of chosen attraction, e.g. Mon - Thu. \n";
            std::string editDays = util::getStrInput();
            chosenAttraction->setDays(editDays);
        }
        else if (attributeSelect == 4){
            std::cout << "Please type the new opening hours of chosen attraction, e.g. 09:00 - 18:00. \n";
            std::string editHours = util::getStrInput();
            chosenAttraction->setHours(editHours);
        }
        else if (attributeSelect == 5){
            std::cout << "Please type the new contact number of chosen attraction, e.g. 01-222 3333. \n";
            std::string editContact = util::getStrInput();
            chosenAttraction->setContact(editContact);
        }
        else if (attributeSelect == 6){
            if (typeSelect == 1){
                std::cout << "Please type the new age limit of chosen sport attraction. \n";
                int editAgeLimit = util::getIntInput();
                sportAttraction->setAgeLimit(editAgeLimit);
            }
            else if (typeSelect == 2){
                std::cout << "Please type the new entrance fee of chosen culture attraction. \n";
                double editEntranceFee = util::getDoubleInput();
                cultureAttraction->setEntranceFee(editEntranceFee);
            }
            else if (typeSelect == 3){
                std::cout << "Please type the new discount of chosen shopping attraction. Note: % is not required. \n";
                int editDiscount = util::getIntInput();
                shoppingAttraction->setDiscount(editDiscount);
            }
        }
        else if (attributeSelect == 7){
            if (typeSelect == 1){
                std::cout << "Please type the new sport type of chosen sport attraction. \n";
                std::string editSportType = util::getStrInput();
                sportAttraction->setSportType(editSportType);
            }
            else if (typeSelect == 2){
                std::cout << "Please type the new museum type of chosen culture attraction. \n";
                std::string editMuseumType = util::getStrInput();
                cultureAttraction->setMuseumType(editMuseumType);
            }
            else if (typeSelect == 3){
                std::cout << "Please select a mall to proceed: \n";
                LinkedList<std::string> malls = shoppingAttraction->getMalls();
                int mallsLength = malls.getLength();
                int numOfOptions;
                for (numOfOptions = 0; numOfOptions < mallsLength; numOfOptions++)
                    std::cout << "(" << numOfOptions + 1 << ") " << malls.getEntry(numOfOptions) << "\n";
                int mallSelect = util::getIntInputWithin(numOfOptions + 1);
                std::cout << "Please type the new mall of chosen shopping attraction. \n";
                std::string editMall = util::getStrInput();
                shoppingAttraction->setMall(mallSelect - 1, editMall);
            }
        }
        else if (attributeSelect == 8) return;
        if (attributeSelect >= 1 && attributeSelect <= 7){
            std::cout << "Existing attraction is edited successfully. \n";
            util::pauseScreen();
        }
    }
}

// Release memory allocated to the containers
TourismSystem::~TourismSystem()
{
    cities.clear();
    delete flightMap;
    flightMap = nullptr;
}
