/* Class to define a Red Black Tree. Rules : 
 *  1. Each node is either Red or Black                        --> maintained by insert/delete           
 *  2. All NULL node (leaves) are considered black             --> maintained by insert/delete
 *  3. A red node does not have a red child                    --> Red violation
 *  4. Every path from a given node to any of its descendanrs  --> Black violation
 *     NULL nodes goes through the same number of black nodes
 */


#ifndef RBT_HPP

#define RBT_HPP

namespace ft
{

    template <class T>
    class rbt_node
    {
        public:

        T content;
        bool is_red;
        bool is_null;
        rbt_node* parent;
        rbt_node* left;
        rbt_node* right;

        rbt_node() : is_red(true), is_null(false), parent(NULL), left(NULL), right(NULL)
        {
            return;
        }
        
        rbt_node(T content) : content(content), is_red(true), is_null(false), parent(NULL), left(NULL), right(NULL)
        {
            return;
        }

        rbt_node(rbt_node const& src) : content(src.content), is_red(src.is_red), is_null(src.is_null), parent(src.parent), left(src.left), right(src.right)
        {
            return;
        }

        ~rbt_node();

        rbt_node& operator=(rbt_node const& src)
        {
            this->content = src.content; // a revoir
            this->is_red = src.is_red;
            this->is_null = src.is_null;
            this->parent = src.parent;
            this->left = src.left;
            this->right = src.right;
            return *this;
        }

        rbt_node* getGrandParent() const
        {
            if (this->parent == NULL)
                return NULL;
            return this->parent->parent;
        }

        rbt_node* getUncle() const
        {
            rbt_node* grand_parent = getGrandParent();
            if (grand_parent == NULL)
                return NULL;
            if (grand_parent->left == getParent())
                return grand_parent->right;
            else
                return grand_parent->left;
        }

        rbt_node* getSibling() const
        {
            if (parent == NULL)
                return NULL;
            if (parent->left == this)
                return parent->right;
            else
                return parent->left;
        }

        rbt_node* getMinChild() const
        {
            rbt_node* min_child = this->left;
            while (min_child && min_child->left && min_child->left->is_null == false)
                min_child = min_child->left;
            return min_child;
        }

        rbt_node* getMaxChild() const
        {
            rbt_node* max_child = this->right;
            while (max_child && max_child->right && max_child->right->null == false)
                max_child = max_child->right;
            return max_child;
        }
    };
}

#endif