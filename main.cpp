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

    [[nodiscard]] std::string name1() const
    {
        return name;
    }

    void set_name(const std::string &name)
    {
        this->name = name;
    }

    [[nodiscard]] std::string species1() const
    {
        return species;
    }

    void set_species(const std::string &species)
    {
        this->species = species;
    }

    [[nodiscard]] int age1() const
    {
        return age;
    }

    void set_age(int age)
    {
        this->age = age;
    }

    [[nodiscard]] float weight1() const
    {
        return weight;
    }

    void set_weight(float weight)
    {
        this->weight = weight;
    }

    [[nodiscard]] float height1() const
    {
        return height;
    }

    void set_height(float height)
    {
        this->height = height;
    }

    [[nodiscard]] bool is_healthy() const
    {
        return isHealthy;
    }

    void set_is_healthy(bool is_healthy)
    {
        isHealthy = is_healthy;
    }

    [[nodiscard]] int get_price() const
    {
        return price;
    }

    void set_price(int new_price)
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

    [[nodiscard]] std::string type1() const
    {
        return type;
    }

    void set_type(const std::string &type)
    {
        this->type = type;
    }

    [[nodiscard]] std::vector<Animal> animals1() const
    {
        return animals;
    }

    void set_animals(const std::vector<Animal> &animals)
    {
        this->animals = animals;
    }

    [[nodiscard]] int capacity1() const
    {
        return capacity;
    }

    void set_capacity(int capacity)
    {
        this->capacity = capacity;
    }

    [[nodiscard]] bool is_clean() const
    {
        return isClean;
    }

    void set_is_clean(bool is_clean)
    {
        isClean = is_clean;
    }

    [[nodiscard]] float get_price() const
    {
        return price;
    }

    void set_price(float new_price)
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

    [[nodiscard]] std::string name1() const
    {
        return name;
    }

    void set_name(const std::string &name)
    {
        this->name = name;
    }

    [[nodiscard]] std::vector<Habitat> habitats1() const
    {
        return habitats;
    }

    void set_habitats(const std::vector<Habitat> &habitats)
    {
        this->habitats = habitats;
    }

    [[nodiscard]] int visitor_count() const
    {
        return visitorCount;
    }

    void set_visitor_count(int visitor_count)
    {
        visitorCount = visitor_count;
    }

    [[nodiscard]] bool is_open() const
    {
        return isOpen;
    }

    void set_is_open(bool is_open)
    {
        isOpen = is_open;
    }

    [[nodiscard]] float buget1() const
    {
        return buget;
    }

    void set_buget(float buget)
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

    [[nodiscard]] std::string name1() const
    {
        return name;
    }

    void set_name(const std::string &name)
    {
        this->name = name;
    }

    [[nodiscard]] std::string position1() const
    {
        return position;
    }

    void set_position(const std::string &position)
    {
        this->position = position;
    }

    [[nodiscard]] int age1() const
    {
        return age;
    }

    void set_age(int age)
    {
        this->age = age;
    }

    [[nodiscard]] float salary1() const
    {
        return salary;
    }

    void set_salary(float salary)
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

    [[nodiscard]] std::string name1() const
    {
        return name;
    }

    void set_name(const std::string &NewName)
    {
        this->name = NewName;
    }

    [[nodiscard]] int age1() const
    {
        return age;
    }

    void set_age(int age)
    {
        this->age = age;
    }

    [[nodiscard]] float money1() const
    {
        return money;
    }

    void set_money(float money)
    {
        this->money = money;
    }
};

int main() {

    return 0;
}
