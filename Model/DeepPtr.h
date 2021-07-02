#ifndef DEEPPTR_H
#define DEEPPTR_H

template <class T>
class DeepPtr {
public:
	DeepPtr(T* ptr = nullptr);
	DeepPtr(const DeepPtr<T>& dp);
	DeepPtr(DeepPtr<T>&& dp);
	DeepPtr<T>& operator=(const DeepPtr<T>& dp);
	DeepPtr<T>& operator=(DeepPtr<T>&& dp);
	~DeepPtr();
	T& operator*() const;
	T* operator->() const;
	bool operator!() const;
	operator bool() const;

private:
	T* ptr_;
};

template <class T>
DeepPtr<T>::DeepPtr(T* ptr) : ptr_(ptr) {}

template <class T>
DeepPtr<T>::DeepPtr(const DeepPtr<T>& dp) : ptr_(dp.ptr_ ? dp->clone() : nullptr) {}

template <class T>
DeepPtr<T>::DeepPtr(DeepPtr<T>&& dp) : ptr_(dp.ptr_) {
	dp.ptr_ = nullptr;
}

template <class T>
DeepPtr<T>& DeepPtr<T>::operator=(const DeepPtr<T>& dp) {
	if (this != &dp) {
		delete ptr_;
		ptr_ = dp.ptr_ ? dp->clone() : nullptr;
	}
	return *this;
}

template <class T>
DeepPtr<T>& DeepPtr<T>::operator=(DeepPtr<T>&& dp) {
	if (this != &dp) {
		delete ptr_;
		ptr_ = dp.ptr_;
		dp.ptr_ = nullptr;
	}
	return *this;
}

template <class T>
DeepPtr<T>::~DeepPtr() { 
	delete ptr_; 
}

template <class T>
T& DeepPtr<T>::operator*() const {
	return *ptr_;
}

template <class T>
T* DeepPtr<T>::operator->() const {
	return ptr_;
}

template <class T>
bool DeepPtr<T>::operator!() const {
	return !ptr_;
}

template <class T>
DeepPtr<T>::operator bool() const {
	return ptr_ != nullptr;
}

#endif
