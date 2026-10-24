#pragma once

class DynamicArray
{
public:
	class iterator;

	DynamicArray();
	DynamicArray(const int* const Array, const int ArrayLength);
	DynamicArray(const DynamicArray& other);
	DynamicArray(DynamicArray&& other);
	~DynamicArray();

	int get_length() const;

	void swap(DynamicArray& other);

	DynamicArray& input();
	void output() const;

	DynamicArray& sort();
	DynamicArray& insert(const int element, const int index);
	DynamicArray& insert(const int element, const iterator iterator);
	DynamicArray& delete_position(const int position);
	DynamicArray& delete_element(const int element);
	DynamicArray& delete_all_element(const int element);
	DynamicArray& delete_element(iterator it);
	DynamicArray& delete_element(iterator it_begin, iterator it_end);


	int min() const;
	int max() const;

	iterator begin() const;
	iterator end() const;

	int& operator [](const int index) const;
	DynamicArray& operator =(const DynamicArray& other);
	DynamicArray& operator =(DynamicArray&& other);
	
	DynamicArray operator +(const int element) const;
	DynamicArray& operator +=(const int element);

	DynamicArray operator +(const DynamicArray& other) const;
	DynamicArray& operator +=(const DynamicArray& other);

	bool operator == (const DynamicArray& other) const;
	bool operator != (const DynamicArray& other) const;

	int search(const int element) const;


private:
	int* data;
	int length;
};


class DynamicArray::iterator
{
public:
	iterator();
	iterator(int* data, int index);

	bool operator == (const iterator otherIterator);
	bool operator != (const iterator otherIterator);
	int operator - (const iterator otherIterator);
	iterator& operator + (const int n);
	iterator& operator - (const int n);
	iterator& operator ++();
	iterator operator ++ (int);
	int& operator *() const;

private:
	int* data;
	int index;
};