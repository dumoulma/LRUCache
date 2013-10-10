/*
 * LRUCache.h
 *
 *  Created on: Sep 21, 2013
 *      Author: Mathieu Dumoulin
 */

#ifndef LRUCACHE_H_
#define LRUCACHE_H_

#include <string>
#include <list>
#include <map>

class ICurl;

class LRUCache {
public:
	LRUCache(ICurl & curl, std::size_t max_capacity);

	std::string getDocument(const std::string &key);
	std::size_t size() const;
	std::size_t getValueCount() const;

private:
	void makeSpace(std::size_t neededSpace);
	void addToCache(const std::string &url, const std::string &document);

	std::list<std::string> history_;
	std::map<std::string, std::string> cache_;
	std::size_t max_capacity_;
	std::size_t current_size_;

	ICurl & curl_;
};

#endif /* LRUCACHE_H_ */

