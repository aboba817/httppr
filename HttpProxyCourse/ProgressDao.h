
#pragma once

#include <QString>
#include <QDateTime>

/*!
 * @brief Представляет структуру данных UserProgress
 */
struct UserProgress {
    int userId;              
    int lastTopicId;         
    QDateTime updatedAt;     
    
    UserProgress() : userId(-1), lastTopicId(-1) {}
    
    UserProgress(int uid, int topicId, const QDateTime& updated  =  QDateTime::currentDateTime())
        : userId(uid), lastTopicId(topicId), updatedAt(updated) {}
};

/*!
 * @brief Реализует функциональность класса ProgressDao
 */
class ProgressDao {
public:
    
/*!
 * @brief Выполняет основную операцию
 * @param userId Входной параметр
 * @return Результат выполнения
 */
    static UserProgress findByUserId(int userId);

/*!
 * @brief Выполняет основную операцию
 * @param userId Входной параметр
 * @param topicId Входной параметр
 * @return Результат выполнения
 */
    static bool updateProgress(int userId, int topicId);

/*!
 * @brief Создает объект
 * @param userId Входной параметр
 * @param 0 Входной параметр
 * @return Результат выполнения
 */
    static bool createProgress(int userId, int topicId  =  0);

/*!
 * @brief Выполняет основную операцию
 * @param userId Входной параметр
 * @return Результат выполнения
 */
    static bool deleteByUserId(int userId);
};