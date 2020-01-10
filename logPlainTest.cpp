#include <log4cplus/logger.h>
#include <log4cplus/consoleappender.h>
#include <log4cplus/layout.h>
#include <log4cplus/fileappender.h>
#include <log4cplus/loggingmacros.h>

#include <log4cplus/helpers/loglog.h>

#include <iostream>
#include <memory>
#include <iomanip>
#include <unistd.h>

using namespace std;
using namespace log4cplus;
using namespace log4cplus::helpers;

/* 函数声明 */
static void write_log_to_logfile(void);
static void test_loglog(void);

int main(void)
{
    /*  Filter
        过滤器，过滤输出消息。过滤器，解决哪些信息需要输出的问题，比如DEBUG，WARR,INFO等的输出控制

        Layout
        布局器，控制输出消息的格式。格式化输出信息,解决了如何输出的问题。

        Appender
        挂接器，与布局器和过滤器紧密配合，将特定格式的消息过滤后输出到所挂接的设备终端如屏幕，文件等等)。接收日志的各个设备,如控制台、文件、网络等。解决了输出到哪里去的问题

        Logger
        记录器，保存并跟踪对象日志信息变更的实体，当你需要对一个对象进行记录时，就需要生成一个logger。日志模块,程序中唯一一个必须得使用的模块，解决了在哪里使用日志的问题。

        Hierarchy
        分类器，层次化的树型结构，用于对被记录信息的分类，层次中每一个节点维护一个logger的所有信息。

        LogLevel
        优先权，包括TRACE,  DEBUG, INFO, WARNING, ERROR, FATAL。 
    */

    /* 实例化一个封装了输出介质的appender对象 */
    SharedObjectPtr<Appender> _append(new ConsoleAppender());
    _append->setName("append for test");

    /* 实例化一个封装了输出格式的layout对象 */
    string pattern = "%d{%m/%d/%y %H:%M:%S} -%m [%l]%n";
    unique_ptr<Layout> _layout(new PatternLayout(pattern));

    /* 将layout对象绑定(attach)到appender对象
        如省略此步骤，简单布局器SimpleLayout对象会绑定到logger
    */
    _append->setLayout(std::move(_layout));

    /* 实例化一个封装了日志输出logger对象 */
    Logger _logger = Logger::getInstance("test");

    /* 将appender对象绑定(attach)到logger对象 */
    _logger.addAppender(_append);

    /* 设置logger的优先级，如省略此步骤，各种有限级的日志都将被输出 */
    _logger.setLogLevel(ALL_LOG_LEVEL);

    LOG4CPLUS_TRACE(_logger, "This is"
                                 << " just a t"
                                 << "est." << std::endl);
    sleep(1);
    LOG4CPLUS_DEBUG(_logger, "this is a debug log message...");
    LOG4CPLUS_INFO(_logger, "This is a char:" << 'x');
    LOG4CPLUS_WARN(_logger, "this is a warning log message...");
    LOG4CPLUS_ERROR(_logger, "This is a long(hex):" << std::hex << 100000000);
    LOG4CPLUS_FATAL(_logger, "Thisis a double:" << std::setprecision(15) << 1.2345234234);

    write_log_to_logfile();

    test_loglog();

    return 0;
}

static void write_log_to_logfile(void)
{
    SharedAppenderPtr _append(new DailyRollingFileAppender("test.log", DAILY, 5));
    _append->setName("filelogtest");

    Logger _logger = Logger::getInstance("test.subtestof_filelog");

    _logger.addAppender(_append);

    for (int i = 0; i < 5; ++i)
    {
        LOG4CPLUS_DEBUG(_logger, "the " << i << "st log");
    }

    return;
}

static void print_msgs(void)
{

    std::cout << "Entering  printMsgs()..." << std::endl;
    LogLog::getLogLog()->debug("This is a  Debug statement...");
    LogLog::getLogLog()->warn("This is a  Warning...");
    LogLog::getLogLog()->error("This is a  Error...");
    std::cout << "Exiting  printMsgs()..." << std::endl << std::endl;
}

/* LogLog类实现了debug, warn, error 函数用于logcplus运行时显示log4cplus自身的调试、警告或错误信息
是对标准输出的简单封装，它也可以用来进行简单的日志输出。

LogLog 同时提供了两个方法来进一步控制所输出的信息，其中setInternalDebugging()方法用来控制是否屏蔽输出信息中的调试信息，当输入参数为false则屏蔽，缺省设置为false。 
setQuietMode()方法用来控制是否屏蔽所有输出信息，当输入参数为true则屏蔽，缺省设置为false */
static void test_loglog(void)
{
    print_msgs();
    std::cout << "Turning on  debug..." << std::endl;
    LogLog::getLogLog()->setInternalDebugging(true);
    print_msgs();
    std::cout << "Turning on  quiet mode..." << std::endl;
    LogLog::getLogLog()->setQuietMode(true);
    print_msgs();

    return;
}