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
	LRUCache(ICurl & curl, unsigned int max_capacity = 2000);
	virtual ~LRUCache();
	string getDocument(const string &key);
	int size() const;
	int getValueCount() const;

private:
	void makeSpace(unsigned int neededSpace);
	string addToCache(const string &url);

	std::list<string> history_;
	std::map<string, string> cache_;
	unsigned int max_capacity_;
	unsigned int current_size_;

	ICurl & curl_;
};

#endif /* LRUCACHE_H_ */
