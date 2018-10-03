#include "Shopping.hpp"
#include <iostream>
#include "Attraction.hpp"
#include "LinkedList.cpp"

Shopping::Shopping()
{
}

Shopping::Shopping(std::string name, int typeID, std::string address, std::string days, std::string hours, std::string contact, int discount, LinkedList<std::string> malls)
: Attraction(name, typeID, address, days, hours, contact), discount(discount), malls(malls)
{
}

int Shopping::getDiscount() const
{
    return discount;
}

LinkedList<std::string> Shopping::getMalls() const
{
    return malls;
}

void Shopping::setDiscount(int discount)
{
    this->discount = discount;
}

void Shopping::addMall(std::string mall)
{
    malls.insert(malls.getLength(), mall);
}

void Shopping::setMall(int position, std::string mall)
{
    malls.setEntry(position, mall);
}

void Shopping::display() const
{
    std::cout << "1. Name: " << getName() << "\n";
    std::cout << "2. Address: " << getAddress() << "\n";
    std::cout << "3. Opening Days: " << getDays() << "\n";
    std::cout << "4. Opening Hours: " << getHours() << "\n";
    std::cout << "5. Contact No: " << getContact() << "\n";
    std::cout << "6. Discount: " << discount << "%\n";
    int mallsSize = malls.getLength();
    for (int i = 0; i < mallsSize; i++)
        std::cout << "Mall #" << i + 1 << ": " << malls.getEntry(i) << "\n";
}
