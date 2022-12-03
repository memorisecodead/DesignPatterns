#include <iostream>
#include <string>

/**
 * The Mediator interface provides a method used by components to
 * notify the mediator of various events. The mediator can react to
 * these events and pass the execution on to other components.
 */
class BaseComponent;
class Mediator
 {
 public:
  virtual void Notify(BaseComponent *sender, std::string event) const = 0;
};

/**
 * Basic Component provides basic instance storage functionality
 * mediator within component objects.
 */
class BaseComponent 
{
 protected:
  Mediator *mediator_;

 public:
  BaseComponent(Mediator *mediator = nullptr) : mediator_(mediator)
  {
  }

  void set_mediator(Mediator *mediator) 
  {
    this->mediator_ = mediator;
  }
};

/**
 * Specific Components implement different functionality. They are independent of
 * other components. They also do not depend on any specific classes
 * intermediaries.
 */
class Component1 : public BaseComponent 
{
 public:
  void DoA() 
  {
    std::cout << "Component 1 does A.\n";
    this->mediator_->Notify(this, "A");
  }
  void DoB() 
  {
    std::cout << "Component 1 does B.\n";
    this->mediator_->Notify(this, "B");
  }
};

class Component2 : public BaseComponent 
{
 public:
  void DoC() 
  {
    std::cout << "Component 2 does C.\n";
    this->mediator_->Notify(this, "C");
  }

  void DoD()
  {
    std::cout << "Component 2 does D.\n";
    this->mediator_->Notify(this, "D");
  }
};

/**
 * Specific Mediators implement cooperative behavior by coordinating the individual
 * components.
 */
class ConcreteMediator : public Mediator 
{
 private:
  Component1 *component1_;
  Component2 *component2_;

 public:
  ConcreteMediator(Component1 *c1, Component2 *c2) : component1_(c1), component2_(c2)
  {
    this->component1_->set_mediator(this);
    this->component2_->set_mediator(this);
  }

  void Notify(BaseComponent *sender, std::string event) const override
  {
    if (event == "A") 
    {
      std::cout << "Mediator reacts on A and triggers following operations:\n";
      this->component2_->DoC();
    }
    if (event == "D") 
    {
      std::cout << "Mediator reacts on D and triggers following operations:\n";
      this->component1_->DoB();
      this->component2_->DoC();
    }
  }
};

/**
 * Client code.
 */
void ClientCode()
{
  Component1 *c1 = new Component1;
  Component2 *c2 = new Component2;
  ConcreteMediator *mediator = new ConcreteMediator(c1, c2);
  std::cout << "Client triggers operation A.\n";
  c1->DoA();
  std::cout << "\n";
  std::cout << "Client triggers operation D.\n";
  c2->DoD();

  delete c1;
  delete c2;
  delete mediator;
}

int main() 
{
  ClientCode();
  return 0;
}
