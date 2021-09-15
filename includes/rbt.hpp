/* Class to define a Red Black Tree. Rules : 
 *  1. Each node is either Red or Black                        --> maintained by insert/delete           
 *  2. All NULL node (leaves) are considered black             --> maintained by insert/delete
 *  3. A red node does not have a red child                    --> Red violation
 *  4. Every path from a given node to any of its descendanrs  --> Black violation
 
 
 -*     NULL nodes goes through the same number of black nodes
 */


#ifndef RBT_HPP

#define RBT_HPP

#include <iostream>
#include <cstdlib> //pour NULL

#include "less.hpp"
#include "comparison.hpp"
#include "enable_if.hpp"

// a confirmer
#include <string>
#include <sstream> //pour exceptions messages


//#include "iterator_reverse.hpp"
//#include "iterator_map.hpp"


namespace ft
{
    //template<class Key, class T, class Compare = ft::less<Key>, class Alloc = std::allocator<ft::pair<const Key, T> > >
    template <class value_type>
    class rbt_node
    {
        public:

            value_type content;
            bool is_red;
            bool is_null;
            bool is_init;
            bool is_end;
            rbt_node* parent;
            rbt_node* left;
            rbt_node* right;

            rbt_node(void) : 
            is_red(true), is_null(false), is_init(false), is_end(false), parent(NULL), left(NULL), right(NULL)
            {
                return;
            }
        
            rbt_node(rbt_node const& src) : 
            is_red(src.is_red), is_null(src.is_null), is_init(src.is_init), is_end(src.is_end), parent(src.parent), left(src.left), right(src.right)
            {
                return;
            }

            ~rbt_node() 
            {
                return;
            }

            rbt_node& operator=(rbt_node const& src)
            {
                this->is_red = src.is_red;
                this->is_null = src.is_null;
                this->is_init = src.is_init;
                this->is_end = src.is_end;
                this->parent = src.parent;
                this->left = src.left;
                this->right = src.right;
                return *this;
            }

            rbt_node* getGrandParent() const
            {
                if (this->parent->is_init == true)
                    return NULL;
                else if (this->parent->parent->is_init== true)
                    return NULL;
                return this->parent->parent;
            }

            rbt_node* getUncle() const
            {
                rbt_node* grand_parent = getGrandParent();
                if (grand_parent == NULL)
                    return NULL;
                if (grand_parent->left == this->parent)
                    return grand_parent->right;
                else
                    return grand_parent->left;
            }

            rbt_node* getSibling() const
            {
                if (parent->is_init == true)
                    return NULL;
                if (parent->left == this)
                    return parent->right;
                else
                    return parent->left;
            }

            rbt_node* getMinChild()
            {
                rbt_node* min_child;
                if (this->left && this->left->is_null == false)
                {
                    min_child = this->left;
                    while (min_child && min_child->left && min_child->left->is_null == false)
                        min_child = min_child->left;
                }
                else
                    min_child = this;
                return min_child;
            }

            rbt_node* getMaxChild() 
            {
                rbt_node* max_child;
                if (this->right && this->right->is_null == false)
                {
                    max_child = this->right;
                    while (max_child && max_child->right && max_child->right->is_null == false)
                        max_child = max_child->right;
                }
                else
                    max_child = this;
                return max_child;
            }
    };


}

#endif