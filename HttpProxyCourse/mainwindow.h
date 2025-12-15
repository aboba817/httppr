
#pragma once

#include "SessionManager.h"
#include "AuthService.h"
#include "LoginWidget.h"
#include "TopicSelectionWidget.h"
#include "TopicViewWidget.h"
#include "TestWidget.h"
#include "AdminWidget.h"
#include "StudentProfileWidget.h"
#include <QMainWindow>
#include <QStackedWidget>
#include <QMessageBox>
#include <QMenuBar>
#include <QMenu>
#include <QAction>
#include <QDebug>

/*!
 * @brief Реализует функциональность класса MainWindow
 */
class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    
/*!
 * @brief Выполняет основную операцию
 * @param nullptr Входной параметр
 * @return Результат выполнения
 */
    explicit MainWindow(QWidget* parent  =  nullptr);

    ~MainWindow();

private slots:
    
/*!
 * @brief Обрабатывает событие
 */
    void handleStudentStart();

/*!
 * @brief Обрабатывает событие
 * @param user Входной параметр
 */
    void handleUserAuthenticated(const User& user);

/*!
 * @brief Обрабатывает событие
 * @param password Входной параметр
 */
    void handleAdminLogin(const QString& password);

/*!
 * @brief Обрабатывает событие
 */
    void handleLogout();

/*!
 * @brief Выполняет основную операцию
 */
    void onAdminBackRequested();

/*!
 * @brief Выполняет основную операцию
 * @param index Входной параметр
 */
    void onTopicSelected(int index);

/*!
 * @brief Выполняет основную операцию
 */
    void onStartTestRequested();

/*!
 * @brief Выполняет основную операцию
 * @param answerIndex Входной параметр
 */
    void onAnswerSubmitted(int answerIndex);

/*!
 * @brief Выполняет основную операцию
 * @param score Входной параметр
 * @param maxScore Входной параметр
 * @param timeExpired Входной параметр
 */
    void onTestFinished(int score, int maxScore, bool timeExpired);

/*!
 * @brief Выполняет основную операцию
 */
    void showAboutDialog();

/*!
 * @brief Выполняет основную операцию
 */
    void onShowProfileRequested();

private:
    
/*!
 * @brief Загружает данные
 */
    void loadCourseData();

/*!
 * @brief Устанавливает значение
 */
    void setupMenu();

    SessionManager m_sessionManager;
    QStackedWidget* m_stackedWidget;
    LoginWidget* m_loginWidget;
    TopicSelectionWidget* m_topicWidget;
    TopicViewWidget* m_topicViewWidget;
    TestWidget* m_testWidget;
    AdminWidget* m_adminWidget;
    StudentProfileWidget* m_studentProfileWidget;
};