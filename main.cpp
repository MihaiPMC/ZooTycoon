#include <iostream>
#include <array>
#include <chrono>
#include <thread>

#include <SFML/Graphics.hpp>

#include <Helper.h>

#include "ResourceManager.hpp"


//////////////////////////////////////////////////////////////////////
/// This class is used to test that the memory leak checks work as expected even when using a GUI
class SomeClass {
public:
    explicit SomeClass(int) {}
};

SomeClass *getC() {
    return new SomeClass{2};
}
//////////////////////////////////////////////////////////////////////

class Animal
{
    private:
    std::string name;
    std::string species;
    int age;
    float weight;
    float height;
    bool isHealthy;
    int price;
public:
    Animal(const std::string &name, const std::string &species, int age, float weight, float height, bool is_healthy, int price = 0)
        : name(name),
          species(species),
          age(age),
          weight(weight),
          height(height),
          isHealthy(is_healthy),
          price(price)
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
          price(other.price)
    {
    }

    Animal(Animal &&other) noexcept
        : name(std::move(other.name)),
          species(std::move(other.species)),
          age(other.age),
          weight(other.weight),
          height(other.height),
          isHealthy(other.isHealthy),
          price(other.price)
    {
    }

    Animal & operator=(const Animal &other)
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
        return *this;
    }

    Animal & operator=(Animal &&other) noexcept
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
        return *this;
    }

    [[nodiscard]] const std::string& getName() const
    {
        return name;
    }

    void setName(const std::string &name)
    {
        this->name = name;
    }

    [[nodiscard]] const std::string& getSpecies() const
    {
        return species;
    }

    void setSpecies(const std::string &species)
    {
        this->species = species;
    }

    [[nodiscard]] int getAge() const
    {
        return age;
    }

    void setAge(int age)
    {
        this->age = age;
    }

    [[nodiscard]] float getWeight() const
    {
        return weight;
    }

    void setWeight(float weight)
    {
        this->weight = weight;
    }

    [[nodiscard]] float getHeight() const
    {
        return height;
    }

    void setHeight(float height)
    {
        this->height = height;
    }

    [[nodiscard]] bool getIsHealthy() const
    {
        return isHealthy;
    }

    void setIsHealthy(bool is_healthy)
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
    Habitat(const std::string &type, const std::vector<Animal> &animals, int capacity, bool is_clean, float price = 0.0f)
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

    Habitat & operator=(const Habitat &other)
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

    Habitat & operator=(Habitat &&other) noexcept
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

    [[nodiscard]] const std::string& getType() const
    {
        return type;
    }

    void setType(const std::string &type)
    {
        this->type = type;
    }

    [[nodiscard]] const std::vector<Animal>& getAnimals() const
    {
        return animals;
    }

    void setAnimals(const std::vector<Animal> &animals)
    {
        this->animals = animals;
    }

    [[nodiscard]] int getCapacity() const
    {
        return capacity;
    }

    void setCapacity(int capacity)
    {
        this->capacity = capacity;
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

    Zoo & operator=(const Zoo &other)
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

    Zoo & operator=(Zoo &&other) noexcept
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

    [[nodiscard]] const std::string& getName() const
    {
        return name;
    }

    void setName(const std::string &name)
    {
        this->name = name;
    }

    [[nodiscard]] const std::vector<Habitat>& getHabitats() const
    {
        return habitats;
    }

    void setHabitats(const std::vector<Habitat> &habitats)
    {
        this->habitats = habitats;
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

    void setBuget(float buget)
    {
        this->buget = buget;
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

    Staff & operator=(const Staff &other)
    {
        if (this == &other)
            return *this;
        name = other.name;
        position = other.position;
        age = other.age;
        salary = other.salary;
        return *this;
    }

    Staff & operator=(Staff &&other) noexcept
    {
        if (this == &other)
            return *this;
        name = std::move(other.name);
        position = std::move(other.position);
        age = other.age;
        salary = other.salary;
        return *this;
    }

    [[nodiscard]] const std::string& getName() const
    {
        return name;
    }

    void setName(const std::string &name)
    {
        this->name = name;
    }

    [[nodiscard]] const std::string& getPosition() const
    {
        return position;
    }

    void setPosition(const std::string &position)
    {
        this->position = position;
    }

    [[nodiscard]] int getAge() const
    {
        return age;
    }

    void setAge(int age)
    {
        this->age = age;
    }

    [[nodiscard]] float getSalary() const
    {
        return salary;
    }

    void setSalary(float salary)
    {
        this->salary = salary;
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

    Visitor & operator=(const Visitor &other)
    {
        if (this == &other)
            return *this;
        name = other.name;
        age = other.age;
        money = other.money;
        return *this;
    }

    Visitor & operator=(Visitor &&other) noexcept
    {
        if (this == &other)
            return *this;
        name = std::move(other.name);
        age = other.age;
        money = other.money;
        return *this;
    }

    [[nodiscard]] const std::string& getName() const
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

    void setAge(int age)
    {
        this->age = age;
    }

    [[nodiscard]] float getMoney() const
    {
        return money;
    }

    void setMoney(float money)
    {
        this->money = money;
    }
};

int main() {
    // Create animals
    Animal lion("Leo", "Lion", 5, 190.5, 120.0, true, 5000);
    Animal tiger("Raja", "Tiger", 4, 170.0, 110.0, true, 4500);
    Animal elephant("Dumbo", "Elephant", 10, 4500.0, 300.0, true, 8000);
    Animal giraffe("Spots", "Giraffe", 7, 1200.0, 500.0, false, 6000);
    
    // Display animal information
    std::cout << "Animal Example:" << std::endl;
    std::cout << "Name: " << lion.getName() << ", Species: " << lion.getSpecies() 
              << ", Age: " << lion.getAge() << ", Health Status: " << (lion.getIsHealthy() ? "Healthy" : "Sick") << std::endl;
    
    // Update animal information
    giraffe.setIsHealthy(true);
    std::cout << "Updated " << giraffe.getName() << "'s health status to: " 
              << (giraffe.getIsHealthy() ? "Healthy" : "Sick") << std::endl;
    
    // Create habitats
    std::vector<Animal> savanna_animals = {lion, giraffe};
    std::vector<Animal> jungle_animals = {tiger};
    std::vector<Animal> forest_animals = {elephant};
    
    Habitat savanna("Savanna", savanna_animals, 5, true, 10000.0f);
    Habitat jungle("Jungle", jungle_animals, 3, false, 8000.0f);
    Habitat forest("Forest", forest_animals, 4, true, 7500.0f);
    
    // Display habitat information
    std::cout << "\nHabitat Example:" << std::endl;
    std::cout << "Type: " << savanna.getType() << ", Capacity: " << savanna.getCapacity() 
              << ", Clean: " << (savanna.getIsClean() ? "Yes" : "No") 
              << ", Animals: " << savanna.getAnimals().size() << std::endl;
    
    // Clean the jungle habitat
    jungle.setIsClean(true);
    std::cout << "Cleaned the " << jungle.getType() << " habitat. Status: " 
              << (jungle.getIsClean() ? "Clean" : "Dirty") << std::endl;
    
    // Create zoo with habitats
    std::vector<Habitat> zoo_habitats = {savanna, jungle, forest};
    Zoo wildPark("Wild Park", zoo_habitats, 0, false, 100000.0f);
    
    // Display zoo information
    std::cout << "\nZoo Example:" << std::endl;
    std::cout << "Name: " << wildPark.getName() 
              << ", Number of Habitats: " << wildPark.getHabitats().size() 
              << ", Budget: $" << wildPark.getBuget() << std::endl;
    
    // Open the zoo
    wildPark.setIsOpen(true);
    std::cout << "Zoo is now " << (wildPark.getIsOpen() ? "open" : "closed") << " for visitors" << std::endl;
    
    // Create staff members
    Staff zookeeper("John Smith", "Zookeeper", 35, 3500.0f);
    Staff veterinarian("Sarah Johnson", "Veterinarian", 40, 5000.0f);
    Staff manager("Michael Brown", "Manager", 45, 6500.0f);
    
    // Display staff information
    std::cout << "\nStaff Example:" << std::endl;
    std::cout << "Name: " << zookeeper.getName() << ", Position: " << zookeeper.getPosition() 
              << ", Age: " << zookeeper.getAge() << ", Salary: $" << zookeeper.getSalary() << std::endl;
    
    // Give a raise to the veterinarian
    float newSalary = veterinarian.getSalary() * 1.1f; // 10% raise
    veterinarian.setSalary(newSalary);
    std::cout << veterinarian.getName() << " received a raise. New salary: $" << veterinarian.getSalary() << std::endl;
    
    // Create visitors
    Visitor adult("Alice Williams", 30, 100.0f);
    Visitor child("Bobby Williams", 8, 20.0f);
    Visitor senior("George Davis", 70, 50.0f);
    
    // Display visitor information
    std::cout << "\nVisitor Example:" << std::endl;
    std::cout << "Name: " << adult.getName() << ", Age: " << adult.getAge() 
              << ", Available Money: $" << adult.getMoney() << std::endl;
    
    // Visitors pay entrance fee
    float entranceFee = 15.0f;
    adult.setMoney(adult.getMoney() - entranceFee);
    child.setMoney(child.getMoney() - (entranceFee / 2)); // Half price for children
    senior.setMoney(senior.getMoney() - (entranceFee * 0.7f)); // 30% discount for seniors
    
    // Update zoo visitor count and budget
    wildPark.setVisitorCount(wildPark.getVisitorCount() + 3);
    wildPark.setBuget(wildPark.getBuget() + entranceFee + (entranceFee / 2) + (entranceFee * 0.7f));
    
    std::cout << "After visitors entered:" << std::endl;
    std::cout << "Zoo visitor count: " << wildPark.getVisitorCount() << std::endl;
    std::cout << "Zoo budget: $" << wildPark.getBuget() << std::endl;
    std::cout << adult.getName() << " has $" << adult.getMoney() << " left" << std::endl;

    return 0;
}
