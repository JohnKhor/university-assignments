#ifndef ATTRACTION_HPP
#define ATTRACTION_HPP

#include <iostream>

// Base class of Sport, Culture and Shopping
class Attraction
{
private:
    std::string name;
    int typeID;
    std::string address;
    std::string days;
    std::string hours;
    std::string contact;

public:
    Attraction();
    Attraction(std::string name, int typeID, std::string address, std::string days, std::string hours, std::string contact);
    virtual ~Attraction();

    std::string getName() const;
    int getTypeID() const;
    std::string getAddress() const;
    std::string getDays() const;
    std::string getHours() const;
    std::string getContact() const;

    void setName(std::string name);
    void setTypeID(int typeID);
    void setAddress(std::string address);
    void setDays(std::string days);
    void setHours(std::string hours);
    void setContact(std::string contact);

    virtual void display() const = 0;
};

#endif // ATTRACTION_HPP
