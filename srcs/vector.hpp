#include "base.hpp"

namespace ft
{
    template<class T, class ALlloc = std::allocator<T>>
    
    class vector
    {
        typedef Alloc allocator_type;
        typedef typename allocator_type::reference reference;
        typedef typename allocator_type::const_reference const_reference;
        typedef typename allocator_type::pointer pointer;
        typedef typename allocator_type::const_pointer const_pointer;
        typedef std::size_t size_type;
       
        public:
            
            //FORME CANONIQUE      
            
            vector(void) : _capacity(0), _size(0) {}
            
            Vector(vector const & src) : _capacity(src.getCapacity()), _size(src.getSize()
            {
                this->_arr = new double [getCapacity()];
                for (size_t i = 0, i < getSize(), i++)
                {
                    this->_arr[i] = *(src.getArray() + i);
                }
            }

            ~vector(void)
            {
                if (this->_arr != NULL)
                    delete [] this->_arr;
            }
            
            vector & operator=(Vector const & src)
            {
                if (this->_arr != NULL)
                    delete [] this->arr;

                this->_capacity= src.getCapacity();
                this->_size = src.getSize();
                this->_arr = new double [getCapacity()];
                for (size_t i = 0, i < getsize(), i++)
                {
                    this->_arr[i] = *(src.getArray() + i);
                }
                return *this;
            }

            //GETTERS
            size_t getSize(void)
            {
                return this->_size;
            }
            
            size_t getCapacity(void)
            {
                return this->_capacity;
            }

            double *getArray(void)
            {
                return this->_arr;
            }

            //ELMT ACCESS
            //at
            //operator[]
            //front
            //back

            //CAPACITY
            bool empty(void)
            {
                return (this->getSize() <= 0? true : false);
            }

            size_type size(void)
            {
                return this->getSize();
            }

            //size_type max_size
            //void resize

            size_type capacity(void)
            {
                return this->getCapacity();
            }
            
            //reserve

            // MODIFIERS

            //clear
            //insert
            //erase
            //push_back
            //pop_back
            //swap

            //ALOCATOR
            //get_allocator
        
        private:
            // ATTRIBUTS
            allocator_type _allocator;
            pointer *_array;
            size_type _capacity;
            size_type _size;
    };

}