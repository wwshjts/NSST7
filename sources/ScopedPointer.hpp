#pragma once

template<typename T>
class ScopedPointer {
    T* ptr_;
public:

    ScopedPointer(T * raw) : ptr_ { raw } {}
    ScopedPointer(const ScopedPointer& ref) : ptr_ { ref.ptr_->copy() } {}
    T& operator=(const ScopedPointer& ref); 

    ~ScopedPointer() { delete ptr_; };
    
    T& operator*() { return *ptr_; };
    const T& operator*() const { return *ptr_; };
    T* operator->() { return ptr_; };
    const T* operator->() const { return ptr_; };
};

template <typename T>
inline T& ScopedPointer<T>::operator=(const ScopedPointer& ref) {
    delete ptr_;
    ptr_ = new T { *ref.ptr_ };    
    return *this;
}
