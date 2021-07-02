#ifndef LISTA_H
#define LISTA_H

template<class T>
class Lista {
private:
	class nodo {
	public:
		T info_;
		nodo *prev_, *next_;
		nodo(const T& t, nodo *p = 0, nodo *n = 0);
	};
	
	// Lista vuota: last = first = 0
	nodo *last_, *first_;

	static nodo* copia(nodo* n, nodo* &l, nodo* p = 0);
	static void distruggi(nodo* n);
public:
	class iterator {
	friend class Lista;
	private:
		nodo* ptr_;
		bool end_;
		iterator(nodo* p, bool e);
	public:
		iterator();
		iterator& operator++();
		iterator& operator--();
		iterator operator++(int);
		iterator operator--(int);
		T& operator*() const;
		T* operator->() const;
		bool operator==(const iterator& it) const;
		bool operator!=(const iterator& it) const;
	};

	class const_iterator {
	friend class Lista;
	private:
		const nodo* ptr_;
		bool end_;
		const_iterator(nodo* p, bool e);
	public:
		const_iterator();
		const_iterator(const iterator& i);
		const_iterator& operator++();
		const_iterator& operator--();
		const_iterator operator++(int);
		const_iterator operator--(int);
		const T& operator*() const;
		const T* operator->() const;
		bool operator==(const const_iterator& it) const;
		bool operator!=(const const_iterator& it) const;
	};


	Lista();
	// Ordine di dichiarazione: nodo *last, *first;
	Lista(const Lista& l);
	Lista& operator=(const Lista& l);
	~Lista();
	void push_front(const T& t);
	void push_back(const T& t);
	void erase(int idx);
	void erase(const iterator& it);
	unsigned int size() const;
	T& operator[](int idx) const;
	
	iterator begin();
	iterator end();

	const_iterator begin() const;
	const_iterator end() const;
};

template<class T>
Lista<T>::nodo::nodo(const T& t, nodo *p, nodo *n) : info_(t), prev_(p), next_(n) {}

template<class T>
Lista<T>::Lista() : last_(0), first_(0) {}

template<class T>
Lista<T>::Lista(const Lista& l) : first_(copia(l.first_, last_)) {}

template<class T>
typename Lista<T>::nodo* Lista<T>::copia(nodo* n, nodo* &l, nodo* p) {
	if (!n) {
		l = p;
		return 0;
	}
	nodo* aux = new nodo(n->info_, p);
	aux->next_ = copia(n->next_, l, aux);
	return aux;
}

template<class T>
Lista<T>& Lista<T>::operator=(const Lista& l) {
	if (this != &l) {
		distruggi(first_);
		first_ = copia(l.first_, last_);
	}
	return *this;
}

template<class T>
Lista<T>::~Lista() {
	distruggi(first_);
}

template<class T>
void Lista<T>::distruggi(nodo* n) {
	while (n) {
		nodo* aux = n->next_;
		delete n;
		n = aux;
	}
}

template<class T>
void Lista<T>::push_front(const T& t) {
	if (first_) {
		first_->prev_ = new nodo(t, 0, first_);
		first_ = first_->prev_;
	} else {
		first_ = last_ = new nodo(t, 0, 0);
	}
}

template<class T>
void Lista<T>::push_back(const T& t) {
	if (last_) {
		last_->next_ = new nodo(t, last_, 0);
		last_ = last_->next_;
	} else {
		first_ = last_ = new nodo(t, 0, 0);
	}
}

template<class T>
void Lista<T>::erase(int idx) {
	nodo* aux = first_;
	for (int i = 0; i < idx; ++i) {
		aux = aux->next_;
	}
	if (aux->next_) {
		aux->next_->prev_ = aux->prev_;
	} else {
		last_ = aux->prev_;
	}
	if (aux->prev_) {
		aux->prev_->next_ = aux->next_;
	} else {
		first_ = aux->next_;
	}
	delete aux;
}

template<class T>
void Lista<T>::erase(const iterator& it) {
	nodo* aux = it.ptr_;
	if (aux->next_) {
		aux->next_->prev_ = aux->prev_;
	} else {
		last_ = aux->prev_;
	}
	if (aux->prev_) {
		aux->prev_->next_ = aux->next_;
	} else {
		first_ = aux->next_;
	}
	delete aux;
}

template<class T>
unsigned int Lista<T>::size() const {
	if (!first_) return 0;

	nodo* aux = first_;
	int size = 1;
	while ((aux = aux->next_))
		++size;
	return size;
}

template<class T>
T& Lista<T>::operator[](int idx) const {
	nodo* aux = first_;
	for (int i = 0; i < idx; ++i) {
		aux = aux->next_;
	}
	return aux->info_;
}

template<class T>
typename Lista<T>::iterator Lista<T>::begin() {
	return iterator(first_, !first_);
}

template<class T>
typename Lista<T>::iterator Lista<T>::end() {
	return iterator(last_, true);
}

template<class T>
Lista<T>::iterator::iterator(nodo *p, bool e) : ptr_(p), end_(e) {}

template<class T>
Lista<T>::iterator::iterator() : ptr_(0), end_(0) {}

template<class T>
T& Lista<T>::iterator::operator*() const {
	return ptr_->info_;
}

template<class T>
T* Lista<T>::iterator::operator->() const {
	return &(ptr_->info_);
}

template<class T>
bool Lista<T>::iterator::operator==(const iterator& it) const {
	return (end_ == it.end_) && (ptr_ == it.ptr_);
}

template<class T>
bool Lista<T>::iterator::operator!=(const iterator& it) const {
	return !(*this == it);
}

template<class T>
typename Lista<T>::iterator& Lista<T>::iterator::operator--() {
	if (!end_) {
		ptr_ = ptr_->prev_;
	} else {
		end_ = false;
	}
	return *this;
}

template<class T>
typename Lista<T>::iterator& Lista<T>::iterator::operator++() {
	if (ptr_->next_) {
		ptr_ = ptr_->next_;
	} else {
		end_ = true;
	}
	return *this;
}

template<class T>
typename Lista<T>::iterator Lista<T>::iterator::operator++(int) {
	iterator aux(*this);
	++*this;
	return aux;
}

template<class T>
typename Lista<T>::iterator Lista<T>::iterator::operator--(int) {
	iterator aux(*this);
	--*this;
	return aux;
}

template<class T>
typename Lista<T>::const_iterator Lista<T>::begin() const {
	return const_iterator(first_, !first_);
}

template<class T>
typename Lista<T>::const_iterator Lista<T>::end() const {
	return const_iterator(last_, true);
}

template<class T>
Lista<T>::const_iterator::const_iterator(nodo *p, bool e) : ptr_(p), end_(e) {}

template<class T>
Lista<T>::const_iterator::const_iterator() : ptr_(0), end_(0) {}

template<class T>
Lista<T>::const_iterator::const_iterator(const iterator& i) : ptr_(i.ptr_), end_(i.end_) {}

template<class T>
const T& Lista<T>::const_iterator::operator*() const {
	return ptr_->info_;
}

template<class T>
const T* Lista<T>::const_iterator::operator->() const {
	return &(ptr_->info_);
}

template<class T>
bool Lista<T>::const_iterator::operator==(const const_iterator& it) const {
	return (end_ == it.end_) && (ptr_ == it.ptr_);
}

template<class T>
bool Lista<T>::const_iterator::operator!=(const const_iterator& it) const {
	return !(*this == it);
}

template<class T>
typename Lista<T>::const_iterator& Lista<T>::const_iterator::operator--() {
	if (!end_) {
		ptr_ = ptr_->prev_;
	} else {
		end_ = false;
	}
	return *this;
}

template<class T>
typename Lista<T>::const_iterator& Lista<T>::const_iterator::operator++() {
	if (ptr_->next_) {
		ptr_ = ptr_->next_;
	} else {
		end_ = true;
	}
	return *this;
}

template<class T>
typename Lista<T>::const_iterator Lista<T>::const_iterator::operator++(int) {
	const_iterator aux(*this);
	++*this;
	return aux;
}

template<class T>
typename Lista<T>::const_iterator Lista<T>::const_iterator::operator--(int) {
	const_iterator aux(*this);
	--*this;
	return aux;
}

#endif
