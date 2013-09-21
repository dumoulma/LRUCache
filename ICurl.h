/*
 * ICurl.h
 *
 *  Created on: Sep 21, 2013
 *      Author: dumoulma
 */

#ifndef ICURL_H_
#define ICURL_H_

#include <string>

class ICurl
{
public:
	virtual ~ICurl()
	{
	}

	virtual std::string getFrom(const std::string &url) const =0;
};

#endif /* ICURL_H_ */
