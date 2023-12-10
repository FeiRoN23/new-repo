#define BOOST_TEST_MODULE mytests
#include <boost/test/included/unit_test.hpp>
#include "hello.h"


BOOST_AUTO_TEST_CASE(myTestCase)
{
  BOOST_TEST(1 == 1);
  BOOST_TEST(true);
}


BOOST_AUTO_TEST_CASE(otherTest) {
    
	hello hello;

	BOOST_CHECK_EQUAL(4, hello.doHello());
}