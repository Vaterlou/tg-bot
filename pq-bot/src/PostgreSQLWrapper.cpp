#include "PostgreSQLWrapper.hpp"

using namespace tlg_bot;

PostgreSQLWrapper::PostgreSQLWrapper(PConfig &cfg) : m_upcfg(cfg)
{
    update_id();
}

int PostgreSQLWrapper::check_new_users()
{
    pqxx::connection connect{create_connect_opt()};
    pqxx::work txn{connect};
    pqxx::result result{txn.exec("SELECT id FROM my_table ORDER BY id DESC LIMIT 1")};

    int new_id = result[0]["id"].as<int>();

    if (new_id > prev_id)
    {
        int delta = new_id - prev_id;
        BOOST_LOG_TRIVIAL(info) << delta << " new database entries";
        return delta;
    }
    else
    {
        return 0;
    }
}

pqxx::result PostgreSQLWrapper::get_new_users(const int &count_new_users)
{
    try
    {
        BOOST_LOG_TRIVIAL(info) << "query";
        std::string query = "SELECT * FROM my_table ORDER BY id DESC LIMIT " + std::to_string(count_new_users);
        pqxx::connection connect{create_connect_opt()};
        pqxx::work txn{connect};
        pqxx::result result{txn.exec(query)};
        return result;
    }
    catch (pqxx::sql_error const &e)
    {
        BOOST_LOG_TRIVIAL(error) << e.what() << e.query();
    }
    catch(...)
    {
        BOOST_LOG_TRIVIAL(error) << "unexpected exception";
    }
    return pqxx::result();
}

void PostgreSQLWrapper::save_new_user_to_db(const pqxx::row &row)
{
  pqxx::connection connect{create_connect_opt()};
  pqxx::work txn{connect};
  pqxx::result result{txn.exec0("INSERT INTO last_user (id, user_name, password, email, phone) VALUES (" + txn.quote(row["id"].as<int>()) + ", " +
                                                                                                           txn.quote(row["user_name"].as<std::string>()) + ", " +
                                                                                                           txn.quote(row["password"].as<std::string>()) + ", " +
                                                                                                           txn.quote(row["email"].as<std::string>()) + ", " +
                                                                                                           txn.quote(row["phone"].as<std::string>()) + ")")};
  txn.commit();
  update_id();
  BOOST_LOG_TRIVIAL(info) << "added new record in last_user";
}

void PostgreSQLWrapper::drop_old_user_to_db()
{
  pqxx::connection connect{create_connect_opt()};
  pqxx::work txn{connect};
  pqxx::result result{txn.exec("DELETE FROM last_user WHERE id = (SELECT id FROM last_user ORDER BY id DESC LIMIT 1)")};
  txn.commit();

  BOOST_LOG_TRIVIAL(info) << "deleted old record in last_user";
}

void PostgreSQLWrapper::update_id()
{
    pqxx::connection connect{create_connect_opt()};
    pqxx::work txn{connect};
    pqxx::result result{txn.exec("SELECT id FROM last_user ORDER BY id DESC LIMIT 1")};
    if (result.empty())
        prev_id = 0;
    else
        prev_id = result[0]["id"].as<int>();

    BOOST_LOG_TRIVIAL(info) << "After update, id = " << prev_id;
}

std::string PostgreSQLWrapper::create_connect_opt()
{
    std::string result = "dbname=" + m_upcfg->get_db_name() + " user=" + m_upcfg->get_db_user_name() +
                         " password=" + m_upcfg->get_db_user_pwd() + " hostaddr=" + m_upcfg->get_db_address() +
                         " port=" + m_upcfg->get_db_port() + " connect_timeout=10";
    return result;
}
