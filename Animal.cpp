//
// Created by Mihai Patru on 25.03.2025.
//

#include "Animal.hpp"

Animal::Animal(const std::string &name, const std::string &species, int age, float weight, float height,
               float is_healthy, int price, float hunger)
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

Animal::Animal(const Animal &other)
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

Animal::Animal(Animal &&other) noexcept
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

Animal &Animal::operator=(const Animal &other)
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

Animal &Animal::operator=(Animal &&other) noexcept
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

const std::string &Animal::getName() const
{
    return name;
}

void Animal::setName(const std::string &newName)
{
    this->name = newName;
}

const std::string &Animal::getSpecies() const
{
    return species;
}

void Animal::setSpecies(const std::string &newSpecies)
{
    this->species = newSpecies;
}

int Animal::getAge() const
{
    return age;
}

void Animal::setAge(int newAge)
{
    this->age = newAge;
}

float Animal::getWeight() const
{
    return weight;
}

void Animal::setWeight(float newWeight)
{
    this->weight = newWeight;
}

float Animal::getHeight() const
{
    return height;
}

void Animal::setHeight(float newHeight)
{
    this->height = newHeight;
}

float Animal::getIsHealthy() const
{
    return isHealthy;
}

void Animal::setIsHealthy(float is_healthy)
{
    isHealthy = is_healthy;
}

int Animal::getPrice() const
{
    return price;
}

void Animal::setPrice(int new_price)
{
    price = new_price;
}

float Animal::getHunger() const
{
    return foodLevel;
}

void Animal::setHunger(float newHunger)
{
    this->foodLevel = newHunger;
}

void Animal::updateHealth()
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

void Animal::updateHunger(float deltaTime)
{
    const float decayRate = 0.05f;
    foodLevel -= decayRate * deltaTime;
    if (foodLevel < 0.0f)
    {
        foodLevel = 0.0f;
    }
}

std::ostream &operator<<(std::ostream &os, const Animal &animal)
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
