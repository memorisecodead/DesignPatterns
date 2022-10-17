#include <iostream>

/**
 * The implementation sets the interface for all implementation classes. It must not.
 * correspond to the Abstraction interface. In practice, both interfaces can be
 * quite different. Typically, the Implement interface provides only
 * primitive operations, while the Abstraction defines higher-level operations
 * higher-level operations based on those primitives.
 */

class Implementation {
public:
    virtual ~Implementation() {}
    virtual std::string OperationImplementation() const = 0;
};

/**
 * Each Concrete Implementation corresponds to a specific platform and implements
 * Implementation interface using that platform's API.
 */
class ConcreteImplementationA : public Implementation {
public:
    std::string OperationImplementation() const override {
        return "ConcreteImplementationA: Here's the result on the platform A.\n";
    }
};
class ConcreteImplementationB : public Implementation {
public:
    std::string OperationImplementation() const override {
        return "ConcreteImplementationB: Here's the result on the platform B.\n";
    }
};

/**
 * The abstraction establishes an interface to the "controlling" part of the two hierarchies
 * classes. It contains a reference to an object from the Implementation hierarchy and delegates
 * all the real work to it.
 */

class Abstraction {
    /**
     * @var Implementation
     */
protected:
    Implementation* implementation_;

public:
    Abstraction(Implementation* implementation) : implementation_(implementation) {
    }

    virtual ~Abstraction() {
    }

    virtual std::string Operation() const {
        return "Abstraction: Base operation with:\n" +
            this->implementation_->OperationImplementation();
    }
};
/**
 * You can extend the Abstraction without changing the Implementation classes.
 */
class ExtendedAbstraction : public Abstraction {
public:
    ExtendedAbstraction(Implementation* implementation) : Abstraction(implementation) {
    }
    std::string Operation() const override {
        return "ExtendedAbstraction: Extended operation with:\n" +
            this->implementation_->OperationImplementation();
    }
};

/**
 * With the exception of the initialization phase, when an Abstraction object binds to a
 * certain Realization object, the client code should depend only on the
 * Abstraction class. Thus, client code can support any
 * combination of Abstraction and Implementation.
 */
void ClientCode(const Abstraction& abstraction) {
    // ...
    std::cout << abstraction.Operation();
    // ...
}
/**
 * Client code must work with any pre-configured
 * combination of abstraction and implementation.
 */

int main() {
    Implementation* implementation = new ConcreteImplementationA;
    Abstraction* abstraction = new Abstraction(implementation);
    ClientCode(*abstraction);
    std::cout << std::endl;
    delete implementation;
    delete abstraction;

    implementation = new ConcreteImplementationB;
    abstraction = new ExtendedAbstraction(implementation);
    ClientCode(*abstraction);

    delete implementation;
    delete abstraction;

    return 0;
}