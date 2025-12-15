
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

/*!
 * @brief Реализует функциональность класса LoginWidget
 */
class LoginWidget : public QWidget {
    Q_OBJECT

public:
    
/*!
 * @brief Возвращает значение
 * @param nullptr Входной параметр
 * @return Результат выполнения
 */
    explicit LoginWidget(QWidget* parent  =  nullptr);

signals:
    
/*!
 * @brief Выполняет основную операцию
 * @param user Входной параметр
 */
    void userAuthenticated(const User& user);

/*!
 * @brief Выполняет основную операцию
 * @param password Входной параметр
 */
    void adminLoginAttempt(QString password);

/*!
 * @brief Выполняет основную операцию
 */
    void startStudentSession();

private slots:
    
/*!
 * @brief Выполняет основную операцию
 */
    void onLoginClicked();

/*!
 * @brief Выполняет основную операцию
 */
    void onRegisterClicked();

/*!
 * @brief Выполняет основную операцию
 */
    void onAdminLoginClicked();

private:
    
/*!
 * @brief Создает объект
 * @return Результат выполнения
 */
    QWidget* createLoginTab();

/*!
 * @brief Создает объект
 * @return Результат выполнения
 */
    QWidget* createRegisterTab();

/*!
 * @brief Создает объект
 * @return Результат выполнения
 */
    QWidget* createQuickAccessTab();

    bool validateInput(const QString& login, const QString& password, const QString& fullName  =  QString());

/*!
 * @brief Выполняет основную операцию
 * @param message Входной параметр
 */
    void showError(const QString& message);

/*!
 * @brief Выполняет основную операцию
 * @param message Входной параметр
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