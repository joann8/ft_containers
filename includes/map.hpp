#ifndef MAP_HPP

#define MAP_HPP

#include <iostream>

#include "pair.hpp"
#include "less.hpp"
#include "comparison.hpp"
#include "enable_if.hpp"
#include "iterator_reverse.hpp"
#include "rbt.hpp"
#include "iterator_map.hpp"

#define RESET   "\033[0m"
#define RED     "\033[31m"
#define GREEN   "\033[32m"

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
            typedef ft::pair<const Key, T> value_type;
            typedef Compare key_compare;
            typedef Alloc allocator_type;
            typedef typename allocator_type::reference reference;
            typedef typename allocator_type::const_reference const_reference;
            typedef typename allocator_type::pointer pointer;
            typedef typename allocator_type::const_pointer const_pointer;
            typedef iterator_map<value_type> iterator;
            typedef iterator_map_const<value_type> const_iterator;
            typedef typename ft::reverse_iterator<iterator> reverse_iterator;
            typedef typename ft::reverse_iterator<const_iterator> const_reverse_iterator;
            typedef typename ft::iterator_traits<iterator>::difference_type difference_type;
            typedef std::size_t size_type;
            
	
            class value_compare
	    	{
	    	    protected:
		        	Compare _comp; //constructeur en protected, a voir?

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
				        return this->_comp(x.first, y.first);
		    	    }
		    };
        
        // *********** ATTRIBUTS ***************
        protected:
            typedef rbt_node<value_type> rbt_node;
            typedef typename allocator_type::template rebind<rbt_node>::other node_allocator_type;

            key_compare _comp;
            allocator_type _allocator;
            node_allocator_type _node_allocator;
            size_type _size;
            rbt_node* _root;
            rbt_node* _begin;
            rbt_node* _end;
            
        public:
             
            // ********** MEMBER FUNCTIONS ********** 

            //---> 3 Constructeurs, Destructeur et operateur= 
                       
            // 1. Empty by default , with no elements 
            explicit map (const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type()) :
            _comp(comp), _allocator(alloc), _node_allocator(), _size(0), _root(rbt_create_null_node( NULL)), _begin(rbt_create_null_node(NULL)), _end(rbt_create_null_node( NULL))
            {
                _begin->is_init = true;
                _begin->right = _root;
                _begin->left = _root;
                _begin->parent = NULL;
                _begin->is_null = false;
                _root->parent =_begin;
                _end->is_end = true;
                _end->parent = _root;
                return;
            }

            // 2. Range : Constructs a container with as many elements as the range [first,last), with each element constructed from its corresponding element in that range
            template <class InputIterator>
            map(InputIterator first, InputIterator last, const key_compare comp = key_compare(), const allocator_type& alloc = allocator_type()) :
            _comp(comp), _allocator(alloc), _node_allocator(), _size(0), _root(rbt_create_null_node( NULL)), _begin(rbt_create_null_node( NULL)), _end(rbt_create_null_node( NULL))
            {
                _begin->is_init = true;
                _begin->right = _root;
                _begin->left = _root;
                _begin->parent = NULL;
                _begin->is_null = false;
                _root->parent =_begin;
                _end->is_end = true;
                _end->parent = _root;
         		this->insert(first, last);
                return;
            }

            // 3. Copy constructor
            map(map const & src) :
            _comp(src._comp), _allocator(src._allocator), _node_allocator(src._node_allocator), _size(0), _root(rbt_create_null_node(NULL)), _begin(rbt_create_null_node(NULL)), _end(rbt_create_null_node(NULL))
            {
                _begin->is_init = true;
                _begin->right = _root;
                _begin->left = _root;
                _begin->parent = NULL;
                _begin->is_null = false;
                _root->parent =_begin;
                _end->is_end = true;
                _end->parent = _root;
    		    for(const_iterator it = src.begin(); it != src.end(); it++)
                    this->insert(*it);
            }

            virtual ~map(void)
            {              
                this->clear();
                this->rbt_free_node(_root);
                this->rbt_free_node(_begin);
                this->rbt_free_node(_end);
                return;
            }
            
            map & operator=(map const & src)
            {
                if (this != &src)
                {
                    this->clear();
                    this->_comp = src._comp;               
                    for(const_iterator it = src.begin(); it != src.end(); it++)
                        this->insert(*it);
                }
                return *this;
            }


            //---> Iterators

            iterator begin() 
            {
                rbt_node* tmp;
                if (_root->is_null == false)
                    tmp = _root->getMinChild();
                else
                    tmp = _end;
                return iterator(tmp);
            }

            const_iterator begin() const
            {
                rbt_node* tmp;
                if (_root->is_null == false)
                    tmp = _root->getMinChild();
                else
                    tmp = _end;
                return const_iterator(tmp);
            }

            iterator end() 
            {
                return (iterator(_end));
            }

            const_iterator end() const
            {
                return (const_iterator(_end));
            }

            reverse_iterator rbegin()
            {
                return reverse_iterator(_end);
            }
            
            const_reverse_iterator rbegin() const
            {
                return const_reverse_iterator(_end);
            }
            
            reverse_iterator rend() 
            {
                return reverse_iterator(begin());
            }
            
            const_reverse_iterator rend() const
            {
                return const_reverse_iterator(begin());
            }
        
        
            //---> Elements Access
                       
            mapped_type& operator[](const key_type& k)
            {
                //if k matches the key of an element in the container, the function returns a reference to its mapped value
                //If k does not match, the function inserts a new element with that key and returns a reference to its mapped value.
                //Notice that this always increases the container size by one, even if no mapped value is assigned to the element (the element is constructed using its default constructor).
                return (*((this->insert(value_type(k,mapped_type()))).first)).second; // defini sur cpp
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
                return this->_node_allocator.max_size();
            }
            
            
            // --> Modifiers

            void clear()
            {
                this->rbt_clear_tree(_root);
                _root = rbt_create_null_node(_begin);
                _begin->right = _root;
                _begin->left = _root;
                _end->parent = _root;
                _size = 0;
            }

            // 3 != insert

            ft::pair<iterator, bool> insert(const value_type& val)
            {
                size_type old_size = this->_size;
                rbt_node* tmp = rbt_search_root(val.first);

                if (tmp && tmp->is_null == true)
                    rbt_insert(val);
                iterator it = iterator(rbt_search_root(val.first));
                if (this->_size == old_size)
                    return ft::make_pair<iterator,bool> (it, false);
                else
                    return ft::make_pair<iterator, bool> (it,true);
            }

            iterator insert(iterator position, const value_type& val)
            {
                (void)position;
                insert(val);
                return iterator(rbt_search_root(val.first));
            }

            template <class InputIterator>
            void insert(InputIterator first, InputIterator last)
            {
               while(first != last)
               {
                    insert(*first);
                    first++;
               }
            }

            // 3 != erase

            void erase(iterator position)
            {
                rbt_node* tmp = position.ptr;
                if (tmp && tmp->is_null == false)
                {
                   if (rbt_search_root(tmp->content.first))
                      rbt_delete(tmp->content.first, position);
                }
            }

            size_type erase(const key_type& k)
            {

                rbt_node* tmp = rbt_search_root(k);
                size_type size =  this->size();
                if (tmp && tmp->is_null == false)
                    rbt_delete(k, iterator(tmp));
                return this->size() != size;
            }

            void erase (iterator first, iterator last)
            {
                size_type diff = 0;
                iterator start = first;
                while (start != last)
                {
                    diff++;
                    start++;
                }

                size_type i = 0;
                while (i < diff)
                {
                    rbt_node* tmp = rbt_search_root(first->first);
                    if (tmp && tmp->is_null == false)
                        first = rbt_delete(tmp->content.first, first);
                    first++;
                    i++;
                }
            }
            
            void swap (map& src)
            {
                key_compare tmp_comp = src._comp;
                allocator_type tmp_allocator = src._allocator;
                node_allocator_type tmp_node_allocator = src._node_allocator;
                rbt_node* tmp_root =  src._root;
                rbt_node* tmp_end =  src._end;
                rbt_node* tmp_begin =  src._begin;
                size_type tmp_size = src._size;

                src._comp = _comp;
                src._allocator = _allocator;
                src._node_allocator = _node_allocator;
                src._root = _root;
                src._begin = _begin;
                src._end = _end; 
                src._size = _size;
              
                _comp = tmp_comp;
                _allocator = tmp_allocator;
                _node_allocator = tmp_node_allocator;
                _root = tmp_root;
                _end = tmp_end;
                _begin = tmp_begin;
                _size = tmp_size;
            }


            // ---> Observers

            key_compare key_comp() const
            {
                return this->_comp;
            }

            value_compare value_comp() const
            {
                return value_compare(this->_comp);
            }


            //---> Operations

            iterator find(const key_type& k)
            {
                rbt_node* tmp = rbt_search_root(k);
                if (tmp && tmp->is_null == false)
                    return (iterator(tmp));
                else
                    return end();
            }
            
            const_iterator find(const key_type& k) const
            {
                rbt_node* tmp = rbt_search_root(k);
                if (tmp && tmp->is_null == false)
                    return (const_iterator(tmp));
                else
                    return end();             
            }

            size_type count(const key_type& k) const
            {
                rbt_node* tmp = rbt_search_root(k);
                if (tmp->is_null == false)
                    return (1);
                else
                    return 0;   
            }

            iterator lower_bound(const key_type& k)
            {   
                iterator it = begin();
                iterator ite = end();
                while (it != ite)
                {
                    if (it->first == k || _comp(it->first, k) == false)
                        return it;
                    it++;
                }
                return end();
            }

            const_iterator lower_bound(const key_type& k) const
            {
                const_iterator it = begin();
                const_iterator ite = end();
                while (it != ite)
                {
                    if (it->first == k || _comp(it->first, k) == false)
                        return const_iterator(it);
                    it++;
                }
                return const_iterator(end());
            }

            iterator upper_bound(const key_type& k)
            {   
                iterator it = begin();
                iterator ite = end();
                while (it != ite)
                {
                    if (it->first != k && _comp(it->first, k) == false)
                        return it;
                    it++;
                }
                return end();
            }

            const_iterator upper_bound(const key_type& k) const
            {
                const_iterator it = begin();
                const_iterator ite = end();
                while (it != ite)
                {
                    if (it->first != k && _comp(it->first, k) == false)
                        return const_iterator(it);
                    it++;
                }
                return const_iterator(end());
            }
            
            ft::pair<const_iterator, const_iterator> equal_range(const key_type& k) const
            {
                return ft::make_pair(lower_bound(k), upper_bound(k));
            }

            ft::pair<iterator, iterator> equal_range(const key_type& k)
            {
                return ft::make_pair(lower_bound(k), upper_bound(k));
            }
            
            //---> Allocator
            
            allocator_type get_allocator() const
            {
                return this->_allocator;
            }

        
        // ADDITIONAL FUNCTION

        protected:
            
            rbt_node* rbt_create_null_node(rbt_node *parent)
            {
                rbt_node* new_node = _node_allocator.allocate(1);
                _node_allocator.construct(new_node, rbt_node());
                new_node->left = NULL;
                new_node->right = NULL;
                new_node->parent = parent;
                new_node->is_red = false;
                new_node->is_null = true;
                new_node->is_init = false;
                new_node->is_end = false;
                return new_node;
            }

            rbt_node* rbt_create_node(value_type const & data)
            {
                rbt_node* new_node = _node_allocator.allocate(1);
                _node_allocator.construct(new_node, rbt_node());

                new_node->parent = NULL;
                new_node->right = NULL;
                new_node->left = NULL;
                new_node->is_null = false;
                new_node->is_init = false;
                new_node->is_red = true;
                new_node->is_end = false;
                _allocator.construct(&new_node->content, data);
                return new_node;
            }

            void rbt_free_node(rbt_node *node)
            {
                if (node)
                {
                    _node_allocator.destroy(node);
                    _node_allocator.deallocate(node, 1);
                }
            }

            void rbt_clear_tree(rbt_node* node)
            {
                if (node->left)
                    rbt_clear_tree(node->left);
                if (node->right && node->right->is_end == false)
                    rbt_clear_tree(node->right);
                this->rbt_free_node(node);
            }

            rbt_node* rbt_search(rbt_node* src, const Key& key) const
            {
                while (src && src->is_null == false) 
                {
                    if (this->_comp(key, src->content.first) == true)
                        src = src->left;
                    else if (this->_comp(src->content.first, key) == true)
                        src = src->right;
                    else
                        return (src);
                }
                return (src);
            }

            rbt_node* rbt_search_root(const Key& key) const
            {
                return rbt_search(_root, key);
            }

            void rbt_rotate_right(rbt_node* node)
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

                if (node == _root)
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
           
            void rbt_insert_fix_violation(rbt_node *node)
            {
                if (node != _root)
                {
                    if(node->parent->is_red == false)
                        return;
                    if (node->parent == _root)
                    {
                        node->parent->is_red = false;
                        return;
                    }

                    rbt_node* uncle = node->getUncle();
                    rbt_node* grand_parent = node->getGrandParent();
                    if (uncle && grand_parent)
                    {
                        if (uncle && uncle->is_red == true)
                        {
                            node->parent->is_red = false;
                            uncle->is_red = false;
                            grand_parent->is_red = true;
                            rbt_insert_fix_violation(grand_parent);    
                        }

                        else // !uncle || uncle->is_red == false // 4 cases
                        {                        
                            //Left Left Case==> Line on left, right rotation of grandfather
                            if (node == node->parent->left && node->parent == grand_parent->left)
                            {
                                rbt_rotate_right(grand_parent);
                                grand_parent->is_red = true;
                                node->parent->is_red = false;
                            }

                            //Left Right  ==> triangle < : left rotation of parent then right rotation of grand father
                            else if (node == node->parent->right && node->parent == grand_parent->left)
                            {
                                rbt_rotate_left(node->parent);
                                rbt_rotate_right(grand_parent);
                                grand_parent->is_red = true;
                                node->parent->is_red = false;
                            }

                            // Right Right  ==> line on right, left rotation of grand father
                            else if (node == node->parent->right && node->parent == grand_parent->right)
                            {
                                rbt_rotate_left(grand_parent);
                                grand_parent->is_red = true;
                                node->parent->is_red = false;
                            }

                            // Right Left Case ==> triangle >
                            else if (node == node->parent->left && node->parent == grand_parent->right)
                            {
                                rbt_rotate_right(node->parent);
                                rbt_rotate_left(grand_parent);
                                grand_parent->is_red = true;
                                node->parent->is_red = false;
                            }
                        }
                    }
               }
            }
            
            void rbt_insert(value_type const & data)
            {
                rbt_node* new_node = rbt_create_node(data);
                
                if (_root->is_null == true) //CASE 1ST NODE IN THE TREE
                {
                    new_node->is_red = false;
                    rbt_free_node(_root);
                    _root = new_node;
                    _begin->right = _root;
                    _begin->left = _root;
                    _root->parent = _begin;
                    _root->right = _end;
                    _root->left = rbt_create_null_node(_root); 
                    _end->parent = _root;
                    this->_size++;
                    return;
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
                        rbt_free_node(tmp);
                        new_node->left = rbt_create_null_node(new_node);
                        new_node->right = rbt_create_null_node(new_node);
                    }
                    else
                    {
                        tmp->parent->right = new_node;
                        new_node->left = rbt_create_null_node(new_node);
                        if (tmp->is_end == true) // pour gérer _end
                        {
                            new_node->right = _end; 
                            _end->parent = new_node;
                        }
                        else
                        {
                            rbt_free_node(tmp);
                            new_node->right = rbt_create_null_node(new_node);
                        }
                    }
                    this->_size++;
                    rbt_insert_fix_violation(new_node);
                    return;
                }
            }
 
            //Node to delete has two NULL children
            void rbt_delete_case1(rbt_node *to_delete)
            {          
                _allocator.destroy(&to_delete->content);
                rbt_free_node(to_delete->left);
                if (to_delete->right == _end)
                {
                    if (to_delete->parent->is_init == false)
                    {
                        to_delete->parent->right = _end; 
                        _end->parent = to_delete->parent;
                        rbt_free_node(to_delete);
                    }
                    else
                    {
                        _root = rbt_create_null_node( _begin);                    
                        _begin->left = _root;
                        _begin->right = _root;
                        _root->right = _end; 
                        _end->parent = _root; 
                        rbt_free_node(to_delete);
                    }  
                }              
                else 
                {
                    rbt_free_node(to_delete->right);
                    to_delete->is_red = false;
                    to_delete->is_null = true;
                    to_delete->left = NULL;
                    to_delete->right = NULL;
                }
            }
            
            //Node to delete has one NULL children
            void rbt_delete_case2(rbt_node *to_delete, rbt_node* child, rbt_node *sibling)
            {
                child->parent = to_delete->parent;
                if (to_delete == _root)
                    _root = child;
                else if (to_delete == to_delete->parent->left)
                    to_delete->parent->left = child;
                else
                    to_delete->parent->right = child;
                if (sibling == _end)
                {
                    if (child == _root)
                    {
                        _end->parent = child;
                        rbt_free_node(child->right);
                        child->right = _end;
                    }
                    else
                    {
                       rbt_node* tmp = _root->getMaxChild();
                       rbt_free_node(tmp->right);
                       tmp->right = _end;
                      _end->parent = tmp;
                    }
                }
                else
                    rbt_free_node(sibling);
                rbt_free_node(to_delete);
            }
            
            void rbt_double_black_solve(rbt_node* replacement)
            {
                rbt_node* sibling;

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
                        && sibling->is_red == true
                        && sibling->left->is_red == false
                        && sibling->right->is_red == false)
                {
                    sibling->is_red = false;
                    replacement->parent->is_red = true;
                    if (sibling == replacement->parent->right)
                        rbt_rotate_left(replacement->parent);
                    else
                        rbt_rotate_right(replacement->parent);
                    rbt_double_black_solve(replacement);
                }

                //case 3 (mirror) --> works for both mirror
                else if (replacement->parent->is_red == false
                            && sibling->is_red == false
                            && sibling->left->is_red == false
                            && sibling->right->is_red == false)
                {
                    sibling->is_red =  true;
                    rbt_double_black_solve(replacement->parent);
                }
                
                //case 4 (mirror) --> terminate case --> works for both mirror
                else if (replacement->parent->is_red == true
                            && sibling->is_red == false
                            && sibling->left->is_red == false 
                            && sibling->right->is_red == false)
                {
                    replacement->parent->is_red = false;
                    sibling->is_red =true;
                    return;
                }

                //case 5 
                else if (replacement == replacement->parent->left
                            && replacement->parent->is_red == false 
                            && sibling->is_red == false
                            && sibling->left->is_red == true
                            && sibling->right->is_red == false)
                {
                    sibling->left->is_red = false;
                    sibling->is_red = true;
                    rbt_rotate_right(sibling);
                    rbt_double_black_solve(replacement);
                }
                else if (replacement == replacement->parent->right
                           && replacement->parent->is_red == false 
                           && sibling->is_red == false
                           && sibling->left->is_red == false
                           && sibling->right->is_red == true)
                {
                    sibling->right->is_red = false;
                    sibling->is_red = true;
                    rbt_rotate_left(sibling);
                    rbt_double_black_solve(replacement);
                }

                //case 6 (mirror)--> terminate case      
                else if (replacement == replacement->parent->left
                            && sibling->is_red == false
                            && sibling->right->is_red == true)
                {
                    sibling->is_red = replacement->parent->is_red;
                    replacement->parent->is_red = false;
                    sibling->right->is_red = false;
                    rbt_rotate_left(replacement->parent);                    
                } 
                else if (replacement == replacement->parent->right
                            && sibling->is_red == false
                            && sibling->left->is_red == true)
                {
                    sibling->is_red = replacement->parent->is_red;
                    replacement->parent->is_red = false;
                    sibling->left->is_red = false;
                    rbt_rotate_right(replacement->parent);
                }

                return;
            }

            void rbt_delete_fix_violation(bool original_is_red, rbt_node* replacement)
            {
                if (original_is_red == true || replacement->is_red == true)
                {
                    replacement->is_red = false;
                    return;
                }
                else //node deleted equal to double black
                    rbt_double_black_solve(replacement);
            }

            iterator rbt_delete(const key_type& key, iterator position)
            {               
                rbt_node* to_delete = rbt_search(_root, key);
                rbt_node* replacement;

                if (to_delete->is_null == true)
                    return position;
                iterator save = position--;// sert a retrouver le bon iterator quand on change l'allocation mémoire

                //Initital steps --> convert to a 0 or 1 child case 
                if (to_delete->left->is_null == false && to_delete->right->is_null == false)
                {
                    replacement = to_delete;
                    to_delete = to_delete->right->getMinChild();
                    _allocator.destroy(&replacement->content);
                    _allocator.construct(&replacement->content, to_delete->content);
                }
                
                bool original_is_red = to_delete->is_red;

                if (to_delete->left->is_null == true && to_delete->right->is_null == true)
                {
                 //  std::cout << "\n** Case 2 null childs**" << std::endl;
                    replacement = to_delete;
                    if (to_delete->right == _end)
                        replacement = _end;
                    rbt_delete_case1(to_delete);
                }
                else if (to_delete->left->is_null == false)
                {
                //  std::cout << "\n** Case 1 left child non null**" << std::endl;
                    replacement = to_delete->left;
                    rbt_delete_case2(to_delete, to_delete->left, to_delete->right);
                }
                else if (to_delete->right->is_null == false)
                {
                //  std::cout << "\n** Case 1 right child non null**" << std::endl;
                    replacement = to_delete->right;
                    rbt_delete_case2(to_delete, to_delete->right, to_delete->left);
                }                    
                this->_size--;
                if (_root->is_null == false)
                    rbt_delete_fix_violation(original_is_red, replacement);
                return save;
            }

        /*public:

            void print_rbt() const
            {
                std::cout << std::endl;
                print_rbt(this->_root);
                return;
            }

            void print_rbt(rbt_node* node) const
            {
                if (node == NULL)
                    return;
                std::cout << std::endl;
                print_node(node);
                if (node->left && node->left->is_null == false)
                    print_rbt(node->left);
                if (node->right && node->right->is_null == false)
                    print_rbt(node->right);
            }

            void print_node(rbt_node* node) const
            {
                if (node == NULL)
                {
                    std::cout << "NULL" << std::endl;
                    return;
                }
                std::cout << std::endl;
                if (node->is_red) 
                    std::cout << RED;
                std::cout << "val : " << node->content.first << " | " << node->content.second << std::endl;
                std::cout << "is_null = " << node->is_null << " | is_init = " << node->is_init << " | is_end = " << node->is_end << std::endl;
                std::cout << "parent : ";
                if (node->parent) 
                {
                    if (node->parent == _begin)
                        std::cout << "BEGIN" << std::endl;
                    else                
                        std::cout << node->parent->content.first << std::endl;
                }
                else
                    std::cout << "NULL" << std::endl;

                std::cout << "left : ";
                if (node->left == NULL)
                    std::cout << "*NULL NODE*" << std::endl;
                else if (node->left->is_null == true) 
                    std::cout << "NULL LEAF" << std::endl;
                else if (node->left->is_null == false) 
                    std::cout << node->left->content.first << std::endl;
                
                std::cout << "right : ";
                if (node->right == NULL)
                    std::cout << "*NULL NODE*" << std::endl;
                else if (node->right->is_null == true)
                {
                    if (node->right == _end)
                        std::cout << "_end" << std::endl;
                    else
                        std::cout << "NULL LEAF" << std::endl;
                }
                else if (node->right->is_null == false) 
                    std::cout << node->right->content.first << std::endl;
                std::cout << RESET;
        } */              
    };

    // ********** NON MEMBER FUNCTIONS OVERLOARDS ********** 

    // --> Relational Operators
    
    template< class Key, class T, class Compare, class Alloc >
	bool operator==(const ft::map<Key,T,Compare,Alloc>& lhs, const ft::map<Key,T,Compare,Alloc>& rhs) 
	{
		if (lhs.size() != rhs.size()) {
			return false;
		}
		return ft::equal(lhs.begin(), lhs.end(), rhs.begin());
	}

	template< class Key, class T, class Compare, class Alloc >
	bool operator!=(ft::map<Key,T,Compare,Alloc> const& lhs, ft::map<Key,T,Compare,Alloc> const& rhs)
	{
		return !(lhs == rhs);
	}

	template< class Key, class T, class Compare, class Alloc >
	bool operator<(ft::map<Key,T,Compare,Alloc> const& lhs, ft::map<Key,T,Compare,Alloc> const& rhs)
	{
		return ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
	}

	template< class Key, class T, class Compare, class Alloc >
	bool operator<=(ft::map<Key,T,Compare,Alloc> const& lhs, ft::map<Key,T,Compare,Alloc> const& rhs)
	{
		return !(rhs < lhs);
	}

	template< class Key, class T, class Compare, class Alloc >
	bool operator>(ft::map<Key,T,Compare,Alloc> const& lhs, ft::map<Key,T,Compare,Alloc> const& rhs)
	{
		return rhs < lhs;
	}

	template< class Key, class T, class Compare, class Alloc >
	bool operator>=(ft::map<Key,T,Compare,Alloc> const& lhs, ft::map<Key,T,Compare,Alloc> const& rhs)
	{
		return !(lhs < rhs);
	}

    // --> Swap of vectors

	template< class Key, class T, class Compare, class Alloc >
	void swap(ft::map<Key,T,Compare,Alloc>& lhs, ft::map<Key,T,Compare,Alloc>& rhs)
	{
		lhs.swap(rhs);
		return;
	}
}

#endif