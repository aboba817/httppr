
#pragma once

#include "DomainTypes.h"
#include <QString>
#include <QList>

/*!
 * @brief Реализует функциональность класса UserDao
 */
class UserDao {
public:
    
/*!
 * @brief Выполняет основную операцию
 * @param login Входной параметр
 * @return Результат выполнения
 */
    static User findByLogin(const QString& login);

/*!
 * @brief Создает объект
 * @param user Входной параметр
 * @param passwordHash Входной параметр
 * @return Результат выполнения
 */
    static bool create(const User& user, const QString& passwordHash);

/*!
 * @brief Выполняет основную операцию
 * @param login Входной параметр
 * @return Результат выполнения
 */
    static bool existsByLogin(const QString& login);

    static QList<User> findAll();

/*!
 * @brief Выполняет основную операцию
 * @param user Входной параметр
 * @return Результат выполнения
 */
    static bool update(const User& user);

/*!
 * @brief Выполняет основную операцию
 * @param userId Входной параметр
 * @return Результат выполнения
 */
    static bool deleteById(int userId);
};