#ifndef _PROPERTY_INCLUDE_HPP_
#define _PROPERTY_INCLUDE_HPP_

namespace Svd2cppObjects
{

    template<typename T>
    class Property
    {
    protected:
        T value;

    public:
        Property(){};
        explicit Property(T t) : value{t} {};
        ~Property(){};

        // copy assignment
        T* operator=(const T& f)
        {
#if defined(DEV_DEBUG)
            std::cout << "copy assignment operator" << std::endl;
#endif
            value = f;
            return &value;
        }

        // move assignment
        T* operator=(const T&& f)
        {
#if defined(DEV_DEBUG)
            std::cout << "move assignment operator" << std::endl;
#endif
            value = std::move(f);
            return &value;
        }

        // function call operator
        T* operator()()
        {
#if defined(DEV_DEBUG)
            std::cout << "const function call operator" << std::endl;
#endif
            return &value;
        }

        // function call operator
        T operator()() const
        {
#if defined(DEV_DEBUG)
            std::cout << "function call operator" << std::endl;
#endif
            return value;
        }

        // user defined conversion to  T
        operator T() const
        {
#if defined(DEV_DEBUG)
            std::cout << "user defined conversion" << std::endl;
#endif
            return value;
        }

        // user defined conversion to  T*
        explicit operator T*()
        {
#if defined(DEV_DEBUG)
            std::cout << "explicit user defined conversion to pointer" << std::endl;
#endif
            return &value;
        }

        // pointer access operator
        T* operator->()
        {
#if defined(DEV_DEBUG)
            std::cout << "pointer access operator" << std::endl;
#endif
            return &value;
        }
    };

}  // namespace Svd2cppObjects

#endif  // _PROPERTY_INCLUDE_HPP_
