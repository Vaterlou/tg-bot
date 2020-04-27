#include "Config.hpp"

using namespace tlg_bot;

Config::Config()
    : m_tlg_host(set_config_value("TLG_API_HOST", "api.telegram.org")),
      m_tlg_api_token(set_config_value("TLG_BOT_API_TOKEN", "1085976154:AAEBci6sBTIga4idTufy9UMFN7YcHkfHQH0")),
      m_tlg_chat_id(set_config_value("TLG_CHAT_ID", "-1001218382942")),
      m_db_address(set_config_value("PG_DB_HOST", "127.0.0.1")),
      m_db_port(set_config_value("PG_DB_PORT", "5432")),
      m_db_name(set_config_value("PG_DB_NAME", "mydb")),
      m_db_user_name(set_config_value("PG_DB_USR", "admin")),
      m_db_user_pwd(set_config_value("PG_DB_PWD", "admin"))
{
}

std::string Config::get_tlg_host()
{
    return m_tlg_host;
}

std::string Config::get_tlg_api_token()
{
    return m_tlg_api_token;
}

std::string Config::get_tlg_chat_id()
{
    return m_tlg_chat_id;
}

std::string Config::get_db_address()
{
    return m_db_address;
}

std::string Config::get_db_port()
{
    return m_db_port;
}

std::string Config::get_db_name()
{
    return m_db_name;
}

std::string Config::get_db_user_name()
{
    return m_db_user_name;
}

std::string Config::get_db_user_pwd()
{
    return m_db_user_pwd;
}
std::string Config::get_db_table_name()
{
    return m_db_table_name;
}

std::string Config::set_config_value(const std::string &env_name, const std::string &default_value)
{
    auto param = std::getenv(env_name.c_str());
    return (param != nullptr) ? param : default_value;
}