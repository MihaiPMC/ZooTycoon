#include <iostream>
#include <array>
#include <chrono>
#include <thread>

#include <SFML/Graphics.hpp>

#include <Helper.h>


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

    void isFeed(float food)
    {
        foodLevel += food;
        if (foodLevel > 1.0f)
        {
            foodLevel = 1.0f;
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


public:
    Animal(const std::string &name, const std::string &species, int age, float weight, float height, float is_healthy,
           int price = 0, float hunger = 0.0f)
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

    [[nodiscard]] float getIsHealthy() const // Changed return type from bool to float
    {
        return isHealthy;
    }

    void setIsHealthy(float is_healthy) // Changed parameter type from bool to float
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

class Habitat
{
private:
    std::string type;
    std::vector<Animal> animals;
    int capacity;
    bool isClean;
    float price;

public:
    Habitat(const std::string &type, const std::vector<Animal> &animals, int capacity, bool is_clean,
            float price = 0.0f)
        : type(type),
          animals(animals),
          capacity(capacity),
          isClean(is_clean),
          price(price)
    {
    }

    ~Habitat() = default;

    Habitat(const Habitat &other)
        : type(other.type),
          animals(other.animals),
          capacity(other.capacity),
          isClean(other.isClean),
          price(other.price)
    {
    }

    Habitat(Habitat &&other) noexcept
        : type(std::move(other.type)),
          animals(std::move(other.animals)),
          capacity(other.capacity),
          isClean(other.isClean),
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
        isClean = other.isClean;
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
        isClean = other.isClean;
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

    [[nodiscard]] bool getIsClean() const
    {
        return isClean;
    }

    void setIsClean(bool is_clean)
    {
        isClean = is_clean;
    }

    [[nodiscard]] float getPrice() const
    {
        return price;
    }

    void setPrice(float new_price)
    {
        price = new_price;
    }
    
    friend std::ostream &operator<<(std::ostream &os, const Habitat &habitat)
    {
        os << "Habitat: " << habitat.type << "\n"
           << "  Capacity: " << habitat.capacity << "\n"
           << "  Status: " << (habitat.isClean ? "Clean" : "Dirty") << "\n"
           << "  Price: $" << habitat.price << "\n"
           << "  Animals: " << habitat.animals.size();
        return os;
    }
};

class Zoo
{
private:
    std::string name;
    std::vector<Habitat> habitats;
    int visitorCount;
    bool isOpen;
    float buget;

public:
    Zoo(const std::string &name, const std::vector<Habitat> &habitats, int visitor_count, bool is_open, float buget)
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

class Staff
{
private:
    std::string name;
    std::string position;
    int age;
    float salary;

public:
    Staff(const std::string &name, const std::string &position, int age, float salary)
        : name(name),
          position(position),
          age(age),
          salary(salary)
    {
    }

    ~Staff() = default;

    Staff(const Staff &other)
        : name(other.name),
          position(other.position),
          age(other.age),
          salary(other.salary)
    {
    }

    Staff(Staff &&other) noexcept
        : name(std::move(other.name)),
          position(std::move(other.position)),
          age(other.age),
          salary(other.salary)
    {
    }

    Staff &operator=(const Staff &other)
    {
        if (this == &other)
            return *this;
        name = other.name;
        position = other.position;
        age = other.age;
        salary = other.salary;
        return *this;
    }

    Staff &operator=(Staff &&other) noexcept
    {
        if (this == &other)
            return *this;
        name = std::move(other.name);
        position = std::move(other.position);
        age = other.age;
        salary = other.salary;
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

    [[nodiscard]] const std::string &getPosition() const
    {
        return position;
    }

    void setPosition(const std::string &newPosition)
    {
        this->position = newPosition;
    }

    [[nodiscard]] int getAge() const
    {
        return age;
    }

    void setAge(int newAge)
    {
        this->age = newAge;
    }

    [[nodiscard]] float getSalary() const
    {
        return salary;
    }

    void setSalary(float newSalary)
    {
        this->salary = newSalary;
    }
    
    friend std::ostream &operator<<(std::ostream &os, const Staff &staff)
    {
        os << "Staff: " << staff.name << "\n"
           << "  Position: " << staff.position << "\n"
           << "  Age: " << staff.age << " years\n"
           << "  Salary: $" << staff.salary;
        return os;
    }
};

class Visitor
{
private:
    std::string name;
    int age;
    float money;

public:
    Visitor(const std::string &name, int age, float money)
        : name(name),
          age(age),
          money(money)
    {
    }

    ~Visitor() = default;

    Visitor(const Visitor &other)
        : name(other.name),
          age(other.age),
          money(other.money)
    {
    }

    Visitor(Visitor &&other) noexcept
        : name(std::move(other.name)),
          age(other.age),
          money(other.money)
    {
    }

    Visitor &operator=(const Visitor &other)
    {
        if (this == &other)
            return *this;
        name = other.name;
        age = other.age;
        money = other.money;
        return *this;
    }

    Visitor &operator=(Visitor &&other) noexcept
    {
        if (this == &other)
            return *this;
        name = std::move(other.name);
        age = other.age;
        money = other.money;
        return *this;
    }

    [[nodiscard]] const std::string &getName() const
    {
        return name;
    }

    void setName(const std::string &NewName)
    {
        this->name = NewName;
    }

    [[nodiscard]] int getAge() const
    {
        return age;
    }

    void setAge(int newAge)
    {
        this->age = newAge;
    }

    [[nodiscard]] float getMoney() const
    {
        return money;
    }

    void setMoney(float newMoney)
    {
        this->money = newMoney;
    }
    
    friend std::ostream &operator<<(std::ostream &os, const Visitor &visitor)
    {
        os << "Visitor: " << visitor.name << "\n"
           << "  Age: " << visitor.age << " years\n"
           << "  Money: $" << visitor.money;
        return os;
    }
};

int main()
{
    return 0;
}

