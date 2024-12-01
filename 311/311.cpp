// 311.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <memory>
#include <string>

class Toy {
public:
    Toy(const std::string& name)
        : name_(name) {}

    std::string getName() {
        return name_;
    }

    ~Toy() {
        std::cout << "Toy " << name_ << " was dropped." << std::endl;
    }

private:
    std::string name_;
};

class Dog {
public:
    Dog(const std::string& name)
        : name_(name), toy_(nullptr) {}

    void getToy(std::shared_ptr<Toy> toy) {
        if (toy_ == toy) {
            std::cout << name_ << ": I already have this toy." << std::endl;
            return;
        }

        if (toy.use_count() > 1) {
            std::cout << name_ << ": Another dog is playing with this toy." << std::endl;
            return;
        }

        toy_ = toy;
        std::cout << name_ << ": I've picked up the toy: " << toy_->getName() << "!" << std::endl;
    }

    void dropToy() {
        if (toy_ == nullptr) {
            std::cout << name_ << ": Nothing to drop." << std::endl;
            return;
        }

        std::cout << name_ << ": Dropping the toy: " << toy_->getName() << "." << std::endl;
        toy_.reset();
    }

private:
    std::string name_;
    std::shared_ptr<Toy> toy_;
};

int main() {
    auto ball = std::make_shared<Toy>("Ball");
    auto frisbee = std::make_shared<Toy>("Frisbee");

    Dog dog1("Rex");
    Dog dog2("Buddy");

    dog1.getToy(ball);
    dog2.getToy(ball); 
    dog1.dropToy(); 

    dog2.getToy(ball);
    dog1.getToy(frisbee); 
    dog1.dropToy(); 

    return 0;
}