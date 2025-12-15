/**
 * Заголовочный файл LoginWidget.h.
 * Содержит объявления классов и функций для системы HTTP Proxy Course.
 */

#pragma once

#include "DomainTypes.h"
#include <QWidget>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QTabWidget>
#include <QMessageBox>
#include <QRegularExpressionValidator>

/**
 * Виджет авторизации пользователей в системе.
 */
class LoginWidget : public QWidget {
    Q_OBJECT

public:
    
    explicit LoginWidget(QWidget *parent  =  nullptr);

signals:
    
    void userAuthenticated(const User& user);

    void adminLoginAttempt(QString password);

    void startStudentSession();

private slots:
    
    void onLoginClicked();

    void onRegisterClicked();

    void onAdminLoginClicked();

private:
    
    QWidget* createLoginTab();

    QWidget* createRegisterTab();

    QWidget* createQuickAccessTab();

    bool validateInput(const QString& login, const QString& password, const QString& fullName  =  QString());

    /**
     * Отображает элемент интерфейса.
     */
    void showError(const QString& message);

    /**
     * Отображает элемент интерфейса.
     */
    void showSuccess(const QString& message);

    QTabWidget* m_tabWidget;

    QLineEdit* m_loginEdit;
    QLineEdit* m_passwordEdit;
    QPushButton* m_loginButton;

    QLineEdit* m_regLoginEdit;
    QLineEdit* m_regPasswordEdit;
    QLineEdit* m_regFullNameEdit;
    QPushButton* m_registerButton;

    QLineEdit* m_adminPasswordEdit;
    QPushButton* m_adminLoginButton;
    QPushButton* m_studentStartButton;
};