#include <iostream>

/**
 * The Subject interface declares common operations for both the Real Subject and the
 * for the Substitute. As long as the client is working with the Real Subject, using this
 * interface, you will be able to pass the Substitute to him instead of the Real Subject.
 */
class Subject {
 public:
  virtual void Request() const = 0;
};

/**
 * The real Entity contains some basic business logic. As a general rule,
 * Real Entities are capable of doing some useful work, which in addition
 * Also can be very slow or accurate - for example, correcting input
 * data. The Substitute can do these tasks without making any changes to the Real Subject's code.
 * of the Real Entity.
 */
class RealSubject : public Subject {
 public:
  void Request() const override {
    std::cout << "RealSubject: Handling request.\n";
  }
};
/**
 * The interface of the Substitute is identical to that of the Real Subject.
 */
class Proxy : public Subject {
  /**
   * @var RealSubject
   */
 private:
  RealSubject *real_subject_;

  bool CheckAccess() const {
    // Some real checks have to take place here.
    std::cout << "Proxy: Checking access prior to firing a real request.\n";
    return true;
  }
  void LogAccess() const {
    std::cout << "Proxy: Logging the time of request.\n";
  }

  /**
   * The substitute stores a reference to an object of the RealSubject class. The client can
   * either lazily load it or pass it to the Substitute.
   */
 public:
  Proxy(RealSubject *real_subject) : real_subject_(new RealSubject(*real_subject)) {
  }

  ~Proxy() {
    delete real_subject_;
  }
  
  /**
   * The most common uses for the Alternate pattern
   * are lazy loading, caching, access control, logging, etc.
   * etc. The Alternate can perform one of these tasks, and then, depending on the
   * depending on the result, pass the execution to a method of the same name in the linked object
   * of the Real Subject class.
   */
  void Request() const override {
    if (this->CheckAccess()) {
      this->real_subject_->Request();
      this->LogAccess();
    }
  }
};

/**
 * Client code must work with all objects (both real and
 * Substitutes) through the Subject interface to support both real
 * subjects as well as substitutes. In real life, however, clients mostly
 * work with real subjects directly. In this case, in order to more easily
 * implementation of the pattern, you can extend the substitute from the real * subject class
 * subject.
 */
void ClientCode(const Subject &subject) {
  // ...
  subject.Request();
  // ...
}

int main() {
  std::cout << "Client: Executing the client code with a real subject:\n";
  RealSubject *real_subject = new RealSubject;
  ClientCode(*real_subject);
  std::cout << "\n";
  std::cout << "Client: Executing the same client code with a proxy:\n";
  Proxy *proxy = new Proxy(real_subject);
  ClientCode(*proxy);

  delete real_subject;
  delete proxy;
  return 0;
}