#pragma once

#include <memory>

#include "Factory.hpp"

namespace Cake 
{
namespace DependencyInjection
{

template<typename Interface>
class InstanceFactory : public Factory<Interface>
{
public:
    InstanceFactory(std::shared_ptr<Interface> instance) :
        m_instance(instance)
    {
    }

    virtual std::shared_ptr<Interface> create()
    {
        return m_instance;
    }

private:
    std::shared_ptr<Interface> m_instance;
};

}
}
