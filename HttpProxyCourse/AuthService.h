/**
 * Заголовочный файл AuthService.h.
 * Содержит объявления классов и функций для системы HTTP Proxy Course.
 */

#pragma once

#include "DomainTypes.h"
#include <QString>
#include <QSqlError>

/**
 * Сервис аутентификации пользователей с поддержкой различных ролей.
 */
class AuthService {
public:
    
    enum class AuthResult {
        Success,            
        InvalidCredentials, 
        UserNotFound,       
        DatabaseError       
    };
    
    enum class RegisterResult {
        Success,            
        UserExists,         
        InvalidInput,       
        DatabaseError       
    };

    static AuthResult login(const QString& login, const QString& password, User& user);

    static RegisterResult registerUser(const QString& login, const QString& password, 
                                     const QString& fullName, const QString& role  =  "student");

    static bool checkAdminPassword(const QString& password);

    static bool isPasswordStrong(const QString& password);

    static bool isLoginValid(const QString& login);

private:
    
    static QString calculateSha256(const QString& input);
};