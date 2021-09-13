#ifndef VECTOR_HPP

#define VECTOR_HPP

#include "iterator_reverse.hpp"
#include "iterator_traits.hpp"
#include "iterator_vector.hpp"
#include "comparison.hpp"
#include "enable_if.hpp"
#include <iostream>
#include <sstream> //pour exceptions messages

namespace ft
{
    template<class T, class Alloc = std::allocator<T> >
    //Alloc corresponds to the type of allocator object that is used to define the storage location model
    
    class vector
    {
        // *********** MEMBERS TYPES **************
        public: 
            typedef T value_type;
            typedef Alloc allocator_type;
            typedef typename allocator_type::reference reference;
            typedef typename allocator_type::const_reference const_reference;
            typedef typename allocator_type::pointer pointer;
            typedef typename allocator_type::const_pointer const_pointer;
        
            typedef iterator_vector<T> iterator;
            typedef iterator_vector_const<T> const_iterator;
        // class iterator_vector; // typedef typename vector pour plus de clarté?
        //class iterator_vector_const; // typedef typename vector_const pour plus de clarté?
       
            typedef typename ft::reverse_iterator<iterator> reverse_iterator;
            typedef typename ft::reverse_iterator<const_iterator> const_reverse_iterator;
           // typedef typename ft::iterator_traits<iterator>::difference_type difference_type;
            typedef std::ptrdiff_t difference_type;
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
            _allocator(alloc), _capacity(n), _size(n), _array(this->_allocator.allocate(this->_capacity))
            {
                for (size_type i = 0; i < n; i++)
                {
                    this->_allocator.construct(this->_array + i, val);
                }
                return;
            }

            // 3. Range : constructs a container with as many elmts as the range [first, last)
            // (each elmt constructed from its corresponding elmt in that range, same order)
           template <class InputOperator>
           vector(InputOperator first, InputOperator last, const allocator_type & alloc = allocator_type(),
                    typename ft::enable_if<!ft::is_integral<InputOperator>::value, bool>::type =true) :
            _allocator(alloc), _capacity(0), _size(0), _array(NULL)
            {
                size_type n = 0;
                for (InputOperator it = first; it != last; it++)
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
            }
           
            // 4.  Copy 
            vector(vector const & src) :
            _allocator(src._allocator), _capacity(src._size), _size(src._size), _array(this->_allocator.allocate(this->_capacity))
            {
                for (size_type i = 0, size = src._size; i < size; i++)
                {
                    this->_allocator.construct(this->_array + i, src._array[i]);
                }
                return;
            }

            virtual ~vector(void)
            {
                this->clear();
                if (_capacity != 0)
                    this->_allocator.deallocate(this->_array, this->_capacity);
            }
            
            vector & operator=(vector const & src)
            {
                if (this != &src)
                {
                    this->clear();
                    if (this->_capacity < src._size)
                    {
                        this->_allocator.deallocate(this->_array, this->_capacity);
                        this->_capacity = src._size;
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

            iterator begin()
            {
                return iterator(this->_array);
            }

            const_iterator begin() const
            {
                return const_iterator(this->_array);
            }

            iterator end()
            {
                return iterator(this->_array + this->_size);
            }

            const_iterator end() const
            {
                return const_iterator(this->_array + this->_size);
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
            
            reference operator[] (size_type n) // no check is performed according to def 
            {
                return this->_array[n];
            }
            
            const_reference operator[] (size_type n) const // no check is performed according to def
            { 
                return this->_array[n];
            }

            reference at(size_type n)      
            {
                if (n >= this->_size || n < 0)
                {
                    std::ostringstream oss;
				    oss << "vector::_M_range_check: __n (which is " << n << ") >= this->size() (which is " << this->_size << ")";
                    throw std::out_of_range(oss.str());
                }
                return this->_array[n];
            }
            
            const_reference at(size_type n) const
            { 
                if (n >= this->_size || n < 0)
                {
                    std::ostringstream oss;
				    oss << "vector::_M_range_check: __n (which is " << n << ") >= this->size() (which is s" << this->_size << ")";
                    throw std::out_of_range(oss.str());
                }
                return this->_array[n];
            }
 
            reference front()      
            {
                return this->_array[0];
            }
            
            const_reference front() const
            { 
                return this->_array[0];
            }

            reference back()      
            {
                if (_size == 0)
                    return _array[0];
                else
                    return _array[this->_size - 1];
            }
            
            const_reference back() const
            { 
                if (_size == 0)
                    return _array[0];
                else
                   return _array[this->_size - 1];
            }

            //---> Capacity

            bool empty() const
            {
                return (this->_size == 0? true : false);
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
                if (n < this->_size)
                {
                    this->_size = n;
                }
                else
                {
                
                    this->insert(this->end(), n - this->_size, val);
                }
                return;
            }

            size_type capacity(void) const
            {
                return this->_capacity;
            }
            
            void reserve(size_type n) 
            {
                if (n > this->max_size())
                    throw std::length_error("***vector exception - reserve : n over max size***"); 
                if (n <= this->_capacity)
                    return;

                pointer ptr_new = _allocator.allocate(n);
                for (size_type i = 0; i < _size; i++)
                {
                    _allocator.construct(ptr_new + i, _array[i]);
                    _allocator.destroy(_array + i);
                }
                if (_capacity != 0)
                    _allocator.deallocate(_array, _capacity);
                _capacity = n;
                _array = ptr_new; 
            }

            // --> Modifiers

            template <class InputIterator>
            void assign(InputIterator first, InputIterator last,
                         typename ft::enable_if<!ft::is_integral<InputIterator>::value, bool>::type =true)
            {
                this->clear();
                size_type n = 0;
                for (InputIterator it = first; it != last; it++)
                    n++;
                this->_size = n;
                if (this->_capacity < n)
                {
				    this->_allocator.deallocate(this->_array, this->_capacity);
				    this->_capacity = n;
				    this->_array = this->_allocator.allocate(this->_capacity);
			    }
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
                if (this->_capacity < n)
                {
				    this->_allocator.deallocate(this->_array, this->_capacity);
				    this->_capacity = n;
				    this->_array = this->_allocator.allocate(this->_capacity);
			    }
                for(size_type i = 0; i < n; i++)  
                {
                    this->_allocator.construct(this->_array + i, val);
                }
                return;
            }

            void clear()
            {
                if (this->empty())
                    return;
                for (size_type i = 0, size = this->_size; i < size; i++) //++i?
                {
                    this->_allocator.destroy(this->_array + i);
                }
                this->_size = 0;
                return;
            }

            iterator insert(iterator position, const value_type& val)
            {
                difference_type elmt = position._ptr_current - this->_array; // important car apres reserve, iterator plus bon!!
                this->insert(position, 1, val);
                return iterator(this->begin() + elmt);
            }
            
            void insert(iterator position, size_type n, const value_type& val)
            {
                difference_type elmt = position._ptr_current - this->_array; // important car apres reserve, iterator plus bon!!

                if (n == 0)
                    return;
                if (this->_size + n > this->_size * 2)
                    this->reserve(this->_size + n);
                else if (this->_size + n > this->_capacity)
                    this->reserve(this->_size * 2);

                for(pointer it = this->_array + this->_size + n - 1, ite = this->_array + elmt + n - 1; it != ite; --it) 
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
            void insert(iterator position, InputIterator first, InputIterator last,
                            typename ft::enable_if<!ft::is_integral<InputIterator>::value, bool>::type = true) 
            {
                if (first == last)
                    return;
                
                difference_type elmt = position._ptr_current - this->_array;

                size_type n = 0;
                for (InputIterator it = first; it != last; it++)
                    n++;
                if (this->_size + n > this->_size * 2)
                    this->reserve(this->_size + n);
                else if (this->_size + n > this->_capacity)
                    this->reserve(this->_size * 2);

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
            
            iterator erase(iterator position)
            {
                if (this->empty() || position == this->end())
                    return this->end();
                this->_allocator.destroy(position._ptr_current);
                for(pointer it = position._ptr_current, ite = this->end()._ptr_current - 1; it != ite; it++) //++it?
                {
                    this->_allocator.construct(it, *(it + 1));
                    this->_allocator.destroy(it + 1);
                }
                this->_size--;
                return position;
            }

            iterator erase(iterator first, iterator last)
            {  
                 if (this->empty() || first == last)
                    return this->end();
                
                size_type n = 0;
                for (iterator it = first; it != last; it++)
                    n++;
                for (pointer it = first._ptr_current; it != last._ptr_current; it++)
                    this->_allocator.destroy(it);
                for(pointer it = first._ptr_current, ite = this->end()._ptr_current - n; it != ite; it++) //++it?
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
        if (lhs.size() !=  rhs.size())
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