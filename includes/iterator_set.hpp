// CLASS for Set Const Map Iterator 
// Tag utilisé = bidirectional
// Bidirectional iterators are iterators that can be used to access the sequence of elements in a range in both directions (towards the end and towards the beginning).

#ifndef ITERATOR_SET_HPP

#define ITERATOR_SET_HPP

#include <memory> //std::allocator
#include "rbt.hpp"
#include "iterator_traits.hpp"

namespace ft
{
    template <class T>
    class iterator_set_const : public ft::iterator<ft::bidirectional_iterator_tag, T, std::ptrdiff_t, T*, T&>
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
           
            iterator_set_const() : ptr(NULL) {}

            iterator_set_const(rbt_node* data) : ptr(data) { return;}
            
            iterator_set_const(const iterator_set_const& src) : ptr(src.ptr) {}
                                   
            iterator_set_const& operator=(const iterator_set_const & src)
            {
                if (this != &src)
                    this->ptr = src.ptr;
                return *this;
            }

            virtual ~iterator_set_const() {}
            
            //---> operators

            //____________ Arithmetic operators ('classic')

            iterator_set_const& operator++()
            {
                rbt_node* current = ptr;
                rbt_node* res;
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
                return *this;
            }           

            iterator_set_const operator++(int)
            {
                iterator_set_const tmp = *this;
                ++(*this);
                return tmp;
            }

            iterator_set_const& operator--()
            {
                rbt_node* current = ptr;
                rbt_node* res;
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
                return *this;
            }

            iterator_set_const operator--(int)
            {
                iterator_set_const tmp = *this;
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

            bool operator==(const iterator_set_const& rhs) const
            {
                return this->ptr == rhs.ptr;
            }
            
            bool operator!=(const iterator_set_const& rhs) const
            {
                return this->ptr != rhs.ptr;
            }
    };
 }
#endif