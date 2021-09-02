// CLASS for Map Iterator and Const Map Iterator 
// Tag utilisé = bidirectional
// Bidirectional iterators are iterators that can be used to access the sequence of elements in a range in both directions (towards the end and towards the beginning).

#ifndef ITERATOR_MAP_HPP

#define ITERATOR_MAP_HPP

#include <iterator>
#include <memory> //std::allocator
#include "iterator_traits.hpp"
#include "rbt.hpp"

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
            typedef rbt_node<value_type> rbt_node;

            // ******** Attribute ***************
            rbt_node* ptr;
            
            // ********** MEMBER FUNCTIONS ********** 

            //---> Constructeurs, Destructeur et operateur=
           
            iterator_map() : ptr(NULL) { return;}

            iterator_map(rbt_node* data) : ptr(data) { return; }
            
            iterator_map(const iterator_map& src) : ptr(src.ptr)  { return; }

            iterator_map& operator=(const iterator_map & src)
            {
                if (this != &src)
                    this->ptr = src.ptr;
                return *this;
            }

            virtual ~iterator_map() { return; }
            
            //---> operators

            //____________ Arithmetic operators ('classic')

            // a verifier à l'exec pbm memoire?
            iterator_map& operator++() // find next value
            {
                rbt_node* current = ptr;
                rbt_node* res;
                if (current->right) // si j'ai un fils droit, je cherche la valeur min dans cette branche
                    res = current->right.findMinChild();
                else
                {
                    rbt_node* current_parent = curent->parent;
                    while (current_parent && current == current_parent->right) // tant que je suis un fils droit
                    {
                        current = current_parent;
                        current_parent = current_parent->parent;
                    }
                    res = current_parent;
                }
                this->ptr = res;
                return *this;
            }           

            iterator_map operator++(int)
            {
                iterator_map tmp = *this;
                ++(*this);
                return tmp;
            }

            // a verifier à l'exec pbm memoire?
            iterator_map& operator--() // find previous value
            {
                rbt_node* current = ptr;
                rbt_node* res;
                if (current->left) // si j'ai un fils gauche, je cherche la valeur max dans cette branche
                    res = current->left.findMaxChild();
                else
                {
                    rbt_node* current_parent = curent->parent;
                    while (current_parent && current == current_parent->left) // tant que je suis un fils gauche
                    {
                        current = current_parent;
                        current_parent = current_parent->parent;
                    }
                    res = current_parent;
                }
                this->ptr = res;
                return *this;
            }

            iterator_map operator--(int)
            {
                iterator_map tmp = *this;
                --(*this);
                return tmp;
            }
       
            reference operator*() const
            {
                return this->ptr->content;
            }

            pointer operator->() const 
            {
                return &(this->ptr->content);
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
            typedef rbt_node<value_type> rbt_node;

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
                rbt_node* current = ptr;
                rbt_node* res;
                if (current->right) // si j'ai un fils droit, je cherche la valeur min dans cette branche
                    res = current->right.findMinChild();
                else
                {
                    rbt_node* current_parent = curent->parent;
                    while (current_parent && current == current_parent->right) // tant que je suis un fils droit
                    {
                        current = current_parent;
                        current_parent = current_parent->parent;
                    }
                    res = current_parent;
                }
                this->ptr = res;
                return *this;
            }           

            iterator_map_const operator++(int)
            {
                iterator_map_const tmp = *this;
                ++(*this);
                return tmp;
            }

            iterator_map_const& operator--()
            {
                rbt_node* current = ptr;
                rbt_node* res;
                if (current->left) // si j'ai un fils gauche, je cherche la valeur max dans cette branche
                    res = current->left.findMaxChild();
                else
                {
                    rbt_node* current_parent = curent->parent;
                    while (current_parent && current == current_parent->left) // tant que je suis un fils gauche
                    {
                        current = current_parent;
                        current_parent = current_parent->parent;
                    }
                    res = current_parent;
                }
                this->ptr = res;
                return *this;
            }

            iterator_map_const operator--(int)
            {
                iterator_map_const tmp = *this;
                --(*this);
                return tmp;
            }
       
            reference operator*() const
            {
                return this->ptr->content;
            }

            pointer operator->() const 
            {
                return &(this->ptr->content);
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