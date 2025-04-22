#include "../include/Zoo.hpp"
#include <algorithm>

Zoo::Zoo(const std::string &name, const std::vector<Habitat> &habitats, int visitor_count, bool is_open, float budget)
    : name(name),
      habitats(habitats),
      visitorCount(visitor_count),
      isOpen(is_open),
      budget(budget)
{
}

Zoo::Zoo(const Zoo &other)
    : name(other.name),
      habitats(other.habitats),
      visitorCount(other.visitorCount),
      isOpen(other.isOpen),
      budget(other.budget)
{
}

Zoo::Zoo(Zoo &&other) noexcept
    : name(std::move(other.name)),
      habitats(std::move(other.habitats)),
      visitorCount(other.visitorCount),
      isOpen(other.isOpen),
      budget(other.budget)
{
}

Zoo &Zoo::operator=(const Zoo &other)
{
    if (this == &other)
        return *this;
    name = other.name;
    habitats = other.habitats;
    visitorCount = other.visitorCount;
    isOpen = other.isOpen;
    budget = other.budget;
    return *this;
}

Zoo &Zoo::operator=(Zoo &&other) noexcept
{
    if (this == &other)
        return *this;
    name = std::move(other.name);
    habitats = std::move(other.habitats);
    visitorCount = other.visitorCount;
    isOpen = other.isOpen;
    budget = other.budget;
    return *this;
}

const std::string &Zoo::getName() const
{
    return name;
}

void Zoo::setName(const std::string &newName)
{
    this->name = newName;
}

const std::vector<Habitat> &Zoo::getHabitats() const
{
    return habitats;
}

void Zoo::addHabitats(const std::vector<Habitat> &newHabitats)
{
    for (const auto &habitat: newHabitats)
    {
        this->habitats.push_back(habitat);
    }
}

void Zoo::addHabitats(const Habitat &habitat)
{
    this->habitats.push_back(habitat);
    this->budget -= habitat.getPrice();
}

int Zoo::getVisitorCount() const
{
    return visitorCount;
}

void Zoo::setVisitorCount(int visitor_count)
{
    visitorCount = visitor_count;
}

bool Zoo::getIsOpen() const
{
    return isOpen;
}

void Zoo::setIsOpen(bool is_open)
{
    isOpen = is_open;
}

float Zoo::getBudget() const
{
    return budget;
}

void Zoo::setBudget(float newBudget)
{
    this->budget = newBudget;
}

void Zoo::feedAnimals(float foodAmountPerAnimal, float costPerAnimal)
{
    int totalAnimals = 0;
    float totalCost = 0.0f;

    for (const auto& habitat : habitats)
    {
        totalAnimals += habitat.getAnimals().size();
    }

    totalCost = totalAnimals * costPerAnimal;

    if (budget < totalCost)
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

    budget -= totalCost;

    std::cout << "Fed " << totalAnimals << " animals for a total cost of $" << totalCost << std::endl;
    std::cout << "Remaining budget: $" << budget << std::endl;
}

void Zoo::updateHunger(float deltaTime)
{
    for (const auto &habitat: habitats)
    {
        for (auto &animal: const_cast<std::vector<Animal> &>(habitat.getAnimals()))
        {
            animal.updateHunger(deltaTime);
        }
    }
}

std::ostream &operator<<(std::ostream &os, const Zoo &zoo)
{
    os << "Zoo: " << zoo.name << "\n"
       << "  Habitats: " << zoo.habitats.size() << "\n"
       << "  Visitor Count: " << zoo.visitorCount << "\n"
       << "  Status: " << (zoo.isOpen ? "Open" : "Closed") << "\n"
       << "  Budget: $" << zoo.budget;
    return os;
}
