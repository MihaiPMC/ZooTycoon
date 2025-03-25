//
// Created by Mihai Patru on 25.03.2025.
//

#ifndef HABITAT_H
#define HABITAT_H

#include <string>
#include "Animal.hpp"


class Habitat
{
private:
    std::string type;
    std::vector<Animal> animals;
    int capacity;
    float cleanlinessLevel;
    float price;

public:
    Habitat(const std::string &type, const std::vector<Animal> &animals, int capacity = 5, float cleanlinessLevel = 1.0f,
            float price = 10000.0f)
        : type(type),
          animals(animals),
          capacity(capacity),
          cleanlinessLevel(cleanlinessLevel),
          price(price)
    {
    }

    ~Habitat() = default;

    Habitat(const Habitat &other)
        : type(other.type),
          animals(other.animals),
          capacity(other.capacity),
          cleanlinessLevel(other.cleanlinessLevel),
          price(other.price)
    {
    }

    Habitat(Habitat &&other) noexcept
        : type(std::move(other.type)),
          animals(std::move(other.animals)),
          capacity(other.capacity),
          cleanlinessLevel(other.cleanlinessLevel),
          price(other.price)
    {
    }

    Habitat &operator=(const Habitat &other)
    {
        if (this == &other)
            return *this;
        type = other.type;
        animals = other.animals;
        capacity = other.capacity;
        cleanlinessLevel = other.cleanlinessLevel;
        price = other.price;
        return *this;
    }

    Habitat &operator=(Habitat &&other) noexcept
    {
        if (this == &other)
            return *this;
        type = std::move(other.type);
        animals = std::move(other.animals);
        capacity = other.capacity;
        cleanlinessLevel = other.cleanlinessLevel;
        price = other.price;
        return *this;
    }

    [[nodiscard]] const std::string &getType() const
    {
        return type;
    }

    void setType(const std::string &newType)
    {
        this->type = newType;
    }

    [[nodiscard]] const std::vector<Animal> &getAnimals() const
    {
        return animals;
    }

    void addAnimals(const std::vector<Animal> &newAnimals)
    {
        for (const auto &animal: newAnimals)
        {
            this->animals.push_back(animal);
        }
    }

    void addAnimals(const Animal &animal)
    {
        this->animals.push_back(animal);
    }

    [[nodiscard]] int getCapacity() const
    {
        return capacity;
    }

    void setCapacity(int newCapacity)
    {
        this->capacity = newCapacity;
    }

    [[nodiscard]] float getCleanlinessLevel() const
    {
        return cleanlinessLevel;
    }

    void setCleanlinessLevel(float level)
    {
            cleanlinessLevel = level;
    }

    [[nodiscard]] float getPrice() const
    {
        return price;
    }

    void setPrice(float new_price)
    {
        price = new_price;
    }

    void cleanHabitat()
    {
        cleanlinessLevel = 1.0f;
    }

    void updateCleanliness(float deltaTime)
    {
        int totalAnimals = animals.size();
        if (totalAnimals > 0)
        {
            const float decayRate = 0.01f;
            cleanlinessLevel -= decayRate * totalAnimals * deltaTime;
            if (cleanlinessLevel < 0.0f)
            {
                cleanlinessLevel = 0.0f;
            }
        }
    }

    friend std::ostream &operator<<(std::ostream &os, const Habitat &habitat)
    {
        os << "Habitat: " << habitat.type << "\n"
           << "  Capacity: " << habitat.capacity << "\n"
           << "  Cleanliness: " << (habitat.cleanlinessLevel * 100) << "%" << "\n"
           << "  Price: $" << habitat.price << "\n"
           << "  Animals: " << habitat.animals.size();
        return os;
    }
};



#endif //HABITAT_H
