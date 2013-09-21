/*
 * LRUCache.cpp
 *
 *  Created on: Sep 21, 2013
 *      Author: dumoulma
 */

#include "LRUCache.h"
#include "ICurl.h"

LRUCache::LRUCache(ICurl & curl, unsigned int max_capacity) :
		max_capacity_(max_capacity), current_size_(0), curl_(curl)
{

}

LRUCache::~LRUCache()
{

}

string LRUCache::getDocument(const string &url)
{
	if (cache_.find(url) != cache_.end())
	{
		history_.remove(url);
		history_.push_front(url);
		return cache_[url];
	}
	// else
	return addToCache(url);
}

string LRUCache::addToCache(const string &url)
{
	string document = curl_.getFrom(url);

	if (document.size() > max_capacity_)
		return document;

	if (current_size_ + document.size() > max_capacity_)
	{
		makeSpace(document.size());
	}
	history_.push_front(url);
	cache_[url] = document;
	current_size_ += document.size();

	return document;
}

void LRUCache::makeSpace(unsigned int neededSpace)
{

	while (max_capacity_ - current_size_ < neededSpace and !cache_.empty())
	{
		string url = history_.back();
		history_.pop_back();
		string document = cache_[url];
		cache_.erase(url);
		current_size_ -= document.size();
	}
}

int LRUCache::getValueCount() const
{
	return cache_.size();
}
int LRUCache::size() const
{
	return current_size_;
}

