# include "server-core.hpp"

Logger::Logger(string const& path) {

    string logpath;
    run = true;
    logpath = joinPath(path, "/log/notice.log");
    logfile.open(logpath, ios::in | ios::out | ios::trunc);
    if (!logfile.is_open()) {
        cerr << NAME << ": [Warning]: can't open logfile" << endl;
        run = false;
    }
}

bool Logger::running() const {
    return run;
}

string Logger::timer() {
    char timestamp[30];
    bzero(timestamp, sizeof(timestamp));
    time_t _time = time(NULL);
    tm*    _localTime = localtime(&_time);

    strftime(timestamp, sizeof(timestamp), "%d/%b/%Y:%H:%M:%S %Z", _localTime);
    return string(timestamp);
}


void Logger::notice(const string &msg) {
    if (!running())
        return ;
    logfile << " [" << timer() << "]: " << msg << endl;
}

Logger::~Logger() {
    if (!running())
        return ;
    logfile.close();
}
Logger logger;