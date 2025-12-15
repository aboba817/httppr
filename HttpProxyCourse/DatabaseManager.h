/**
 * Заголовочный файл DatabaseManager.h.
 * Содержит объявления классов и функций для системы HTTP Proxy Course.
 */

#pragma once

#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QString>
#include <QMutex>
#include "DatabaseConfig.h"

/**
 * Менеджер базы данных, обеспечивающий подключение и работу с PostgreSQL.
 * Реализует паттерн Singleton для обеспечения единственного подключения к БД.
 */
class DatabaseManager {
public:
    /**
     * Возвращает единственный экземпляр класса (Singleton).
     *
     * @return Ссылка на экземпляр DatabaseManager.
     */
    static DatabaseManager& instance();

    /**
     * Устанавливает соединение с базой данных PostgreSQL.
     *
     * @return true если подключение установлено успешно, false в противном случае.
     */
    bool connectDb();

    /**
     * Инициализирует схему базы данных, создавая необходимые таблицы.
     *
     * @return true если инициализация прошла успешно, false в противном случае.
     */
    bool initSchema();

    /**
     * Проверяет состояние подключения к базе данных.
     *
     * @return true если подключение активно, false в противном случае.
     */
    bool isConnected() const;

    /**
     * Возвращает ссылку на объект подключения к базе данных.
     *
     * @return Ссылка на QSqlDatabase.
     */
    QSqlDatabase& database();

    ~DatabaseManager();

private:
    
    DatabaseManager();

    DatabaseManager(const DatabaseManager&)  =  delete;
    DatabaseManager& operator = (const DatabaseManager&)  =  delete;

    bool createTables();

    bool seedData();

    QString calculateSha256(const QString& input) const;

    QSqlDatabase m_database;    
    QMutex m_mutex;            
    bool m_connected;          
};