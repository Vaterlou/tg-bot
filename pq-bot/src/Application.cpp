#include "Application.hpp"

using namespace tlg_bot;
using namespace boost::asio;

Application::Application()
{
    m_upcfg = std::make_unique<Config>(Config());
    m_uppg = std::make_unique<PostgreSQLWrapper>(PostgreSQLWrapper(m_upcfg));
    m_uphttp = std::make_unique<HttpClient>();
    m_uptlgapi = std::make_unique<TelegramBotAPI>(TelegramBotAPI(m_upcfg));

    BOOST_LOG_TRIVIAL(info) << "pq-bot launched...";
}

void Application::run()
{
    for (;;)
    {
        do_cron_job();
    }
}

void Application::do_cron_job()
{
    try
    {
        io_context io;
        steady_timer t(io, chrono::seconds(30));
        t.wait();

        BOOST_LOG_TRIVIAL(info) << "cron job start";

        const int count_new_users = m_uppg->check_new_users();

        if (count_new_users > 0)
        {
            auto result = m_uppg->get_new_users(count_new_users);

            for ( auto it = result.rbegin(); it != result.rend(); ++it )
            {
                auto row = *it;

                BOOST_LOG_TRIVIAL(info) << row["id"].as<int>() << " "
                                        << row["user_name"].as<std::string>() << " "
                                        << row["email"].as<std::string>();

                std::string message = "ID: " + row["id"].as<std::string>() + "%0A"
                                      "USER: " + row["user_name"].as<std::string>() + "%0A"
                                      "EMAIL: " + row["email"].as<std::string>() + "%0A"
                                      "PHONE: " + row["phone"].as<std::string>();

                m_uphttp->send_request_https(m_upcfg->get_tlg_host(), http::verb::post, m_uptlgapi->send_message(message));

                m_uppg->drop_old_user_to_db();
                m_uppg->save_new_user_to_db(row);
            }
        }
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << '\n';
    }
}
