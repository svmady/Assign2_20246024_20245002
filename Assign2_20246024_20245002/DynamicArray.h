#pragma once
#ifndef DYNAMICARRAY_H
#define DYNAMICARRAY_H

#include <cstddef>

template <typename T>
class DynamicArray {
private:
    T* data;
    int size;
    int capacity;

    void resize(int newCapacity) {
        T* newData = new T[newCapacity];
        for (int i = 0; i < size; ++i) {
            newData[i] = data[i];
        }
        delete[] data;
        data = newData;
        capacity = newCapacity;
    }

public:
    DynamicArray(int initialCapacity = 8)
        : data(new T[initialCapacity]), size(0), capacity(initialCapacity) {}

    ~DynamicArray() {
        delete[] data;
    }

    void add(const T& value) {
        if (size == capacity) {
            resize(capacity * 2);
        }
        data[size++] = value;
    }

    T& operator[](int index) {
        return data[index];
    }

    const T& operator[](int index) const {
        return data[index];
    }

    int getSize() const {
        return size;
    }

    T* getData() {
        return data;
    }

    const T* getData() const {
        return data;
    }
};

#endif