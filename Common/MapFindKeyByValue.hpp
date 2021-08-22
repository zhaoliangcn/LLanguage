#pragma once


#include <algorithm> 
template <class K, class V>
class value_equals//本模板类来自于<The C++ Standard Library> 
{
private:
	V value;
public:
	// constructor (initialize value to compare with) 
	value_equals(const V& v) : value(v) {}
	// comparison 
	bool operator() (std::pair<const K, V> elem)
	{
		return elem.second == value;
	}
};

template <typename K, typename V, typename Map>
K FindKeyByValue(const Map& m, const V& v, const K&k)
{
	typename Map::const_iterator pos = find_if(m.begin(), m.end(), value_equals<K, V>(v));
	if (pos != m.end())
	{
		return pos->first;
	}
	K defaultKeyValue;
	return defaultKeyValue;
}
