//
// Created by Mihai Patru on 25.03.2025.
//

#ifndef STAFF_H
#define STAFF_H

#include <string>
#include <iostream>



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




#endif //STAFF_H
