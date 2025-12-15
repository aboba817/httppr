/**
 * Заголовочный файл mainwindow.h.
 * Содержит объявления классов и функций для системы HTTP Proxy Course.
 */

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

/**
 * Главное окно приложения с основным интерфейсом пользователя.
 */
class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    
    explicit MainWindow(QWidget *parent  =  nullptr);

    ~MainWindow();

private slots:
    
    /**
     * Обрабатывает событие или сигнал.
     */
    void handleStudentStart();

    /**
     * Обрабатывает событие или сигнал.
     */
    void handleUserAuthenticated(const User& user);

    /**
     * Обрабатывает событие или сигнал.
     */
    void handleAdminLogin(const QString& password);

    /**
     * Обрабатывает событие или сигнал.
     */
    void handleLogout();

    void onAdminBackRequested();

    void onTopicSelected(int index);

    void onStartTestRequested();

    void onAnswerSubmitted(int answerIndex);

    void onTestFinished(int score, int maxScore, bool timeExpired);

    /**
     * Отображает элемент интерфейса.
     */
    void showAboutDialog();

    void onShowProfileRequested();

private:
    
    void loadCourseData();

    /**
     * Настраивает компонент для работы.
     */
    void setupMenu();

    SessionManager m_sessionManager;
    QStackedWidget *m_stackedWidget;
    LoginWidget *m_loginWidget;
    TopicSelectionWidget *m_topicWidget;
    TopicViewWidget *m_topicViewWidget;
    TestWidget *m_testWidget;
    AdminWidget *m_adminWidget;
    StudentProfileWidget *m_studentProfileWidget;
};