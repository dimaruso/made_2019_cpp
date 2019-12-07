#pragma once
#include <memory>
#include <initializer_list>
#include <algorithm>

template <class T, class Alloc = std::allocator<T>>
class MyVector
{

public:

	using size_type = size_t;
	using value_type = T;
	using reference = T & ;
	using const_reference = const T&;
	using allocator_type = Alloc;

	template <class TypeI>
	class Iterator : public std::iterator<std::random_access_iterator_tag, TypeI>
	{
	public:
		Iterator(TypeI* p);
		Iterator(const Iterator &it);

		bool operator!=(Iterator const& other) const;
		bool operator==(Iterator const& other) const;
		TypeI& operator*() const;
		Iterator& operator++();
		Iterator& operator--();
	private:
		TypeI* p;
	};

	using iterator = Iterator<T>;
	using const_iterator = Iterator<const T>;

	using reverse_iterator = std::reverse_iterator<iterator>;
	using const_reverse_iterator = std::reverse_iterator<const_iterator>;


	MyVector();
	explicit MyVector(const size_type& count);
	MyVector(const size_type& count, const value_type& defaultValue);
	MyVector(std::initializer_list<value_type> init);
	
	~MyVector();

	const_reference operator[](const size_type& i) const;
	reference operator[](const size_type& i);
	
	void push_back(value_type&& value);
	void push_back(const value_type& value);
	void pop_back();

	void reserve(size_type count);
	size_type capacity() const noexcept;
	
	void resize(size_type newSize);
	void resize(size_type newSize, const value_type& defaultValue);
	
	void clear() noexcept;
	const bool empty() const noexcept;
	const size_type size() const noexcept;
	
	iterator begin() noexcept;
	reverse_iterator rbegin() noexcept;
	const_iterator cbegin() const noexcept;
	const_reverse_iterator crbegin() const noexcept;

	iterator end() noexcept;
	reverse_iterator rend() noexcept;
	const_iterator cend() const noexcept;
	const_reverse_iterator crend() const noexcept;
	
private:
	allocator_type alloc_;
	size_type size_;
	size_type capacity_;
	value_type* data;

	void extendData(size_type newCapacity);
};

template <class T, class Alloc>
MyVector<T, Alloc>::MyVector() :
	size_(0),
	capacity_(0),
	data(nullptr)
{
}

template <class T, class Alloc>
MyVector<T, Alloc>::MyVector(const size_type& count) :
	size_(count),
	capacity_(count),
	data(alloc_.allocate(count))
{
	for (size_type i = 0; i < size_; ++i)		
		alloc_.construct(data + i, value_type());
}

template <class T, class Alloc>
MyVector<T, Alloc>::MyVector(const size_type& count, const value_type& defaultValue) :
	size_(count),
	capacity_(count),
	data(alloc_.allocate(count))
{
	for (size_type i = 0; i < size_; ++i)
		alloc_.construct(data + i, defaultValue);
}

template <class T, class Alloc>
MyVector<T, Alloc>::MyVector(std::initializer_list<value_type> init) :
	size_(init.size()),
	capacity_(init.size()),
	data(alloc_.allocate(init.size()))
{
	size_type k = 0;
	for (auto& i : init)
		alloc_.construct(data + k++, i);
}

template <class T, class Alloc>
MyVector<T, Alloc >::~MyVector()
{
	if (data)
	{
		for (size_type i = 0; i < size_; ++i)
			alloc_.destroy(data + i);
		alloc_.deallocate(data, capacity_);
		data = nullptr;
	}
	size_ = 0;
	capacity_ = 0;
}

template <class T, class Alloc>
typename MyVector<T, Alloc>::const_reference MyVector<T, Alloc>::operator[](const size_type& i) const
{
	if (i < size_) return data[i];
	else
		throw std::out_of_range("out of range");
}

template <class T, class Alloc>
typename MyVector<T, Alloc>::reference MyVector<T, Alloc>::operator[](const size_type& i)
{
	if (i < size_) return data[i];
	else
		throw std::out_of_range("out of range");
}

template <class T, class Alloc>
void MyVector<T, Alloc>::push_back(value_type&& value)
{
	if (capacity_ <= size_)
		extendData(1);
	alloc_.construct(data + size_++, std::move(value));
}

template <class T, class Alloc>
void MyVector<T, Alloc>::push_back(const value_type& value)
{
	if (capacity_ <= size_)
		extendData(1);
	alloc_.construct(data + size_++, value);
}

template <class T, class Alloc>
void MyVector<T, Alloc>::pop_back()
{
	if(size_) --size_;
}

template <class T, class Alloc>
void MyVector<T, Alloc>::reserve(size_type count)
{
	if (capacity_ < count)
		extendData(count - capacity_);
}

template <class T, class Alloc>
typename MyVector<T, Alloc>::size_type MyVector<T, Alloc>::capacity() const noexcept
{
	return capacity_;
}

template <class T, class Alloc>
void MyVector<T, Alloc>::resize(size_type newSize)
{
	if (capacity_ < newSize)
	{
		extendData(newSize - capacity_);
		for (size_type i = size_; i < newSize; ++i)
			alloc_.construct(data + i, value_type());
	}
	else
	{
		for (size_type i = newSize; i < size_; ++i)
			alloc_.destroy(data + i);
	}
	size_ = newSize;
}

template <class T, class Alloc>
void MyVector<T, Alloc>::resize(size_type newSize, const value_type& defaultValue)
{
	if (capacity_ < newSize)
		extendData(newSize - capacity_);
	else
	{
		for (size_type i = newSize; i < size_; ++i)
			alloc_.destroy(data + i);
	}
	size_ = newSize;
	for (size_type i = 0; i < size_; ++i)
		alloc_.construct(data + i, defaultValue);
}

template <class T, class Alloc>
void MyVector<T, Alloc>::clear() noexcept
{
	for (size_type i = 0; i < size_; ++i)
		alloc_.destroy(data + i);
	size_ = 0;
}
template <class T, class Alloc>
const bool MyVector<T, Alloc>::empty() const noexcept
{
	return !size_;
}
template <class T, class Alloc>
const typename MyVector<T, Alloc>::size_type MyVector<T, Alloc>::size() const noexcept
{
	return size_;
}

template <class T, class Alloc>
typename MyVector<T, Alloc>::iterator MyVector<T, Alloc>::begin() noexcept
{
	return iterator(data);
}
template <class T, class Alloc>
typename MyVector<T, Alloc>::reverse_iterator MyVector<T, Alloc>::rbegin() noexcept
{
	return reverse_iterator(end());
}

template <class T, class Alloc>
typename MyVector<T, Alloc>::const_iterator MyVector<T, Alloc>::cbegin() const noexcept
{
	return const_iterator(data);
}
template <class T, class Alloc>
typename MyVector<T, Alloc>::const_reverse_iterator MyVector<T, Alloc>::crbegin() const noexcept
{
	return const_reverse_iterator(cend());
}

template <class T, class Alloc>
typename MyVector<T, Alloc>::iterator MyVector<T, Alloc>::end() noexcept
{
	return iterator(data+size_);

}
template <class T, class Alloc>
typename MyVector<T, Alloc>::reverse_iterator MyVector<T, Alloc>::rend() noexcept
{
	return reverse_iterator(begin());
}
template <class T, class Alloc>
typename MyVector<T, Alloc>::const_iterator MyVector<T, Alloc>::cend() const noexcept
{
	return const_iterator(data+size_);
}
template <class T, class Alloc>
typename MyVector<T, Alloc>::const_reverse_iterator MyVector<T, Alloc>::crend() const noexcept
{
	return const_reverse_iterator(cbegin());
}

template <class T, class Alloc>
void MyVector<T, Alloc>::extendData(size_type newCapacity)
{
	size_type oldcapacity = capacity_;
	if(capacity_ && 3* capacity_ <= 2*(newCapacity+capacity_)) capacity_ += newCapacity;
	else if (capacity_ >= 4) capacity_ += capacity_ / 2;
	else ++capacity_;

	value_type* newData = alloc_.allocate(size_);
	
	for (size_type i = 0; i < size_; ++i)
	{
		alloc_.construct(newData +i, data[i]);
		alloc_.destroy(data + i);
	}
	alloc_.deallocate(data, oldcapacity);
	data = alloc_.allocate(capacity_);
	for (size_type i = 0; i < size_; ++i)
	{
		alloc_.construct(data + i, newData[i]);
		alloc_.destroy(newData + i);
	}
	alloc_.deallocate(newData, size_);
}

template <class T, class Alloc>
template <class TypeI>
MyVector<T, Alloc>::Iterator<TypeI>::Iterator(TypeI *_p) :
	p(_p)
{
}

template <class T, class Alloc>
template <class TypeI>
MyVector<T, Alloc>::Iterator<TypeI>::Iterator(const Iterator& it) :
	p(it.p)
{
}

template <class T, class Alloc>
template <class TypeI>
bool MyVector<T, Alloc>::Iterator<TypeI>::operator!=(Iterator const& other) const
{
	return p != other.p;
}

template <class T, class Alloc>
template <class TypeI>
bool MyVector<T, Alloc>::Iterator<TypeI>::operator==(Iterator const& other) const
{
	return p == other.p;
}

template <class T, class Alloc>
template <class TypeI>
TypeI& MyVector<T, Alloc>::Iterator<TypeI>::operator*() const
{
	return *p;
}

template <class T, class Alloc>
template <class TypeI>
MyVector<T, Alloc>::Iterator<TypeI>& MyVector<T, Alloc>::Iterator<TypeI>::operator++()
{
	++p;
	return *this;
}

template <class T, class Alloc>
template <class TypeI>
MyVector<T, Alloc>::Iterator<TypeI>& MyVector<T, Alloc>::Iterator<TypeI>::operator--()
{
	--p;
	return *this;
}
