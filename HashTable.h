//
// Created by eyall on 6/5/2019.
//

#ifndef WET2_HASHTABLE_H
#define WET2_HASHTABLE_H

#define DEFAULT_SIZE 10
#define ENLARGEMENT_RATIO 1
#define ENLARGEMENT_FACTOR 2
#define REDUCTION_RATIO 0.25
#define REDUCTION_FACTOR 0.5
#include "List.h"
#include "KeyValuePair.h"

template<typename T>
class HashTable {
public:
    //c'tor & d'tor
    HashTable();
    ~HashTable();

    //interface functions:
    void Insert(int key, T*);
    T* Find(int key);
    void Delete(int key);

    //helper functions:
    void printHashTable();


private:
    //helper functions:
    void Rehash(int new_arr_size);
    void RehashChain(List<KeyValuePair<T>>& chain,
            List<KeyValuePair<T>> *new_array, int new_array_size);
    void InsertAux(List<KeyValuePair<T>>* array, int current_array_size,
            KeyValuePair<T> *newElement);
    void printChain(int chainKey, List<KeyValuePair<T>>& chain);

    //properties:
    List<KeyValuePair<T> > * array;
    int array_size;
    int num_of_elements;
};

template<typename T>
HashTable<T>::HashTable() : array_size(DEFAULT_SIZE), num_of_elements(0) {
    array = new List<KeyValuePair<T>>[array_size];
}

template<typename T>
HashTable<T>::~HashTable(){
    delete[] array;
}

template<typename T>
void HashTable<T>::Insert(int key, T* value){
    KeyValuePair<T> *newVal = new KeyValuePair<T>(key, value);
    InsertAux(array, array_size, newVal);

    num_of_elements++;
    if(num_of_elements/array_size > ENLARGEMENT_RATIO) {
        Rehash(ENLARGEMENT_FACTOR * array_size);
    }
}

template<typename T>
void HashTable<T>::InsertAux(List<KeyValuePair<T>>* current_array,
            int current_array_size, KeyValuePair<T> *newElement) {
    int arr_location = newElement->getKey() % current_array_size;
    current_array[arr_location].insertNode(newElement);
}


template<typename T>
void HashTable<T>::Rehash(int new_arr_size) {
    List<KeyValuePair<T>> *new_array = new List<KeyValuePair<T>>[new_arr_size];

    for (int i = 0; i < array_size; ++i) {
        RehashChain(array[i], new_array, new_arr_size);
    }

    for (int i = 0; i < array_size; ++i) {
        ListNode<KeyValuePair<T>> *iterator = array[i].getHead();
        while(iterator) {
            iterator->setValue(NULL);
            iterator = iterator->getNext();
        }
    }
    delete[] array;

    array = new_array;
    array_size = new_arr_size;
}

template<typename T>
void HashTable<T>::RehashChain(List<KeyValuePair<T>>& chain,
                    List<KeyValuePair<T>> *new_array, int new_array_size) {
    ListNode<KeyValuePair<T>> *iterator = chain.getHead();

    while(iterator) {
        KeyValuePair<T> *current = iterator->getVal();
        InsertAux(new_array, new_array_size, current);
        iterator = iterator->getNext();
    }
}


template<typename T>
T* HashTable<T>::Find(int key){
    int arr_location = key % array_size;
    ListNode<KeyValuePair<T>> *iterator = array[arr_location].getHead();

    while(iterator) {
        KeyValuePair<T> *current = iterator->getVal();
        if(current->getKey() == key) {
            return current->getValue();
        }
        iterator = iterator->getNext();
    }
    return NULL;
}

template<typename T>
void HashTable<T>::Delete(int key) {
    int arr_location = key % array_size;
    ListNode<KeyValuePair<T>> *iterator = array[arr_location].getHead();

    while(iterator) {
        KeyValuePair<T> *current = iterator->getVal();
        if(current->getKey() == key) {
            array[arr_location].deleteNode(iterator);
            num_of_elements--;
            if (array_size > DEFAULT_SIZE &&
                (double)num_of_elements/array_size <= REDUCTION_RATIO ) {
                Rehash((int)(REDUCTION_FACTOR * array_size));
            }
            return;
        }
        iterator = iterator->getNext();
    }
}

template<typename T>
void HashTable<T>::printHashTable() {
    std::cout << "~~Printing HashTable. HashTable size: "<< array_size << " ~~"
                <<  std::endl;

    for (int i = 0; i < array_size; ++i) {
        printChain(i, array[i]);
    }
    std::cout << "~~Done~~" << std::endl;

}

template<typename T>
void HashTable<T>::printChain(int chainKey, List<KeyValuePair<T>>& chain) {
    ListNode<KeyValuePair<T>> *iterator = chain.getHead();
    if (!iterator) {
        std::cout << "Chain: " << chainKey << " is empty." << std::endl;

        return;
    }
    std::cout << "Printing Chain: " << chainKey << std::endl;

    while(iterator) {
        KeyValuePair<T> *current = iterator->getVal();

        std::cout << "Key: " << current->getKey() << std::endl;

        iterator = iterator->getNext();
    }
}

#endif //WET2_HASHTABLE_H
