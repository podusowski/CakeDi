#pragma once

#include <memory>

#include "Detail/NullType.hpp"
#include "Factory.hpp"

namespace Cake
{
namespace DependencyInjection
{

template<typename Interface, typename Implementation, typename... Args> class GenericFactory : public Factory<Interface, Args...>
{
public:
    std::shared_ptr<Interface> create(Args... args)
    {
        return std::make_shared<Implementation>(args...);
    }
};

template<typename Interface, typename Implementation>
class GenericFactory0 : public Factory<Interface>
{
public:
    virtual std::shared_ptr<Interface> create()
    {
        return std::make_shared<Implementation>();
    }
};

template<typename Interface, typename Implementation, typename Arg1>
class GenericFactory1 : public Factory<Interface, Arg1>
{
public:
    virtual std::shared_ptr<Interface> create(Arg1 arg1)
    {
        return std::make_shared<Implementation>(arg1);
    }
};

}
}
