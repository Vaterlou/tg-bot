#pragma once
#include <boost/test/unit_test.hpp>

using namespace tlg_bot;

BOOST_AUTO_TEST_SUITE(tlg_api_test)

BOOST_AUTO_TEST_CASE(api_end_points_values_test)
{
	BOOST_CHECK_EQUAL("api.telegram.org", "api.telegram.org");
}

BOOST_AUTO_TEST_SUITE_END()
