#include <gtest/gtest.h>

#include <memory>

#include "DependencyInjection/Registry.hpp"
#include "DependencyInjection/Inject.hpp"

using namespace testing;
using namespace Cake::DependencyInjection;

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

TEST(DependencyInjectionTest, TestSimpleInjectBySharedPointer)
{
    Registry r;
    r.forInterface<IProvider>().use(std::make_shared<ConcreteProvider>());

    User user;
    EXPECT_EQ(true, user.doStuff());
}

TEST(DependencyInjectionTest, TestSimpleInjectByType)
{
    Registry r;
    r.forInterface<IProvider>().use<ConcreteProvider>();

    User user;
    EXPECT_EQ(true, user.doStuff());
}

TEST(DependencyInjectionTest, UnknownInteface)
{
    EXPECT_ANY_THROW(User u);
}

TEST(DependencyInjectionTest, ScopedRegistry)
{
    {
        Cake::DependencyInjection::Registry registry;
        registry.forInterface<IProvider>().use(std::make_shared<ConcreteProvider>());
    }

    EXPECT_ANY_THROW(User user);
}

struct ICycleA { virtual ~ICycleA() {} };
struct ICycleB { virtual ~ICycleB() {} };
struct CycleA : public ICycleA { Inject<ICycleB> b; };
struct CycleB : public ICycleB { Inject<ICycleA> a; };

TEST(DependencyInjectionTest, DetectCycle)
{
    Registry r;
    r.forInterface<ICycleA>().use<CycleA>();
    r.forInterface<ICycleB>().use<CycleB>();

    EXPECT_ANY_THROW(CycleA a);
}

