/**
 * Заголовочный файл DatabaseConfig.h.
 * Содержит объявления классов и функций для системы HTTP Proxy Course.
 */

#pragma once

#include <QString>
#include <QSettings>

/**
 * Конфигурация подключения к базе данных.
 */
class DatabaseConfig {
public:
    
    /**
     * Возвращает единственный экземпляр класса (Singleton).
     */
    static DatabaseConfig& instance();

    void loadConfig(const QString& configPath  =  "config.ini");

    QString hostName() const { return m_hostName; }

    QString databaseName() const { return m_databaseName; }

    QString userName() const { return m_userName; }

    QString password() const { return m_password; }

    int port() const { return m_port; }

private:
    
    DatabaseConfig();

    DatabaseConfig(const DatabaseConfig&)  =  delete;
    DatabaseConfig& operator = (const DatabaseConfig&)  =  delete;

    void createDefaultConfig(const QString& configPath);

    QString m_hostName;      
    QString m_databaseName;  
    QString m_userName;      
    QString m_password;      
    int m_port;              
};