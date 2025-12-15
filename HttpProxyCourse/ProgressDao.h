/**
 * Заголовочный файл ProgressDao.h.
 * Содержит объявления классов и функций для системы HTTP Proxy Course.
 */

#pragma once

#include <QString>
#include <QDateTime>

struct UserProgress {
    int userId;              
    int lastTopicId;         
    QDateTime updatedAt;     
    
    UserProgress() : userId(-1), lastTopicId(-1) {}
    
    UserProgress(int uid, int topicId, const QDateTime& updated  =  QDateTime::currentDateTime())
        : userId(uid), lastTopicId(topicId), updatedAt(updated) {}
};

/**
 * Объект доступа к данным прогресса обучения студентов.
 */
class ProgressDao {
public:
    
    static UserProgress findByUserId(int userId);

    static bool updateProgress(int userId, int topicId);

    static bool createProgress(int userId, int topicId  =  0);

    static bool deleteByUserId(int userId);
};