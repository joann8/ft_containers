// CLASS for Vector Iterator and Const Vector Iterator 
// Quelques calculs a revoir peut être

#ifndef ITERATOR_VECTOR_HPP

#define ITERATOR_VECTOR_HPP

#include <iterator>
#include <memory> //std::allocator
#include "iterator_traits.hpp"

namespace ft
{
    template <class T>
    class iterator_vector : public ft::iterator<ft::random_access_iterator_tag, T, std::ptrdiff_t, T*, T&>
    {
        public:
            // ******** MEMBER TYPES ************
            typedef std::ptrdiff_t difference_type;
            typedef T value_type;
            typedef T* pointer;
            typedef T& reference;
            typedef ft::random_access_iterator_tag iterator_category;

            // ******** Attribute ***************
            pointer _ptr_current;
            
            // ********** MEMBER FUNCTIONS ********** 

            //---> Constructeurs, Destructeur et operateur=
           
            iterator_vector() {}

            iterator_vector(T* data) : _ptr_current(data) {}
            
            iterator_vector(const iterator_vector& src)
            {
                *this = src;
            }

            iterator_vector& operator=(const iterator_vector & src)
            {
                if (this != &src)
                    this->_ptr_current = src._ptr_current;
                return *this;
            }

            virtual ~iterator_vector() {}
            
            //---> operators

            //____________ Arithmetic operators ('classic')

            iterator_vector operator+(difference_type n) const
            {
                return iterator_vector(_ptr_current + n);
            }

            iterator_vector& operator+=(difference_type n) //on modifie egalement current
            {
                _ptr_current += n;
                return *this;
            }

            iterator_vector& operator++()
            {
                _ptr_current++;
                return *this;
            }           

            iterator_vector operator++(int)
            {
                iterator_vector tmp = *this;
                ++(*this);
                return tmp;
            }

            iterator_vector operator-(difference_type n) const
            {
                return iterator_vector(_ptr_current - n);
            }

            iterator_vector& operator-=(difference_type n) //on modifie egalement current
            {
                _ptr_current -= n;
                return *this;
            }

            iterator_vector& operator--()
            {
                _ptr_current--;
                return *this;
            }

            iterator_vector operator--(int)
            {
                iterator_vector tmp = *this;
                --(*this);
                return tmp;
            }
       
            reference operator*() const
            {
                return *_ptr_current;
            }

            pointer operator->() const 
            {
                return _ptr_current;
            }
            
            reference operator[](difference_type n) const
            {
                return *(_ptr_current + n); //brunet != 
            }

            ///____________ Relational operators
    
            bool operator==(const iterator_vector& rhs)
            {
                return this->_ptr_current == rhs._ptr_current;
            }
            
            bool operator!=(const iterator_vector& rhs)
            {
                return !(this->_ptr_current == rhs._ptr_current);
            }

            bool operator<(const iterator_vector& rhs)
            {
                return this->_ptr_current < rhs._ptr_current;
            }
           
            bool operator>(const iterator_vector& rhs)
            {
                return rhs._ptr_ccurent < this->_ptr_current;
            }
           
            bool operator<=(const iterator_vector& rhs)
            {
                return !(this->_ptr_ccurent > rhs._ptr_current);
            }

            bool operator>=(const iterator_vector& rhs)
            {
                return !(this->_ptr_ccurent < rhs._ptr_current);
            }
    
            //---> Operator + et - // pourquoi member ?

            friend iterator_vector operator+(difference_type n, iterator_vector const & rhs)
            {
                return iterator_vector(rhs._ptr_current + n);
                //return iterator_vector(rhs._ptr_current + n)
            }
            
            friend difference_type operator-(iterator_vector const & lhs, iterator_vector const & rhs)
            {
                return lhs._ptr_current - rhs._ptr_current;
            }
            
    };


    template <class T>
    class iterator_vector_const : public ft::iterator<ft::random_access_iterator_tag, T, std::ptrdiff_t, T*, T&>
    {
        public:
            // ******** MEMBER TYPES ************
            typedef std::ptrdiff_t difference_type;
            typedef T value_type;
            typedef T* pointer;
            typedef T& reference;
            typedef ft::random_access_iterator_tag iterator_category;

            // ******** Attribute ***************
            pointer _ptr_current;
            
            // ********** MEMBER FUNCTIONS ********** 

            //---> Constructeurs, Destructeur et operateur=
           
            iterator_vector_const() {}

            iterator_vector_const(pointer data) : _ptr_current(data) {}
            
            iterator_vector_const(iterator_vector_const const & src)
            {
                *this = src;
            }
  
            iterator_vector_const(iterator_vector<T> const & src) :  _ptr_current(src._ptr_current) {} // capable de construire a partir d'un it non constant 
            
            iterator_vector_const& operator=(const iterator_vector_const & src)
            {
                if (this != &src)
                    this->_ptr_current = src._ptr_current;
                return *this;
            }

            virtual ~iterator_vector_const() {}
            
            //---> operators

            //____________ Arithmetic operators ('classic')

            iterator_vector_const operator+(difference_type n) const
            {
                return iterator_vector_const(_ptr_current + n);
            }

            iterator_vector_const& operator+=(difference_type n) //on modifie egalement current
            {
                _ptr_current += n;
                return *this;
            }

            iterator_vector_const& operator++()
            {
                _ptr_current++;
                return *this;
            }           

            iterator_vector_const operator++(int)
            {
                iterator_vector_const tmp = *this;
                _ptr_current++;
                return tmp;
            }

            iterator_vector_const operator-(difference_type n) const
            {
                return iterator_vector_const(_ptr_current - n);
            }

            iterator_vector_const& operator-=(difference_type n) //on modifie egalement current
            {
                _ptr_current -= n;
                return *this;
            }

            iterator_vector_const& operator--()
            {
                _ptr_current--;
                return *this;
            }

            iterator_vector_const operator--(int)
            {
                iterator_vector_const tmp = *this;
                _ptr_current--; 
                return tmp;
            }
       
            reference operator*() const
            {
                return *_ptr_current;
            }

            pointer operator->() const 
            {
                return _ptr_current;
            }
            
            reference operator[](difference_type n) const
            {
                return *(_ptr_current + n); //brunet != 
            }

            ///____________ Relational operators
    
            bool operator==(const iterator_vector_const& rhs)
            {
                return this->_ptr_current == rhs._ptr_current;
            }
            
            bool operator!=(const iterator_vector_const& rhs)
            {
                return !(this->_ptr_current == rhs._ptr_current);
            }

            bool operator<(const iterator_vector_const& rhs)
            {
                return this->_ptr_current < rhs._ptr_current;
            }
           
            bool operator>(const iterator_vector_const& rhs)
            {
                return rhs._ptr_current < this->_ptr_current;
            }
           
            bool operator<=(const iterator_vector_const& rhs)
            {
                return !(this->_ptr_current > rhs._ptr_current);
            }

            bool operator>=(const iterator_vector_const& rhs)
            {
                return !(this->_ptr_current < rhs._ptr_current);
            }
            
            //---> Operator + et -  // pourquoi member?

            friend iterator_vector_const operator+(difference_type n, const iterator_vector_const & rhs)
            {
                return iterator_vector_const(rhs._ptr_current + n);
            }

            friend difference_type operator-(const iterator_vector_const & lhs, const iterator_vector_const & rhs)
            {
                return lhs._ptr_current - rhs._ptr_current;
            }
    };
   
 }
#endif