/*
 * LRUCache.h
 *
 *  Created on: Sep 21, 2013
 *      Author: dumoulma
 */

#ifndef LRUCACHE_H_
#define LRUCACHE_H_

#include <string>
#include <list>
#include <map>

using std::string;
class ICurl;

class LRUCache
{
public:
	LRUCache(ICurl & curl, std::size_t max_capacity);
	virtual ~LRUCache();
	string getDocument(const string &key);
	std::size_t size() const;
	std::size_t getValueCount() const;

private:
	void makeSpace(std::size_t neededSpace);
	string addToCache(const string &url);

	std::list<string> history_;
	std::map<string, string> cache_;
	std::size_t max_capacity_;
	std::size_t current_size_;

	ICurl & curl_;
};

#endif /* LRUCACHE_H_ */
