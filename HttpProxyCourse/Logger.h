
#pragma once

#include <QString>
#include <QDebug>
#include <QDateTime>
#include <QFile>
#include <QTextStream>

/*!
 * @brief Определяет перечисление Logger
 */
class Logger {
public:
    
/*!
 * @brief Определяет перечисление Level
 */
    enum class Level {
        Debug,    
        Info,     
        Warning,  
        Error,    
        Critical  
    };

/*!
 * @brief Выполняет основную операцию
 * @param level Входной параметр
 * @param message Входной параметр
 * 
 * @return Результат выполнения
 */
    static void log(Level level, const QString& message, const QString& category  =  "General");

/*!
 * @brief Устанавливает значение
 * @param enabled Входной параметр
 * 
 * @return Результат выполнения
 */
    static void setFileLogging(bool enabled, const QString& filePath  =  "application.log");

/*!
 * @brief Выполняет основную операцию
 * @param message Входной параметр
 * 
 * @return Результат выполнения
 */
    static void debug(const QString& message, const QString& category  =  "General") {
        log(Level::Debug, message, category);
    }
    
/*!
 * @brief Выполняет основную операцию
 * @param message Входной параметр
 * 
 * @return Результат выполнения
 */
    static void info(const QString& message, const QString& category  =  "General") {
        log(Level::Info, message, category);
    }
    
/*!
 * @brief Выполняет основную операцию
 * @param message Входной параметр
 * 
 * @return Результат выполнения
 */
    static void warning(const QString& message, const QString& category  =  "General") {
        log(Level::Warning, message, category);
    }
    
/*!
 * @brief Выполняет основную операцию
 * @param message Входной параметр
 * 
 * @return Результат выполнения
 */
    static void error(const QString& message, const QString& category  =  "General") {
        log(Level::Error, message, category);
    }
    
/*!
 * @brief Выполняет основную операцию
 * @param message Входной параметр
 * 
 * @return Результат выполнения
 */
    static void critical(const QString& message, const QString& category  =  "General") {
        log(Level::Critical, message, category);
    }

private:
    
/*!
 * @brief Выполняет основную операцию
 * @param level Входной параметр
 * @return Результат выполнения
 */
    static QString levelToString(Level level);

    static bool s_fileLoggingEnabled;  
    static QString s_logFilePath;      
};