#include "TelegramBotAPI.hpp"

using namespace tlg_bot;

TelegramBotAPI::TelegramBotAPI(PConfig& cfg) : m_upcfg(cfg)
{
}

std::string TelegramBotAPI::get_me()
{
    std::string result = "/bot" + m_upcfg->get_tlg_api_token() + "/getMe";
    return result;
}

std::string TelegramBotAPI::get_updates()
{
    std::string result = "/bot" + m_upcfg->get_tlg_api_token() + "/getUpdates";
    return result;
}

std::string TelegramBotAPI::send_message(const std::string &text)
{
    std::string result = "/bot" + m_upcfg->get_tlg_api_token() + "/sendMessage?chat_id=" + m_upcfg->get_tlg_chat_id() + "&text=" + text;
    return result;
}
