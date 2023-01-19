/****************************************************************************************************************************
Title         :   LinkedList.hpp
Author        :   modified by Kasaf Shah
Description   :   Implementation files for LinkedList class
Date modified : 11/20/2022
****************************************************************************************************************************/



#include <iostream>
#include <string>
#include <cstdlib>


/* Default constructor*/
template <typename ItemType>
LinkedList<ItemType>::LinkedList()
{
    head_ = nullptr;
    size_ = 0;
}

/* Copy Contructors*/
template <typename ItemType>
LinkedList<ItemType>::LinkedList(const LinkedList<ItemType> &list)// : head_{nullptr}, size_{0}
{
    head_ = nullptr;
    size_ = 0;
    if (!list.isEmpty()) {
        Node<ItemType> *copyHead = list.getHeadPtr();
        int counter = 0;

        while (counter < list.getSize()) {
            insert(copyHead->getItem(), counter);
            counter++;
            copyHead = copyHead->getNext();
        }
    }
}





template<typename ItemType>
Node<ItemType>* LinkedList<ItemType>::getHeadPtr() const {
    return head_;
}


/*

    @post    : removes all items from the caller list,
               no nodes remain in the list
**/
template<typename ItemType>
void LinkedList<ItemType>::clear() {
    Node<ItemType>* curr_item = head_;
    Node<ItemType>* temp = curr_item;
    for(int i = 0; i<size_; i++) {
        temp = curr_item;
        curr_item = curr_item->getNext();
        delete temp;
    }
    temp = nullptr;
    size_ = 0;
}


/* Destructor */
template<typename ItemType>
LinkedList<ItemType>::~LinkedList() {
    clear();
}

template<typename ItemType>
bool LinkedList<ItemType>::insert(const ItemType& item, const int &position){
    if((position < 0 || position > size_)){
        return false;
    }

    Node<ItemType> *node = new Node<ItemType>();
    node->setItem(item);

    if(size_ == 0){
        head_ = node;
    }
    else {
        Node<ItemType> *iterator;

        if(position == 0){
            node->setNext(head_);
            head_ = node;
        }

        else if (position == size_){
            iterator = getAtPos(size_-1);
            iterator->setNext(node);
        }
        else {
            iterator = getAtPos(position-1);
            node->setNext(iterator->getNext());
            iterator->setNext(node);
        }
    }
    size_++;
    return true;
}


template <typename ItemType>
bool LinkedList<ItemType>::remove(const int&position) {
    if (position < 0 || position >= size_) {
        return false;
    }

    Node<ItemType> *iterator = nullptr;
    Node<ItemType> *previous = nullptr;

    if (position == 0){
        iterator = head_;
        head_ = head_->getNext();
    }
    else {
        previous = getAtPos(position-1);
        iterator = getAtPos(position);
        previous->setNext(iterator->getNext());
    }

    size_--;
    previous = nullptr;
    iterator->setNext(nullptr);
    delete iterator;
    return true;

}


/*
    @param            :   Another LinkedList passed by reference
    @post             :   Sets the current LinkedList with the same items as the provided
                          LinkedList but in reverse order
*/
template <typename ItemType>
void LinkedList<ItemType>::reverseCopy(const LinkedList<ItemType> &a_list) {
    LinkedList<ItemType> newList(a_list);

    Node<ItemType> *current = newList.getHeadPtr();
    const int START = 0;
    const int END = newList.getSize();

    while (current != nullptr){
        insert(current->getItem(), START);
        current = current->getNext();
        remove(END);
    }
}

template<typename ItemType>
int LinkedList<ItemType>::getSize() const {
    return size_;
}

template<typename ItemType>
bool LinkedList<ItemType>::isEmpty() const {
    return size_ == 0 ? true : false;
}



/*
    @pre      :   current_position and new_position is valid
    @return   :   true if item is moved to new_position, false otherwise
    @post     :   Moves item from current_position to new_position, if valid
**/
template <typename ItemType>
bool LinkedList<ItemType>::moveItem(int &current_position, const int &new_position) {
    if(
        (current_position > -1 && current_position < size_) &&
        (new_position > -1 && new_position < size_)
    ) {
        if(new_position != current_position) {
            if(new_position < current_position) {
                Node<ItemType>* temp_curr = this->getAtPos(current_position);
                Node<ItemType>* temp_prev = this->getAtPos(current_position-1);
                temp_curr = temp_prev;
                temp_prev = temp_curr;
                current_position--;
            }
            else {
                Node<ItemType>* temp_curr = this->getAtPos(current_position);
                Node<ItemType>* temp_next = this->getAtPos(current_position+1);
                temp_curr = temp_next;
                temp_next = temp_curr;
                current_position++;
            }

            return moveItem(current_position, new_position);
        }
        else {
            return true;
        }
    }
    else {
        return false;
    }
}



/*
    @param            :   A reference to an item
    @return           :   Return true if item was moved to top, false otherwise
    @post             :   Will move the item from its current position to the front
                          of the list.
                          For example, given the list 1 -> 3 -> 5 -> 6, moving 5 to the
                          top of the list would result in 5 -> 1 -> 3 -> 6
                          (recall that positions start at 0 and end at n-1).
*/
template<typename ItemType>
bool LinkedList<ItemType>::moveItemToTop(const ItemType &item)
    {
    if (getIndexOf(item) < 1) //If the item does not exist or it is already on top, return false
        return false;
    else
        {
        Node<ItemType>* new_head = new Node<ItemType>(); //Create a new head Node
        new_head->setItem(item); //Set the value of the new head Node to the item you want to move
        remove(getIndexOf(item)); //Remove the item you want to move from the List
        new_head->setNext(head_); //Set the new head pointer's next value to the current head pointer
        head_ = new_head; //Set the List's head to the new head pointer
        return true;
        }
    }



    /*
        @pre      :  pos is a valid place in the list, otherwise nullptr will be returned
        @param    :  the position of the item to be returned
        @return   :  a pointer to the node at pos
    **/
template<typename ItemType>
Node<ItemType>* LinkedList<ItemType>::getAtPos(const int &pos) const {

    if(pos < 0 || pos >= size_) {
        return nullptr;
    }

    Node<ItemType>* curr_item = head_;
    int counter = 0;
    while(counter < pos && curr_item != nullptr) {
        counter++;
        curr_item = curr_item->getNext();
    }
    return curr_item;
}


/*
    @param         : item object to find in the list
    @return     : the position (index) of the parameter object
*/
template<typename ItemType>
int LinkedList<ItemType>::getIndexOf(const ItemType &item) const {
    Node<ItemType>* curr_item = head_;
    int counter = 0;
    while(curr_item != nullptr) {
        if(curr_item->getItem() == item) {
            return counter;
        }
        counter++;
        curr_item = curr_item->getNext();
    }
    return -1;
}
/*helper function for bsortByusername in Network class
post: swaps two items
*/
template <typename ItemType>
void LinkedList<ItemType>::swap(Node<ItemType> *a, Node<ItemType> *b){

  
    ItemType temp = a->getItem();
    a->setItem(b->getItem());
    b->setItem(temp);
    
}

/*helper function for bSortbyusername in Network class
comp: comparator function
i:count for the swaps 
return: a sorted linked list 
*/

template <typename ItemType>
template<typename Comparator>
void LinkedList<ItemType>::bSort(Comparator comp, int* i){
     
    bool swapped=true; 
     
    Node<ItemType> *current = head_;
    Node<ItemType> *next = head_->getNext();

    while(swapped && current != nullptr){
        current = head_;
        next = head_->getNext();
        swapped=false; 

        while(next != nullptr ){
            
            if(comp(*(next->getItem()), *(current->getItem()))){
                swap(current,next);
                swapped=true; 
               (*i)++; 
            }
            next = next->getNext();
             current = current->getNext();

        }
       
        
    }
}

