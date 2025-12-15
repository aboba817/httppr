
#pragma once

#include "DomainTypes.h"
#include "Serializer.h"
#include <QString>
#include <QList>
#include <QDateTime>

/*!
 * @brief Определяет перечисление SessionManager
 */
class SessionManager {
public:
    
    static const int MAX_ERRORS  =  3;
    
/*!
 * @brief Определяет перечисление SubmitResult
 */
    enum class SubmitResult {
        Correct,        
        Wrong,          
        FailRelearn,    
        TopicFinished,  
        CourseFinished  
    };

    SessionManager();

/*!
 * @brief Устанавливает значение
 * @param user Входной параметр
 */
    void setCurrentUser(const User& user);

    const User& getCurrentUser() const;

    bool hasUser() const;

/*!
 * @brief Выполняет основную операцию
 */
    void clearSession();

/*!
 * @brief Загружает данные
 * @param filePath Входной параметр
 */
    void loadCourse(const QString& filePath);

    bool isCourseLoaded() const;

/*!
 * @brief Выполняет основную операцию
 * @param topicIndex Входной параметр
 */
    void startTopic(int topicIndex);

    const Course& getCourse() const;

/*!
 * @brief Возвращает значение
 * @return Результат выполнения
 */
    Course& getMutableCourse();

/*!
 * @brief Возвращает значение
 * @return Результат выполнения
 */
    Topic* getCurrentTopic();

/*!
 * @brief Возвращает значение
 * @return Результат выполнения
 */
    Question* getCurrentQuestion();

/*!
 * @brief Выполняет основную операцию
 * @param answerIndex Входной параметр
 * @return Результат выполнения
 */
    SubmitResult submitAnswer(int answerIndex);

/*!
 * @brief Сохраняет данные
 * @return Результат выполнения
 */
    bool saveProgress();

/*!
 * @brief Загружает данные
 * @return Результат выполнения
 */
    bool loadProgress();

private:
    Course currentCourse;
    bool m_isLoaded;
    User m_currentUser;

    qint32 currentTopicIndex;
    qint32 currentQuestionIndex;
    qint32 errorsInTopic;
};