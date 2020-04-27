#pragma once
#include <boost/test/unit_test.hpp>
#include "Config.hpp"
 
using namespace tlg_bot;

BOOST_AUTO_TEST_SUITE(config_test)

BOOST_AUTO_TEST_CASE(default_values_test)
{
	Config config;
	BOOST_CHECK_EQUAL(config.get_tlg_host(), "api.telegram.org");
	BOOST_CHECK_EQUAL(config.get_tlg_api_token(), "1085976154:AAEBci6sBTIga4idTufy9UMFN7YcHkfHQH0");
	BOOST_CHECK_EQUAL(config.get_tlg_chat_id(), "-1001218382942");
	BOOST_CHECK_EQUAL(config.get_db_address(), "127.0.0.1");
	BOOST_CHECK_EQUAL(config.get_db_port(), "5432");
	BOOST_CHECK_EQUAL(config.get_db_name(), "mydb");
	BOOST_CHECK_EQUAL(config.get_db_user_name(), "admin");
	BOOST_CHECK_EQUAL(config.get_db_user_pwd(), "admin");
}

BOOST_AUTO_TEST_SUITE_END()
