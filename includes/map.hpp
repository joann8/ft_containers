#ifndef map_HPP

#define map_HPP

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
				        return this->_comp(x.first, y.first);
		    	    }
		    };
        
        // *********** ATTRIBUTS ***************
        protected:
            // A revoir
            typedef rbt_node<value_type> rbt_node;
            typedef typename allocator_type::template rebind<rbt_node>::other node_allocator_type;

            key_compare _comp;
            allocator_type _allocator;
            node_allocator_type _node_allocator;
            
            value_type _val;

            rbt_node* _root;
            size_type _size;
            rbt_node* _begin;
            


        public:
             
            // ********** MEMBER FUNCTIONS ********** 

            //---> 3 Constructeurs, Destructeur et operateur= 
                       
            // 1. Empty by default , with no elements 
            explicit map (const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type()) :
            _comp(comp), _allocator(alloc), _node_allocator(), _val(ft::make_pair(key_type(), mapped_type())), _root(rbt_create_null_node(_val)), _size(0), _begin(rbt_create_null_node(_val))
            {
              //  std::cout << "Enter constructor 1" << std::endl;
                _begin->is_init = true;
                _begin->right = _root;
                _begin->left = _root;
                _begin->parent = NULL;
                _begin->is_null = false;
               // std::cout << "Exit constructor 1" << std::endl;
                return;
            }

            // 2. Range : Constructs a container with as many elements as the range [first,last), with each element constructed from its corresponding element in that range
            template <class InputIterator>
            map(InputIterator first, InputIterator last, const key_compare comp = key_compare(), const allocator_type& alloc = allocator_type()) :
            _comp(comp), _allocator(alloc), _node_allocator(), _val(ft::make_pair(key_type(), mapped_type())), _root(rbt_create_null_node(_val)), _size(0), _begin(rbt_create_null_node(_val))

            {
               // std::cout << "Enter constructor 2" << std::endl;
                _begin->is_init = true;
                _begin->right = _root;
                _begin->left = _root;
                _begin->parent = NULL;
                _begin->is_null = false;
         		this->insert(first, last);
              //  std::cout << "Exit constructor 2" << std::endl;
                return;
            }

            // 3. Copy constructor
            map(map const & src) :
            _comp(src._comp), _allocator(src._allocator), _node_allocator(src._node_allocator), _val(src._val), _root(rbt_create_null_node(_val)), _size(0), _begin(rbt_create_null_node(_val))
            {
               // std::cout << "Enter constructor 3" << std::endl;
                _begin->is_init = true;
                _begin->right = _root;
                _begin->left = _root;
                _begin->parent = NULL;
                _begin->is_null = false;
    		    for(const_iterator it = src.begin(); it != src.end(); it++)
                {
                    std::cout  << "end = " << src.end()->first << std::endl;
                    std::cout  << "it = " << it->first << std::endl;
                    this->insert(*it);
                }
               // std::cout << "Exit constructor 3" << std::endl;
            }

            virtual ~map(void)
            {              
                this->clear();
                this->rbt_free_node(_begin);
                return;
            }
            
            map & operator=(map const & src)
            {
               // std::cout << "Enter operator=" << std::endl;

                if (this != &src)
                {
                    this->clear();
                    this->_comp = src._comp;               
                    for(const_iterator it = src.begin(); it != src.end(); it++)
				    {
                        this->insert(*it);

                    }
                }
               // std::cout << "Exit operator=" << std::endl;
                return *this;
            }

            //---> Iterators

            iterator begin() 
            {
                rbt_node* tmp;

                if (_root->is_null == false)
                    tmp = _root->getMinChild();
                else
                    tmp = _begin->right;
                return iterator(tmp);
            }

            const_iterator begin() const
            {
                rbt_node* tmp;

                if (_root->is_null == false)
                    tmp = _root->getMinChild();
                else
                    tmp = _begin->right;
                return const_iterator(tmp);

            }

            iterator end() 
            {
                rbt_node* tmp;
                if (_root->is_null == false)
                    tmp = _root->getMaxChild();
                else
                    tmp = _begin;
                return iterator(tmp->right); // pas sure
            }

            const_iterator end() const
            {
                
                rbt_node* tmp;
                   
                if (_root->is_null == false)
                    tmp = _root->getMaxChild();
                else
                    tmp = _begin;
                return const_iterator(tmp->right); // pas sure
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
               return reverse_iterator(begin());
            }
            
            const_reverse_iterator rend() const
            {
               return const_reverse_iterator(begin());
            }
        
        
            //---> Elements Access
            
                       
            mapped_type& operator[] (const key_type& k)
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
                _root = rbt_create_null_node(_val);
                _root->parent = _begin;
                _size = 0;
            }

            // 3 != insert

            ft::pair<iterator, bool> insert(const value_type& val)
            {
                size_type old_size = this->_size;
                this->_size += this->rbt_insert(val); // return 1 if an element was inserted
                iterator it = iterator(rbt_search_root(val.first));
                if (this->_size == old_size)
                    return ft::make_pair<iterator,bool> (it, false);
                else
                    return ft::make_pair<iterator, bool> (it,true);
            }

            iterator insert(iterator position, const value_type& val)
            {
                //cense accelerer--> a faire?
                (void)position;
                insert(val);
                return iterator(rbt_search_root(val.first));
            }

            template <class InputIterator>
            void insert(InputIterator first, InputIterator last)
            {
                // garde fou pour la range?
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
                if (tmp)
                {
                   if (rbt_search_root(tmp->content.first))
                    {
                       // std::cout << "\ncontent found!" << std::endl;
                      //  std::cout << "to delete = " << tmp->content.first << std::endl;
                        rbt_delete(tmp->content.first);
                    }
                }
            }

            size_type erase(const key_type& k)
            {
                return rbt_delete(k);
            }

            void erase (iterator first, iterator last)
            {
                std::cout << "INIT = " << first->first << std::endl;

                while (first != last)
                {

                    std::cout << "----start while" << std::endl;
                    iterator to_delete = first;
                    std::cout << "first = " << first->first << std::endl;

                    first++;
                    std::cout << "first ++ = " << first->first << std::endl;

                    std::cout << "to_delete = " << to_delete->first << std::endl;
                    erase(to_delete);
                                        std::cout << "next" << std::endl;

                    std::cout << "to_delete = " << to_delete->first << std::endl;
                    std::cout << "first = " << first->first << std::endl;
                    std::cout << "---end while" << std::endl;
                }
            }
            
            void swap (map& src) // a modifier si attributs changent!!!
            {
                key_compare tmp_comp = src._comp;
                allocator_type tmp_allocator = src._allocator;
                node_allocator_type tmp_node_allocator = src._node_allocator;
                rbt_node* tmp_root =  src._root;
                size_type tmp_size = src._size;

                src._comp = _comp;
                src._allocator = _allocator;
                src._node_allocator = _node_allocator;
                src._root = _root;
                src._size = _size;
              
                _comp = tmp_comp;
                _allocator = tmp_allocator;
                _node_allocator = tmp_node_allocator;
                _root = tmp_root;
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
                if (tmp != NULL)
                    return (iterator(tmp));
                else
                    return end();
            }
            
            const_iterator find(const key_type& k) const
            {
                rbt_node* tmp = rbt_search_root(k);
                if (tmp != NULL)
                    return (const_iterator(tmp));
                else
                    return end();             
            }

            size_type count(const key_type& k) const
            {
                rbt_node* tmp = rbt_search_root(k);
                if (tmp != NULL)
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
                this->_allocator;
            }

        
        // ADDITIONAL FUNCTION

        protected:
            
            rbt_node* rbt_create_null_node(value_type const & data)
            {
             //   std::cout << " *** Enter rbt_create_null_node " << std::endl;

                rbt_node* new_node = _node_allocator.allocate(1);
               // _allocator.construct(&new_node->content, data);
                (void)data;
                //_node_allocator.construct(new_node, rbt_node());
                new_node->left = NULL;
                new_node->right = NULL;
                new_node->parent = NULL;
                new_node->is_red = false;
                new_node->is_null = true;
                new_node->is_init = false;
            //    std::cout << " *** Exit rbt_create_null_node " << std::endl;

                return new_node;
            }

            rbt_node* rbt_create_node(value_type const & data)
            {
              //  std::cout << " *** Enter rbt_create_node" << std::endl;

                rbt_node* new_node = _node_allocator.allocate(1);
                //_node_allocator.construct(new_node, rbt_node());
                _allocator.construct(&new_node->content, data);
                new_node->left = rbt_create_null_node(data);
                new_node->left->parent = new_node;
                new_node->right = rbt_create_null_node(data);
                new_node->right->parent = new_node;
                new_node->parent = NULL;
                new_node->is_null = false;
                new_node->is_init = false;
                new_node->is_red = true;
            //    std::cout << " *** Exit rbt_create_node "<< std::endl;


                return new_node;
            }

            void rbt_free_node(rbt_node *node)
            {
                
           //     std::cout << " Enter rbt_free node" << std::endl;

               /* if (node && node->is_null == false)
                    _node_allocator.destroy(node); //node->->content?;
                */
                _allocator.destroy(&node->content);
                _node_allocator.deallocate(node, 1);
              //  std::cout << "Exit rbt_free node" << std::endl;
            }

            void rbt_convert_to_null(rbt_node *node)
            {
                //_node_allocator.destroy(node);
                _allocator.destroy(&node->content);
                rbt_free_node(node->left);
                rbt_free_node(node->right);
                node->is_red = false;
                node->is_null = true;
                node->left = NULL;
                node->right = NULL;
            }

            void rbt_clear_tree(rbt_node* node)
            {
                if (node->left)
                    rbt_clear_tree(node->left);
                if (node->right) // node->right != end ?
                    rbt_clear_tree(node->right);
                this->rbt_free_node(node);
            }

            rbt_node* rbt_search(rbt_node* src, const Key& key) const
            {
                if (src && src->is_null == false) 
                {
                    if (this->_comp(key, src->content.first) == true)
                        return (rbt_search(src->left, key));
                    else if (this->_comp(src->content.first, key) == true)
                        return (rbt_search(src->right, key));
                    else
                        return (src);
                }
                return (NULL);
            }

            rbt_node* rbt_search_root(const Key& key) const
            {
                return rbt_search(_root, key);
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
           
            void rbt_insert_fix_violation(rbt_node *node) // !! ROOT A SUIVRE
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
                                //std::cout << "\n***** LEFT LEFT CASE *** " << std::endl;

                                rbt_rotate_right(grand_parent);
                                grand_parent->is_red = true;
                                node->parent->is_red = false;
                            }

                            //Left Right  ==> triangle < : left rotation of parent then right rotation of grand father
                            else if (node == node->parent->right && node->parent == grand_parent->left)
                            {
                               // std::cout << "\n***** LEFT RIGHT *** " << std::endl;                             
                                rbt_rotate_left(node->parent);
                                rbt_rotate_right(grand_parent);
                                grand_parent->is_red = true;
                                node->parent->is_red = false;
                            }

                            // Right Right  ==> line on right, left rotation of grand father
                            else if (node == node->parent->right && node->parent == grand_parent->right)
                            {
                               // std::cout << "\n***** RIGHT RIGHTCASE *** " << std::endl;
                                rbt_rotate_left(grand_parent);
                                grand_parent->is_red = true;
                                node->parent->is_red = false;
                            }

                            // Right Left Case ==> triangle >
                            else if (node == node->parent->left && node->parent == grand_parent->right)
                            {
                               // std::cout << "\n***** RIGHT LEFT CASE *** " << std::endl;
                                rbt_rotate_right(node->parent);
                                rbt_rotate_left(grand_parent);
                                grand_parent->is_red = true;
                                node->parent->is_red = false;
                            }
                        }
                    }
               }
            }
            
            size_type rbt_insert(value_type const & data)
            {
              //  std::cout << "STATUS TREE INIT: " << std::endl;
              //  print_rbt();
                
                rbt_node* new_node = rbt_create_node(data);
                
                if (_root->is_null == true)
                {
                    new_node->is_red = false;
                    rbt_free_node(_root);
                    _root = new_node;
                    _begin->right = _root;
                    _root->parent = _begin;
                    //std::cout << "\nSTATUS TREE FINAL (root): " << std::endl;
                    //print_rbt();
                    return(1);
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
                         //   std::cout << "\nSTATUS TREE FINAL (already exist): " << std::endl;
                         //   print_rbt();
                            return (0);
                        }
                    }
                    if (is_left_child == 1)
                    {
                        tmp->parent->left = new_node;
                       // new_node->parent = tmp;
                    }
                    else
                    {
                        tmp->parent->right = new_node;
                       // new_node->parent = tmp->parent;
                    }
                    rbt_free_node(tmp);
                    //std::cout << "\nSTATUS TREE BEFORE FIX: " << std::endl;
                    //print_rbt();
                    rbt_insert_fix_violation(new_node);
                 //   std::cout << "\nSTATUS TREE FINAL (after insert fix): " << std::endl;
                 //   print_rbt();
                 //   std::cout << std::endl;
                    return(1);
                }
            }

 
            //Node to delete has two NULL children
            void rbt_delete_case1(rbt_node *to_delete, rbt_node *child)
            {
                (void)child;
              /*  if (to_delete ==_root)
                {
                    _root = rbt_create_null_node(_val);;
                }*/
                rbt_convert_to_null(to_delete);
                /*
                else if (to_delete == to_delete->parent->left)
                {
                    to_delete->parent->left = child;
                    child->parent = to_delete->parent;
                }
                else
                {
                    to_delete->parent->right = child;
                    child->parent = to_delete->parent;
                }*/
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
                child->parent = to_delete->parent;
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
                        rbt_rotate_right(replacement->parent); // ajout, a verifier
                    rbt_double_black_solve(replacement);
                }

                //case 3 (mirror)
                else if (replacement->parent->is_red == false
                            && sibling->is_red == false
                            && sibling->left->is_red == false
                            && sibling->right->is_red == false)
                {
                    //works for both mirror
                    sibling->is_red =  true;
                    rbt_double_black_solve(replacement->parent);
                }
                
                //case 4 (mirror) --> terminate case
                else if (replacement->parent->is_red == true
                            && sibling->is_red == false
                            && sibling->left->is_red == false 
                            && sibling->right->is_red == false)
                {
                    //works for both mirror
                    replacement->parent->is_red = false;
                    sibling->is_red =true;
                    return;
                }

                //case 5   // miror ? TBC
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
                    //
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
                {
                    rbt_double_black_solve(replacement);
                }
            }

            size_type rbt_delete(const key_type& key)
            {

            //    std::cout << "\nSTATUS TREE INIT DELETE: " << std::endl;
            //    std::cout << "root = " << _root->content.first << std::endl;
            //    print_rbt();
                
                rbt_node* to_delete = rbt_search(_root, key);
                rbt_node* replacement;

                if (to_delete == NULL)
                {
                //    std::cout << "-------> exit rbt delete 0" << std::endl;
                    return 0;
                }
                
               // std::cout << "to_delete = " << to_delete->content.first << std::endl;

                //Initital steps --> convert to a 0 or 1 child case 
                if (to_delete->left->is_null == false && to_delete->right->is_null == false)
                {
                 //   std::cout << "\n** Case 2  non null childs --- > conversion **" << std::endl;

                    replacement = to_delete;
                    to_delete = to_delete->right->getMinChild();

                   _allocator.destroy(&replacement->content);
                    _allocator.construct(&replacement->content, to_delete->content);
                }
                
                bool original_is_red = to_delete->is_red;

                if (to_delete->left->is_null == true && to_delete->right->is_null == true)
                {
                //    std::cout << "\n** Case 2 null childs**" << std::endl;
                    replacement = to_delete;
                    rbt_delete_case1(to_delete, to_delete->right);
       //             rbt_free_node(to_delete->left);

                }
                else if (to_delete->left->is_null == false)
                {
                //    std::cout << "\n** Case 1 left child non null**" << std::endl;
                    replacement = to_delete->left;
                    rbt_delete_case2(to_delete, to_delete->left, to_delete->right);
                  //  rbt_free_node(to_delete->right);

                }
                else if (to_delete->right->is_null == false)
                {
                //    std::cout << "\n** Case 1 right child non null**" << std::endl;
                    replacement = to_delete->right;
                    rbt_delete_case2(to_delete, to_delete->right, to_delete->left);
                   // rbt_free_node(to_delete->left);
                }
               // replacement = to_delete;

                //rbt_convert_to_null(to_delete);
                this->_size--;
             //   std::cout << "replacement = " << replacement->content.first << std::endl;
             //   std::cout << "STATUS BEFORE FIX " << std::endl;
             //   print_rbt();
                
                if (_root->is_null == false)
                    rbt_delete_fix_violation(original_is_red, replacement); 
              //  std::cout << "-------> exit rbt delete with 1" << std::endl;
                return 1;
            }

        
        public:

        void print_rbt() const
		{
			//std::cout << "size = " << this->size() << std::endl;
			std::cout << std::endl;
			print_rbt(this->_root);
			return;
		}

		void print_rbt(rbt_node* node) const
		{
			if (node == NULL) {
				return;
			}
			std::cout << std::endl;
			if (node->is_red) 
				std::cout << RED;
			
			std::cout << "val : " << node->content.first << std::endl;
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
				std::cout << "NULL LEAF" << std::endl;
			else if (node->right->is_null == false) 
				std::cout << node->right->content.first << std::endl;
			
			std::cout << RESET;
            if (node->left && node->left->is_null == false)
			    print_rbt(node->left);
            if (node->right && node->right->is_null == false)
                print_rbt(node->right);
        }
                
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