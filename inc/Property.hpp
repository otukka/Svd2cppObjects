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
        ~Property(){};

        // copy assignment
        T* operator=(const T& f)
        {
            // std::cout << "copy assignment operator" << std::endl;
            value = f;
            return &value;
        }

        // move assignment
        T* operator=(const T&& f)
        {
            // std::cout << "move assignment operator" << std::endl;
            value = std::move(f);
            return &value;
        }

        // function call operator
        T* operator()()
        {
            // std::cout << "const function call operator" << std::endl;
            return &value;
        }

        // function call operator
        T operator()() const
        {
            // std::cout << "function call operator" << std::endl;
            return value;
        }

        // user defined conversion to  T
        operator T() const
        {
            // std::cout << "user defined conversion" << std::endl;
            return value;
        }

        // user defined conversion to  T*
        explicit operator T*()
        {
            // std::cout << "explicit user defined conversion to pointer" << std::endl;
            return &value;
        }

        // pointer access operator
        T* operator->()
        {
            // std::cout << "pointer access operator" << std::endl;
            return &value;
        }
    };

}  // namespace Svd2cppObjects

#endif  // _PROPERTY_INCLUDE_HPP_
