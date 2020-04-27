#pragma once
#include "PostgreSQLWrapper.hpp"
#include "TelegramBotAPI.hpp"
#include "HttpClient.hpp"

namespace tlg_bot
{
class Application
{
public:
    Application();
    void run();

private:
    void do_cron_job();
    
    PConfig m_upcfg;
    PPostgre m_uppg;
    PHttp m_uphttp;
    PTlgBotAPI m_uptlgapi;
};
}