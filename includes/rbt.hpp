#ifndef RBT_HPP

#define RBT_HPP

namespace ft
{
    template <class T>
    class rbt_node
    {
        public:

        // Attributs
        T content;
        bool is_red;
        rbt_node* parent;
        rbt_node* left;
        rbt_node* right;

        rbt_node() : is_red(true), parent(NULL), left(NULL), right(NULL)
        //Ajout content?
        {
            return;
        }

        rbt_node(rbt_node const& src) : is_red(src.is_red), parent(src.parent), left(src.left), right(src.right)
        //Ajout content?
        {
            return;
        }

        ~rbt_node();

        rbt_node& operator=(rbt_node const& src)
        {
            // Ajout content?
            this->is_red = src.is_red;
            this->parent = src.parent;
            this->left = src.left;
            this->right = src.right;
            return *this;
        }
    };

}



#endif