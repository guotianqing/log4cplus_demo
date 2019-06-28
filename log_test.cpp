#include <log4cplus/logger.h>
#include <log4cplus/consoleappender.h>
#include <log4cplus/layout.h>
#include <log4cplus/fileappender.h>
#include <log4cplus/loggingmacros.h>

#include <unistd.h>

using namespace std;
using namespace log4cplus;
using namespace log4cplus::helpers;

int main(void)
{
    SharedObjectPtr<Appender> _append(new ConsoleAppender());
    _append->setName("append for test");

    string pattern = "%d{%m/%d/%y %H:%M:%S} -%m [%l]%n";
    auto_ptr<Layout> _layout(new PatternLayout(pattern));

    _append->setLayout(_layout);

    Logger _logger = Logger::getInstance("test");

    _logger.addAppender(_append);

    _logger.setLogLevel(ALL_LOG_LEVEL);

    LOG4CPLUS_DEBUG(_logger, "this is the first log message...");
    sleep(1);
    LOG4CPLUS_WARN(_logger, "this is the second log message...");
    return 0;
}