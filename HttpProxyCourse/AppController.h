/**
 * Заголовочный файл AppController.h.
 * Содержит объявления классов и функций для системы HTTP Proxy Course.
 */

#pragma once

#include <QObject>
#include <QTimer>
#include <QStackedWidget>
#include "DomainTypes.h"
#include "CourseModel.h"
#include "SessionManager.h"

class LoginWidget;
class TopicSelectionWidget;
class TopicViewWidget;
class TestWidget;
class AdminWidget;
class StudentProfileWidget;

/**
 * Главный контроллер приложения, управляющий навигацией между экранами и координацией работы компонентов.
 * Реализует паттерн MVC, обеспечивая связь между моделями данных и представлениями.
 */
class AppController : public QObject {
    Q_OBJECT

public:
    /**
     * Конструктор контроллера приложения.
     *
     * @param stackedWidget Виджет для управления экранами приложения.
     * @param parent Родительский объект для управления памятью.
     */
    explicit AppController(QStackedWidget* stackedWidget, QObject* parent = nullptr);

    /**
     * Инициализирует контроллер и загружает необходимые данные.
     *
     * @return true если инициализация прошла успешно, false в противном случае.
     */
    bool initialize();

    /**
     * Возвращает указатель на модель данных курса.
     *
     * @return Указатель на объект CourseModel.
     */
    CourseModel* getCourseModel() const { return m_courseModel; }

    /**
     * Возвращает указатель на модель результатов тестирования.
     *
     * @return Указатель на объект TestResultsModel.
     */
    TestResultsModel* getTestResultsModel() const { return m_testResultsModel; }

public slots:
    /**
     * Обрабатывает успешную аутентификацию пользователя в системе.
     *
     * @param user Объект пользователя с данными аутентификации.
     */
    void handleUserAuthenticated(const User& user);

    /**
     * Обрабатывает выход пользователя из системы.
     */
    void handleLogout();

    /**
     * Обрабатывает выбор темы для изучения студентом.
     *
     * @param topicIndex Индекс выбранной темы в списке курса.
     */
    void handleTopicSelected(int topicIndex);

    /**
     * Обрабатывает запуск процедуры тестирования.
     */
    void handleStartTest();

    /**
     * Обрабатывает отправку ответа на вопрос теста.
     *
     * @param answerIndex Индекс выбранного варианта ответа.
     */
    void handleAnswerSubmitted(int answerIndex);

    /**
     * Обрабатывает запрос на отображение профиля студента.
     */
    void handleShowProfile();

    /**
     * Обрабатывает обновление прогресса изучения материала.
     *
     * @param topicIndex Индекс изученной темы.
     */
    void handleProgressUpdate(int topicIndex);

    /**
     * Обрабатывает возврат из административной панели.
     */
    void handleAdminBack();

    /**
     * Обрабатывает истечение времени, отведенного на тестирование.
     */
    void handleTestTimeout();

signals:
    /**
     * Сигнал об ошибке в работе контроллера.
     *
     * @param errorMessage Текст сообщения об ошибке.
     */
    void errorOccurred(const QString& errorMessage);

    /**
     * Сигнал о необходимости показать сообщение пользователю.
     *
     * @param title Заголовок сообщения.
     * @param message Текст сообщения.
     */
    void showMessage(const QString& title, const QString& message);

private slots:
    /**
     * Обрабатывает ошибки модели данных курса.
     *
     * @param errorMessage Текст сообщения об ошибке.
     */
    void handleCourseModelError(const QString& errorMessage);

    /**
     * Обрабатывает ошибки модели результатов тестирования.
     *
     * @param errorMessage Текст сообщения об ошибке.
     */
    void handleTestResultsError(const QString& errorMessage);

private:
    /**
     * Создает и настраивает все виджеты приложения.
     */
    void setupViews();

    /**
     * Подключает сигналы и слоты между компонентами системы.
     */
    void connectSignals();

    /**
     * Переключает отображение на указанный виджет.
     *
     * @param widget Виджет для отображения.
     */
    void switchToView(QWidget* widget);

    /**
     * Начинает новый тест для текущего пользователя.
     */
    void startNewTest();

    /**
     * Завершает текущий тест и сохраняет результат.
     */
    void finishTest();

    /**
     * Отображает следующий вопрос в текущем тесте.
     */
    void showNextQuestion();

    /**
     * Сохраняет прогресс студента в базе данных.
     *
     * @param userId Идентификатор пользователя.
     * @param topicId Идентификатор последней изученной темы.
     * @return true если сохранение прошло успешно, false в противном случае.
     */
    bool saveStudentProgress(int userId, int topicId);

    /**
     * Загружает прогресс студента из базы данных.
     *
     * @param userId Идентификатор пользователя.
     * @return Идентификатор последней изученной темы или -1 при ошибке.
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

    static const int TEST_TIME_LIMIT_MS = 300000;  // 5 минут на тест
};