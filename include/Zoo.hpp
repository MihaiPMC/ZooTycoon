//
// Created by Mihai Patru on 25.03.2025.
//

#ifndef ZOO_H
#define ZOO_H

#include <string>
#include <vector>
#include <iostream>
#include "Animal.hpp"
#include "Habitat.hpp"


class Zoo
{
private:
    std::string name;
    std::vector<Habitat> habitats;
    int visitorCount;
    bool isOpen;
    float budget;

public:
    Zoo(const std::string &name, const std::vector<Habitat> &habitats, int visitor_count, bool is_open, float budget = 100000);
    ~Zoo() = default;
    Zoo(const Zoo &other);
    Zoo(Zoo &&other) noexcept;
    Zoo &operator=(const Zoo &other);
    Zoo &operator=(Zoo &&other) noexcept;

    [[nodiscard]] const std::string &getName() const;
    void setName(const std::string &newName);
    [[nodiscard]] const std::vector<Habitat> &getHabitats() const;
    void addHabitats(const std::vector<Habitat> &newHabitats);
    void addHabitats(const Habitat &habitat);
    [[nodiscard]] int getVisitorCount() const;
    void setVisitorCount(int visitor_count);
    [[nodiscard]] bool getIsOpen() const;
    void setIsOpen(bool is_open);
    [[nodiscard]] float getBudget() const;
    void setBudget(float newBudget);
    void feedAnimals(float foodAmountPerAnimal = 0.3f, float costPerAnimal = 10.0f);
    void updateHunger(float deltaTime);

    friend std::ostream &operator<<(std::ostream &os, const Zoo &zoo);
};

#endif //ZOO_H
