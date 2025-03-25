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
    float buget;

public:
    Zoo(const std::string &name, const std::vector<Habitat> &habitats, int visitor_count, bool is_open, float buget = 100000)
        : name(name),
          habitats(habitats),
          visitorCount(visitor_count),
          isOpen(is_open),
          buget(buget)
    {
    }

    ~Zoo() = default;

    Zoo(const Zoo &other)
        : name(other.name),
          habitats(other.habitats),
          visitorCount(other.visitorCount),
          isOpen(other.isOpen),
          buget(other.buget)
    {
    }

    Zoo(Zoo &&other) noexcept
        : name(std::move(other.name)),
          habitats(std::move(other.habitats)),
          visitorCount(other.visitorCount),
          isOpen(other.isOpen),
          buget(other.buget)
    {
    }

    Zoo &operator=(const Zoo &other)
    {
        if (this == &other)
            return *this;
        name = other.name;
        habitats = other.habitats;
        visitorCount = other.visitorCount;
        isOpen = other.isOpen;
        buget = other.buget;
        return *this;
    }

    Zoo &operator=(Zoo &&other) noexcept
    {
        if (this == &other)
            return *this;
        name = std::move(other.name);
        habitats = std::move(other.habitats);
        visitorCount = other.visitorCount;
        isOpen = other.isOpen;
        buget = other.buget;
        return *this;
    }

    [[nodiscard]] const std::string &getName() const
    {
        return name;
    }

    void setName(const std::string &newName)
    {
        this->name = newName;
    }

    [[nodiscard]] const std::vector<Habitat> &getHabitats() const
    {
        return habitats;
    }

    void addHabitats(const std::vector<Habitat> &newHabitats)
    {
        for (const auto &habitat: newHabitats)
        {
            this->habitats.push_back(habitat);
        }
    }

    void addHabitats(const Habitat &habitat)
    {
        this->habitats.push_back(habitat);
        this->buget -= habitat.getPrice();
    }

    [[nodiscard]] int getVisitorCount() const
    {
        return visitorCount;
    }

    void setVisitorCount(int visitor_count)
    {
        visitorCount = visitor_count;
    }

    [[nodiscard]] bool getIsOpen() const
    {
        return isOpen;
    }

    void setIsOpen(bool is_open)
    {
        isOpen = is_open;
    }

    [[nodiscard]] float getBuget() const
    {
        return buget;
    }

    void setBuget(float newBuget)
    {
        this->buget = newBuget;
    }

    void  feedAnimals(float foodAmountPerAnimal = 0.3f, float costPerAnimal = 10.0f)
    {
        int totalAnimals = 0;
        float totalCost = 0.0f;

        for (const auto& habitat : habitats)
        {
            totalAnimals += habitat.getAnimals().size();
        }

        totalCost = totalAnimals * costPerAnimal;

        if (buget < totalCost)
        {
            std::cout << "Not enough budget to feed all animals!" << std::endl;
            return;
        }

        for (const auto& habitat : habitats)
        {
            for (auto& animal : const_cast<std::vector<Animal>&>(habitat.getAnimals()))
            {
                animal.setHunger(std::min(1.0f, animal.getHunger() + foodAmountPerAnimal));
            }
        }

        buget -= totalCost;

        std::cout << "Fed " << totalAnimals << " animals for a total cost of $" << totalCost << std::endl;
        std::cout << "Remaining budget: $" << buget << std::endl;
    }

    void updateHunger(float deltaTime)
    {
        for (const auto &habitat: habitats)
        {
            for (auto &animal: const_cast<std::vector<Animal> &>(habitat.getAnimals()))
            {
                animal.updateHunger(deltaTime);
            }
        }
    }



    friend std::ostream &operator<<(std::ostream &os, const Zoo &zoo)
    {
        os << "Zoo: " << zoo.name << "\n"
           << "  Habitats: " << zoo.habitats.size() << "\n"
           << "  Visitor Count: " << zoo.visitorCount << "\n"
           << "  Status: " << (zoo.isOpen ? "Open" : "Closed") << "\n"
           << "  Budget: $" << zoo.buget;
        return os;
    }
};



#endif //ZOO_H
