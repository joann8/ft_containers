#ifndef STACK_HPP

#define STACK_HPP

#include "vector.hpp"

namespace ft
{
    template<class T, class Container = vector<T> >
    class stack;

     // --> Relational Operators

    template <class T, class Container>
    bool operator==(const stack<T, Container> & lhs, const stack<T, Container> & rhs)
    {
        return lhs._current == rhs._current;
    }

    template <class T, class Container>
    bool operator!=(const stack<T, Container> & lhs, const stack<T, Container> & rhs)
    {
        return lhs._current != rhs._current;
    }

    template <class T, class Container>
    bool operator<(const stack<T, Container> & lhs, const stack<T, Container> & rhs)
    {
        return lhs._current < rhs._current;
    }

    template <class T, class Container>
    bool operator>(const stack<T, Container> & lhs, const stack<T, Container> & rhs)
    {
        return lhs._current > rhs._current;
    }

    template <class T, class Container>
    bool operator<=(const stack<T, Container> & lhs, const stack<T, Container> & rhs)
    {
        return lhs._current <= rhs._current;
    }

    template <class T, class Container>
    bool operator>=(const stack<T, Container> & lhs, const stack<T, Container> & rhs)
    {
        return lhs._current >= rhs._current;
    }

    template <class T, class Container>
    class stack
    {
        // *********** MEMBERS TYPES **************
        public: 
            typedef T value_type;
            typedef Container container_type;
            typedef std::size_t size_type;
        

        // ********** ATTRIBUTS ********** 

        protected:
            container_type _current;
               
        
        // ********** MEMBER FUNCTIONS ********** 
        
        public:

            //---> Constructeurs, Destructeur et operateur= 

            explicit stack (const container_type& ctnr = container_type()) : _current(ctnr)
            {
                return;
            }

            stack(const stack& src) : _current(src._current)
            {
                return;
            }

            stack& operator=(const stack& src)
            {
                if (this != &src)
                {
                    _current = src._current;
                }
                return *this;
            }

            virtual ~stack() {return; }


            //---> Others

            bool empty() const
            {
                return _current.empty();
            }

            size_type size() const
            {
                return _current.size();
            }

            // Returns a reference to the top element in the stack == last inserted
            value_type& top()
            {
                return _current.back();
            }

            const value_type& top() const
            {
                return _current.back();
            }

            // Inserts a new element at the top of the stack, above its current top element
            void push(const value_type& val)
            {
                _current.push_back(val);
            }

            // Removes the element on top of the stack, effectively reducing its size by one.
            void pop()
            {
                _current.pop_back();
            }

        friend bool operator== <T, Container>(stack const& lhs, stack const& rhs);
		friend bool operator!= <T, Container>(stack const& lhs, stack const& rhs);
		friend bool operator< <T, Container>(stack const& lhs, stack const& rhs);
		friend bool operator<= <T, Container>(stack const& lhs, stack const& rhs);
		friend bool operator> <T, Container>(stack const& lhs, stack const& rhs);
		friend bool operator>= <T, Container>(stack const& lhs, stack const& rhs);
    };

     // ********** NON MEMBER FUNCTIONS OVERLOARDS ********** 

   
       
}

#endif