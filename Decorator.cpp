/**
 * The base interface of the Component defines the behavior that is modified
 * decorators.
 */
class Component {
 public:
  virtual ~Component() {}
  virtual std::string Operation() const = 0;
};
/**
 * Specific Components provide default behavior implementations. There may be
 * There can be several variations of these classes.
 */
class ConcreteComponent : public Component {
 public:
  std::string Operation() const override {
    return "ConcreteComponent";
  }
};

/**
 * The Decorator base class follows the same interface as the other components.
 * The main purpose of this class is to define a wrapper interface for all specific
 * Decorators. The default implementation of the wrapper code may include a field
 * to store the wrapped component and a means of initializing it.
 */
class Decorator : public Component
{
	
  /**
   * @var Component
   */
 protected:
  Component* component_;

 public:
  Decorator(Component* component) : component_(component) {
  }
  /**
   * The decorator delegates all work to the wrapped component.
   */
  std::string Operation() const override {
    return this->component_->Operation();
  }
};

/**
 * Specific Decorators call the wrapped object and change its result
 * in some way.
 */
class ConcreteDecoratorA : public Decorator
{
  /**
   * Decorators can call the parent implementation of an operation, instead of
   * to call the wrapped object directly. This approach simplifies the extension
   * Decorator classes.
   */
 public:
  ConcreteDecoratorA(Component* component) : Decorator(component) {
  }
  std::string Operation() const override {
    return "ConcreteDecoratorA(" + Decorator::Operation() + ")";
  }
};
/**
 * Decorators can perform their behavior before or after calling the wrapped
 * object.
 */
class ConcreteDecoratorB : public Decorator {
 public:
  ConcreteDecoratorB(Component* component) : Decorator(component) {
  }

  std::string Operation() const override {
    return "ConcreteDecoratorB(" + Decorator::Operation() + ")";
  }
};

/**
 * Client code works with all objects using the Component interface.
 * In this way, it remains independent of the specific component classes with which it
 * it works with.
 */
void ClientCode(Component* component) 
{
  // ...
  std::cout << "RESULT: " << component->Operation();
  // ...
}

int main()
{
  /**
   * Thus, the client code can support both simple components...
   */
  Component* simple = new ConcreteComponent;
  std::cout << "Client: I've got a simple component:\n";
  ClientCode(simple);
  std::cout << "\n\n";
  
  /**
   * ...as well as decorated.
   *
   * Note that decorators can wrap not only simple
   * components, but also other decorators.
   */
  Component* decorator1 = new ConcreteDecoratorA(simple);
  Component* decorator2 = new ConcreteDecoratorB(decorator1);
  std::cout << "Client: Now I've got a decorated component:\n";
  ClientCode(decorator2);
  std::cout << "\n";

  delete simple;
  delete decorator1;
  delete decorator2;

  return 0;
}