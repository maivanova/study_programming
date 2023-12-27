#include <iostream>
#include <vector>
#include <string>


using namespace std;

class Animal
{
private:
    string name;
    string type;
public:
    Animal(string name, string type)
    {
        this->name = name;
        this->type = type;
    }
    string getName()
    {
        return name;
    }
    string getType()
    {
        return type;
    }
    void setName(string name)
    {
        this->name = name;
    }
    void setType(string type)
    {
        this->type = type;
    }
    void feed()
    {
        cout << "Animal " << name << " is eating" << endl;
    }
    void call()
    {
        cout << "Animal " << name << " is calling" << endl;
    }
    void stroke()
    {
        cout << "Animal " << name << " is being stroked" << endl;
    }
};

class Cat : public Animal
{
public:
    Cat(string name) : Animal(name, "Cat")
    {
    }
};

class Dog : public Animal
{
public:
    Dog(string name) : Animal(name, "Dog")
    {
    }
};

class Giraffe : public Animal
{
public:
    Giraffe(string name) : Animal(name, "Giraffe")
    {
    }
};

class Zoo
{
private:
    vector<Animal*> animals;
public:
    Zoo()
    {

    }
    ~Zoo()
    {
        for (int i = 0; i < animals.size(); i++)
        {
            delete animals[i];
        }
    }
    void addAnimal(Animal* animal)
    {
        animals.push_back(animal);
    }
    void deleteAnimal(string name)
    {
        for (int i = 0; i < animals.size(); i++)
        {
            if (animals[i]->getName() == name)
            {
                animals.erase(animals.begin() + i);
                break;
            }
        }
    }
    void feedAll()
    {
        for (int i = 0; i < animals.size(); i++)
        {
            animals[i]->feed();
        }
    }
    void callAll()
    {
        for (int i = 0; i < animals.size(); i++)
        {
            animals[i]->call();
        }
    }
    void strokeAll()
    {
        for (int i = 0; i < animals.size(); i++)
        {
            animals[i]->stroke();
        }
    }
};

int main()
{
    Zoo zoo;
    zoo.addAnimal(new Cat("Kitty"));
    zoo.addAnimal(new Dog("Doggy"));
    zoo.addAnimal(new Giraffe("Giraffy"));

    zoo.feedAll();
    zoo.callAll();
    zoo.strokeAll();
    cout << "\n\n";
    zoo.deleteAnimal("Doggy");

    zoo.feedAll();

    return 0;
};
