/*
 * LRUCache_test.cpp
 *
 *  Created on: Sep 21, 2013
 *      Author: dumoulma
 */

#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include "ICurl.h"
#include <string>
#include <ostream>

#include "LRUCache.h"

using std::string;
using namespace testing;
using ::testing::Return;
using std::cout;
using std::endl;

class ICurlMock: public ICurl
{
public:
	MOCK_CONST_METHOD1(getFrom, string(const string &url));
};

class LRUCacheTest: public Test
{
public:
	LRUCacheTest() :
			cache(mock, 100)
	{
	}

protected:
	ICurlMock mock;
	LRUCache cache;
};

TEST_F(LRUCacheTest, newCacheHasSizeZero)
{
	EXPECT_EQ(0, cache.size());
}

TEST_F(LRUCacheTest, addAnewItemToCacheFetchesURLWithCurlAndAddsToCache)
{
	string url = "www.ulaval.ca";
	string expected = "<html>www.ulaval.ca</html>";
	EXPECT_CALL(mock, getFrom(A<const string&>())).Times(1).WillOnce(
			Return(expected));

	string actual = cache.getDocument(url);

	EXPECT_EQ(1, cache.getValueCount());
	EXPECT_EQ(expected.size(), cache.size());
	EXPECT_EQ(expected, actual);
}

TEST_F(LRUCacheTest, getDocumentSecondTimeShouldHitTheCache)
{
	string url = "www.ulaval.ca";
	string expected = "<html>www.ulaval.ca</html>";
	EXPECT_CALL(mock, getFrom(A<const string&>())).Times(1).WillOnce(
			Return(expected));

	cache.getDocument(url);
	string actual = cache.getDocument(url);

	EXPECT_EQ(1, cache.getValueCount());
	EXPECT_EQ(expected, actual);
	EXPECT_EQ(expected.size(), cache.size());
}

TEST_F(LRUCacheTest, twoNewDocumentsAreAddedToTheCache)
{
	string url1 = "www.ulaval.ca";
	string expected1 = "<html>www.ulaval.ca</html>";
	string url2 = "www.ift.ulaval.ca";
	string expected2 =
			"<html>bienvenu au site du departement d'informatique</html>";

	EXPECT_CALL(mock, getFrom(url1)).Times(1).WillOnce(Return(expected1));
	EXPECT_CALL(mock, getFrom(url2)).Times(1).WillOnce(Return(expected2));

	string actual1 = cache.getDocument(url1);
	string actual2 = cache.getDocument(url2);

	EXPECT_EQ(2, cache.getValueCount());
	EXPECT_EQ(expected1, actual1);
	EXPECT_EQ(expected2, actual2);
	EXPECT_EQ(expected1.size() + expected2.size(), cache.size());
}

TEST_F(LRUCacheTest, addElementToFullCacheMakesSpaceOK1)
{
	string url1 = "www.ulaval.ca";
	string expected1 = "<html>www.ulaval.ca</html>";
	string url2 = "www.ift.ulaval.ca";
	string expected2 =
			"<html>bienvenu au site du departement d'informatique</html>";
	string url3 = "www.gel-gif.ulaval.ca";
	string expected3 =
			"<html>bienvenu au site du departement de genie electrique et genie informatique</html>";

	EXPECT_CALL(mock, getFrom(url1)).Times(1).WillOnce(Return(expected1));
	EXPECT_CALL(mock, getFrom(url2)).Times(1).WillOnce(Return(expected2));
	EXPECT_CALL(mock, getFrom(url3)).Times(1).WillOnce(Return(expected3));

	string actual1 = cache.getDocument(url1);
	string actual2 = cache.getDocument(url2);
	string actual3 = cache.getDocument(url3);

	EXPECT_EQ(1, cache.getValueCount());
	EXPECT_EQ(expected3.size(), cache.size());
}

TEST_F(LRUCacheTest, addElementToFullCacheMakesSpaceOK2)
{
	string url1 = "www.ulaval.ca";
	string expected1 = "<html>www.ulaval.ca</html>";
	string url2 = "www.ift.ulaval.ca";
	string expected2 =
			"<html>bienvenu au site du departement d'informatique</html>";
	string url3 = "www.monblog.ca";
	string expected3 = "<html>bienvenu a mon blug</html>";

	EXPECT_CALL(mock, getFrom(url1)).Times(1).WillOnce(Return(expected1));
	EXPECT_CALL(mock, getFrom(url2)).Times(1).WillOnce(Return(expected2));
	EXPECT_CALL(mock, getFrom(url3)).Times(1).WillOnce(Return(expected3));

	string actual1 = cache.getDocument(url1);
	EXPECT_EQ(expected1.size(), cache.size());

	string actual2 = cache.getDocument(url2);
	EXPECT_EQ(expected1.size() + expected2.size(), cache.size());

	string actual3 = cache.getDocument(url3);
	EXPECT_EQ(2, cache.getValueCount());
	EXPECT_EQ(expected2.size() + expected3.size(), cache.size());
}

int main(int argc, char** argv)
{
	// The following line must be executed to initialize Google Mock
	// (and Google Test) before running the tests.
	::testing::InitGoogleMock(&argc, argv);
	return RUN_ALL_TESTS();
}
