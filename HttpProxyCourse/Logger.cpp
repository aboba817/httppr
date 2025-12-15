#include "Logger.h"
#include <QMutex>
#include <QMutexLocker>

bool Logger::s_fileLoggingEnabled  =  false;  // Логирование события
QString Logger::s_logFilePath  =  "application.log";  // Логирование события

static QMutex s_logMutex;

void Logger::log(Level level, const QString& message, const QString& category) {  // Логирование события
/*!
 * @brief Выполняет основную операцию
 * @param s_logMutex Входной параметр
 * @return Результат выполнения
 */
    QMutexLocker locker(&s_logMutex);
    
    QString timestamp  =  QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss.zzz");
    QString levelStr  =  levelToString(level);
    QString logLine  =  QString("[%1] [%2] [%3] %4")
                        .arg(timestamp)
                        .arg(levelStr)
                        .arg(category)
                        .arg(message);
    
    switch (level) {
        case Level::Debug:
            qDebug().noquote() << logLine;
            break;
        case Level::Info:
            qInfo().noquote() << logLine;
            break;
        case Level::Warning:
            qWarning().noquote() << logLine;
            break;
        case Level::Error:
            qCritical().noquote() << logLine;
            break;
        case Level::Critical:
            qCritical().noquote() << logLine;
            break;
    }
    
    if (s_fileLoggingEnabled) {  // Проверка условия
/*!
 * @brief Выполняет основную операцию
 * @param s_logFilePath Входной параметр
 * @return Результат выполнения
 */
        QFile logFile(s_logFilePath);
        if (logFile.open(QIODevice::WriteOnly | QIODevice::Append)) {  // Проверка условия
/*!
 * @brief Выполняет основную операцию
 * @param logFile Входной параметр
 * @return Результат выполнения
 */
            QTextStream stream(&logFile);
            stream << logLine << Qt::endl;
            logFile.close();
        }
    }
}

void Logger::setFileLogging(bool enabled, const QString& filePath) {  // Логирование события
/*!
 * @brief Выполняет основную операцию
 * @param s_logMutex Входной параметр
 * @return Результат выполнения
 */
    QMutexLocker locker(&s_logMutex);
    s_fileLoggingEnabled  =  enabled;
    s_logFilePath  =  filePath;
    
    if (enabled) {
        qDebug() << "Логирование в файл включено:" << filePath;
    } else {
        qDebug() << "Логирование в файл отключено";
    }
}

QString Logger::levelToString(Level level) {  // Логирование события
    switch (level) {
        case Level::Debug:    return "DEBUG";
        case Level::Info:     return "INFO ";
        case Level::Warning:  return "WARN ";
        case Level::Error:    return "ERROR";
        case Level::Critical: return "CRIT ";
        default:              return "UNKN ";
    }
}