#include <algorithm>
#include <iostream>
#include <list>
#include <string>

/**
 * The Component base class declares common operations for both simple and
 * complex structure objects.
 */
class Component {
  /**
   * @var Component
   */
 protected:
  Component *parent_;
  /**
   * If necessary, the base Component can declare an interface to set
   * and retrieve the component's parent in a tree structure. It can also
   * provide some default implementation for these methods.
   */
 public:
  virtual ~Component() {}
  void SetParent(Component *parent) {
    this->parent_ = parent;
  }
  Component *GetParent() const {
    return this->parent_;
  }
  /**
   * In some cases it is reasonable to define descendant control operations
   * directly in the base class Component. That way, you don't have to
   * provide specific component classes to client code, even during
   * assembly of the object tree. The disadvantage of this approach is that these methods
   * will be empty for leaf-level components.
   */
  virtual void Add(Component *component) {}
  virtual void Remove(Component *component) {}
  /**
   * You can provide a method that allows the client code to understand
   * Whether a component can have nested objects.
   */
  virtual bool IsComposite() const {
    return false;
  }
  /**
   * The base Component can implement some default behavior itself
   * or delegate it to specific classes by declaring the method containing the behavior
   * abstract.
   */
  virtual std::string Operation() const = 0;
};
/**
 * The Sheet class represents finite structure objects. A leaf cannot have
 * nested components.
 *
 * Usually Leaf objects do the actual work, whereas
 * Containers only delegate work to their subcomponents.
 */
class Leaf : public Component {
 public:
  std::string Operation() const override {
    return "Leaf";
  }
};
/**
 * The Container class contains complex components that can have nested
 * components. Usually Container objects delegate the actual work to their
 * children, and then "summarize" the result.
 */
class Composite : public Component {
  /**
   * @var \SplObjectStorage
   */
 protected:
  std::list<Component *> children_;

 public:
  /**
   * A container object can both add components to its list of nested
   * container object can add components to its list of nested * components, as well as remove them, both simple and complex.
   */
  void Add(Component *component) override {
    this->children_.push_back(component);
    component->SetParent(this);
  }
  /**
   * Have in mind that this method removes the pointer to the list but doesn't
   * frees the
   *     memory, you should do it manually or better use smart pointers.
   */
  void Remove(Component *component) override {
    children_.remove(component);
    component->SetParent(nullptr);
  }
  bool IsComposite() const override {
    return true;
  }
  /**
   * The container performs its basic logic in a special way. It goes through
   * recursively through all of its children, collecting and summarizing their results.
   * As the container's descendants pass these calls on to their descendants and so on.
   * further, the whole object tree is bypassed as a result.
   */
  std::string Operation() const override {
    std::string result;
    for (const Component *c : children_) {
      if (c == children_.back()) {
        result += c->Operation();
      } else {
        result += c->Operation() + "+";
      }
    }
    return "Branch(" + result + ")";
  }
};
/**
 * The client code works with all components through a basic interface.
 */
void ClientCode(Component *component) {
  // ...
  std::cout << "RESULT: " << component->Operation();
  // ...
}

/**
 * Because descendant control operations are declared in the base class
 * Component, client code can handle both simple and complex
 * components, regardless of their specific classes.
 */
void ClientCode2(Component *component1, Component *component2) {
  // ...
  if (component1->IsComposite()) {
    component1->Add(component2);
  }
  std::cout << "RESULT: " << component1->Operation();
  // ...
}

/**
 * In this way, the client code can support simple leaf components...
 */

int main() {
  Component *simple = new Leaf;
  std::cout << "Client: I've got a simple component:\n";
  ClientCode(simple);
  std::cout << "\n\n";
  /**
   * ...as well as complex containers.
   */

  Component *tree = new Composite;
  Component *branch1 = new Composite;

  Component *leaf_1 = new Leaf;
  Component *leaf_2 = new Leaf;
  Component *leaf_3 = new Leaf;
  branch1->Add(leaf_1);
  branch1->Add(leaf_2);
  Component *branch2 = new Composite;
  branch2->Add(leaf_3);
  tree->Add(branch1);
  tree->Add(branch2);
  std::cout << "Client: Now I've got a composite tree:\n";
  ClientCode(tree);
  std::cout << "\n\n";

  std::cout << "Client: I don't need to check the components classes even when managing the tree:\n";
  ClientCode2(tree, simple);
  std::cout << "\n";

  delete simple;
  delete tree;
  delete branch1;
  delete branch2;
  delete leaf_1;
  delete leaf_2;
  delete leaf_3;

  return 0;
}