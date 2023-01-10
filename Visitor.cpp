/**
 * The Visitor interface declares a set of visit methods corresponding to
 * component classes. The visit method signature allows the visitor to
 * identify the specific component class it's dealing with.
 */
class ConcreteComponentA;
class ConcreteComponentB;

class Visitor {
 public:
  virtual void VisitConcreteComponentA(const ConcreteComponentA *element) const = 0;
  virtual void VisitConcreteComponentB(const ConcreteComponentB *element) const = 0;
};

/**
 * The Component interface declares an accept method, which as an argument
 * can receive any object that implements the visitor interface.
 */

class Component
{
 public:
  virtual ~Component() {}
  virtual void Accept(Visitor *visitor) const = 0;
};

/**
 * Each Concrete Component must implement the accept method in such a way,
 * so that it calls the visitor's method corresponding to the class of the component.
 */
class ConcreteComponentA : public Component 
{
  /**
   * Note that we are calling visitConcreteComponentA, which corresponds to
   * the name of the current class. In this way, we let the visitor know
   * which component class he is working with.
   */
 public:
  void Accept(Visitor *visitor) const override 
  {
    visitor->VisitConcreteComponentA(this);
  }
  /**
   * Specific Components can have special methods not declared in their
   * base class or interface. The visitor can still use these
   * methods because they are aware of the component's specific class.
   */
  std::string ExclusiveMethodOfConcreteComponentA() const 
  {
    return "A";
  }
};

class ConcreteComponentB : public Component 
{
  /**
   * Same here: visitConcreteComponentB => ConcreteComponentB
   */
 public:
  void Accept(Visitor *visitor) const override 
  {
    visitor->VisitConcreteComponentB(this);
  }
  
  std::string SpecialMethodOfConcreteComponentB() const
  {
    return "B";
  }
};

/**
 * Specific Visitors implement multiple versions of the same algorithm,
 * which can work with all classes of specific components.
 *
 * You'll get the most out of the Visitor pattern when you use it with
 * A complex object structure, such as a Composer tree. In this case.
 * it would be useful to store some intermediate state of the algorithm when
 * execution of Visitor methods over various objects in the structure.
 */
class ConcreteVisitor1 : public Visitor
{
 public:
  void VisitConcreteComponentA(const ConcreteComponentA *element) const override 
  {
    std::cout << element->ExclusiveMethodOfConcreteComponentA() << " + ConcreteVisitor1\n";
  }

  void VisitConcreteComponentB(const ConcreteComponentB *element) const override 
  {
    std::cout << element->SpecialMethodOfConcreteComponentB() << " + ConcreteVisitor1\n";
  }
};

class ConcreteVisitor2 : public Visitor
{
 public:
  void VisitConcreteComponentA(const ConcreteComponentA *element) const override
  {
    std::cout << element->ExclusiveMethodOfConcreteComponentA() << " + ConcreteVisitor2\n";
  }
  void VisitConcreteComponentB(const ConcreteComponentB *element) const override 
  {
    std::cout << element->SpecialMethodOfConcreteComponentB() << " + ConcreteVisitor2\n";
  }
};

/**
 * The client code can perform visitor operations on any set of
 * elements without figuring out their specific classes. An accept operation directs
 * call to the corresponding operation in the visitor's object.
 */
void ClientCode(std::array<const Component *, 2> components, Visitor *visitor)
{
  // ...
  for (const Component *comp : components)
  {
    comp->Accept(visitor);
  }
  // ...
}

int main() 
{
  std::array<const Component *, 2> components = {new ConcreteComponentA, new ConcreteComponentB};
  std::cout << "The client code works with all visitors via the base Visitor interface:\n";
  ConcreteVisitor1 *visitor1 = new ConcreteVisitor1;
  ClientCode(components, visitor1);
  std::cout << "\n";
  std::cout << "It allows the same client code to work with different types of visitors:\n";
  ConcreteVisitor2 *visitor2 = new ConcreteVisitor2;
  ClientCode(components, visitor2);

  for (const Component *comp : components)
  {
    delete comp;
  }
  
  delete visitor1;
  delete visitor2;

  return 0;
}
