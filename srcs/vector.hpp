#ifndef VECTOR_HPP

#define VECTOR_HPP

#include "iterator_reverse.hpp"
#include "iterator_traits.hpp"
#include "iterator_vector.hpp"
#include "comparison.hpp"

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
            _allocator(alloc), _capacity(0), _size(0), _array(NULL)
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
            _allocator(alloc), _capacity(0), _size(0), _array(NULL)
            {
                size_type n = 0;
                for (pointer it = first; it != last; it++)
                    n++;
                this->_size = n;
                this->_capacity = n;
                this->_array = this->_allocator.allocate(this->_capacity);

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
                for (size_type i = 0; i < src._size; i++) 
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
                if (this != &src)
                {
                    this->clear();
                    if (this->_capacity < src._size)
                    {
                        this->_allocator.deaollocate(this->_array, this->_capacity);
                        this->_capacity = src._capacity;
                        this->_array = this->_allocator.allocate(this->_capacity);
                    }
                    this->_size = src._size;
                    for (size_type i = 0; i < src._size; i++) //++i?
                    {   
                        this->_allocator.construct(this->_array + i, src._array[i]);
                    }
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

            reverse_iterator rbegin()
            {
                return reverse_iterator(this->_array + this->_size);
            }
            
            reverse_iterator_const rbegin() 
            {
                return reverse_iterator_const(this->_array + this->_size);
            }
            
            reverse_iterator rend() 
            {
                return reverse_iterator(this->_array);
            }
            
            reverse_iterator_const rend()
            {
                return reverse_iterator_const(this->_array);
            }
        
            //---> Elements Access
            
            reference at(size_type n)      
            {
                if (n >= this_size || n < 0)
                    throw std::out_of_range("vector : pbm with n in at");
                return *(this->_array + n);
            }
            
            const_reference at(size_type n) const
            { 
                if (n >= this_size || n < 0)
                    throw std::out_of_range("vector : pbm with n in const_at");
                return *(this->_array + n)
            }
            
            reference operator[] (size_type n) // no check is performed according to def 
            {
                return *(this->_array + n);
            }
            
            const_reference operator[] (size_type n) const :// no check is performed according to def
            { 
                return *(this->_array + n)
            }
 
            reference front(size_type n)      
            {
                return *this->_array;
            }
            
            const_reference front() const
            { 
                return *this->_array;
            }

            reference back()      
            {
                return *(this->_array + this->_size - 1);
            }
            
            const_reference front() const
            { 
                return *(this->_array + this->_size - 1);
            }

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
                return this->_allocator.max_size();
            }
            
            void resize(size_type n, value_type val = value_type())
            {
                ifif (n < this->_size)
                    this->_size = n;
                else
                    this->insert(this->end(), n - this->_size, val);
                return;
            }

            size_type capacity(void) const
            {
                return this->_capacity;
            }
            
            void reserve(size_type n) 
            {
                if (n > this->max_size())
                    throw std::length_error("vector : pbm with n in reserve"); 
                if (n <= this->_capacity)
                    return;
                pointer old = this->_array;
                this->_array = this->_allocator.allocate(n);
                for (pointer it = this->_array, old_it = old, old_ite = old_it + this->_size;
                        old_it != old_ite; it++, old_it++)
                {
                    this->_allocator.construct(it, *old_it);
                    this->_allocator.destroy(old_it);
                }
                this->_allocator.deallocate(old, this->_capacity);
                this->_capacity = n;
                
            }

            // --> Modifiers

            template <class InputIterator>
            void assign(InputIterator first, InputIterator last)
            {
                this->clear();
                size_type n = 0;
                for (pointer it = first; it != last; it++)
                    n++;
                this->_size = n;
                this->reserve(n);
                pointer it = this->_array;
                while (first != last) //pbm si first < last?
                {
                    this->_allocator.construct(it, *first);
                    first++;
                    it++;
                }
                return;
            }

            void assign(size_type n, const value_type& val)
            {
                this->clear();
                this->_size = n;
                this->reserve(n);
                for(size_type i = 0; i < n; i++)  
                {
                    this->_allocator.construct(this->_array + i, val);
                }
                return;
            }

            void clear()
            {
                for (size_type i = 0, size_type size = this->_size; i < size; i++) //++i?
                {
                    this->_allocator.destroy(this->_array + i);
                }
                this->_size = 0;
                return;
            }

            iterator_vector insert(iterator_vector position, const val_type&val)
            {
                if (this->_capacity == 0)
                    this->reserve(1);
                else if (this->_capacity == this->_size)
                    this->reserve(this->_capacity * 2); //on double la capacité pour ne pas reallouer à chaque ajouter
                
                difference_type elmt = position.pointer - this->_array;
                for(pointer it = this->_array + this->_size, ite = this->_array + elmt; it != ite; it--) 
                {
                    this->_allocator.construct(it, *(it - 1));
                    this->_allocator.destroy(it - 1);
                }
                this->_allocator.construct(this->_array + elmt, val);
                this->_size++;
                return (this->_array + elmt);
            }
            
            void insert(iterator_vector position, size_type n, const val_type&val)
            {
                if (n == 0)
                    return;
                if (this->size + n > this->_capacity)
                {
                    if (this->_capacity * 2 < this->_size + n) // cas 0 fonctionne aussi
                        this->reserve(this->_size + n);
                     else
                        this->reserve((this->_capacity * 2);
                }

                difference_type elmt = position.pointer - this->_array;

                for(pointer it = this->_array + this->_size + n - 1, ite = this->_array + elmt + n - 1; it != ite; it--) 
                {
                    this->_allocator.construct(it, *(it - n));
                    this->_allocator.destroy(it - n);
                }
                this->_size += n;
                while (n > 0)
                {
                    this->_allocator.construct(this->_array + elmt - 1 + n, val);
                    n--;
                }
                return;
            }
            
            template<class InputIterator>
            void insert(iterator_vector position, InputIterator first, InputIterator last)
            {
                if (first == last)
                    return;

                size_type n = 0;
                for (pointer it = first; it != last; it++)
                    n++;
                if (this->size + n > this->_capacity)
                {
                    if (this->_capacity * 2 < this->_size + n) // cas 0 fonctionne aussi
                        this->reserve(this->_size + n);
                     else
                        this->reserve((this->_capacity * 2);
                }

                difference_type elmt = position.pointer - this->_array;

                for(pointer it = this->_array + this->_size + n - 1, ite = this->_array + elmt + n - 1; it != ite; it--) 
                {
                    this->_allocator.construct(it, *(it - n));
                    this->_allocator.destroy(it - n);
                }
                this->_size += n;
                while (n > 0)
                {
                    last--;
                    this->_allocator.construct(this->_array + elmt - 1 + n, *last);
                    n--;
                }
                return;
            }
            
            iterator_vector erase(iterator_vector position)
            {
                this->_allocator.destroy(position.pointer);
                for(pointer it = position.pointer, ite = this->end().pointer - 1; it != ite; it++) //++it?
                {
                    this->_allocator.construct(it, *(it + 1));
                    this->_allocator.destroy(it + 1);
                }
                this->_size--;
                return position;
            }

            iterator_vector erase(iterator_vector first, iterator_vector last)
            {  
                if (first == last)
                    return first;
                size_type n = 0;
                for (pointer it = first.pointer; it != last.pointer; it++)
                    this->_allocator.destroy(it);
                for(pointer it = first.pointer, ite = this->end().pointer - n; it != ite; it++) //++it?
                {
                    this->_allocator.construct(it, *(it + n));
                    this->_allocator.destroy(it + n);
                }
                this->_size -= n;
                return first;
            }

            void push_back(const value_type& val)
            {
                if (this->_capacity == 0)
                    this->reserve(1);
                else if (this->_capacity == this->_size)
                    this->reserve(this->_capacity * 2); //on double la capacité pour ne pas reallouer à chaque ajout
                this->_allocator.construct(this->_array + this->_size, val);
                this->_size++;
            }

            void pop_back()
            {
                this->_size--;
                this->_allocator.destroy(this->_array + this->_size);
            }
            
            void swap (vector& src)
            {
                allocator_type tmp_allocator = src._allocator;
                size_type tmp_size = src._size;
                size_type tmp_capacity = src._capacity;
                pointer tmp_array = src._array;
                
                src._allocator = _allocator;
                src._size = _size;
                src._capacity = _capacity;
                src._array = _array;

                _allocator = tmp_allocator;
                _size = tmp_size;
                _capacity = tmp_capacity;
                _array = tmp_array;                
            }

            //---> Allocator
            
            allocator_type get_allocator() const
            {
                this->_allocator;
            }
    };
    
    // ********** NON MEMBER FUNCTIONS OVERLOARDS ********** 

    // --> Relational Operators

    template <class T, class Alloc>
    bool operator==(vector<T, Alloc> const & lhs, vector<T, Alloc> const & rhs)
    {
        if (lhs.size !=  rhs.size())
            return false;
        return ft::equal(lhs.begin(), lhs.end(), rhs.begin());
    }

    template <class T, class Alloc>
    bool operator!=(vector<T, Alloc> const & lhs, vector<T, Alloc> const & rhs)
    {
        return (!(lhs == rhs));
    }

    template <class T, class Alloc>
    bool operator<(vector<T, Alloc> const & lhs, vector<T, Alloc> const & rhs)
    {
        return ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
    }

    template <class T, class Alloc>
    bool operator>(vector<T, Alloc> const & lhs, vector<T, Alloc> const & rhs)
    {
        return rhs < lhs;
    }

    template <class T, class Alloc>
    bool operator<=(vector<T, Alloc> const & lhs, vector<T, Alloc> const & rhs)
    {
        return !(rhs < lhs);
    }

    template <class T, class Alloc>
    bool operator>=(vector<T, Alloc> const & lhs, vector<T, Alloc> const & rhs)
    {
        return !(lhs < rhs);
    } 
       
    // --> Swap of vectors

    template <class T, class Alloc>
    void swap(vector<T, Alloc> const & lhs, vector<T, Alloc> const & rhs)
    {
        lhs.swap(rhs);
        return;
    } 
}

#endif