#include "../headers/List.hpp"
#include <cstddef>
#include <cassert>
#include <limits>

///=====================================LIST=============================================================

template <typename T>
List<T>::List()
    : begin_(new Node())
    , end_(begin_)
{}

template <typename T>
List<T>::List(const size_type size, const_reference value)
    : begin_(new Node())
    , end_(begin_)
{
    resize(size, value);
}

template <typename T>
List<T>::List(const int size, const_reference value)
    : begin_(new Node())
    , end_(begin_)
{
    resize(size, value);
}

template <typename T>
List<T>::List(const List<T>& rhv)
    : begin_(new Node())
    , end_(begin_)
{
    for (const_iterator it = rhv.begin(); it != rhv.end(); ++it) {
        push_back(*it);
    }
}

template <typename T>
template <typename InputIterator>
List<T>::List(InputIterator first, InputIterator last)
    : begin_(new Node())
    , end_(begin_)
{
    for (InputIterator it = first; it != last; ++it) {
        push_back(*it);
    }
}

template <typename T>
List<T>::~List()
{
    clear();
}

template <typename T>
List<T>&
List<T>::operator=(const List<T>& rhv)
{
    if (this != &rhv) {
        clear();
        for (const_iterator it = rhv.begin(); it != rhv.end(); ++it) {
            push_back(*it); 
        }
    }
    return *this;
}

template <typename T>
bool
List<T>::operator==(const List<T>& rhv) const
{
    if (this == &rhv)         return true;
    if (size() != rhv.size()) return false;

    for (const_iterator it1 = begin(), it2 = rhv.begin();
        it1 != end() && it2 != rhv.end(); ++it1, ++it2) {

        if (*it1 != *it2) {
            return false;
        }
    }
    return true;
}

template <typename T>
bool
List<T>::operator!=(const List<T>& rhv) const
{
    return !(*this == rhv); 
}

template <typename T>
bool
List<T>::operator<(const List<T>& rhv) const
{
    return lexicographical_compare(begin(), end(), rhv.begin(), rhv.end());
}

template <typename T>
bool
List<T>::operator>(const List<T>& rhv) const
{
    return !(*this == rhv || *this < rhv);
}

template <typename T>
bool
List<T>::operator<=(const List<T>& rhv) const
{
    return !(*this > rhv);
}

template <typename T>
bool
List<T>::operator>=(const List<T>& rhv) const
{
    return !(*this < rhv);
}

template <typename T>
typename List<T>::iterator
List<T>::insert(iterator position, const_reference value)
{
    Node* newNode = new Node(value, position->previous_, position.getPtr());

    position->previous_ = newNode;

    if (newNode->previous_ != NULL) {
        newNode->previous_->next_ = newNode; 
    } else {
        begin_ = newNode;
    }

    return iterator(newNode);
}

template <typename T>
void
List<T>::insert(iterator position, const size_type size, const_reference value)
{
    for (size_type i = 0; i < size; ++i) {
        position = insert(position, value);
    }
}

template <typename T>
void
List<T>::insert(iterator position, const int size, const_reference value)
{
    for (int i = 0; i < size; ++i) {
        position = insert(position, value);
    }
}

template <typename T>
template <typename InputIterator>
void
List<T>::insert(iterator position, InputIterator first, InputIterator last)
{
    while (first != last) {
        position = insert(position, *first);
        ++first;
        ++position;
    }
}

template <typename T>
typename List<T>::iterator
List<T>::erase(iterator position)
{
    Node* ptr = position.getPtr();
    Node* nextNode = ptr->next_;

    ptr->next_->previous_ = ptr->previous_;

    if (ptr->previous_) {
        ptr->previous_->next_ = ptr->next_;
    } else {
        begin_ = ptr->next_;
    }

    delete ptr;
    return iterator(nextNode);
}


template <typename T>
typename List<T>::iterator
List<T>::erase(iterator first, iterator last)
{
    while (first != last) {
        first = erase(first);
    }
    return last;
}

template <typename T>
void
List<T>::push_back(const_reference value)
{ 
    if (empty()) {
        push_front(value);
        return;
    }

    Node* newNode = new Node(value, end_->previous_, end_);
    end_->previous_->next_ = newNode;
    end_->previous_ = newNode;
}

template <typename T>
void
List<T>::push_front(const_reference value)
{
    Node* newNode = new Node(value, NULL, begin_);
    begin_->previous_ = newNode;
    begin_ = newNode;
}

template <typename T>
void
List<T>::pop_back()
{
    if (empty()) return;
    
    Node* ptr = end_->previous_;
    end_->previous_ = end_->previous_->previous_;
   
    if (NULL != end_->previous_) {
        end_->previous_->next_ = end_;
    } else {
        begin_ = end_;
    }
    delete ptr;
}

template <typename T>
void
List<T>::pop_front()
{
    if (empty()) return;
    
    Node* ptr = begin_;
    
    begin_ = begin_->next_;
    begin_->previous_ = NULL;
    delete ptr;   
}

template <typename T>
typename List<T>::reference
List<T>::front()
{
    return begin()->data_;
}

template <typename T>
typename List<T>::const_reference
List<T>::front() const
{
    return begin()->data_;
}

template <typename T>
typename List<T>::reference
List<T>::back()
{
    return end_->previous_->data_;
}

template <typename T>
typename List<T>::const_reference
List<T>::back() const
{
    return end_->previous_->data_;
}

template <typename T>
void
List<T>::swap(List<T>& rhv)
{
    List<T> temp(*this);
    *this = rhv;
    rhv = temp;
}

template <typename T>
void
List<T>::splice(iterator position, List<T>& rhv) 
{
    if (empty()) {
        begin_ = rhv.begin_;
        end_   = rhv.end_;
    } else {
        Node* posNode = position.getPtr();

        Node* firstRhv = rhv.begin_;
        Node* lastRhv  = rhv.end_->previous_;

        lastRhv->next_ = posNode;
        if (posNode->previous_ != NULL) {
            posNode->previous_->next_ = firstRhv;
        } else {
            begin_ = firstRhv; 
        }
        firstRhv->previous_ = posNode->previous_;
        posNode->previous_ = lastRhv;
    }
    rhv.begin_ = rhv.end_;
    rhv.end_->previous_ = NULL;
}

template <typename T>
void
List<T>::splice(iterator position, List<T>& rhv, iterator index)
{
    Node* posNode = position.getPtr();
    Node* nodeIndex = index.getPtr();

    if (NULL == nodeIndex || NULL == posNode || nodeIndex == posNode || nodeIndex->next_ == posNode) {
        return;
    }

    if (nodeIndex->previous_ != NULL) {
        nodeIndex->previous_->next_ = nodeIndex->next_;
    } else {
        rhv.begin_ = nodeIndex->next_; 
    }

    if (nodeIndex->next_ != NULL) {
        nodeIndex->next_->previous_ = nodeIndex->previous_;
    } else {
        rhv.end_->previous_ = nodeIndex->previous_;
    }
    /// insert
    nodeIndex->next_ = posNode;
    nodeIndex->previous_ = posNode->previous_;

    if (posNode->previous_ != NULL) {
        posNode->previous_->next_ = nodeIndex;
    } else {
        begin_ = nodeIndex;
    }
    
    posNode->previous_ = nodeIndex;
}

template <typename T>
void List<T>::splice(iterator position, List<T>& rhv, iterator first, iterator last)
{
    Node* posNode   = position.getPtr();
    Node* firstNode = first.getPtr();
    Node* lastNode  = last.getPtr();

    if (firstNode == lastNode) {
        return;
    }

    Node* beforeFirst = firstNode->previous_;
    Node* lastPrev    = (lastNode != NULL ? lastNode->previous_ : rhv.end_->previous_);

    if (beforeFirst != NULL) {
        beforeFirst->next_ = lastNode;
    } else {
        rhv.begin_ = lastNode;
    }

    if (lastNode != NULL) {
        lastNode->previous_ = beforeFirst;
    } else {
        rhv.end_->previous_ = beforeFirst;
    }

    ///insert
    Node* beforePos = posNode->previous_;

    if (beforePos != NULL) {
        beforePos->next_ = firstNode;
    } else {
        begin_ = firstNode; 
    }

    firstNode->previous_ = beforePos;

    if (posNode != NULL) {
        posNode->previous_ = lastPrev;
    }

    if (lastPrev != NULL) {
        lastPrev->next_ = posNode;
    }
}

template <typename T>
void
List<T>::remove(const_reference value)
{
    iterator it = begin();
    while (it != end()) {
        if (value == *it) {
            it = erase(it);
            continue;
        }
        ++it;
    }
}

template <typename T>
template <typename Predicate>
void
List<T>::remove_if(Predicate predicate)
{
    iterator it = begin();
    while (it != end()) {
        if (predicate(*it)) {
            it = erase(it);
            continue;
        }
        ++it;
    }
}

template <typename T>
void 
List<T>::unique()
{
    if (empty()) return;

    iterator current = begin();
    iterator next = current;
    ++next;

    while (next != end()) {
        if (*current == *next) {
            next = erase(next);
            continue;
        }
        ++current;
        ++next;
    }
}

template <typename T>
template <typename BinaryPredicate>
void 
List<T>::unique(BinaryPredicate predicate)
{
    if (empty()) return;

    iterator current = begin();
    iterator next = current;
    ++next;

    while (next != end()) {
        if (predicate(*current, *next)) {
            next = erase(next);
            continue;
        } 
        ++current;
        ++next;
    }
}

template <typename T>
void
List<T>::merge(List<T>& rhv)
{
    if (&rhv == this || rhv.empty()) return;

    iterator itThis = begin();
    iterator itRhv  = rhv.begin();

    while (itThis != end() && itRhv != rhv.end()) {
        if (*itRhv < *itThis) {
            iterator nextRhv = itRhv;
            ++nextRhv;
            splice(itThis, rhv, itRhv);
            itRhv = nextRhv;
            continue;
        }
        ++itThis;
    }

    if (itRhv != rhv.end()) {
        splice(end(), rhv, itRhv, rhv.end());
    }
}

template <typename T>
template <typename BinaryPredicate>
void 
List<T>::merge(List<T>& rhv, BinaryPredicate comparison)

{
    if (&rhv == this || rhv.empty()) return;

    iterator itThis = begin();
    iterator itRhv  = rhv.begin();

    while (itThis != end() && itRhv != rhv.end()) {
        if (comparison(*itRhv, *itThis)) {
            iterator nextRhv = itRhv;
            ++nextRhv;
            splice(itThis, rhv, itRhv);
            itRhv = nextRhv;
            continue;
        }
        ++itThis;
    }

    if (itRhv != rhv.end()) {
        splice(end(), rhv, itRhv, rhv.end());
    }
}

template <typename T>
void
List<T>::reverse()
{
    Node* current = begin_;
    Node* previous = end_; 
    Node* next = NULL;

    while (current != end_) {

        next = current->next_;
        current->next_ = previous;
        current->previous_ = next;

        previous = current;
        current = next;
    }

    end_->previous_ = begin_;
    begin_ = previous;
}

template <typename T>
void
List<T>::sort()
{
    for (iterator it = begin(); it != end(); ++it) {
        iterator jt = it;
        ++jt;
        while (jt != end()) {
            if (*jt < *it) {
                std::swap(*it, *jt);
            }
            ++jt;
        }
    }
}

template <typename T>
template<typename BinaryPredicate>
void 
List<T>::sort(BinaryPredicate comparison)
{
    for (iterator it = begin(); it != end(); ++it) {
        iterator jt = it;
        ++jt;
        while (jt != end()) {
            if (comparison(*jt, *it)) {
                std::swap(*it, *jt);
            }
            ++jt;
        }
    }
}

template <typename T>
void
List<T>::resize(size_type newSize, const_reference value)
{
    const size_type previousSize = size();
    for (size_type i = previousSize; i < newSize; ++i) {
        push_back(value);
    }
    for (size_type i = newSize; i < previousSize; ++i) {
        pop_back();
    }
}

template <typename T>
typename List<T>::size_type
List<T>::size() const
{
    const_iterator it = begin();
    size_type count = 0;
    while (it != end()) {
        ++it;
        ++count;
    }
    return count;
}

template <typename T>
typename List<T>::size_type
List<T>::max_size() const
{
    return std::numeric_limits<size_type>::max() / sizeof(Node); 
}

template <typename T>
bool
List<T>::empty() const
{
    return end_ == begin_;
}

template <typename T>
void
List<T>::clear()
{
    while (!empty()) {
        pop_back();
    }
}

template <typename T>
typename List<T>::const_iterator
List<T>::begin() const
{
    return const_iterator(begin_); 
}

template <typename T>
typename List<T>::const_iterator
List<T>::end() const
{
    return const_iterator(end_); 
}

template <typename T>
typename List<T>::const_reverse_iterator
List<T>::rbegin() const
{
    return const_reverse_iterator(end_->previous_); 
}

template <typename T>
typename List<T>::const_reverse_iterator
List<T>::rend() const
{
    return const_reverse_iterator(begin_->previous_); 
}

template <typename T>
typename List<T>::iterator
List<T>::begin()
{
    return iterator(begin_); 
}

template <typename T>
typename List<T>::iterator
List<T>::end()
{
    return iterator(end_); 
}

template <typename T>
typename List<T>::reverse_iterator
List<T>::rbegin()
{
    return reverse_iterator(end_->previous_); 
}

template <typename T>
typename List<T>::reverse_iterator
List<T>::rend()
{
    return reverse_iterator(begin_->previous_); 
}

template <typename T>
template <typename InputIt1, typename InputIt2>
bool
List<T>::lexicographical_compare(InputIt1 first1, InputIt1 last1,
                                 InputIt2 first2, InputIt2 last2)
{
    for ( ; (first1 != last1) && (first2 != last2); ++first1, ++first2) {
        if (*first1 < *first2) return true; 
        if (*first2 < *first1) return false; 
    }
    return (first1 == last1) && (first2 != last2);
}

///==================================CONST_ITERATOR===============================================================
template <typename T>
List<T>::const_iterator::const_iterator()
    : ptr_(NULL)
{}

template <typename T>
List<T>::const_iterator::const_iterator(const const_iterator& rhv)
    : ptr_(rhv.ptr_)
{}

template <typename T>
List<T>::const_iterator::const_iterator(Node* node)
    : ptr_(node)
{}

template <typename T>
List<T>::const_iterator::~const_iterator()
{
    ptr_ = NULL;
}

template <typename T>
typename List<T>::const_iterator&
List<T>::const_iterator::operator=(const const_iterator& rhv)
{
    if (this != &rhv) {
        ptr_ = rhv.ptr_;
    }
    return *this;
}

template <typename T>
typename List<T>::const_reference
List<T>::const_iterator::operator*() const
{
    return ptr_->data_; 
}

template <typename T>
typename List<T>::Node*
List<T>::const_iterator::operator->() const
{
    return ptr_;
}

template <typename T>
typename List<T>::const_iterator&
List<T>::const_iterator::operator++()
{
    ptr_ = ptr_->next_;
    return *this;
}

template <typename T>
typename List<T>::const_iterator
List<T>::const_iterator::operator++(int)
{
    const_iterator temp(*this);
    ++(*this);
    return temp;
}

template <typename T>
typename List<T>::const_iterator&
List<T>::const_iterator::operator--()
{
    ptr_ = ptr_->previous_;
    return *this;;
}

template <typename T>
typename List<T>::const_iterator
List<T>::const_iterator::operator--(int)
{
    const_iterator temp(*this);
    --(*this);
    return temp;
}

template <typename T>
bool
List<T>::const_iterator::operator==(const const_iterator& rhv) const
{
    return ptr_ == rhv.ptr_;
}

template <typename T>
bool
List<T>::const_iterator::operator!=(const const_iterator& rhv) const
{
    return !(*this == rhv);
}

template <typename T>
typename List<T>::Node*
List<T>::const_iterator::getPtr() const
{
    return ptr_;
}

///===================================ITERATOR===============================================================
template <typename T>
List<T>::iterator::iterator()
    : const_iterator()
{}

template <typename T>
List<T>::iterator::iterator(const iterator& rhv)
    : const_iterator(rhv.getPtr())
{}

template <typename T>
List<T>::iterator::iterator(Node* node)
    : const_iterator(node)
{}

template <typename T>
List<T>::iterator::~iterator()
{}

template <typename T>
typename List<T>::reference
List<T>::iterator::operator*() const
{
    return this->getPtr()->data_; 
}

template <typename T>
typename List<T>::Node*
List<T>::iterator::operator->() const
{
    return this->getPtr();
}

///======================================CONST_REVERSE_ITERATOR==========================================

template <typename T>
List<T>::const_reverse_iterator::const_reverse_iterator()
    : ptr_(NULL)
{}

template <typename T>
List<T>::const_reverse_iterator::const_reverse_iterator(const const_reverse_iterator& rhv)
    : ptr_(rhv.ptr_)
{}

template <typename T>
List<T>::const_reverse_iterator::const_reverse_iterator(Node* node)
    : ptr_(node)
{}

template <typename T>
List<T>::const_reverse_iterator::~const_reverse_iterator()
{
    ptr_ = NULL;
}

template <typename T>
typename List<T>::const_reverse_iterator&
List<T>::const_reverse_iterator::operator=(const const_reverse_iterator& rhv)
{
    if (this != &rhv) {
        ptr_ = rhv.ptr_;
    }
    return *this;
}

template <typename T>
typename List<T>::const_reference
List<T>::const_reverse_iterator::operator*() const
{
    return ptr_->data_; 
}

template <typename T>
typename List<T>::Node*
List<T>::const_reverse_iterator::operator->() const
{
    return ptr_;
}

template <typename T>
typename List<T>::const_reverse_iterator&
List<T>::const_reverse_iterator::operator++()
{
    ptr_ = ptr_->previous_;
    return *this;
}

template <typename T>
typename List<T>::const_reverse_iterator
List<T>::const_reverse_iterator::operator++(int)
{
    const_reverse_iterator temp(*this);
    ++(*this);
    return temp;
}

template <typename T>
typename List<T>::const_reverse_iterator&
List<T>::const_reverse_iterator::operator--()
{
    ptr_ = ptr_->next_;
    return *this;
}

template <typename T>
typename List<T>::const_reverse_iterator
List<T>::const_reverse_iterator::operator--(int)
{
    const_reverse_iterator temp(*this);
    --(*this);
    return temp;
}

template <typename T>
bool
List<T>::const_reverse_iterator::operator==(const const_reverse_iterator& rhv) const
{
    return ptr_ == rhv.ptr_;
}

template <typename T>
bool
List<T>::const_reverse_iterator::operator!=(const const_reverse_iterator& rhv) const
{
    return !(*this == rhv);
}

template <typename T>
typename List<T>::Node*
List<T>::const_reverse_iterator::getPtr() const
{
    return ptr_;
}

///======================================REVERSE_ITERATOR==========================================

template <typename T>
List<T>::reverse_iterator::reverse_iterator()
    : const_reverse_iterator()
{}

template <typename T>
List<T>::reverse_iterator::reverse_iterator(const reverse_iterator& rhv)
    : const_reverse_iterator(rhv.getPtr())
{}

template <typename T>
List<T>::reverse_iterator::reverse_iterator(Node* node)
    : const_reverse_iterator(node)
{}

template <typename T>
List<T>::reverse_iterator::~reverse_iterator()
{}

template <typename T>
typename List<T>::reference
List<T>::reverse_iterator::operator*() const
{
    return this->getPtr()->data_; 
}

template <typename T>
typename List<T>::Node*
List<T>::reverse_iterator::operator->() const
{
    return this->getPtr();
}

