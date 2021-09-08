#ifndef PAIR_HPP

#define PAIR_HPP

namespace ft
{
    template <class T1, class T2>
    struct pair 
    {
        public:
            
            // Member types
            typedef T1 first_type;
            typedef T2 second_type;

            // Member variables
            first_type first;
            second_type second;

            //Member Functions

            pair() : first(), second() { return; }

            template <class U, class V>
            pair (const pair< U, V>& src) : first(src.first), second(src.second)
            {       
                return;
            }

            pair(const first_type& a, const second_type& b) : first(a), second(b)
            {
                return;
            }

            ~pair() {};
    
            pair& operator=(const pair& src)
            {
                this->first = src.first;
                this->second = src.second;
                return *this;
            }         

    };

    //  ********** NON MEMBER FUNCTIONS  ********** 

    //---> Relational operators
    
    template <class T1, class T2>
    bool operator==(const pair<T1,T2>& lhs, const pair<T1,T2>& rhs)
    {
        return ((lhs.first == rhs.first) && (lhs.second == rhs.second));
    }

    template <class T1, class T2>
    bool operator!=(const pair<T1,T2>& lhs, const pair<T1,T2>& rhs)
    {
        return !(lhs == rhs);
    }
    
    template <class T1, class T2>
    bool operator<(const pair<T1,T2>& lhs, const pair<T1,T2>& rhs)
    {
        return ((lhs.first < rhs.first) || (!(rhs.first < lhs.first) && lhs.second < rhs.second));
    }
    
    template <class T1, class T2>
    bool operator>(const pair<T1,T2>& lhs, const pair<T1,T2>& rhs)
    {
        return rhs < lhs;
    }

    template <class T1, class T2>
    bool operator<=(const pair<T1,T2>& lhs, const pair<T1,T2>& rhs)
    {
        return !(lhs > rhs);
    }

    template <class T1, class T2>
    bool operator>=(const pair<T1,T2>& lhs, const pair<T1,T2>& rhs)
    {
        return !(lhs < rhs);
    }

    //---> Add make_pair

    template <class T1, class T2>
    pair<T1, T2> make_pair(T1 x, T2 y)
    {
        return (pair<T1,T2>(x, y));
    }
}

#endif