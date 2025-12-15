#pragma once

#include <QObject>
#include <QTimer>
#include <QStackedWidget>
#include "DomainTypes.h"
#include "CourseModel.h"
#include "SessionManager.h"

/*!
 * @brief Реализует функциональность класса LoginWidget
 */
class LoginWidget;
/*!
 * @brief Реализует функциональность класса TopicSelectionWidget
 */
class TopicSelectionWidget;
/*!
 * @brief Реализует функциональность класса TopicViewWidget
 */
class TopicViewWidget;
/*!
 * @brief Реализует функциональность класса TestWidget
 */
class TestWidget;
/*!
 * @brief Реализует функциональность класса AdminWidget
 */
class AdminWidget;
/*!
 * @brief Реализует функциональность класса StudentProfileWidget
 */
class StudentProfileWidget;

/*!
 * @brief Реализует функциональность класса AppController
 */
class AppController : public QObject {
    Q_OBJECT

public:
    
/*!
 * @brief Выполняет основную операцию
 * @param stackedWidget Входной параметр
 * @param nullptr Входной параметр
 * @return Результат выполнения
 */
    explicit AppController(QStackedWidget* stackedWidget, QObject* parent = nullptr);

/*!
 * @brief Инициализирует компонент
 * @return Результат выполнения
 */
    bool initialize();

    CourseModel* getCourseModel() const { return m_courseModel; }

    TestResultsModel* getTestResultsModel() const { return m_testResultsModel; }

public slots:
    
/*!
 * @brief Обрабатывает событие
 * @param user Входной параметр
 */
    void handleUserAuthenticated(const User& user);

/*!
 * @brief Обрабатывает событие
 */
    void handleLogout();

/*!
 * @brief Обрабатывает событие
 * @param topicIndex Входной параметр
 */
    void handleTopicSelected(int topicIndex);

/*!
 * @brief Обрабатывает событие
 */
    void handleStartTest();

/*!
 * @brief Обрабатывает событие
 * @param answerIndex Входной параметр
 */
    void handleAnswerSubmitted(int answerIndex);

/*!
 * @brief Обрабатывает событие
 */
    void handleShowProfile();

/*!
 * @brief Обрабатывает событие
 * @param topicIndex Входной параметр
 */
    void handleProgressUpdate(int topicIndex);

/*!
 * @brief Обрабатывает событие
 */
    void handleAdminBack();

/*!
 * @brief Обрабатывает событие
 */
    void handleTestTimeout();

signals:
    
/*!
 * @brief Выполняет основную операцию
 * @param errorMessage Входной параметр
 */
    void errorOccurred(const QString& errorMessage);

/*!
 * @brief Выполняет основную операцию
 * @param title Входной параметр
 * @param message Входной параметр
 */
    void showMessage(const QString& title, const QString& message);

private slots:
    
/*!
 * @brief Обрабатывает событие
 * @param errorMessage Входной параметр
 */
    void handleCourseModelError(const QString& errorMessage);

/*!
 * @brief Обрабатывает событие
 * @param errorMessage Входной параметр
 */
    void handleTestResultsError(const QString& errorMessage);

private:
    
/*!
 * @brief Устанавливает значение
 */
    void setupViews();

/*!
 * @brief Выполняет основную операцию
 */
    void connectSignals();

/*!
 * @brief Выполняет основную операцию
 * @param widget Входной параметр
 */
    void switchToView(QWidget* widget);

/*!
 * @brief Выполняет основную операцию
 */
    void startNewTest();

/*!
 * @brief Выполняет основную операцию
 */
    void finishTest();

/*!
 * @brief Выполняет основную операцию
 */
    void showNextQuestion();

/*!
 * @brief Сохраняет данные
 * @param userId Входной параметр
 * @param topicId Входной параметр
 * @return Результат выполнения
 */
    bool saveStudentProgress(int userId, int topicId);

/*!
 * @brief Загружает данные
 * @param userId Входной параметр
 * @return Результат выполнения
 */
    int loadStudentProgress(int userId);

    CourseModel* m_courseModel;
    TestResultsModel* m_testResultsModel;
    SessionManager m_sessionManager;
    QStackedWidget* m_stackedWidget;
    LoginWidget* m_loginWidget;
    TopicSelectionWidget* m_topicWidget;
    TopicViewWidget* m_topicViewWidget;
    TestWidget* m_testWidget;
    AdminWidget* m_adminWidget;
    StudentProfileWidget* m_profileWidget;
    QTimer* m_testTimer;
    int m_currentTopicIndex;
    int m_currentQuestionIndex;
    int m_correctAnswers;
    QList<int> m_userAnswers;

    static const int TEST_TIME_LIMIT_MS = 300000;  
};