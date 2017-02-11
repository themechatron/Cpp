#include "HashTable.h"

template <class Key, class Value>
HashMap<Key, Value>::HashMap()
{
	m_table.assign(HASH_INITIAL_SIZE, list<KeyValue>());
	m_maxRows = HASH_INITIAL_SIZE;
	m_size = 0;
}
template <class Key, class Value>
HashMap<Key, Value>::HashMap(size_t size)
{
	m_table.assign(size, list<KeyValue>());
	m_maxRows = size;
	m_size = 0;
}

template <class Key, class Value>
bool HashMap<Key, Value>::contains(const Key& key)
{
	size_t idx = hashFunction(key);
	return !m_table[idx].empty();
}

template <class Key, class Value>
void HashMap<Key, Value>::resize()
{
	findNextPrime(m_maxRows);
	vector<list<KeyValue> > newTable;
	newTable.assign(m_maxRows, list<KeyValue>());
	for(auto i : m_table)
	{
		for(auto j : i)
		{
			size_t idx = hashFunction(j.m_key);
			newTable[idx].push_back(j);
		}
	}
	m_table = newTable;
}

template <class Key, class Value>
void HashMap<Key, Value>::add(const Key& key, const Value& value)
{
	size_t idx = hashFunction(key);
	if(m_table[idx].empty())
	{
		m_size++;
	}
	int currentSize = m_table[idx].size();
	m_table[idx].push_back(KeyValue(key, value));
	if(m_size == m_maxRows * 75 / 100)
	{
		resize();
	}
}

template <class Key, class Value>
Value HashMap<Key, Value>::get(const Key& key)
{
	size_t idx = hashFunction(key);
	for(const auto& i : m_table[idx])
	{
		if(i.m_key == key)
		{
			return i.m_value;
		}
	}
	return Value();
}

template <class Key, class Value>
size_t HashMap<Key, Value>::size() const
{
	return m_table.size();
}

template <class Key, class Value>
Value& HashMap<Key, Value>::operator[](const Key& key)
{
	if(m_size >= m_maxRows * 75 / 100)
	{
		resize();
	}
	size_t idx = hashFunction(key);
	for(auto &i : m_table[idx])
	{
		if(i.m_key == key)
		{
			return i.m_value;
		}
	}
	if(m_table[idx].empty())
	{
		m_size++;
	}
	m_table[idx].push_back(KeyValue(key, Value()));
	return m_table[idx].back().m_value;
}

template <class Key, class Value>
Value HashMap<Key, Value>::operator[](const Key& key) const
{
	size_t idx = hashFunction(key);
	for(const auto &i : m_table[idx])
	{
		if(i.m_key == key)
		{
			return i.m_value;
		}
	}
	return Value();
}

template <class Key, class Value>
size_t HashMap<Key, Value>::findNextPrime(size_t& currentPrime)
{
	do
	{
		++currentPrime;
	}while(!isPrime(currentPrime));
	return currentPrime;
}

template <class Key, class Value>
bool HashMap<Key, Value>::isPrime(const size_t& num)
{
	if(num == 1)
	{
		return false;
	}
	for (int i = 2; i < num/2; ++i)
	{
		if(num % i == 0)
		{
			return false;
		}
	}
	return true;
}

template <class Key, class Value>
size_t HashMap<Key, Value>::hashFunction(const Key& key) const
{
	size_t result = 0;
	int numchars = 0;
	for(char i : key)
	{
		result += i*pow(31, strlen(key.c_str()) - numchars++);
	}
	return result % m_maxRows;
}
