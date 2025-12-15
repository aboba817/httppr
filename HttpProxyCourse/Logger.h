/**
 * Заголовочный файл Logger.h.
 * Содержит объявления классов и функций для системы HTTP Proxy Course.
 */

#pragma once

#include <QString>
#include <QDebug>
#include <QDateTime>
#include <QFile>
#include <QTextStream>

/**
 * Система логирования приложения с поддержкой файлового вывода.
 */
class Logger {
public:
    
    enum class Level {
        Debug,    
        Info,     
        Warning,  
        Error,    
        Critical  
    };

    static void log(Level level, const QString& message, const QString& category  =  "General");

    static void setFileLogging(bool enabled, const QString& filePath  =  "application.log");

    static void debug(const QString& message, const QString& category  =  "General") {
        log(Level::Debug, message, category);
    }
    
    static void info(const QString& message, const QString& category  =  "General") {
        log(Level::Info, message, category);
    }
    
    static void warning(const QString& message, const QString& category  =  "General") {
        log(Level::Warning, message, category);
    }
    
    static void error(const QString& message, const QString& category  =  "General") {
        log(Level::Error, message, category);
    }
    
    static void critical(const QString& message, const QString& category  =  "General") {
        log(Level::Critical, message, category);
    }

private:
    
    static QString levelToString(Level level);

    static bool s_fileLoggingEnabled;  
    static QString s_logFilePath;      
};