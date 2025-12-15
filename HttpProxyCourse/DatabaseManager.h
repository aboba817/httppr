
#pragma once

#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QString>
#include <QMutex>
#include "DatabaseConfig.h"

/*!
 * @brief Реализует функциональность класса DatabaseManager
 */
class DatabaseManager {
public:
    
/*!
 * @brief Выполняет основную операцию
 * @return Результат выполнения
 */
    static DatabaseManager& instance();

/*!
 * @brief Выполняет основную операцию
 * @return Результат выполнения
 */
    bool connectDb();

/*!
 * @brief Инициализирует компонент
 * @return Результат выполнения
 */
    bool initSchema();

    bool isConnected() const;

/*!
 * @brief Выполняет основную операцию
 * @return Результат выполнения
 */
    QSqlDatabase& database();

    ~DatabaseManager();

private:
    
    DatabaseManager();

    DatabaseManager(const DatabaseManager&)  =  delete;
    DatabaseManager& operator = (const DatabaseManager&)  =  delete;

/*!
 * @brief Создает объект
 * @return Результат выполнения
 */
    bool createTables();

/*!
 * @brief Выполняет основную операцию
 * @return Результат выполнения
 */
    bool seedData();

    QString calculateSha256(const QString& input) const;

    QSqlDatabase m_database;    
    QMutex m_mutex;            
    bool m_connected;          
};