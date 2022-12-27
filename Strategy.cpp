/**
 * The Strategy interface declares operations common to all supported versions
 * of some algorithm.
 *
 * The Context uses this interface to call the algorithm  * defined by Specific Strategies.
 */
class Strategy
{
public:
    virtual ~Strategy() = default;
    virtual std::string doAlgorithm(std::string_view data) const = 0;
};

/**
 * The context defines the interface of interest to the clients.
 */

class Context
{
    /**
     * @var Strategy Context stores a reference to one of the 	     * Strategy objects.
     * Context does not know a specific Strategy class. It      * should work with
     * all strategies through the Strategy interface.
     */
private:
    std::unique_ptr<Strategy> strategy_;
    /**
     * Normally, the Context takes a strategy through a      * constructor, and also
     * provides a setter to change it at runtime.
     */
public:
    explicit Context(std::unique_ptr<Strategy> &&strategy = {}) : strategy_(std::move(strategy))
    {
    }
    /**
     * Normally Context allows you to replace a Strategy
     * object at runtime.
     */
    void set_strategy(std::unique_ptr<Strategy> &&strategy)
    {
        strategy_ = std::move(strategy);
    }
    /**
     * Instead of implementing multiple versions of the
     * of the algorithm, the Context delegates some work to      * the Strategy object.
     */
    void doSomeBusinessLogic() const
    {
        if (strategy_) {
            std::cout << "Context: Sorting data using the strategy (not sure how it'll do it)\n";
            std::string result = strategy_->doAlgorithm("aecbd");
            std::cout << result << "\n";
        } else {
            std::cout << "Context: strategy isn't set\n";
        }
    }
};

/**
 * Specific Strategies implements the algorithm, following the  * basic interface
 * Strategies. This interface makes them interchangeable in  * the Context.
 */
class ConcreteStrategyA : public Strategy
{
public:
    std::string doAlgorithm(std::string_view data) const override
    {
        std::string result(data);
        std::sort(std::begin(result), std::end(result));

        return result;
    }
};
class ConcreteStrategyB : public Strategy
{
    std::string doAlgorithm(std::string_view data) const override
    {
        std::string result(data);
        std::sort(std::begin(result), std::end(result), std::greater<>());

        return result;
    }
};
/**
 * Client code selects a specific strategy and passes it into  * context. The client
 * must be aware of the differences between strategies in order to make the right choice.
 */

void clientCode()
{
    Context context(std::make_unique<ConcreteStrategyA>());
    std::cout << "Client: Strategy is set to normal sorting.\n";
    context.doSomeBusinessLogic();
    std::cout << "\n";
    std::cout << "Client: Strategy is set to reverse sorting.\n";
    context.set_strategy(std::make_unique<ConcreteStrategyB>());
    context.doSomeBusinessLogic();
}

int main()
{
    clientCode();
    return 0;
}
