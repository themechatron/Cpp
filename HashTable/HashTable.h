#pragma once
#include <iostream>
#include <vector>
#include <list>
#include <cmath>
#include <string.h>

using namespace std;

template <class Key, class Value>
class HashMap
{
	static const int HASH_INITIAL_SIZE = 7;
	private:
		struct KeyValue
		{
			Key m_key;
			Value m_value;
			KeyValue(const Key& key, const Value& value):m_key(key), m_value(value){}
		};
		vector<list<KeyValue> > m_table;
		size_t m_maxRows;
		size_t m_size;
	public:
		HashMap();
		HashMap(size_t);
		void add(const Key&, const Value&);
		Value get(const Key&);
		bool contains(const Key&);
		size_t size() const;
		Value& operator[](const Key&);
		Value operator[](const Key&) const;
	private:
		void resize();
		size_t hashFunction(const Key&) const;
		size_t findNextPrime(size_t&);
		bool isPrime(const size_t&);
};