//
// Created by Mihai Patru on 25.03.2025.
//

#ifndef VISITOR_H
#define VISITOR_H

#include <string>
#include <iostream>
#include <vector>

class Visitor
{
private:
    std::string name;
    int age;
    float money;
    std::string type;

public:
    Visitor(const std::string &name, int age, float money, const std::string &type)
        : name(name),
          age(age),
          money(money),
          type(type)
    {
    }

    ~Visitor() = default;

    Visitor(const Visitor &other)
        : name(other.name),
          age(other.age),
          money(other.money),
          type(other.type)
    {
    }

    Visitor(Visitor &&other) noexcept
        : name(std::move(other.name)),
          age(other.age),
          money(other.money),
          type(other.type)
    {
    }

    Visitor &operator=(const Visitor &other)
    {
        if (this == &other)
            return *this;
        name = other.name;
        age = other.age;
        money = other.money;
        type = other.type;
        return *this;
    }

    Visitor &operator=(Visitor &&other) noexcept
    {
        if (this == &other)
            return *this;
        name = std::move(other.name);
        age = other.age;
        money = other.money;
        type = other.type;
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

    [[nodiscard]] const std::string &getType() const
    {
        return type;
    }

    void setType(const std::string &newType)
    {
        this->type = newType;
    }

    friend std::ostream &operator<<(std::ostream &os, const Visitor &visitor)
    {
        os << "Visitor: " << visitor.name << "\n"
           << "  Type: " << visitor.type << "\n"
           << "  Age: " << visitor.age << " years\n"
           << "  Money: $" << visitor.money;
        return os;
    }
};




#endif //VISITOR_H
