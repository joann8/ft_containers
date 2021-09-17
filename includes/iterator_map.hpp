// CLASS for Map Iterator and Const Map Iterator 
// Tag utilisé = bidirectional
// Bidirectional iterators are iterators that can be used to access the sequence of elements in a range in both directions (towards the end and towards the beginning).

#ifndef ITERATOR_MAP_HPP

#define ITERATOR_MAP_HPP

#include <memory> //std::allocator
#include "rbt.hpp"
#include "iterator"
#include "iterator_traits.hpp"

namespace ft
{
    template <class T>
    class iterator_map_const;

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
            typedef rbt_node<T> rbt_node;

            // ******** Attribute ***************
            rbt_node *ptr;
            
            // ********** MEMBER FUNCTIONS ********** 

            //---> Constructeurs, Destructeur et operateur=
           
            iterator_map() : ptr(NULL) {}

            iterator_map(rbt_node* data) : ptr(data) {}

            iterator_map(const iterator_map& src) : ptr(src.ptr) {}

            iterator_map& operator=(const iterator_map & src)
            {
                if (this != &src)
                    this->ptr = src.ptr;
                return *this;
            }

            virtual ~iterator_map() { return; }
            
            //---> operators

            //____________ Arithmetic operators ('classic')

            iterator_map& operator++() // find next value
            {
                rbt_node* current = ptr;
                rbt_node* res;
                if (current)
                {
                    if (current->right && current->right->is_null == false) // si j'ai un fils droit, je cherche la valeur min dans cette branche
                        res = current->right->getMinChild();
                    else
                    {
                        rbt_node* parent = current->parent;                 
                        while (parent && current == parent->right
                                && parent->is_init == false) // tant que je suis un fils droit
                        {
                            current = parent;
                            parent = parent->parent;
                        }
                        if (parent->is_init == true) //pour resoudre le cas root
                            res = ptr->right;
                        else
                            res = parent;
                    }
                    this->ptr = res;
                }
                return *this;
            }               

            iterator_map operator++(int)
            {
                iterator_map tmp = *this;
                ++(*this);
                return tmp;
            }

            iterator_map& operator--() // find previous value
            {
                rbt_node* current = ptr;
                rbt_node* res;

                if (current)
                {
                    if (current->left && current->left->is_null == false) // si j'ai un fils gauche, je cherche la valeur max dans cette branche
                        res = current->left->getMaxChild();
                    else
                    {
                        rbt_node* parent = current->parent;
                        while (parent && parent->right != current && parent->is_init == false)
                        {
                            current = parent;
                            parent = current->parent;
                        }
                        if (parent->is_init == true)
                            res = ptr->left;
                        else
                        res = parent;
                    }
                    this->ptr = res;
                }
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
                return &this->ptr->content;
            }

            bool operator==(const iterator_map_const<T>& rhs) const
            {
                return this->ptr == rhs.ptr;
            }
            
            bool operator!=(const iterator_map_const<T>& rhs) const
            {
                return this->ptr != rhs.ptr;
            }        
    };


    template <class T>
    class iterator_map_const : public ft::iterator<ft::bidirectional_iterator_tag, T, std::ptrdiff_t, T*, T&>
    {
        public:
            // ******** MEMBER TYPES ************
            typedef std::ptrdiff_t difference_type;
            typedef const T value_type;
            typedef const T* pointer;
            typedef const T& reference;
            typedef ft::bidirectional_iterator_tag iterator_category;
            typedef rbt_node<T> rbt_node;

            // ******** Attribute ***************
            rbt_node* ptr; 
            
            // ********** MEMBER FUNCTIONS ********** 

            //---> Constructeurs, Destructeur et operateur=
           
            iterator_map_const() : ptr(NULL) {}

            iterator_map_const(rbt_node* data) : ptr(data) { return;}
            
            iterator_map_const(const iterator_map_const& src) : ptr(src.ptr) {}
              
            iterator_map_const(const iterator_map<T>& src) :  ptr(src.ptr) { } // capable de construire a partir d'un it non constant 
                      
            iterator_map_const& operator=(const iterator_map_const & src)
            {
                if (this != &src)
                    this->ptr = src.ptr;
                return *this;
            }

            iterator_map_const& operator=(const iterator_map<T> & src)
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
                if (current)
                {
                    if (current->right && current->right->is_null == false) // si j'ai un fils droit, je cherche la valeur min dans cette branche
                        res = current->right->getMinChild();
                    else
                    {
                        rbt_node* current_parent = current->parent;                 
                        while (current_parent && current == current_parent->right
                                && current_parent->is_init == false) // tant que je suis un fils droit
                        {
                            current = current_parent;
                            current_parent = current_parent->parent;
                        }
                        if (current_parent->is_init == true)
                            res = ptr->right;
                        else
                            res = current_parent;
                    }
                    this->ptr = res;
                }
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
                if (current)
                {
                    if (current->left && current->left->is_null == false) // si j'ai un fils gauche, je cherche la valeur max dans cette branche
                        res = current->left->getMaxChild();
                    else
                    {
                        rbt_node* parent = current->parent;
                        while (parent && parent->right != current
                                && parent->is_init == false) // tant que je suis un fils gauche
                        {
                            current = parent;
                            parent = current->parent;
                        }
                        if (parent->is_init == true) //cas current == min
                            res = ptr->left;
                        else
                            res = parent;
                        res = parent;
                    }
                    this->ptr = res;
                }
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

            bool operator==(const iterator_map_const& rhs) const
            {
                return this->ptr == rhs.ptr;
            }
            
            bool operator!=(const iterator_map_const& rhs) const
            {
                return this->ptr != rhs.ptr;
            }
    };
 }
#endif