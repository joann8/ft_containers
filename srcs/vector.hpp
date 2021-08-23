#ifndef VECTOR_HPP

#define VECTOR_HPP

#include "iterator_reverse.hpp"
#include "iterator_traits.hpp"
#include "iterator_vector.hpp"

namespace ft
{
    template<class T, class Alloc = std::allocator<T>>
    //Alloc corresponds to the type of allocator object that is used to define the storage location model
    
    class vector
    {
        // *********** MEMBERS TYPES **************
        typedef T value_type;
        typedef Alloc allocator_type;
        typedef typename allocator_type::reference reference;
        typedef typename allocator_type::const_reference const_reference;
        typedef typename allocator_type::pointer pointer;
        typedef typename allocator_type::const_pointer const_pointer;
        class iterator_vector; // typedef typename vector pour plus de clarté?
        class iterator_vector_const; // typedef typename vector_const pour plus de clarté?
        typedef typename ft::reverse_iterator<iterator_vector> reverse_iterator;
        typedef typename ft::reverse_iterator<iterator_vector_const> reverse_iterator_const;
        typedef typdename ft::iterator_traits<iterator_vector>::difference_type difference_type;
        typedef std::size_t size_type;

        
        // *********** ATTRIBUTS ***************
        protected:
            allocator_type _allocator;
            size_type _capacity;
            size_type _size;
            pointer _array;

        public:
             
            // ********** MEMBER FUNCTIONS ********** 

            //---> 4 Constructeurs, Destructeur et operateur= 
            
            // 1. Default : constructs an empty container with no elmt
            // (explicit prevents the compiler from performing implicit conversions)
            explicit vector(const allocator_type & alloc = allocator_type()) :
            _allocator(alloc), _capacity(0), _size(0), _array(this._allocator.allocate(this->_capacity))
            {
                return;
            }
        
            // 2. Fill : constructs a container with n elmts, each elmt is a copy of val
            explicit vector(size_type n, const value_type & val = value_type(), const allocator_type & alloc = allocator_type()) :
            _allocator(alloc), _capacity(n), _size(n), _array(this._allocator.allocate(this->_capacity))
            {
                for (size_type i = 0; i < n; i++)
                {
                    this->_allocator.construct(this->_array + i, val);
                }
                return;
            }

            // 3. Range : constructs a container with as many elmts as the ranfe [first, last)
            // (each elmt constructed from its corresponding elmt in that range, same order)
           template <class InputOperator>
           vector(InputOperator first, InputOperator last, const allocator_type & alloc = allocator_type()) :
            _allocator(alloc), _capacity(iteration_size(first, last), _size(iteration_size(first, last), _array(this._allocator.allocate(this->_capacity))
            {
                pointer it = this->_array;
                while (first != last)
                {
                    this->_allocator.construct(it, *first);
                    it++;
                    first++;
                }
                return;
                // !!! Trow an exception when the range is not valid???
            }
           
            // 4.  Copy 
            vector(vector const & src) :
            _allocator(src._allocator), _capacity(src._capacity), _size(src._size), _array(this._allocator.allocate(this->_capacity))
            {
                for (size_type i = 0; i < src._size; i++) //++i?
                {
                    this->_allocator.construct(this->_array + i, src._array[i]);
                }
            }

            virtual ~vector(void)
            {
                this->clear();
                this->_allocator.deallocate(this->_array, this->_capacity);
            }
            
            vector & operator=(vector const & src)
            {
                this->clear();
                if (this->_capacity < src._size)
                {
                        this->_allocator.deaollocate(this->_array, this->_capacity);
                        this->_capacity = src._capacity;
                        this->_array = this->_allocator.allocate(this->_capacity);
                }
                this->_size = src._size;
                for (size_type i = 0; i < src._size; i++)
                {   
                    this->_allocator.construct(this->_array + i, src._array[i]);
                }
                return *this;
            }

            //---> Iterators

            iterator_vector begin()
            {
                return iterator_vector(this->_array);
            }

            iterator_vector_const begin()
            {
                return iterator_vector_const(this->_array);
            }

            iterator_vector end()
            {
                return iterator_vector(this->_array + this->_size);
            }

            iterator_vector_const end()
            {
                return iterator_vector_const(this->_array + this->_size);
            }

            reverse_iterator rbegin() // A inverser avec rend ?? 
            {
                return reverse_iterator(this->_array);
            }
            
            reverse_iterator_const rbegin() // A inverser avec rend ?? 
            {
                return reverse_iterator_const(this->_array);
            }
            
            reverse_iterator rend() // A inverser avec rbegin ?? 
            {
                return reverse_iterator(this->_array + this->_size);
            }
            
            reverse_iterator_const rend() // A inverser avec rbegin ?? 
            {
                return reverse_iterator_const(this->_array + this->_size);
            }
        
            //---> Elements Access
            //at
            //operator[]
            //front
            //back

            //---> Capacity

            bool empty() const
            {
                return (this->_size <= 0? true : false);
            }

            size_type size() const
            {
                return this->_size;
            }

            size_type max_size() const
            {
                return this->allocator.max_size();
            }
            
            void resize(size_type n, value_type val = value_type())
            {
                if (n < this->_size)
                    this->_size = n;
                else
                    this->insert(this->end(), n - this->_size, val);
                return;
            }

            size_type capacity(void) const
            {
                return this->_capacity;
            }
            
            //reserve A FAIRE

            // --> Modifiers

            void clear()
            {
                for (size_type i = 0, size_type size = this->_size; i < size; i++) //++i?
                {
                    this->_allocator.destroy(this->_array + i);
                }
                this->_size = 0;
                return;
            }
            //insert
            //erase
            //push_back
            //pop_back
            //swap

            //---> Allocator
            //get_allocator
    };
    
    // ********** NON MEMBER FUNCTIONS OVERLOARDS ********** 

    // --> Relational Operators

    // --> Swap of vectors


}

#endif