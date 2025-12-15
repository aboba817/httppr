/**
 * Заголовочный файл SessionManager.h.
 * Содержит объявления классов и функций для системы HTTP Proxy Course.
 */

#pragma once

#include "DomainTypes.h"
#include "Serializer.h"
#include <QString>
#include <QList>
#include <QDateTime>

/**
 * Менеджер сессий пользователей для отслеживания активных подключений.
 */
class SessionManager {
public:
    
    static const int MAX_ERRORS  =  3;
    
    enum class SubmitResult {
        Correct,        
        Wrong,          
        FailRelearn,    
        TopicFinished,  
        CourseFinished  
    };

    SessionManager();

    void setCurrentUser(const User& user);

    const User& getCurrentUser() const;

    bool hasUser() const;

    /**
     * Очищает данные или состояние.
     */
    void clearSession();

    void loadCourse(const QString& filePath);

    bool isCourseLoaded() const;

    void startTopic(int topicIndex);

    const Course& getCourse() const;

    Course& getMutableCourse();

    Topic* getCurrentTopic();

    Question* getCurrentQuestion();

    SubmitResult submitAnswer(int answerIndex);

    /**
     * Сохраняет данные в хранилище.
     */
    bool saveProgress();

    /**
     * Загружает данные из хранилища.
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