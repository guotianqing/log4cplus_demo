#include <string>
#include <log4cplus/logger.h>
#include <log4cplus/configurator.h>
#include <log4cplus/loggingmacros.h>

using namespace log4cplus;
using namespace std;

int main()
{
    log4cplus::initialize();
    log4cplus::PropertyConfigurator::doConfigure(LOG4CPLUS_TEXT("log4cplus.config"));
    log4cplus::Logger m_log = log4cplus::Logger::getInstance(LOG4CPLUS_TEXT("MemoryCheck"));

    try
    {
        int x = 8;
        double y = 8.88;
        string allocated_memory = "here";
        LOG4CPLUS_TRACE(m_log, "x = " << x);
        LOG4CPLUS_DEBUG(m_log, "y = " << y);
        /* ... */
        LOG4CPLUS_INFO(m_log, "Allocated = " << allocated_memory);
    }
    catch (std::bad_alloc &e)
    {
        /* I KNOW HOW TO DEAL WITH THIS ERROR!! */
        /* ...code that handle the error is here... */
        LOG4CPLUS_ERROR(m_log, e.what());
    }
    catch (std::exception &e)
    {
        /* I KNOW HOW TO DEAL WITH THIS ERROR!! */
        /* ...code that handle the error is here... */
        LOG4CPLUS_ERROR(m_log, e.what());
    }
    catch (...)
    {
        /* I DON'T KNOW HOW MANAGE THE ERROR!! */
        LOG4CPLUS_FATAL(m_log, "unexpected error...use gdb core dump");
        exit(-1);
    }

    int memory_remaining = 100;
    if (memory_remaining < 123)
    {
        LOG4CPLUS_WARN(m_log, "LOW MEMORY!!");
    }
    if (memory_remaining < 110)
    {
        LOG4CPLUS_ERROR(m_log, "LOW MEMORY!!");
    }

    return 0;
}