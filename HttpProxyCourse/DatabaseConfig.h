
#pragma once

#include <QString>
#include <QSettings>

/*!
 * @brief Реализует функциональность класса DatabaseConfig
 */
class DatabaseConfig {
public:
    
/*!
 * @brief Выполняет основную операцию
 * @return Результат выполнения
 */
    static DatabaseConfig& instance();

/*!
 * @brief Загружает данные
 * 
 */
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

/*!
 * @brief Создает объект
 * @param configPath Входной параметр
 */
    void createDefaultConfig(const QString& configPath);

    QString m_hostName;      
    QString m_databaseName;  
    QString m_userName;      
    QString m_password;      
    int m_port;              
};