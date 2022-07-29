/**
 * The Product interface declares the operations that all
 * specific products.
 */

class Product {
 public:
  virtual ~Product() {}
  virtual std::string Operation() const = 0;
};

/**
 * Specific Products provide different implementations of the Product interface.
 */
class ConcreteProduct1 : public Product {
 public:
  std::string Operation() const override {
    return "{Result of the ConcreteProduct1}";
  }
};
class ConcreteProduct2 : public Product {
 public:
  std::string Operation() const override {
    return "{Result of the ConcreteProduct2}";
  }
};

/**
 * The Creator class declares a factory method that should return an object
 * Product class. Creator subclasses usually provide an implementation of this
 * method.
 */

class Creator {
  /**
   * Note that the Creator can also provide an implementation of
   * factory default method.
   */
 public:
  virtual ~Creator(){};
  virtual Product* FactoryMethod() const = 0;
  /**
   * Also note that, despite the name, the Creator's primary responsibility
   * is not to create products. It usually contains some basic
   * business logic, which is based on Product objects that are returned
   * factory method. Subclasses can indirectly modify this business logic,
   * overriding the factory method and returning a different type of product from it.
   */

  std::string SomeOperation() const {
    // Call the factory method to get the product object.
    Product* product = this->FactoryMethod();
    // Next, work with this product.
    std::string result = "Creator: The same creator's code has just worked with " + product->Operation();
    delete product;
    return result;
  }
};

/**
 * Specific Creators override the factory method in order to change
 * The type of the resulting product.
 */
class ConcreteCreator1 : public Creator {
  /**
   * Note that the method signature still uses the type
   * abstract product, although the method actually returns a specific
   * product. In this way, the Creator can remain independent of the
   * specific product classes.
   */
 public:
  Product* FactoryMethod() const override {
    return new ConcreteProduct1();
  }
};

class ConcreteCreator2 : public Creator {
 public:
  Product* FactoryMethod() const override {
    return new ConcreteProduct2();
  }
};

/**
 * Client code works with an instance of a particular creator, albeit through its
 * base interface. As long as the client continues to work with the creator through the base
 * interface, you can pass it any subclass of the creator.
 */
void ClientCode(const Creator& creator) {
  // ...
  std::cout << "Client: I'm not aware of the creator's class, but it still works.\n"
            << creator.SomeOperation() << std::endl;
  // ...
}

/**
 * The application selects the creator type depending on the configuration or environment.
 */

int main() {
  std::cout << "App: Launched with the ConcreteCreator1.\n";
  
  Creator* creator = new ConcreteCreator1();
  ClientCode(*creator);
  
  std::cout << std::endl;
  std::cout << "App: Launched with the ConcreteCreator2.\n";
  
  Creator* creator2 = new ConcreteCreator2();
  ClientCode(*creator2);

  delete creator;
  delete creator2;
  
  return 0;
}