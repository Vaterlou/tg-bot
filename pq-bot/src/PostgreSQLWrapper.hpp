#pragma once
#include <pqxx/pqxx>
#include <boost/log/trivial.hpp>
#include "Config.hpp"

namespace tlg_bot
{
class PostgreSQLWrapper
{
public:
    PostgreSQLWrapper(PConfig& cfg);

    int check_new_users();
    pqxx::result get_new_users(const int &count_new_users);
    void save_new_user_to_db(const pqxx::row &row);
    void drop_old_user_to_db();
    void update_id();

private:
    std::string create_connect_opt();
    
    PConfig &m_upcfg;

    int prev_id;
};
typedef std::unique_ptr<PostgreSQLWrapper> PPostgre;
} // namespace tlg_bot
