/**
 * The subsystem can accept requests either from the facade or from the client directly.
 * In either case, for the Subsystem, the Facade is another client and is not
 * part of the Subsystem.
 */
class Subsystem1 {
 public:
  std::string Operation1() const {
    return "Subsystem1: Ready!\n";
  }
  // ...
  std::string OperationN() const {
    return "Subsystem1: Go!\n";
  }
};
/**
 * Some facades can work with different subsystems at the same time.
 */
class Subsystem2 {
 public:
  std::string Operation1() const {
    return "Subsystem2: Get ready!\n";
  }
  // ...
  std::string OperationZ() const {
    return "Subsystem2: Fire!\n";
  }
};

/**
 * The Facade class provides a simple interface to the complex logic of one or
 * multiple subsystems. Facade delegates client requests to the appropriate
 * objects within a subsystem. Facade is also responsible for managing their lifecycle
 * cycle. All of this protects the client from unwanted subsystem complexity.
 */
class Facade {
 protected:
  Subsystem1 *subsystem1_;
  Subsystem2 *subsystem2_;
  /**
   * Depending on the needs of your application, you can provide
   * Facade with existing subsystem objects or have Facade create them
   * yourself.
   */
 public:
  /**
   * In this case we will delegate the memory ownership to Facade Class
   */
  Facade(
      Subsystem1 *subsystem1 = nullptr,
      Subsystem2 *subsystem2 = nullptr) {
    this->subsystem1_ = subsystem1 ?: new Subsystem1;
    this->subsystem2_ = subsystem2 ?: new Subsystem2;
  }
  ~Facade() {
    delete subsystem1_;
    delete subsystem2_;
  }
  /**
   * Facade methods are convenient for quick access to complex functionality
   * subsystems. However, customers only get a fraction of the subsystem's capabilities.
   */
  std::string Operation() {
    std::string result = "Facade initializes subsystems:\n";
    result += this->subsystem1_->Operation1();
    result += this->subsystem2_->Operation1();
    result += "Facade orders subsystems to perform the action:\n";
    result += this->subsystem1_->OperationN();
    result += this->subsystem2_->OperationZ();
    return result;
  }
};

/**
 * Client code works with complex subsystems through a simple interface,
 * provided by Facade. When Facade manages the subsystem lifecycle,
 * the client may not even be aware of the subsystem's existence. This approach allows you to
 * keep the complexity under control.
 */
void ClientCode(Facade *facade) {
  // ...
  std::cout << facade->Operation();
  // ...
}
/**
 * Some subsystem objects may already be created in the client code. In this case
 * In this case it might be reasonable to initialize the Facade with these
 * objects instead of allowing Facade to create new instances.
 */

int main() {
  Subsystem1 *subsystem1 = new Subsystem1;
  Subsystem2 *subsystem2 = new Subsystem2;
  Facade *facade = new Facade(subsystem1, subsystem2);
  ClientCode(facade);

  delete facade;

  return 0;
}