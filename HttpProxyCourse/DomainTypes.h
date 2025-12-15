#pragma once

#include <QString>
#include <QStringList>
#include <QList>
#include <QDataStream>
#include <QDebug>

/*!
 * @brief Представляет структуру данных User
 */
struct User {
    int id;
    QString login;
    QString fullName;
    QString role;

    User() : id(-1) {}

    User(int userId, const QString& userLogin, const QString& userFullName, const QString& userRole)
        : id(userId), login(userLogin), fullName(userFullName), role(userRole) {}

    bool isValid() const { return id > 0 && !login.isEmpty(); }

    bool isAdmin() const { return role == "admin"; }
};

/*!
 * @brief Представляет структуру данных Question
 */
struct Question {
    QString text;
    QStringList variants;
    qint32 correctIndex;

    friend QDataStream& operator<<(QDataStream& out, const Question& q) {
        out << q.text << q.variants << q.correctIndex;
        return out;
    }

    friend QDataStream& operator>>(QDataStream& in, Question& q) {
        in >> q.text >> q.variants >> q.correctIndex;
        
        if (q.variants.isEmpty()) {  // Проверка условия
            qWarning() << "Question deserialization: empty variants list, adding default options";
            q.variants << "Да" << "Нет";
            q.correctIndex = 0;
        } else if (q.correctIndex < 0 || q.correctIndex >= q.variants.size()) {  // Проверка условия
            qWarning() << "Question deserialization: invalid correctIndex" << q.correctIndex 
                      << "for" << q.variants.size() << "variants, reset to 0";
            q.correctIndex = 0; 
        }
        
        return in;
    }
};

/*!
 * @brief Представляет структуру данных Topic
 */
struct Topic {
    QString title;
    QString htmlContent;
    QList<Question> questions;

    friend QDataStream& operator<<(QDataStream& out, const Topic& t) {
        out << t.title << t.htmlContent << t.questions;
        return out;
    }

    friend QDataStream& operator>>(QDataStream& in, Topic& t) {
        in >> t.title >> t.htmlContent >> t.questions;
        return in;
    }
};

/*!
 * @brief Представляет структуру данных Course
 */
struct Course {
    QList<Topic> topics;

    friend QDataStream& operator<<(QDataStream& out, const Course& c) {
        out << c.topics;
        return out;
    }

    friend QDataStream& operator>>(QDataStream& in, Course& c) {
        in >> c.topics;
        return in;
    }
};