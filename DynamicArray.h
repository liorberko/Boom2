#ifndef DYNAMIC_ARRAY_H
#define DYNAMIC_ARRAY_H

template <class T>
class DynamicArray
{
private:
    int max_size;
    T* array;
public:
    DynamicArray(int arr_size) : max_size(arr_size), array(new T[arr_size]) {}
    ~DynamicArray()
    {
        if (array != nullptr)
        {
            delete[] array;
        }
    }
};






#endif