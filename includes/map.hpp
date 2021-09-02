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
            node_allocator_type _allocator;
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
    };
}

#endif