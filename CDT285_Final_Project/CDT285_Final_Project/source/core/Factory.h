#pragma once

#include <string>
#include <set>
#include <memory>


template <class T>
class Factory {
private:
	static std::set<T*> m_Collection;

public:
	static T* Create();

	static void Add(T*);
	
	static std::set<T*>& getCollection();
};

template <class T>
std::set<T*> Factory<T>::m_Collection;

template <class T>
T* Factory<T>::Create() 
{
	auto newT = new T();

	m_Collection.insert(newT);

	return newT;
}

template <class T>
void Factory<T>::Add(T* rawPointer) {
	m_Collection.insert(rawPointer);
}

template <class T>
std::set<T*>& Factory<T>::getCollection() {
	return m_Collection;
}
