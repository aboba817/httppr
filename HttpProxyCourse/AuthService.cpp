#include "AuthService.h"
#include "DatabaseManager.h"
#include "Logger.h"
#include <QCryptographicHash>
#include <QByteArray>
#include <QSqlQuery>
#include <QSqlError>
#include <QRegularExpression>
#include <QDebug>

AuthService::AuthResult AuthService::login(const QString& login, const QString& password, User& user) {
    
    if (login.trimmed().isEmpty() || password.isEmpty()) {  // Проверка условия
        return AuthResult::InvalidCredentials;
    }

    DatabaseManager& dbManager  =  DatabaseManager::instance();  // Работа с базой данных
    if (!dbManager.isConnected()) {  // Проверка условия
        qCritical() << "Database not connected for authentication";
        return AuthResult::DatabaseError;
    }

    QSqlQuery query(dbManager.database());
    query.prepare("SELECT id, login, password_hash, full_name, role FROM users WHERE login  =  ?");  // Выполнение SQL запроса
    query.addBindValue(login.trimmed());

    if (!query.exec()) {  // Проверка условия
        qCritical() << "Failed to execute login query:" << query.lastError().text();
        return AuthResult::DatabaseError;
    }

    if (!query.next()) {  // Проверка условия
        qDebug() << "User not found:" << login;
        return AuthResult::UserNotFound;
    }

    int userId  =  query.value("id").toInt();
    QString storedLogin  =  query.value("login").toString();
    QString storedHash  =  query.value("password_hash").toString();
    QString fullName  =  query.value("full_name").toString();
    QString role  =  query.value("role").toString();

    QString inputHash  =  calculateSha256(password);
    if (inputHash  !=  storedHash) {  // Проверка условия
        qDebug() << "Invalid password for user:" << login;
        return AuthResult::InvalidCredentials;
    }

    user  =  User(userId, storedLogin, fullName, role);
    qDebug() << "User authenticated successfully:" << login << "(" << role << ")";
    
    return AuthResult::Success;
}

AuthService::RegisterResult AuthService::registerUser(const QString& login, const QString& password, 
                                                    const QString& fullName, const QString& role) {
    
    if (login.trimmed().isEmpty() || password.isEmpty() || fullName.trimmed().isEmpty()) {  // Проверка условия
        Logger::warning("Попытка регистрации с пустыми полями", "Auth");  // Логирование события
        return RegisterResult::InvalidInput;
    }

    if (!isLoginValid(login)) {  // Проверка условия
        Logger::warning("Попытка регистрации с невалидным логином: " + login, "Auth");  // Логирование события
        return RegisterResult::InvalidInput;
    }

    if (!isPasswordStrong(password)) {  // Проверка условия
        Logger::warning("Попытка регистрации со слабым паролем для пользователя: " + login, "Auth");  // Логирование события
        return RegisterResult::InvalidInput;
    }

    DatabaseManager& dbManager  =  DatabaseManager::instance();  // Работа с базой данных
    if (!dbManager.isConnected()) {  // Проверка условия
        qCritical() << "Database not connected for registration";
        return RegisterResult::DatabaseError;
    }

    QSqlQuery checkQuery(dbManager.database());
    checkQuery.prepare("SELECT COUNT(*) FROM users WHERE login  =  ?");
    checkQuery.addBindValue(login.trimmed());
    
    if (!checkQuery.exec()) {  // Проверка условия
        qCritical() << "Failed to check user existence:" << checkQuery.lastError().text();
        return RegisterResult::DatabaseError;
    }
    
    if (checkQuery.next() && checkQuery.value(0).toInt() > 0) {  // Проверка условия
        qDebug() << "User already exists:" << login;
        return RegisterResult::UserExists;
    }

    QString passwordHash  =  calculateSha256(password);
    
    QSqlQuery insertQuery(dbManager.database());
    insertQuery.prepare("INSERT INTO users (login, password_hash, full_name, role) VALUES (?, ?, ?, ?)");
    insertQuery.addBindValue(login.trimmed());
    insertQuery.addBindValue(passwordHash);
    insertQuery.addBindValue(fullName.trimmed());
    insertQuery.addBindValue(role);

    if (!insertQuery.exec()) {  // Проверка условия
        qCritical() << "Failed to register user:" << insertQuery.lastError().text();
        return RegisterResult::DatabaseError;
    }

    qDebug() << "User registered successfully:" << login << "(" << role << ")";
    return RegisterResult::Success;
}

bool AuthService::checkAdminPassword(const QString& password) {
    User user;
    AuthResult result  =  login("admin", password, user);
    return result  ==  AuthResult::Success && user.isAdmin();
}

QString AuthService::calculateSha256(const QString& input) {
    QByteArray hashBytes  =  QCryptographicHash::hash(
        input.toUtf8(),
        QCryptographicHash::Sha256
    );
    return QString::fromLatin1(hashBytes.toHex());
}

bool AuthService::isPasswordStrong(const QString& password) {
    
    if (password.length() < 4) {  // Проверка условия
        return false;
    }

    return true; 
}

bool AuthService::isLoginValid(const QString& login) {
    
    if (login.length() < 3 || login.length() > 20) {  // Проверка условия
        return false;
    }

/*!
 * @brief Выполняет основную операцию
 * 
 * @return Результат выполнения
 */
    QRegularExpression loginRegex("^[a-zA-Z0-9_]+$");
    return loginRegex.match(login).hasMatch();
}