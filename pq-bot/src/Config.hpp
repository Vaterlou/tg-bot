#pragma once
#include <string>
#include <memory>

namespace tlg_bot
{
class Config
{
public:
    Config();

    std::string get_tlg_host();
    std::string get_tlg_api_token();
    std::string get_tlg_chat_id();

    std::string get_db_address();
    std::string get_db_port();
    std::string get_db_name();
    std::string get_db_user_name();
    std::string get_db_user_pwd();
    std::string get_db_table_name();

private:

    std::string set_config_value(const std::string &env_name, const std::string &default_value);

    std::string m_tlg_host;
    std::string m_tlg_api_token;
    std::string m_tlg_chat_id;

    std::string m_db_address;
    std::string m_db_port;
    std::string m_db_name;
    std::string m_db_user_name;
    std::string m_db_user_pwd;
    std::string m_db_table_name;
};
typedef std::unique_ptr<Config> PConfig;
} // namespace tlg_bot
