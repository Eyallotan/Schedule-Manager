//
// Created by eyall on 6/5/2019.
//

#ifndef WET2_KEYVALUEPAIR_H
#define WET2_KEYVALUEPAIR_H

template<typename T>
class KeyValuePair {
public:
    //c'tor & d'tor
    KeyValuePair(int key, T* value);
    ~KeyValuePair();

    //helper functions:
    int getKey();
    T* getValue();
    void setValue(T* new_val);
private:
    //properties:
    int key;
    T* value;
};

template<typename T>
KeyValuePair<T>::KeyValuePair(int key, T* value) : key(key), value(value){}

template<typename T>
int KeyValuePair<T>::getKey(){
    return key;
}

template<typename T>
T* KeyValuePair<T>::getValue(){
    return value;
}

template<typename T>
void KeyValuePair<T>::setValue(T *new_val) {
    value = new_val;
}

template<typename T>
KeyValuePair<T>::~KeyValuePair() {
    delete value;
}

#endif //WET2_KEYVALUEPAIR_H
