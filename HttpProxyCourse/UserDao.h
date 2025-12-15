/**
 * Заголовочный файл UserDao.h.
 * Содержит объявления классов и функций для системы HTTP Proxy Course.
 */

#pragma once

#include "DomainTypes.h"
#include <QString>
#include <QList>

/**
 * Объект доступа к данным пользователей в базе данных.
 */
class UserDao {
public:
    
    static User findByLogin(const QString& login);

    static bool create(const User& user, const QString& passwordHash);

    static bool existsByLogin(const QString& login);

    static QList<User> findAll();

    static bool update(const User& user);

    static bool deleteById(int userId);
};