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
            rbt_node* _null_node;
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
                new_node->left = rbt_create_null_node();
                new_node->left->parent = new_node;
                new_node->right = rbt_create_null_node();
                new_node->right->parent = new_node;
                new_node->parent = NULL;
                new_node->is_null = false;
                return new_node;
            }

            rbt_node* rbt_create_null_node()
            {
                rbt_node* new_node = _node_allocator.allocate(1);
                new_node->left = NULL;
                new_node->right = NULL;
                new_node->parent = NULL;
                new_node->is_red = false;
                new_node->is_null = true;
                return new_node;
            }

            void rbt_free_node(rbt_node *node)
            {
                if (node->is_null == false)
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
                    while (tmp && tmp->is_null == false)
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

                    if (is_left_child == 1)
                    {
                        tmp->parent->left = new_node;
                        new_node->parent = tmp;
                    }
                    else
                    {
                        tmp->parent->right = new_node;
                        new_node->parent = tmp->parent;
                    }
                    rbt_free_node(tmp);
                    rbt_insert_fix_violation(new_node);
                    return;
                }
            }

            void rbt_insert_fix_violation(rbt_node *node)
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
                            //Left Left Case==> Line on left, right rotation of grandfather
                            if (node == node->parent->left && node->parent == grand_parent->left)
                            {
                                rbt_rotate_right(grand_parent);
                                grand_parent->is_red = true;
                                parent->is_red = false;
                            }

                            //Left Right  ==> triangle < : left rotation of parent then right rotation of grand father
                            else if (node == node->parent->right && node->parent == grand_parent->left)
                            {
                                rbt_rotate_left(node->parent);
                                rbt_rotate_right(grand_parent);
                                grand_parent->is_red = true;
                                parent->is_red = false;
                            }

                            // Right Right  ==> line on right, left rotation of grand father
                            else if (node == node->parent->right && node->parent == grand_parent->right)
                            {
                                rbt_rotate_left(grand_parent);
                                grand_parent->is_red = true;
                                parent->is_red = false;
                            }

                            // Right Left Case ==> triangle >
                            else if (node == node->parent->left && node->parent == grand_parent->right)
                            {
                                rbt_rotate_right(node->parent);
                                rbt_rotate_left(grand_parent);
                                grand_parent->is_red = true;
                                parent->is_red = false;
                            }
                        }
                    }
               }
            }

            void rbt_rotate_right(rbt_node* node)//parent, rbdt_node* grand_parent)
            {
                rbt_node* tmp = node->left->right;

                if (node->parent && node == node->parent->left)
                    node->parent->left = node->left;
                else if (node->parent && node == node->parent->right)
                    node->parent->right = node->left;
                node->left->parent = node->parent;

                node->left->right = node;
                node->parent = node->left;
                
                node->left = tmp;
                node->left->parent = node;

                if (node ==_root)
                    _root = node->parent;
            }

            void rbt_rotate_left(rbt_node* node)
            {
                rbt_node* tmp = node->right->left;

                if (node->parent && node == node->parent->left)
                    node->parent->left = node->right;
                else if (node->parent && node == node->parent->right)
                    node->parent->right = node->right;
                node->right->parent = node->parent;

                node->right->left = node;
                node->parent = node->right;
                
                node->right = tmp;
                node->right->parent = node;

                if (node ==_root)
                    _root = node->parent;
            }

            void rbt_delete(rbt_node *node)
            {
                rbt_node* to_delete = rbt_search(_root, node);
                rbt_node* replacement;

                if (to_delete == NULL)
                    return;
                
                //Initital steps --> convert to a 0 or 1 child case 
                if (to_delete->left->is_null == false && to_delete->right->is_null == false)
                {
                    replacement = to_delete;
                    to_delete = to_delete->right->getMinChild();
                    replacement->content = copy(to_delete); // A FAIRE
                }
                
                bool original_is_red = to_delete->is_red;

                if (to_delete->left->is_null == true && to_delete->right->is_null == true)
                {
                    replacement = to_delete->right;
                    rbt_delete_case1(to_delete);
                    rbt_free_node(to_delete->left);

                }
                else if (to_delete->left->is_null == false)
                {
                    replacement = to_delete->left;
                    rbt_delete_case2(to_delete, to_delete->left)
                    rbt_free_node(to_delete->right);

                }
                else if (to_delete->right->is_null == false)
                {
                    replacement = to_delete->right;
                    rbt_delete_case2(to_delete, to_delete->right)
                    rbt_free_node(to_delete->left);
                }
               
                rbt_free_node(to_delete);
                
                if (_root != NULL)
                    rbt_delete_fix_violation(original_is_red, replacement); 
            }
        
            //Node to delete has two NULL children
            void rbt_delete_case1(rbt_node *to_delete, rbt_node *child)
            {
                if (to_delete ==_root)
                {
                    _root = rbt_create_null_node();;
                }
                else if (to_delete == to_delete->parent->left)
                {
                    to_delete->parent->left = child;
                    child->parent = to_delete->parent;
                }
                else
                {
                    to_delete->parent->right = child;
                    child->parent = to_delete->parent;
                }
            }
            
            //Node to delete has one NULL children
            void rbt_delete_case2(rbt_node *to_delete, rbt_node* child)
            {
                child->parent = to_delete->parent;
                if (to_delete == _root)
                    _root = child;
                else if (to_delete == to_delete->parent->left)
                    to_delete->parent->left = child;
                else
                    to_delete->parent->right = child;
                child->parent = to_delete->parent;

            }

            void rbt_delete_fix_violation(bool original_is_red, rbt_node* replacement)
            {
                if (original_is_red == true || replacement->is_red == true)
                {
                    replacement->is_red == false;
                    return;
                }
                else //node deleted equal to double black
                {
                    rbt_double_black_solve(replacement);
                }
            }
            
            void double_black_solve(rbt_node* replacement)
            {
                rbt_node* sibling;
                rbt_node* tmp;

                if (replacement->parent) // to avoid root
                {
                    if (replacement == replacement->parent->left)
                        sibling = replacement->parent->right;
                    else 
                        sibling = replacement->parent->left;
                }

                //case 1 --> terminate case      
                if (replacement == _root)
                {
                    replacement->is_red = false;
                    return;
                }

                //case 2 (mirror) 
                else if (replacement->parent->is_red == false
                        sibling->is_red == true
                        sibling->left->is_red == false
                        sibling->right->is_red == false)
                {
                    if (sibling == replacement->parent->right)
                    {
                        sibling->is_red = false;
                        replacement->parent->is_red = true;
                        rbt_rotate_left(replacement->parent);
                        double_black_solve(replacement);
                    }
                   // else


                }
                //case 3 (mirror)
                else if (replacement->parent->_is_red == false
                            && sibling->is_red == false
                            && sibling->left->is_red == false
                            && sibling->right->is_red == false)
                {
                    //works for both mirror
                    sibling->is_red == true;
                    double_black_solve(replacement->parent);
                }
                
                //case 4 (mirror) --> terminate case
                else if (replacement->parent->is_red == true
                            && sibling->is_red == false
                            && sibling->left->is_red == false 
                            && sibling->right->is_red == false)
                {
                    //works for both mirror
                    replacement->parent->is_red = false;
                    sibling->is_red == true;
                    return;
                }

                //case 5   
                else if (replacement->parent->is_red == false 
                            && sibling->is_red == false
                            && siblling->left->is_red == true
                            && sibling->right->is_red == false)
                {
                    sibling->left->is_red == false;
                    sibling->is_red = true;
                    rbt_rotate_right(sibling);
                    double_black_solve(replacement):
                }

                //case 6 (mirror)--> terminate case      
                 else if (sibling->is_red == false
                            && sibling->right->is_red == true)
                {
                    if (sibling == replacement->parent->right)
                    {
                        sibling->is_red = replacement->parent->is_red;
                        replacement->parent->is_red = false;
                        sibling->right->is_red = false;
                        rbt_rotate_left(replacement->parent);
                    }
                    else // to redefine
                    {
                        //
                        rbt_rotate_right(replacement->parent);
                        //
                    }

                    return;
                }



            }
            

            rbt_node* rbt_search(rbt_node* src, rbt_node* node)
            {
                if (src && node && node->is_null == false) 
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