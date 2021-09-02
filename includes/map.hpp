#ifndef map_HPP

#define map_HPP

#include "iterator_reverse.hpp"
#include "iterator_traits.hpp"
#include "iterator_map.hpp"
#include "comparison.hpp"
#include "enable_if.hpp"
#include "pair.hpp"
#include "less.hpp"

namespace ft
{
    template<class Key, class T, class Compare = ft::less<Key>, class Alloc = std::allocator<ft::pair<const Key, T> > >
    //Alloc corresponds to the type of allocator object that is used to define the storage location model
    
    class map
    {
        // *********** MEMBERS TYPES **************
        public: 
            typedef Key key_type;
            typedef T mapped_type;
            typedef ft::pair<const key_type, mapped_type> value_type;
            typedef Compare key_compare;
            typedef Alloc allocator_type;
            typedef typename allocator_type::reference reference;
            typedef typename allocator_type::const_reference const_reference;
            typedef typename allocator_type::pointer pointer;
            typedef typename allocator_type::const_pointer const_pointer;
            typedef iterator_map<T> iterator;
            typedef iterator_map_const<T> const_iterator;
            typedef typename ft::reverse_iterator<iterator> reverse_iterator;
            typedef typename ft::reverse_iterator<const_iterator> const_reverse_iterator;
            typedef typename ft::iterator_traits<iterator>::difference_type difference_type;
            typedef std::size_t size_type;
            
	
            class value_compare
	    	{
	    	    protected:
		        	Compare _comp; 
                    //constructeur en protected, a voir?

	    	    public:
		    	    typedef bool result_type;
			        typedef value_type first_argument_type;
		    	    typedef value_type second_argument_type;

			        value_compare(Compare c) : _comp(c)
                    {
                        return;
                    }

		    	    bool operator()(value_type const& x, value_type const& y) const
			        {
				        return this->comp_(x.first, y.first);
		    	    }
		    };
        
        // *********** ATTRIBUTS ***************
        protected:
            // A revoir
            typedef rbt_node<value_type> rbt_node;
            typedef typename allocator_type::template  rebind<rbt_node>::other node_allocator_type;

            key_compare _comp;
            allocator_type _allocator;
            rbt_node* _root;
            rbt_node* _end;
            rbt_node* _node;
            rbt_node* leaf;
            node_allocator_type _node_allocator;
            size_type _size;


            // A FAIRE AVEC RBT

        public:
             
            // ********** MEMBER FUNCTIONS ********** 

            //---> 4 Constructeurs, Destructeur et operateur= 
            
            // A FAIRE
           
            // 4.  Copy 
            map(map const & src)
            {
                // A FAIRE
            }

            virtual ~map(void)
            {              
                // A FAIRE
            }
            
            map & operator=(map const & src)
            {
                 // A FAIRE
            }

            //---> Iterators

            iterator begin()
            {
                rbt_node* tmp = _root;
                while (tmp->left)
                    tmp = tmp->left;
                return iterator(tmp);
            }

            const_iterator begin() const
            {
                rbt_node* tmp = _root;
                while (tmp->left)
                    tmp = tmp->left;
                return const_iterator(tmp);
            }

            iterator end()
            {
                rbt_node* tmp = _root;
                while (tmp->right)
                    tmp = tmp->right;
                return iterator(tmp); // pas sure
            }

            const_iterator end() const
            {
                rbt_node* tmp = _root;
                while (tmp->right)
                    tmp = tmp->right;
                return const_iterator(tmp); // pas sure
            }

            reverse_iterator rbegin()
            {
               return reverse_iterator(end());
            }
            
            const_reverse_iterator rbegin() const
            {
               return const_reverse_iterator(end());
            }
            
            reverse_iterator rend() 
            {
               return reverse_iterator(begin()));
            }
            
            const_reverse_iterator rend() const
            {
               return const_reverse_iterator(begin());
            }
        
            //---> Elements Access
            
                       
            reference operator[] (size_type n)
            {
                // A FAIRE
            }
            
            const_reference operator[] (size_type n) const 
            { 
                // A FAIRE
            }
 
        
            //---> Capacity

            bool empty() const
            {
                return (this->_size == 0 ? true : false);
            }

            size_type size() const
            {
                return this->_size;
            }

            size_type max_size() const
            {
                return this->_allocator.max_size();
            }
            
            
            // --> Modifiers

           
            void clear()
            {
                // A FAIRE
            }

            iterator insert(iterator position, const mapped_type& val)
            {
                // A FAIRE
            }

            // erase
            
            void swap (map& src)
            {
                // A FAIRE
            }


            // ---> Observers

            // key_comp

            // value_comp


            //---> Operations

            // find

            // count

            // lower_bound

            // upper_bound

            // equal_range

            
            //---> Allocator
            
            allocator_type get_allocator() const
            {
                this->_allocator;
            }

        
        // ADDITIONAL FUNCTION

        private:
            
            //init
            //leaf->is_red = false
             
            rbt_node* rbt_create_node(value_type data)
            {
                rbt_node* new_node = _node_allocator.allocate(1);
                _allocator.construct(&new_node->content, data);
                new_node->left = leaf;
                new_node->right = leaf;
                new_node->parent = NULL;
                return new_node;
            }

            void rbt_free_node(rbt_node *node)
            {
                _node_allocator.destroy(&node->content);
                _node_allocator.deallocate(node, 1);
            }

            void rbt_clear_tree(rbt_node* node)
            {
                if (node->left)
                    rbt_clear_tree(node->left);
                if (node->right) // node->right != end ?
                    rbt_clear_tree(node->right);
                this->rbt_free_node(node);
            }

            void rbt_insert(value_type data)
            {
                rbt_node* new_node = rbt_create_node(data);
                if (_root == NULL)
                {
                    new_node->is_red = false;
                    _root = new_node;
                    //_end = ?
                }   
                else
                {
                    rbt_node* tmp = _root;
                    bool is_left_child;
                    while (tmp)
                    {
                        new_node->parent = tmp;
                        if (_comp(tmp->content.first, new_node->content.first) == true) // si new_node est plus grand
                        {   
                            is_left_child = 0;
                            tmp = tmp->right;
                        }
                        else if (_comp(new_node->content.first, tmp->content.first) == true) // si new_node est plus petit
                        {
                            is_left_child = 1;
                            tmp = tmp->left;
                        }
                        else //node already exist
                        {
                            rbt_free_node(new_node);
                            return;
                        }
                    }
                    tmp = new_node;
                    if (is_left_child == 1)
                        new_node->parent->left = tmp;
                    else
                        new_node->parent->right = tmp;
                    rbt_fix_violation(new_node);
                    return;
                }
            }

            void rbt_fix_violation(rbt_node *node)
            {
                if (node != _root)
                {
                    if(node->parent->is_red == false)
                        return;
                    else
                    {
                        rbt_node* uncle = node.getUncle();
                        rbt_node* grand_parent = node.getGrandParent());

                        if (uncle && uncle->is_red == true)
                        {
                            node->parent->is_red == false;
                            uncle->is_red = false;
                            grand_parent->is_red = true;
                            rbt_fix_violation(grand_parent);
                        }

                        else // !uncle || uncle->is_red == false // 4 cases
                        {                        
                            //Left Left ==> Line on left, 2 rotation to right
                            if (node == node->parent->left && node->parent == grand_parent->left)
                                rbt_rotate_right_right(node->parent, grand_parent);

                            //Left Right  ==> triangle <
                            else if (node == node->parent->right && node->parent == grand_parent->left)
                                rbt_rotate_left_right(node, node->parent);

                            // Right Right  ==> line on right, 2 rotations to left
                            else if (node == node->parent->right && node->parent == grand_parent->right)
                                rbt_rotate_left_left(node, node->parent);

                            // Right Left Case ==> triangle >
                            else if (node == node->parent->left && node->parent == grand_parent->right)
                                rbt_rotate_right_left(node, node->parent);
                        }
                    }
               }
            }

            void rbt_rotate_left_left(rbt_node* parent, rbdt_node* grand_parent)
            {
                rbt_node* tmp_parent_left = parent->left;

                parent->parent = grand_parent->parent;
                parent->left = grand_parent;
                if (grand_parent ==_root)
                    _root = parent;
                
                grand_parent->parent = parent;
                grand_parent->right = tmp_parent_left;
                
                grand_parent->is_red = true;
                parent->is_red = false;
            }

            void rbt_rotate_right_right(rbt_node* parent, rbdt_node* grand_parent)
            {
                rbt_node* tmp_parent_right = parent->right;

                parent->parent = grand_parent->parent;
                parent->right = grand_parent;
                if (grand_parent ==_root)
                    _root = parent;
                
                grand_parent->parent = parent;
                grand_parent->left = tmp_parent_right;

                grand_parent->is_red = true;
                parent->is_red = false;
            }

          void rbt_rotate_left_right(rbt_node* node, rbdt_node* parent)
            {
                rbt_node* tmp_node_left = node->left;

                node->left = parent;
                node->parent = parent->parent;

                parent->parent->left = node;

                parent->right = tmp_node_left;
                parent->parent = node;

                rbt_rotate_right_right(node, node->parent);
            }

            void rbt_rotate_right_left(rbt_node* node, rbdt_node* parent)
            {
                rbt_node* tmp_node_right = node->right;

                node->right = parent;
                node->parent = parent->parent;

                parent->parent->right = node;

                parent->left = tmp_node_right;
                parent->parent = node;

                rbt_rotate_left_left(node, node->parent);
            }

            void rbt_delete(rbt_node *node)
            {
                rbt_node* to_delete = rbt_search(_root, node);
                if (to_delete == NULL)
                    return;
                
                bool original_is_red = to_delete->is_red;

                if (to_delete->left && to_delete->right == NULL )
                {
                    if (to_delete ==_root)
                    {
                        _root = to_delete->left;
                        to_delete->left->parent = NULL;
                    }
                    else if (to_delete == to_delete->parent->left)
                    {
                        to_delete->parent->left = to_delete->left;
                        to_delete->left->parent = to_delete->parent;
                    } 
                    else
                    {
                        to_delete->parent->right = to_delete->left;
                        to_delete->left->parent = to_delete->parent;
                    }
                     if (original_is_red == true || to_delete->left->is_red == true)
                    {
                         to_delete->left->is_red = false;
                         rbt_free_node(to_delete);
                         return;
                    }
                    else // 2 blacks
                        //Fixe couleur
                }
               
                else if (to_delete->right && to_delete->left == NULL)
                {
                    if (to_delete == _root)
                    {
                        _root = to_delete->right;
                        to_delete->right->parent = NULL;
                    }
                    else if (to_delete == to_delete->parent->left)
                    {
                        to_delete->parent->left = to_delete->right;
                        to_delete->right->parent = to_delete->parent;
                        if (to_delete->right->is_red == true)
                            to_delete->right->is_red = false;
                    } 
                    else
                    {
                        to_delete->parent->right = to_delete->right;
                        to_delete->right->parent = to_delete->parent;
                    }
                    if (original_is_red == true || to_delete->right->is_red == true)
                    {
                         to_delete->right->is_red = false;
                         rbt_free_node(to_delete);
                         return;
                    }
                    else // 2 blacks
                        //Fixe couleur
                    rbt_free_node(to_delete);
                }
                
            }


            rbt_node* rbt_search(rbt_node* src, rbt_node* node)
            {
                if (src && node) 
                {
                    if (this->comp(src->content.first, node->content.first) == false)
                    {
                        if (src->right)
                            return (rbt_search(src->right, node));
                    }
                    else if (this->comp(node->content.first, src->content.first) == false)
                    {
                        if(src->left)
                            return (rbt_search(src->left, node));
                    }
                    else
                    {
                        return (src);
                    }
                }
                return (NULL);
            }
                
    };

}

#endif