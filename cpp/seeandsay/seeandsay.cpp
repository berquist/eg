// Adapted from https://davekilian.com/cpp-type-erasure.html

#include <iostream>

class Animal {
public:
    virtual const char * see() const = 0;
    virtual const char * say() const = 0;
};

class Cow : public Animal {
public:
    const char * see() const { return "cow"; }
    const char * say() const { return "moo"; }
};

class Pig : public Animal {
public:
    const char * see() const { return "pig"; }
    const char * say() const { return "oink"; }
};

class Dog : public Animal {
public:
    const char * see() const { return "dog"; }
    const char * say() const { return "woof"; }
};

void seeAndSay(Animal *animal) {
    std::cout << "The " << animal->see() << " says '" << animal->say() << "!'" << std::endl;
}

// void pullTheString() {
//     Animal *animals[] = { new Cow, new Pig, new Dog };
//     const size_t len = sizeof(animals) / sizeof(Animal*);
//     const size_t index = rand() % len;
//     seeAndSay(animals[index]);
// }

int main() {
    Cow cow;
    Pig pig;
    Dog dog;
    seeAndSay(&cow);
    seeAndSay(&pig);
    seeAndSay(&dog);
    return 0;
}
