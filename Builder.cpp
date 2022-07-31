/**
 * It only makes sense to use the Builder pattern when your products
 * are quite complex and require extensive configuration.
 *
 * Unlike other generating patterns, different specific builders
 * Can produce unrelated products. In other words, the results of different
 * builders may not always follow the same interface.
 */

class Product1{
    public:
    std::vector<std::string> parts_;
    void ListParts()const{
        std::cout << "Product parts: ";
        for (size_t i=0;i<parts_.size();i++){
            if(parts_[i]== parts_.back()){
                std::cout << parts_[i];
            }else{
                std::cout << parts_[i] << ", ";
            }
        }
        std::cout << "\n\n"; 
    }
};


/**
 * The Builder interface declares creating methods for different parts of objects
 * Products.
 */
class Builder{
    public:
    virtual ~Builder(){}
    virtual void ProducePartA() const =0;
    virtual void ProducePartB() const =0;
    virtual void ProducePartC() const =0;
};
/**
 * Concrete Builder classes follow the Builder interface and provide
 * Specific implementations of construction steps. Your program may have several
 * variations of Builders, implemented in different ways.
 */
class ConcreteBuilder1 : public Builder{
    private:

    Product1* product;

    /**
     * A new builder instance must contain an empty product object,
     * which is used in further builds.
     */
    public:

    ConcreteBuilder1(){
        this->Reset();
    }

    ~ConcreteBuilder1(){
        delete product;
    }

    void Reset(){
        this->product= new Product1();
    }
	
    /**
     * All production stages work with the same product instance.
     */
    void ProducePartA()const override{
        this->product->parts_.push_back("PartA1");
    }

    void ProducePartB()const override{
        this->product->parts_.push_back("PartB1");
    }

    void ProducePartC()const override{
        this->product->parts_.push_back("PartC1");
    }

    /**
     * Specific Builders must provide their own methods of
     * of obtaining results. This is because different types of builders
     * Can create completely different products with different interfaces.
     * Therefore, such methods cannot be declared in the base interface
     * Builder (at least in a statically typed
     * programming language). Note that PHP is a dynamically
     * typed language, and this method can be in the base interface.
     * However, we will not declare it here for clarity.
     *
     * As a rule, after returning the final result to the client, the instance
     * builder should be ready to start producing the next product.
     * Therefore, it is common practice to call the reset method at the end of the body
     * getProduct method. However, this behavior is not mandatory; you
     * can make your builders wait for an explicit reset request from the
     * client before getting rid of the previous result.
     */

    /**
     * Please be careful here with the memory ownership. Once you call
     * GetProduct the user of this function is responsable to release this
     * memory. Here could be a better option to use smart pointers to avoid
     * memory leaks
     */


Translated with www.DeepL.com/Translator (free version)
    Product1* GetProduct() {
        Product1* result= this->product;
        this->Reset();
        return result;
    }
};

/**
 * The director is only responsible for performing the construction steps in a certain
 * sequence. This is useful when producing products in a certain
 * order or a special configuration. Strictly speaking, the Director class is optional,
 *as the client can directly manage the builders.
 */
class Director{
    /**
     * @var Builder
     */
    private:
    Builder* builder;
    /**
     * The director works with any instance of the builder that is passed to him
     * by the client code. Thus, the client code can change the final
     * type of the newly built product.
     */

    public:

    void set_builder(Builder* builder){
        this->builder=builder;
    }

    /**
     * The director can build several variations of the product using the same
     * construction steps.
     */

    void BuildMinimalViableProduct(){
        this->builder->ProducePartA();
    }
    
    void BuildFullFeaturedProduct(){
        this->builder->ProducePartA();
        this->builder->ProducePartB();
        this->builder->ProducePartC();
    }
};

/**
 * Client code creates a builder object, passes it to the director, and then
 * initiates the building process. The final result is retrieved from the object-
 * builder object.
 */
/**
 * I used raw pointers for simplicity however you may prefer to use smart
 * pointers here
 */
void ClientCode(Director& director)
{
    ConcreteBuilder1* builder = new ConcreteBuilder1();
    director.set_builder(builder);
    std::cout << "Standard basic product:\n"; 
    director.BuildMinimalViableProduct();
    
    Product1* p= builder->GetProduct();
    p->ListParts();
    delete p;

    std::cout << "Standard full featured product:\n"; 
    director.BuildFullFeaturedProduct();

    p= builder->GetProduct();
    p->ListParts();
    delete p;

    // Remember that the Builder pattern can be used without the Director class.
    std::cout << "Custom product:\n";
    builder->ProducePartA();
    builder->ProducePartC();
    p=builder->GetProduct();
    p->ListParts();
    delete p;

    delete builder;
}

int main(){
    Director* director= new Director();
    ClientCode(*director);
    delete director;
    return 0;    
}