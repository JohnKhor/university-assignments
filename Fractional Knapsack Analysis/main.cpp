#include <iostream>
#include <iomanip> // setw
#include <ctime> // time
#include <cstdlib> // srand, rand
#include <chrono>

#include "PriorityQueue.hpp"

void fractionalKnapsack(PriorityQueue &pq, int knapsackWeight, bool verbose = true) {
    double totalValue = 0.0, portion;
    int totalWeight = 0;

    if (verbose) std::cout << "No    | Portion | Benefit | Weight | Value | Total Weight | Total Value" << std::endl;

    // Go through all items
    while(!pq.isEmpty()) {
        // Retrieve item with the highest value
        Item currentItem = pq.dequeue();

        // Enough space for item - add item completely
        if (totalWeight + currentItem.weight <= knapsackWeight) {
            portion = 100.00;
            totalWeight += currentItem.weight;
            totalValue += currentItem.benefit;
        }
        // Not enough space for item - add a portion of item
        else {
            int remainWeight = knapsackWeight - totalWeight;
            portion = double(remainWeight) / double(currentItem.weight);
            totalWeight += remainWeight;
            totalValue += currentItem.benefit * portion;
        }

        if (verbose) {
            std::cout << std::setw(5) << currentItem.no << " | ";
            std::cout << std::setw(6) << std::fixed << std::setprecision(2) << portion << "% | ";
            std::cout << std::setw(7) << currentItem.benefit << " | ";
            std::cout << std::setw(6) << currentItem.weight << " | ";
            std::cout << std::setw(5) << std::fixed << std::setprecision(2) << currentItem.value << " | ";
            std::cout << std::setw(12) << totalWeight << " | ";
            std::cout << std::setw(11) << std::fixed << std::setprecision(2) << totalValue << std::endl;
        }

        // Knapsack is full
        if (totalWeight == knapsackWeight)
            break;
    }

    if (verbose) {
        std::cout << std::endl << "Total weight: " << totalWeight << std::endl;
        std::cout << "Total value: " << std::fixed << std::setprecision(2) << totalValue << std::endl;
    }
}

void randomise(PriorityQueue &pq, int numOfItems, int maxItemWeight, int maxItemBenefit) {
    // Generate items with random benefit and weight
    for (int i = 0; i < numOfItems; i++) {
        Item item;
        item.no = i + 1;
        item.weight = rand() % maxItemWeight + 1;
        item.benefit = rand() % maxItemBenefit + 1;
        item.value = double(item.benefit) / double(item.weight);
        pq.enqueue(item);
    }
}

void test() {
    int numOfItems, knapsackWeight, maxItemWeight, maxItemBenefit;
    std::string choice;

    std::cout << "Input number of items: " << std::endl;
    std::cin >> numOfItems;

    std::cout << std::endl << "Input knapsack weight: " << std::endl;
    std::cin >> knapsackWeight;

    std::cout << std::endl << "Do you want to randomise benefit and weight? (y/Y)" << std::endl;
    std::cin >> choice;

    std::cout << std::endl;
    PriorityQueue pq(numOfItems);

    if (choice == "y" || choice == "Y") {
        std::cout << "Max item weight: ";
        std::cin >> maxItemWeight;

        std::cout << "Max item benefit: ";
        std::cin >> maxItemBenefit;

        std::cout << std::endl << "Generating items with random weight and benefit..." << std::endl;
        randomise(pq, numOfItems, maxItemWeight, maxItemBenefit);
    } else {
        for (int i = 0; i < numOfItems; i++) {
            Item item;
            item.no = i + 1;
            std::cout << "Item " << item.no << std::endl;

            std::cout << "Item weight: ";
            std::cin >> item.weight;

            std::cout << "Item benefit: ";
            std::cin >> item.benefit;

            item.value = double(item.benefit) / double(item.weight);
            pq.enqueue(item);
            std::cout << std::endl;
        }
    }

    std::cout << std::endl << "Priority Queue:" << std::endl;
    pq.print();

    std::cout << std::endl << "Fractional Knapsack:" << std::endl;
    auto start = std::chrono::system_clock::now();
    fractionalKnapsack(pq, knapsackWeight);
    auto end = std::chrono::system_clock::now();

    std::chrono::duration<double> duration = end - start;
    std::cout << std::endl << "Duration: " << std::fixed << std::setprecision(6) << duration.count() << "s" << std::endl << std::endl;
}

void differentCases() {
    int numOfItems[3] = {100000, 1000000, 10000000}, knapsackWeight[3] = {100000, 1000000, 10000000};
    int maxItemWeight = 50000000, maxItemBenefit = 10000000;

    std::cout << "Max Item Weight: " << maxItemWeight << std::endl;
    std::cout << "Max Item Benefit: " << maxItemBenefit << std::endl << std::endl;
    std::cout << "Number of Items | Knapsack Weight | Duration" << std::endl;

    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            PriorityQueue pq(numOfItems[i]);
            randomise(pq, numOfItems[i], maxItemWeight, maxItemBenefit);

            auto start = std::chrono::system_clock::now();
            fractionalKnapsack(pq, knapsackWeight[j], false);
            auto end = std::chrono::system_clock::now();
            std::chrono::duration<double> duration = end - start;

            std::cout << std::setw(15) << numOfItems[i] << " | ";
            std::cout << std::setw(15) << knapsackWeight[j] << " | ";
            std::cout << std::fixed << std::setprecision(6) << duration.count() << "s" << std::endl;
        }
    }
    std::cout << std::endl;
}

void runtimeAnalysis() {
    int numOfItems[11] = {500, 1000, 1500, 10000, 15000, 100000, 150000, 1000000, 1500000, 10000000, 15000000};
    int knapsackWeight = 2000000, maxItemWeight = 50000000, maxItemBenefit = 10000000;

    std::cout << "Knapsack Weight: " << knapsackWeight << std::endl;
    std::cout << "Max Item Weight: " << maxItemWeight << std::endl;
    std::cout << "Max Item Benefit: " << maxItemBenefit << std::endl << std::endl;
    std::cout << "Number of Items | Duration" << std::endl;

    for (int i = 0; i < 11; i++) {
        PriorityQueue pq(numOfItems[i]);
        randomise(pq, numOfItems[i], maxItemWeight, maxItemBenefit);

        auto start = std::chrono::system_clock::now();
        fractionalKnapsack(pq, knapsackWeight, false);
        auto end = std::chrono::system_clock::now();
        std::chrono::duration<double> duration = end - start;

        std::cout << std::setw(15) << numOfItems[i] << " | ";
        std::cout << std::fixed << std::setprecision(6) << duration.count() << "s" << std::endl;

    }
    std::cout << std::endl;
}

int main() {
    srand(time(0));
    std::string choice;

    while(true) {
        std::cout << "Fractional Knapsack using Priority Queue" << std::endl;
        std::cout << "1. Test" << std::endl;
        std::cout << "2. Best, Average and Worst Cases" << std::endl;
        std::cout << "3. Run-time Analysis" << std::endl;
        std::cout << "4. Quit" << std::endl;
        std::cout << "==> ";
        std::cin >> choice;

        std::cout << std::endl;
        if (choice == "1") test();
        else if (choice == "2") differentCases();
        else if (choice == "3") runtimeAnalysis();
        else break;
    }

    return 0;
}
