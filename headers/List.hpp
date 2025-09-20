#ifndef __LIST_HPP__
#define __LIST_HPP__

#include <cstdlib>


template <typename T>
class List
{
public:
    typedef size_t         size_type;
    typedef T              value_type;
    typedef T&             reference;
    typedef const T&       const_reference;
    typedef T*             pointer;
    typedef const T*       const_pointer;
    typedef std::ptrdiff_t difference_type;
                                            ///====NODE===
private:
    struct Node
    {
        Node(const_reference data = T(), Node* previous = NULL, Node* next = NULL)
            : data_(data)
            , previous_(previous)
            , next_(next) 
        {}
        T data_;
        Node* previous_;
        Node* next_; 
    };
                            ///====CONST_ITERATOR=====
public:
    class const_iterator {
    friend class List<T>;
    public:
        const_iterator();
        const_iterator(const const_iterator& rhv);
        ~const_iterator();
        
        const_iterator& operator=(const const_iterator& rhv);
        const_reference operator*()  const;
        Node*           operator->() const;
        const_iterator& operator++();
        const_iterator  operator++(int);
        const_iterator& operator--();
        const_iterator  operator--(int);
        bool            operator==(const const_iterator& rhv) const;
        bool            operator!=(const const_iterator& rhv) const;
        
    protected:
        Node* getPtr() const;

    private:
        explicit const_iterator(Node* node);
        
    private:
        Node* ptr_;
    };
                                    ///====ITERATOR====
public:
    class iterator : public const_iterator {
    friend class List<T>;
    public:
        iterator();
        iterator(const iterator& rhv);
        ~iterator();
       
        reference operator*()  const;
        Node*     operator->() const;
        
    private:
        explicit iterator(Node* node);
        
    };
                                   /// =====CONST_REVERSE_ITERATOR====
public:
    class const_reverse_iterator {
    friend class List<T>;
    public:
        const_reverse_iterator();
        const_reverse_iterator(const const_reverse_iterator& rhv);
        ~const_reverse_iterator();
        
        const_reverse_iterator& operator=(const const_reverse_iterator& rhv);
        const_reference         operator*()  const;
        Node*                   operator->() const;
        const_reverse_iterator& operator++();
        const_reverse_iterator  operator++(int);
        const_reverse_iterator& operator--();
        const_reverse_iterator  operator--(int);
        bool                    operator==(const const_reverse_iterator& rhv) const;
        bool                    operator!=(const const_reverse_iterator& rhv) const;
        
    protected:
        Node* getPtr() const;

    private:
        explicit const_reverse_iterator(Node* node);
        
    private:
        Node* ptr_;
    };
                                    ///====REVERSE_ITERATOR====
public:
    class reverse_iterator : public const_reverse_iterator {
    friend class List<T>;
    public:
        reverse_iterator();
        reverse_iterator(const reverse_iterator& rhv);
        ~reverse_iterator();
       
        reference operator*()  const;
        Node*   operator->() const;
        
    private:
        explicit reverse_iterator(Node* node);
        
    };

private:
    template <typename  InputIt1, typename  InputIt2>
    static bool lexicographical_compare(InputIt1 first1, InputIt1 last1,
                                        InputIt2 first2, InputIt2 last2);

public:
    List();
    List(const size_type size, const_reference value = T()); 
    List(const int size, const_reference value = T()); 
    List(const List<T>& rhv);
    template <typename InputIterator>
    List(InputIterator first, InputIterator last);
    ~List();

    List<T>& operator=(const List<T>& rhv);
    bool     operator==(const List<T>& rhv) const;
    bool     operator!=(const List<T>& rhv) const;
    bool     operator<(const List<T>& rhv)  const;
    bool     operator>(const List<T>& rhv)  const;
    bool     operator<=(const List<T>& rhv) const;
    bool     operator>=(const List<T>& rhv) const;
 
    iterator insert(iterator position, const_reference value);
    void insert(iterator position, const size_type size, const_reference value);
    void insert(iterator position, const int size, const_reference value);
    template <typename InputIterator>
    void insert(iterator position, InputIterator first, InputIterator last);
    iterator erase(iterator position);
    iterator erase(iterator first, iterator last);
    void push_back(const_reference value);
    void push_front(const_reference value);
    void pop_back();
    void pop_front();
    reference front();
    const_reference front() const;
    reference back(); 
    const_reference back() const;
    
    void swap(List<T>& rhv);
    void splice(iterator position, List<T>& rhv);
    void splice(iterator position, List<T>& rhv, iterator index);
    void splice(iterator position, List<T>& rhv, iterator first, iterator last);
    void remove(const_reference value);
    template <typename Predicate>
    void remove_if(Predicate predicate);
    void unique();
    template <typename BinaryPredicate>
    void unique(BinaryPredicate predicate);
    void merge(List<T>& rhv);
    template <typename BinaryPredicate>
    void merge(List<T>& rhv, BinaryPredicate comparison);
    void reverse();
    void sort();
    template<typename BinaryPredicate>
    void sort(BinaryPredicate comp);

    void resize(const size_type newSize, const_reference value = T());
    size_type size()     const; 
    size_type max_size() const;
    bool empty()         const;
    void clear();

    const_iterator         begin()  const;
    const_iterator         end()    const; 
    const_reverse_iterator rbegin() const;
    const_reverse_iterator rend()   const;
    iterator         begin(); 
    iterator         end();  
    reverse_iterator rbegin();
    reverse_iterator rend();

private:
    Node* begin_;
    Node* end_;
};

#include "../templates/List.cpp"

#endif /// __LIST_HPP__

