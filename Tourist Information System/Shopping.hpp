#ifndef SHOPPING_HPP
#define SHOPPING_HPP

#include <iostream>
#include "Attraction.hpp"
#include "LinkedList.cpp"

// Derived class of Attraction
class Shopping: public Attraction
{
private:
    int discount;
    LinkedList<std::string> malls;

public:
    Shopping();
    Shopping(std::string name, int typeID, std::string address, std::string days, std::string hours, std::string contact, int discount, LinkedList<std::string> malls);

    int getDiscount() const;
    LinkedList<std::string> getMalls() const;

    void setDiscount(int discount);
    void addMall(std::string mall);
    void setMall(int position, std::string mall);

    virtual void display() const;
};

#endif // SHOPPING_HPP
