// Base template class Iterator, that will be used to derive iterator classes from it

#ifndef ITERATOR_BASE_HPP

#define ITERATOR_BASE_HPP

#include <cstddef> //for ptrdiff_t

namespace ft
{
	struct input_iterator_tag {};
    struct output_iterator_tag {};
    struct forward_iterator_tag : public input_iterator_tag {};
    struct bidirectional_iterator_tag : public forward_iterator_tag {};
    struct random_access_iterator_tag : public bidirectional_iterator_tag {};

    template < class Category, class T, class Distance = std::ptrdiff_t, class Pointer = T*, class Reference = T& >
    struct iterator 
    {
        typedef T value_type;
        typedef Distance difference_type;
        typedef Pointer pointer;
        typedef Reference reference;
        typedef Category iterator_category;
    };
}

#endif
