#ifndef map_HPP

#define map_HPP

#include "iterator_reverse.hpp"
#include "iterator_traits.hpp"
#include "iterator_map.hpp"
#include "comparison.hpp"
#include "enable_if.hpp"
#include "pair.hpp"

namespace ft
{
    //LESS A FAIRE
    template<class Key, class T, class Compare = less<Key>, class Alloc = std::allocator<ft::pair<const Key, T> > >
    //Alloc corresponds to the type of allocator object that is used to define the storage location model
    
    class map
    {
        // *********** MEMBERS TYPES **************
        public: 
            typedef Key key_type;
            typedef T mapped_type;
            typedef ft::pair<const key_type, mapped_type> value_type;
            typedef Compare key_compare;

           // typedef value_compare  A A FAIRE

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

        
        // *********** ATTRIBUTS ***************
        protected:
            allocator_type _allocator;
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
               // A FAIRE
            }

            const_iterator begin() const
            {
               // A FAIRE
            }

            iterator end()
            {
               // A FAIRE
            }

            const_iterator end() const
            {
               // A FAIRE
            }

            reverse_iterator rbegin()
            {
               // A FAIRE
            }
            
            const_reverse_iterator rbegin() const
            {
               // A FAIRE
            }
            
            reverse_iterator rend() 
            {
               // A FAIRE
            }
            
            const_reverse_iterator rend() const
            {
               // A FAIRE
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
                // A FAIRE
            }

            size_type size() const
            {
                // A FAIRE
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