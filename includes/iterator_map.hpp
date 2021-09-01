// CLASS for Map Iterator and Const Map Iterator 
// Tag utilisé = bidirectional
// Bidirectional iterators are iterators that can be used to access the sequence of elements in a range in both directions (towards the end and towards the beginning).

#ifndef ITERATOR_MAP_HPP

#define ITERATOR_MAP_HPP

#include <iterator>
#include <memory> //std::allocator
#include "iterator_traits.hpp"

namespace ft
{
    template <class T>
    class iterator_map : public ft::iterator<ft::bidirectional_iterator_tag, T, std::ptrdiff_t, T*, T&>
    {
        public:
            // ******** MEMBER TYPES ************
            typedef std::ptrdiff_t difference_type;
            typedef T value_type;
            typedef T* pointer;
            typedef T& reference;
            typedef ft::bidirectional_iterator_tag iterator_category;

            // ******** Attribute ***************
            rbt_node* ptr; // A definir
            
            // ********** MEMBER FUNCTIONS ********** 

            //---> Constructeurs, Destructeur et operateur=
           
            iterator_map() : ptr(NULL) { return;}

            iterator_map(rbt_node* data) : ptr(data) {}
            
            iterator_map(const iterator_map& src) : ptr(src.ptr)
            {
                *this = src;
            }

            iterator_map& operator=(const iterator_map & src)
            {
                if (this != &src)
                    this->ptr = src.ptr;
                return *this;
            }

            virtual ~iterator_map() {}
            
            //---> operators

            //____________ Arithmetic operators ('classic')

            iterator_map& operator++()
            {
                return ; // A FAIRE
            }           

            iterator_map operator++(int)
            {
                return ; // A FAIRE
            }

            iterator_map& operator--()
            {
                return ; // A FAIRE
            }

            iterator_map operator--(int)
            {
                return ; // A FAIRE
            }
       
            reference operator*() const
            {
                return ; // A FAIRE
            }

            pointer operator->() const 
            {
                return ; // A FAIRE
            }

            ///____________ Relational operators
    
            bool operator==(const iterator_map& rhs) const
            {
                return this->ptr == rhs.ptr;
            }
            
            bool operator!=(const iterator_map& rhs) const
            {
                return !(this->ptr == rhs.ptr);
            }          
    };


    template <class T>
    class iterator_map_const : public ft::iterator<ft::bidirectional_iterator_tag, T, std::ptrdiff_t, T*, T&>
    {
        public:
            // ******** MEMBER TYPES ************
            typedef std::ptrdiff_t difference_type;
            typedef T value_type;
            typedef T* pointer;
            typedef T& reference;
            typedef ft::bidirectional_iterator_tag iterator_category;

            // ******** Attribute ***************
            rbt_node* ptr; // A definir
            
            // ********** MEMBER FUNCTIONS ********** 

            //---> Constructeurs, Destructeur et operateur=
           
            iterator_map_const() : ptr(NULL) { return; }

            iterator_map_const(rbt_node* data) : ptr(data) {}
            
            iterator_map_const(iterator_map_const const & src) : ptr(src.ptr)
            {
                *this = src;
            }
  
            iterator_map_const(iterator_map<T> const & src) :  ptr(src.ptr) {} // capable de construire a partir d'un it non constant 
            
            iterator_map_const& operator=(const iterator_map_const & src)
            {
                if (this != &src)
                    this->ptr = src.ptr;
                return *this;
            }

            virtual ~iterator_map_const() {}
            
            //---> operators

            //____________ Arithmetic operators ('classic')

            iterator_map_const& operator++()
            {
                return ; // A FAIRE
            }           

            iterator_map_const operator++(int)
            {
                return ; // A FAIRE
            }

            iterator_map_const& operator--()
            {
                return ; // A FAIRE
            }

            iterator_map_const operator--(int)
            {
                return ; // A FAIRE
            }
       
            reference operator*() const
            {
                return ; // A FAIRE
            }

            pointer operator->() const 
            {
                return ; // A FAIRE
            }

            ///____________ Relational operators
    
            bool operator==(const iterator_map_const& rhs)
            {
                return this->ptr == rhs.ptr;
            }
            
            bool operator!=(const iterator_map_const& rhs)
            {
                return !(this->ptr == rhs.ptr);
            }
    };
 }
#endif