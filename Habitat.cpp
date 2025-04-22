#include "Habitat.hpp"

Habitat::Habitat(const std::string &type, const std::vector<Animal> &animals, int capacity, float cleanlinessLevel,
        float price)
    : type(type),
      animals(animals),
      capacity(capacity),
      cleanlinessLevel(cleanlinessLevel),
      price(price)
{
}

Habitat::Habitat(const Habitat &other)
    : type(other.type),
      animals(other.animals),
      capacity(other.capacity),
      cleanlinessLevel(other.cleanlinessLevel),
      price(other.price)
{
}

Habitat::Habitat(Habitat &&other) noexcept
    : type(std::move(other.type)),
      animals(std::move(other.animals)),
      capacity(other.capacity),
      cleanlinessLevel(other.cleanlinessLevel),
      price(other.price)
{
}

Habitat &Habitat::operator=(const Habitat &other)
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

Habitat &Habitat::operator=(Habitat &&other) noexcept
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

const std::string &Habitat::getType() const
{
    return type;
}

void Habitat::setType(const std::string &newType)
{
    this->type = newType;
}

const std::vector<Animal> &Habitat::getAnimals() const
{
    return animals;
}

void Habitat::addAnimals(const std::vector<Animal> &newAnimals)
{
    for (const auto &animal: newAnimals)
    {
        this->animals.push_back(animal);
    }
}

void Habitat::addAnimals(const Animal &animal)
{
    this->animals.push_back(animal);
}

int Habitat::getCapacity() const
{
    return capacity;
}

void Habitat::setCapacity(int newCapacity)
{
    this->capacity = newCapacity;
}

float Habitat::getCleanlinessLevel() const
{
    return cleanlinessLevel;
}

void Habitat::setCleanlinessLevel(float level)
{
    cleanlinessLevel = level;
}

float Habitat::getPrice() const
{
    return price;
}

void Habitat::setPrice(float new_price)
{
    price = new_price;
}

void Habitat::cleanHabitat()
{
    cleanlinessLevel = 1.0f;
}

void Habitat::updateCleanliness(float deltaTime)
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

std::ostream &operator<<(std::ostream &os, const Habitat &habitat)
{
    os << "Habitat: " << habitat.type << "\n"
       << "  Capacity: " << habitat.capacity << "\n"
       << "  Cleanliness: " << (habitat.cleanlinessLevel * 100) << "%" << "\n"
       << "  Price: $" << habitat.price << "\n"
       << "  Animals: " << habitat.animals.size();
    return os;
}
