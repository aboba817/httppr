#include "DatabaseConfig.h"
#include <QFile>
#include <QDebug>

DatabaseConfig::DatabaseConfig() 
    : m_hostName("localhost")
    , m_databaseName("proxy_course")
    , m_userName("postgres")
    , m_password("postgres")
    , m_port(5432) {
    
}

DatabaseConfig& DatabaseConfig::instance() {
    static DatabaseConfig instance;
    return instance;
}

void DatabaseConfig::loadConfig(const QString& configPath) {
    
    if (!QFile::exists(configPath)) {  // Проверка условия
        qWarning() << "Файл конфигурации не найден:" << configPath;
        qWarning() << "Создаем файл конфигурации по умолчанию...";
        createDefaultConfig(configPath);
    }

/*!
 * @brief Устанавливает значение
 * @param configPath Входной параметр
 * @param QSettings::IniFormat Параметр функции
 * @return Результат выполнения
 */
    QSettings settings(configPath, QSettings::IniFormat);
    
    settings.beginGroup("Database");
    m_hostName  =  settings.value("hostname", m_hostName).toString();
    m_databaseName  =  settings.value("database", m_databaseName).toString();
    m_userName  =  settings.value("username", m_userName).toString();
    m_password  =  settings.value("password", m_password).toString();
    m_port  =  settings.value("port", m_port).toInt();
    settings.endGroup();

    qDebug() << "Конфигурация БД загружена из" << configPath;
    qDebug() << "Хост:" << m_hostName << "База:" << m_databaseName << "Порт:" << m_port;
}

void DatabaseConfig::createDefaultConfig(const QString& configPath) {
/*!
 * @brief Устанавливает значение
 * @param configPath Входной параметр
 * @param QSettings::IniFormat Параметр функции
 * @return Результат выполнения
 */
    QSettings settings(configPath, QSettings::IniFormat);
    
    settings.beginGroup("Database");
    settings.setValue("hostname", m_hostName);
    settings.setValue("database", m_databaseName);
    settings.setValue("username", m_userName);
    settings.setValue("password", m_password);
    settings.setValue("port", m_port);
    settings.endGroup();

    settings.sync();
    
    qDebug() << "Создан файл конфигурации по умолчанию:" << configPath;
    qDebug() << "Отредактируйте файл для изменения параметров подключения к БД";
}