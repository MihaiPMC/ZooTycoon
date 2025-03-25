//
// Created by Mihai Patru on 25.03.2025.
//

#ifndef ANIMAL_H
#define ANIMAL_H

#include <string>
#include <iostream>

class Animal
{
private:
    std::string name;
    std::string species;
    int age;
    float weight;
    float height;
    float isHealthy;
    int price;
    float foodLevel;


public:
    Animal(const std::string &name, const std::string &species, int age, float weight, float height, float is_healthy = 1.0f,
           int price = 1000, float hunger = 0.0f)
        : name(name),
          species(species),
          age(age),
          weight(weight),
          height(height),
          isHealthy(is_healthy),
          price(price),
          foodLevel(hunger)
    {
    }

    ~Animal() = default;

    Animal(const Animal &other)
        : name(other.name),
          species(other.species),
          age(other.age),
          weight(other.weight),
          height(other.height),
          isHealthy(other.isHealthy),
          price(other.price),
          foodLevel(other.foodLevel)
    {
    }

    Animal(Animal &&other) noexcept
        : name(std::move(other.name)),
          species(std::move(other.species)),
          age(other.age),
          weight(other.weight),
          height(other.height),
          isHealthy(other.isHealthy),
          price(other.price),
          foodLevel(other.foodLevel)
    {
    }

    Animal &operator=(const Animal &other)
    {
        if (this == &other)
            return *this;
        name = other.name;
        species = other.species;
        age = other.age;
        weight = other.weight;
        height = other.height;
        isHealthy = other.isHealthy;
        price = other.price;
        foodLevel = other.foodLevel;
        return *this;
    }

    Animal &operator=(Animal &&other) noexcept
    {
        if (this == &other)
            return *this;
        name = std::move(other.name);
        species = std::move(other.species);
        age = other.age;
        weight = other.weight;
        height = other.height;
        isHealthy = other.isHealthy;
        price = other.price;
        foodLevel = other.foodLevel;
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

    [[nodiscard]] const std::string &getSpecies() const
    {
        return species;
    }

    void setSpecies(const std::string &newSpecies)
    {
        this->species = newSpecies;
    }

    [[nodiscard]] int getAge() const
    {
        return age;
    }

    void setAge(int newAge)
    {
        this->age = newAge;
    }

    [[nodiscard]] float getWeight() const
    {
        return weight;
    }

    void setWeight(float newWeight)
    {
        this->weight = newWeight;
    }

    [[nodiscard]] float getHeight() const
    {
        return height;
    }

    void setHeight(float newHeight)
    {
        this->height = newHeight;
    }

    [[nodiscard]] float getIsHealthy() const
    {
        return isHealthy;
    }

    void setIsHealthy(float is_healthy)
    {
        isHealthy = is_healthy;
    }

    [[nodiscard]] int getPrice() const
    {
        return price;
    }

    void setPrice(int new_price)
    {
        price = new_price;
    }

    [[nodiscard]] float getHunger() const
    {
        return foodLevel;
    }

    void setHunger(float newHunger)
    {
        this->foodLevel = newHunger;
    }

    void updateHealth()
    {
        if (foodLevel < 0.2f)
        {
            isHealthy -= 0.1f;
        }
        else
        {
            isHealthy += 0.1f;
        }
    }

    void updateHunger(float deltaTime)
    {
        const float decayRate = 0.05f;
        foodLevel -= decayRate * deltaTime;
        if (foodLevel < 0.0f)
        {
            foodLevel = 0.0f;
        }
    }

    friend std::ostream &operator<<(std::ostream &os, const Animal &animal)
    {
        os << "Animal: " << animal.name << "\n"
                << "  Species: " << animal.species << "\n"
                << "  Age: " << animal.age << " years\n"
                << "  Weight: " << animal.weight << " kg\n"
                << "  Height: " << animal.height << " cm\n"
                << "  Health Status: " << (animal.isHealthy * 100) << "%" << "\n"
                << "  Hunger Level: " << (animal.foodLevel * 100) << "%" << "\n"
                << "  Price: $" << animal.price;
        return os;
    }
};


#endif //ANIMAL_H
