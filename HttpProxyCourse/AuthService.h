
#pragma once

#include "DomainTypes.h"
#include <QString>
#include <QSqlError>

/*!
 * @brief Определяет перечисление AuthService
 */
class AuthService {
public:
    
/*!
 * @brief Определяет перечисление AuthResult
 */
    enum class AuthResult {
        Success,            
        InvalidCredentials, 
        UserNotFound,       
        DatabaseError       
    };
    
/*!
 * @brief Определяет перечисление RegisterResult
 */
    enum class RegisterResult {
        Success,            
        UserExists,         
        InvalidInput,       
        DatabaseError       
    };

/*!
 * @brief Выполняет основную операцию
 * @param login Входной параметр
 * @param password Входной параметр
 * @param user Входной параметр
 * @return Результат выполнения
 */
    static AuthResult login(const QString& login, const QString& password, User& user);

    static RegisterResult registerUser(const QString& login, const QString& password, 
                                     const QString& fullName, const QString& role  =  "student");

/*!
 * @brief Выполняет основную операцию
 * @param password Входной параметр
 * @return Результат выполнения
 */
    static bool checkAdminPassword(const QString& password);

/*!
 * @brief Выполняет основную операцию
 * @param password Входной параметр
 * @return Результат выполнения
 */
    static bool isPasswordStrong(const QString& password);

/*!
 * @brief Выполняет основную операцию
 * @param login Входной параметр
 * @return Результат выполнения
 */
    static bool isLoginValid(const QString& login);

private:
    
/*!
 * @brief Выполняет основную операцию
 * @param input Входной параметр
 * @return Результат выполнения
 */
    static QString calculateSha256(const QString& input);
};