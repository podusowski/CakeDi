## CakeDi

Dependency Injection framework for C++

(old deepp: https://sourceforge.net/projects/deepp/)

## Requrements

* C++11
* RTTI
* exceptions

## Compilation

CakeDi is header only library so you don't have to compile anything.

However, if you like to see the tests, you can use pake:

`./pake.py -a`

## Usage

```cpp
#include <memory>

#include "DependencyInjection/Registry.hpp"
#include "DependencyInjection/Inject.hpp"

class IProvider
{
public:
    virtual bool foo() = 0;
    virtual ~IProvider() {}
};

class ConcreteProvider : public IProvider
{
public:
    bool foo()
    {
        return true;
    }
};

class User
{
public:
    bool doStuff()
    {
        return m_provider->foo();
    }

private:
    Cake::DependencyInjection::Inject<IProvider> m_provider;
};

int main()
{
    Cake::DependencyInjection::Registry registry;
    registry.forInterface<IProvider>().use(std::make_shared<ConcreteProvider>());
}
```

