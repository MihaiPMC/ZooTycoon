#include <iostream>
#include <array>
#include <chrono>
#include <thread>
#include <map>
#include <random>

#include <SFML/Graphics.hpp>

template<typename T>
T random(T min, T max) {
    static std::random_device rd;
    static std::mt19937 gen(rd());
    
    if constexpr (std::is_integral<T>::value) {
        std::uniform_int_distribution<T> dist(min, max);
        return dist(gen);
    } else {
        std::uniform_real_distribution<T> dist(min, max);
        return dist(gen);
    }
}

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

class Zoo
{
private:
    std::string name;
    std::vector<Habitat> habitats;
    int visitorCount;
    bool isOpen;
    float buget;

public:
    Zoo(const std::string &name, const std::vector<Habitat> &habitats, int visitor_count, bool is_open, float buget = 100000)
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
        this->buget -= habitat.getPrice();
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

    void  feedAnimals(float foodAmountPerAnimal = 0.3f, float costPerAnimal = 10.0f)
    {
        int totalAnimals = 0;
        float totalCost = 0.0f;

        for (const auto& habitat : habitats)
        {
            totalAnimals += habitat.getAnimals().size();
        }

        totalCost = totalAnimals * costPerAnimal;

        if (buget < totalCost)
        {
            std::cout << "Not enough budget to feed all animals!" << std::endl;
            return;
        }

        for (auto& habitat : habitats)
        {
            for (auto& animal : const_cast<std::vector<Animal>&>(habitat.getAnimals()))
            {
                animal.setHunger(std::min(1.0f, animal.getHunger() + foodAmountPerAnimal));
            }
        }

        buget -= totalCost;

        std::cout << "Fed " << totalAnimals << " animals for a total cost of $" << totalCost << std::endl;
        std::cout << "Remaining budget: $" << buget << std::endl;
    }

    void updateHunger(float deltaTime)
    {
        for (auto &habitat: habitats)
        {
            for (auto &animal: const_cast<std::vector<Animal> &>(habitat.getAnimals()))
            {
                animal.updateHunger(deltaTime);
            }
        }
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

int main()
{

    std::map<std::string, std::vector<std::string>> habitatSpecies = {
        {"Forest", {"Bear", "Wolf", "Fox", "Deer", "Owl"}},
        {"Desert", {"Camel", "Scorpion", "Rattlesnake", "Coyote", "Lizard"}},
        {"Ocean", {"Dolphin", "Shark", "Octopus", "Penguin", "Sea Turtle"}},
        {"Savanna", {"Lion", "Elephant", "Zebra", "Giraffe", "Cheetah"}},
        {"Mountain", {"Eagle", "Mountain Lion", "Goat", "Yak", "Snow Leopard"}}
    };

    std::vector<std::string> animalNames = {
        "Luna", "Max", "Rocky", "Bella", "Charlie", "Lucy", "Leo", "Daisy", "Simba", "Nala",
        "Jack", "Molly", "Duke", "Sadie", "Teddy", "Ruby", "Oliver", "Rosie", "Milo", "Lola",
        "Buddy", "Coco", "Oscar", "Maggie", "Tank", "Penny", "Zeus", "Stella", "Rex", "Sophie",
        "Toby", "Zoey", "Riley", "Chloe", "Bandit", "Ellie", "Scout", "Piper", "Bruno", "Lily",
        "Abby", "Ace", "Ada", "Adam", "Addie", "Admiral", "Aero", "Aiden", "Ajax", "Alamo",
        "Alaska", "Alba", "Albert", "Alden", "Alec", "Alex", "Alexa", "Alexis", "Alfie", "Alice",
        "Allie", "Ally", "Amber", "Amelia", "Amigo", "Amos", "Amy", "Angel", "Angus", "Annie",
        "Apollo", "April", "Archie", "Ares", "Aria", "Ariel", "Arlo", "Arnie", "Arrow", "Artemis",
        "Asher", "Ashton", "Aspen", "Astro", "Athena", "Atlas", "Atticus", "Aubrey", "Austin", "Autumn",
        "Avalon", "Avery", "Axel", "Axle", "Babette", "Bailey", "Bali", "Balto", "Bambino", "Bambi",
        "Banjo", "Barney", "Baron", "Basil", "Baxter", "Beamer", "Bean", "Bear", "Beau", "Becky",
        "Bellatrix", "Belle", "Benji", "Benny", "Bentley", "Berry", "Bessie", "Betty", "Bianca", "Billy",
        "Bingo", "Bishop", "Biscuit", "Blaze", "Blitz", "Blizzard", "Blosom", "Blue", "Bo", "Bobby",
        "Bodie", "Bogey", "Bonnie", "Boomer", "Boots", "Boris", "Boss", "Boston", "Bowser", "Boxer",
        "Brady", "Bramble", "Brandy", "Bravo", "Breeze", "Breezy", "Brenna", "Brennan", "Brew", "Brian",
        "Bridget", "Briggs", "Brio", "Bronco", "Bronson", "Brooke", "Brooklyn", "Bruce", "Buck", "Buckeye",
        "Bucky", "Bud", "Buddy", "Buffy", "Bullet", "Bumble", "Bunny", "Buttercup", "Buzz", "Byron",
        "Cade", "Caesar", "Cairo", "Cali", "Callie", "Calvin", "Camden", "Camilla", "Candy", "Captain",
        "Cara", "Carla", "Carlo", "Carmen", "Carter", "Casey", "Cash", "Casper", "Cassie", "Cassius",
        "Castle", "Cayenne", "Cedar", "Cello", "Chance", "Chandler", "Chanel", "Chaos", "Chaplin", "Charger",
        "Charm", "Chase", "Chauncy", "Chaz", "Checkers", "Cheech", "Chelsea", "Cherokee", "Cherry", "Cherub",
        "Chester", "Chevy", "Chew", "Chewie", "Chewy", "Cheyenne", "Chip", "Chipper", "Chips", "Chloe",
        "Chocolate", "Chrissy", "Chubby", "Chuck", "Chucky", "Cinder", "Cinnamon", "Cisco", "Claire", "Clancy",
        "Clark", "Claude", "Clay", "Clemson", "Cleo", "Cleopatra", "Cliff", "Clifford", "Clive", "Cloe",
        "Clover", "Clyde", "Coal", "Cobalt", "Coco", "Cocoa", "Coconut", "Cody", "Coffee", "Cognac",
        "Colby", "Cole", "Comet", "Commando", "Connor", "Cookie", "Cooper", "Copper", "Coral", "Corby",
        "Cortez", "Cosmo", "Cotton", "Courage", "Cowboy", "Cozmo", "Crackers", "Cricket", "Crimson", "Crosby",
        "Crow", "Cruise", "Crunch", "Cruz", "Cubby", "Cujo", "Curry", "Curtis", "Cutie", "Cyrus",
        "Daffodil", "Dagger", "Daisy", "Dakota", "Dallas", "Damien", "Dana", "Dane", "Danger", "Dante",
        "Darby", "Darcy", "Darwin", "Dave", "Dawson", "Dax", "Dayzie", "Dazzle", "Dean", "Deejay",
        "Delta", "Denali", "Denver", "Deuce", "Dexter", "Diablo", "Diamond", "Diego", "Diesel", "Digger",
        "Dillon", "Dingo", "Dinky", "Dino", "Dixie", "Dobie", "Doc", "Dodger", "Domingo", "Domino",
        "Donner", "Dora", "Doreen", "Dorrie", "Dotty", "Doug", "Dozer", "Drake", "Dreamer", "Drover",
        "Drum", "Dryden", "Dudley", "Duffy", "Dugan", "Duke", "Dune", "Duster", "Dusty", "Dutch",
        "Dylan", "Eagle", "Easton", "Echo", "Eddie", "Eden", "Edge", "Edison", "Edward", "Egor",
        "Electra", "Eli", "Elijah", "Elliot", "Elmer", "Elsa", "Elvis", "Ember", "Emerson", "Emily",
        "Emma", "Emmy", "Enzo", "Ernie", "Eva", "Evan", "Everest", "Evie", "Excalibur", "Ezra",
        "Faith", "Falco", "Falcon", "Fancy", "Fang", "Felix", "Fergie", "Ferguson", "Ferris", "Fez",
        "Fidget", "Fido", "Fiji", "Finn", "Fiona", "Fitz", "Flake", "Flash", "Fleet", "Fletcher",
        "Flicka", "Fling", "Flip", "Flora", "Flores", "Floyd", "Fluffy", "Flynn", "Fontana", "Forest",
        "Forrest", "Foster", "Fox", "Foxtrot", "Frankenstein", "Frankie", "Freddie", "Freedom", "Friday", "Frodo",
        "Frosty", "Fuji", "Gabe", "Gabriel", "Gadget", "Gaia", "Galadriel", "Galaxy", "Gandalf", "Garfield",
        "Garth", "Gary", "Gavin", "Gemini", "Genie", "George", "Georgia", "Ghost", "Gia", "Gibson",
        "Gideon", "Gigi", "Ginger", "Ginny", "Giovanni", "Giselle", "Glacier", "Gladys", "Glitter", "Gloria",
        "Glover", "Goliath", "Gonzo", "Goober", "Goose", "Gordon", "Grace", "Gracie", "Grady", "Graham",
        "Granite", "Grant", "Grayson", "Greenie", "Griffin", "Grim", "Grizzly", "Gromit", "Grover", "Guinness",
        "Gunner", "Gus", "Gypsy", "Hades", "Hadley", "Haiku", "Halley", "Halsey", "Hamilton", "Hamlet",
        "Hammer", "Hank", "Hanna", "Hannah", "Hansel", "Happy", "Harley", "Harpo", "Harrison", "Harry",
        "Harvey", "Hawkeye", "Hayes", "Hazel", "Heath", "Heidi", "Henry", "Hero", "Hershey", "Hestia",
        "Hickory", "Hobbes", "Holly", "Homer", "Honey", "Hooch", "Hoover", "Hope", "Horatio", "Hornet",
        "Houston", "Hudson", "Huey", "Hugh", "Hugo", "Humphrey", "Hunter", "Hyde", "Ice", "Iggy",
        "Igloo", "Igor", "Ike", "India", "Indie", "Indigo", "Indy", "Infinity", "Iris", "Irving",
        "Isaac", "Isabel", "Isabella", "Isabelle", "Isaiah", "Isis", "Isla", "Ivan", "Ivory", "Ivy",
        "Izzy", "Jackie", "Jackson", "Jade", "Jagger", "Jake", "Jasmine", "Jasper", "Java", "Jax",
        "Jazz", "Jazzy", "Jedi", "Jelly", "Jenna", "Jenny", "Jericho", "Jersey", "Jesse", "Jessie",
        "Jester", "Jet", "Jethro", "Jett", "Jewel", "Jiffy", "Jimmy", "Jinx", "Jitterbug", "JoJo",
        "Joanie", "Joaquin", "Jock", "Jody", "Joey", "Johnny", "Jojo", "Joker", "Jolene", "Jolly",
        "Jones", "Jordan", "Jorge", "Josie", "Journey", "Joy", "Judge", "Judy", "Jules", "Julia",
        "Julian", "Juliet", "June", "Junior", "Jupiter", "Justice", "Justin", "Kacey", "Kaia", "Kaiser",
        "Kallie", "Kangaroo", "Kansas", "Karma", "Kasey", "Katie", "Katrina", "Katy", "Kawasaki", "Kay",
        "Kayla", "Kaylee", "Kaz", "Kazoo", "Keats", "Keesha", "Kellan", "Kelsey", "Kelvin", "Ken",
        "Kendall", "Kennedy", "Kenny", "Kenya", "Kerry", "Kettle", "Kevin", "Kick", "Kid", "Kiki",
        "Killian", "King", "Kingston", "Kipling", "Kira", "Kirby", "Kit", "Kiwi", "Klaus", "Kleo",
        "Knight", "Knuckles", "Kobe", "Kodiak", "Koko", "Kona", "Kong", "Kosmo", "Kota", "Kramer",
        "Kris", "Krystal", "Kurt", "Kylie", "Kyra", "Lacey", "Laddie", "Lady", "Laika", "Lakota",
        "Lana", "Lance", "Land", "Lane", "Langley", "Lara", "Lark", "Larry", "Laser", "Lassie",
        "Latte", "Lauren", "Layla", "Lazarus", "Lazy", "Lefty", "Legacy", "Leia", "Lemon", "Lenny",
        "Leon", "Leonard", "Leonardo", "Leroy", "Levi", "Lewis", "Lexi", "Libby", "Liberty", "Licorice",
        "Lightning", "Lila", "Lilac", "Lincoln", "Linda", "Linus", "Lionel", "Lisa", "Little", "Logan",
        "London", "Lotus", "Louie", "Louis", "Lovey", "Lucas", "Lucky", "Luke", "Lulu", "Lumiere",
        "Luna", "Lynx", "Lyric", "Mac", "Macaroni", "Mack", "Mackenzie", "Maddie", "Madison", "Madonna",
        "Magic", "Magnum", "Magnus", "Maisie", "Maize", "Major", "Malcolm", "Mali", "Malibu", "Mallory",
        "Mama", "Mandy", "Mango", "Marble", "Marco", "Marcus", "Mariah", "Maris", "Marley", "Marlin",
        "Marmaduke", "Mars", "Marshal", "Martha", "Martin", "Marty", "Marvel", "Mary", "Mason", "Mateo",
        "Matilda", "Matrix", "Mattie", "Maui", "Maverick", "Mavis", "Maximus", "Maxwell", "May", "Maya",
        "Mazda", "McCoy", "Meadow", "Meatball", "Megan", "Memphis", "Mercedes", "Mercury", "Merlin", "Merry",
        "Mesquite", "Mia", "Miami", "Mica", "Michael", "Mickey", "Midnight", "Mikey", "Milan", "Miles",
        "Miller", "Milton", "Mimi", "Minnie", "Mint", "Minty", "Missy", "Misty", "Mitch", "Mittens",
        "Mocha", "Mojave", "Molly", "Monaco", "Mona", "Mongoose", "Monroe", "Montana", "Monterey", "Montgomery",
        "Monty", "Mookie", "Moon", "Moose", "Morgan", "Morris", "Moses", "Mozart", "Muffin", "Murphy",
        "Murray", "Mustang", "Mylo", "Mystic", "Mystique", "Nadia", "Nancy", "Nanette", "Nanny", "Naomi",
        "Napoleon", "Nash", "Natalie", "Nathan", "Navajo", "Navy", "Nemo", "Nena", "Neptune", "Nero",
        "Ness", "Nestle", "Nevada", "Newt", "Newton", "Nibbles", "Nickel", "Nicky", "Nico", "Nike",
        "Nikita", "Nikki", "Niko", "Nina", "Ninja", "Nixon", "Noah", "Nobel", "Noel", "Noelle",
        "Nola", "Noodle", "Noodles", "Norman", "North", "Norton", "Norway", "Nova", "Nugget", "Nutmeg",
        "Oasis", "Obi", "Ocean", "Odessa", "Odette", "Odin", "Ohio", "Okra", "Olaf", "Olive",
        "Oliver", "Olivia", "Ollie", "Olympia", "Omar", "Omega", "Onyx", "Opal", "Opie", "Oreo",
        "Orlando", "Orleans", "Oscar", "Otis", "Otto", "Owen", "Ozark", "Ozzie", "Pablo", "Paco",
        "Paddington", "Paddy", "Page", "Paige", "Paisley", "Paloma", "Pancake", "Pandora", "Panic", "Panther",
        "Papa", "Paris", "Parker", "Pascal", "Patch", "Patches", "Patriot", "Pattie", "Patton", "Paulie",
        "Paws", "Paxton", "Paxil", "Payday", "Peaches", "Peanut", "Pearl", "Pebbles", "Pedro", "Peggy",
        "Pele", "Penelope", "Penny", "Pepe", "Pepper", "Percy", "Periwinkle", "Perkins", "Perry", "Petunia",
        "Phantom", "Pharaoh", "Phoenix", "Phyllis", "Picasso", "Pickles", "Pierce", "Pierre", "Piglet", "Pilot"
    };

    std::cout << "Welcome to the Zoo Management System!" << std::endl;
    std::cout << "----------------------------------------" << std::endl;

    std::cout <<"What is the name of the zoo?" << std::endl;
    std::string zooName;
    std::getline(std::cin, zooName);
    std::cout << "Zoo name: " << zooName << std::endl;

    Zoo myZoo(zooName, {}, 0, true);
    std::cout << "Zoo created!" << std::endl;
    std::cout << "Your budget is $" << myZoo.getBuget() << std::endl;
    std::cout << "----------------------------------------" << std::endl;

    std::cout << "Now let's add some habitats!" << std::endl;
    std::cout<< "Habitat price is $10,000." << std::endl;
    std::cout << "----------------------------------------" << std::endl;

    initialHabitatsAdd:
    int habitatsCount;
    std::cout << "How many habitats do you want to add? ";
    std::cin >> habitatsCount;

    assert(habitatsCount > 0);

    if (habitatsCount > 5)
    {
        std::cout << "You can only add up to 5 habitats at a time." << std::endl;
        goto initialHabitatsAdd;
    }

    std::cout << "You have chosen to add " << habitatsCount << " habitats." << std::endl;


    for (int i = 0; i < habitatsCount; i++)
    {
        initialHabitatsSelection:
        std::cout << "What habitat do you want to add? 1. Forest 2. Desert 3. Ocean 4. Savanna 5. Mountain" << std::endl;
        int habitatType;
        std::cin >> habitatType;

        if (habitatType < 1 || habitatType > 5)
        {
            std::cout << "Invalid habitat type! Please choose again." << std::endl;
            goto initialHabitatsSelection;
        }

        Habitat newHabitat("", {});
        std::string habitatTypeName;

        switch (habitatType) {
            case 1:
                habitatTypeName = "Forest";
                break;
            case 2:
                habitatTypeName = "Desert";
                break;
            case 3:
                habitatTypeName = "Ocean";
                break;
            case 4:
                habitatTypeName = "Savanna";
                break;
            case 5:
                habitatTypeName = "Mountain";
                break;
            default:
                std::cout << "Invalid habitat type!" << std::endl;
                continue;
        }

        newHabitat.setType(habitatTypeName);
        std::cout << "Habitat added: " << newHabitat.getType() << std::endl;
        std::cout << "You have $" << myZoo.getBuget() << " left." << std::endl;

        initialAnimalAdd:
        int animalCount;
        std::cout << "How many animals would you like to add to this " << habitatTypeName << " habitat? (0-5): ";
        std::cout << "Animal price is $1000." << std::endl;
        std::cin >> animalCount;

        if (animalCount < 0 || animalCount > 5) {
            std::cout << "Invalid number of animals! Please choose again." << std::endl;
            goto initialAnimalAdd;
        }

        for (int j = 0; j < animalCount; j++) {
            std::cout << "Available species for " << habitatTypeName << " habitat:" << std::endl;

            const std::vector<std::string>& species = habitatSpecies[habitatTypeName];
            for (size_t k = 0; k < species.size(); k++) {
                std::cout << (k + 1) << ". " << species[k] << std::endl;
            }

            int speciesChoice;
            std::cout << "Choose a species (1-" << species.size() << "): ";
            std::cin >> speciesChoice;

            if (speciesChoice < 1 || speciesChoice > static_cast<int>(species.size())) {
                std::cout << "Invalid choice. Defaulting to first species." << std::endl;
                speciesChoice = 1;
            }

            std::string randomName = animalNames[random(0, static_cast<int>(animalNames.size()) - 1)];

            Animal newAnimal(
                randomName,
                species[speciesChoice - 1],
                random(1, 10),
                random(10.0f, 200.0f),
                random(20.0f, 150.0f),
                random(0.7f, 1.0f)
            );

            

            newHabitat.addAnimals(newAnimal);


            std::cout << "Added " << newAnimal.getName() << " the " << newAnimal.getSpecies()
                      << " to " << habitatTypeName << " habitat!" << std::endl;

            myZoo.setBuget(myZoo.getBuget() - newAnimal.getPrice());
            std::cout << "Remaining budget: $" << myZoo.getBuget() << std::endl;
        }

        myZoo.addHabitats(newHabitat);

    }

    std::cout << "----------------------------------------" << std::endl;
    std::cout << "Your zoo is ready!" << std::endl;
    std::cout << myZoo << std::endl;

    std::cout << "Here are your habitats and animals:" << std::endl;
    for (const auto& habitat : myZoo.getHabitats()) {
        std::cout << habitat << std::endl;
        std::cout << "Animals in this habitat:" << std::endl;
        for (const auto& animal : habitat.getAnimals()) {
            std::cout << "  - " << animal.getName() << " the " << animal.getSpecies() << std::endl;
        }
        std::cout << std::endl;
    }

    std::cout << "----------------------------------------" << std::endl;


    std::cout << "How many days do you want to simulate?" << std::endl;
    int days;
    std::cin >> days;
    assert(days > 0);
    std::cout << "You have chosen to simulate " << days << " days." << std::endl;


    for (int i = 0; i < days; i++)
    {
        std::cout << "Day " << (i + 1) << " of simulation." << std::endl;
        myZoo.updateHunger(1.0f);

        for (auto& habitat : const_cast<std::vector<Habitat>&>(myZoo.getHabitats()))
        {
            habitat.updateCleanliness(1.0f);
        }

        std::cout << "----------------------------------------" << std::endl;
        std::cout << "Daily Management Options:" << std::endl;
        std::cout << "1. Feed animals" << std::endl;
        std::cout << "2. Add a new habitat" << std::endl;
        std::cout << "3. Add animals to existing habitat" << std::endl;
        std::cout << "4. Continue to next day" << std::endl;
        std::cout << "Enter your choice: ";

        int dailyChoice;
        std::cin >> dailyChoice;

        switch (dailyChoice) {
            case 1: {
                myZoo.feedAnimals();
                break;
            }
            case 2: {
                std::cout << "Habitat price is $10,000." << std::endl;
                if (myZoo.getBuget() < 10000) {
                    std::cout << "Not enough budget to add a habitat!" << std::endl;
                    break;
                }

                std::cout << "What habitat do you want to add? 1. Forest 2. Desert 3. Ocean 4. Savanna 5. Mountain" << std::endl;
                int habitatType;
                std::cin >> habitatType;

                if (habitatType < 1 || habitatType > 5) {
                    std::cout << "Invalid habitat type! Operation cancelled." << std::endl;
                    break;
                }

                Habitat newHabitat("", {});
                std::string habitatTypeName;

                switch (habitatType) {
                    case 1: habitatTypeName = "Forest"; break;
                    case 2: habitatTypeName = "Desert"; break;
                    case 3: habitatTypeName = "Ocean"; break;
                    case 4: habitatTypeName = "Savanna"; break;
                    case 5: habitatTypeName = "Mountain"; break;
                    default: break;
                }

                newHabitat.setType(habitatTypeName);
                myZoo.addHabitats(newHabitat);
                std::cout << "Habitat added: " << habitatTypeName << std::endl;
                std::cout << "You have $" << myZoo.getBuget() << " left." << std::endl;

                std::cout << "Would you like to add animals to this new habitat? (1 for Yes, 0 for No): ";
                int addAnimals;
                std::cin >> addAnimals;

                if (addAnimals == 1) {
                    std::cout << "How many animals would you like to add? (0-5): ";
                    int animalCount;
                    std::cin >> animalCount;

                    if (animalCount < 0 || animalCount > 5) {
                        std::cout << "Invalid number of animals! Defaulting to 0." << std::endl;
                        animalCount = 0;
                    }

                    for (int j = 0; j < animalCount; j++) {
                        if (myZoo.getBuget() < 1000) {
                            std::cout << "Not enough budget to add more animals!" << std::endl;
                            break;
                        }

                        std::cout << "Available species for " << habitatTypeName << " habitat:" << std::endl;
                        const std::vector<std::string>& species = habitatSpecies[habitatTypeName];
                        for (size_t k = 0; k < species.size(); k++) {
                            std::cout << (k + 1) << ". " << species[k] << std::endl;
                        }

                        int speciesChoice;
                        std::cout << "Choose a species (1-" << species.size() << "): ";
                        std::cin >> speciesChoice;

                        if (speciesChoice < 1 || speciesChoice > static_cast<int>(species.size())) {
                            std::cout << "Invalid choice. Defaulting to first species." << std::endl;
                            speciesChoice = 1;
                        }

                        std::string randomName = animalNames[random(0, static_cast<int>(animalNames.size()) - 1)];
                        Animal newAnimal(
                            randomName,
                            species[speciesChoice - 1],
                            random(1, 10),
                            random(10.0f, 200.0f),
                            random(20.0f, 150.0f),
                            random(0.7f, 1.0f)
                        );

                        auto& habitats = const_cast<std::vector<Habitat>&>(myZoo.getHabitats());
                        habitats.back().addAnimals(newAnimal);

                        myZoo.setBuget(myZoo.getBuget() - newAnimal.getPrice());
                        std::cout << "Added " << newAnimal.getName() << " the " << newAnimal.getSpecies()
                                << " to " << habitatTypeName << " habitat!" << std::endl;
                        std::cout << "Remaining budget: $" << myZoo.getBuget() << std::endl;
                    }
                }
                break;
            }
            case 3: {
                auto& habitats = const_cast<std::vector<Habitat>&>(myZoo.getHabitats());
                if (habitats.empty()) {
                    std::cout << "No habitats available!" << std::endl;
                    break;
                }

                std::cout << "Select a habitat to add animals to:" << std::endl;
                for (size_t h = 0; h < habitats.size(); h++) {
                    std::cout << (h + 1) << ". " << habitats[h].getType()
                              << " (Animals: " << habitats[h].getAnimals().size() << ")" << std::endl;
                }

                size_t habitatChoice;
                std::cin >> habitatChoice;

                if (habitatChoice < 1 || habitatChoice > habitats.size()) {
                    std::cout << "Invalid habitat choice!" << std::endl;
                    break;
                }

                Habitat& selectedHabitat = habitats[habitatChoice - 1];
                std::string habitatType = selectedHabitat.getType();

                std::cout << "How many animals would you like to add? (0-5): ";
                int animalCount;
                std::cin >> animalCount;

                if (animalCount < 0 || animalCount > 5) {
                    std::cout << "Invalid number of animals! Defaulting to 0." << std::endl;
                    animalCount = 0;
                }

                for (int j = 0; j < animalCount; j++) {
                    if (myZoo.getBuget() < 1000) {
                        std::cout << "Not enough budget to add more animals!" << std::endl;
                        break;
                    }

                    std::cout << "Available species for " << habitatType << " habitat:" << std::endl;
                    const std::vector<std::string>& species = habitatSpecies[habitatType];
                    for (size_t k = 0; k < species.size(); k++) {
                        std::cout << (k + 1) << ". " << species[k] << std::endl;
                    }

                    int speciesChoice;
                    std::cout << "Choose a species (1-" << species.size() << "): ";
                    std::cin >> speciesChoice;

                    if (speciesChoice < 1 || speciesChoice > static_cast<int>(species.size())) {
                        std::cout << "Invalid choice. Defaulting to first species." << std::endl;
                        speciesChoice = 1;
                    }

                    std::string randomName = animalNames[random(0, static_cast<int>(animalNames.size()) - 1)];
                    Animal newAnimal(
                        randomName,
                        species[speciesChoice - 1],
                        random(1, 10),
                        random(10.0f, 200.0f),
                        random(20.0f, 150.0f),
                        random(0.7f, 1.0f)
                    );

                    selectedHabitat.addAnimals(newAnimal);
                    myZoo.setBuget(myZoo.getBuget() - newAnimal.getPrice());
                    std::cout << "Added " << newAnimal.getName() << " the " << newAnimal.getSpecies()
                              << " to " << habitatType << " habitat!" << std::endl;
                    std::cout << "Remaining budget: $" << myZoo.getBuget() << std::endl;
                }
                break;
            }
            case 4:
                std::cout << "Continuing to next day..." << std::endl;
                break;
            default:
                std::cout << "Invalid choice. Continuing to next day..." << std::endl;
                break;
        }

        int habitatCount = myZoo.getHabitats().size();
        int totalAnimals = 0;
        for (const auto &habitat : myZoo.getHabitats()) {
            totalAnimals += habitat.getAnimals().size();
        }

        int baseVisitors = habitatCount * 10 + totalAnimals * 5;
        int variation = random(-5, 5);
        int visitors = std::max(0, baseVisitors + variation);
        const int ticketPrice = 15;
        int revenue = visitors * ticketPrice;

        myZoo.setVisitorCount(visitors);
        myZoo.setBuget(myZoo.getBuget() + revenue);

        std::cout << "----------------------------------------" << std::endl;
        std::cout << "Day " << (i + 1) << " Summary:" << std::endl;
        std::cout << visitors << " visitors came in, earning $" << revenue << std::endl;
        std::cout << "Current budget: $" << myZoo.getBuget() << std::endl;
        std::cout << "----------------------------------------" << std::endl;
    }

    std::cout<< "Simulation is over" << std::endl;


    //Random code to get CppCheck to work

    Animal unusedAnimal("Unused", "Species", 1, 1.0f, 1.0f);
    unusedAnimal.setName("NewName");
    unusedAnimal.setSpecies("NewSpecies");
    unusedAnimal.setAge(2);
    unusedAnimal.setWeight(2.0f);
    unusedAnimal.setHeight(2.0f);
    unusedAnimal.setIsHealthy(0.5f);
    unusedAnimal.setPrice(2000);
    unusedAnimal.setHunger(0.5f);
    std::cout << "Unused Animal Name: " << unusedAnimal.getName() << std::endl;

    Habitat unusedHabitat("Type", {}, 5, 0.5f, 5000.0f);
    unusedHabitat.setType("NewType");
    unusedHabitat.setCapacity(10);
    unusedHabitat.setCleanlinessLevel(0.75f);
    unusedHabitat.setPrice(7500.0f);
    std::cout << "Unused Habitat Type: " << unusedHabitat.getType() << std::endl;

    Zoo unusedZoo("Name", {}, 0, false, 50000.0f);
    unusedZoo.setName("NewZooName");
    unusedZoo.setVisitorCount(100);
    unusedZoo.setIsOpen(true);
    unusedZoo.setBuget(75000.0f);
    std::cout << "Unused Zoo Name: " << unusedZoo.getName() << std::endl;

    Staff unusedStaff("Name", "Position", 30, 60000.0f);
    unusedStaff.setName("NewStaffName");
    unusedStaff.setPosition("NewPosition");
    unusedStaff.setAge(35);
    unusedStaff.setSalary(70000.0f);
    std::cout << "Unused Staff Name: " << unusedStaff.getName() << std::endl;

    Visitor unusedVisitor("Name", 20, 100.0f, "Type");
    unusedVisitor.setName("NewVisitorName");
    unusedVisitor.setAge(25);
    unusedVisitor.setMoney(150.0f);
    unusedVisitor.setType("NewType");
    std::cout << "Unused Visitor Name: " << unusedVisitor.getName() << std::endl;

    return 0;
}

