#pragma once
#include <boost/test/unit_test.hpp>
#include "TelegramBotAPI.hpp"
 
using namespace tlg_bot;

BOOST_AUTO_TEST_SUITE(telegram_api_test)

BOOST_AUTO_TEST_CASE(default_tlg_request_test)
{
	PConfig config = std::make_unique<Config>(Config());
    TelegramBotAPI bot_api = TelegramBotAPI(config);

	BOOST_CHECK_EQUAL(bot_api.get_me(), "/bot1085976154:AAEBci6sBTIga4idTufy9UMFN7YcHkfHQH0/getMe");
	BOOST_CHECK_EQUAL(bot_api.get_updates(), "/bot1085976154:AAEBci6sBTIga4idTufy9UMFN7YcHkfHQH0/getUpdates");

    const std::string message = "Hello";
	BOOST_CHECK_EQUAL(bot_api.send_message(message) , "/bot1085976154:AAEBci6sBTIga4idTufy9UMFN7YcHkfHQH0/sendMessage?chat_id=-1001218382942&text=" + message);
}

BOOST_AUTO_TEST_SUITE_END()