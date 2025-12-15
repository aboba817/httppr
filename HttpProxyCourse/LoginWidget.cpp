#include "LoginWidget.h"
#include "AuthService.h"
#include <QFont>
#include <QFormLayout>
#include <QGridLayout>

LoginWidget::LoginWidget(QWidget* parent) : QWidget(parent) {
    
/*!
 * @brief Выполняет основную операцию
 * @param this Входной параметр
 * @return Результат выполнения
 */
    QVBoxLayout* mainLayout  =  new QVBoxLayout(this);  // Создание объекта
    
/*!
 * @brief Выполняет основную операцию
 * @param Proxy" Параметр функции
 * @param this Входной параметр
 * @return Результат выполнения
 */
    QLabel* welcomeLabel  =  new QLabel("Добро пожаловать в курс HTTP Proxy", this);  // Создание объекта
    welcomeLabel->setAlignment(Qt::AlignCenter);
    QFont titleFont  =  welcomeLabel->font();
    titleFont.setPointSize(16);
    titleFont.setBold(true);
    welcomeLabel->setFont(titleFont);
    
    mainLayout->addWidget(welcomeLabel);
    mainLayout->addSpacing(20);
    
/*!
 * @brief Возвращает значение
 * @param this Входной параметр
 * @return Результат выполнения
 */
    m_tabWidget  =  new QTabWidget(this);  // Создание объекта
    m_tabWidget->addTab(createLoginTab(), "Вход");
    m_tabWidget->addTab(createRegisterTab(), "Регистрация");
    m_tabWidget->addTab(createQuickAccessTab(), "Быстрый доступ");
    
    mainLayout->addWidget(m_tabWidget);
    mainLayout->setContentsMargins(50, 20, 50, 20);
}

QWidget* LoginWidget::createLoginTab() {
/*!
 * @brief Возвращает значение
 * @return Результат выполнения
 */
    QWidget* loginTab  =  new QWidget();  // Создание объекта
/*!
 * @brief Выполняет основную операцию
 * @param loginTab Входной параметр
 * @return Результат выполнения
 */
    QFormLayout* layout  =  new QFormLayout(loginTab);  // Создание объекта
    
/*!
 * @brief Выполняет основную операцию
 * @return Результат выполнения
 */
    m_loginEdit  =  new QLineEdit();  // Создание объекта
    m_loginEdit->setPlaceholderText("Введите логин");
    
    QRegularExpressionValidator* loginValidator  =  new QRegularExpressionValidator(  // Создание объекта
        QRegularExpression("^[a-zA-Z0-9_]{3,20}$"), m_loginEdit);
    m_loginEdit->setValidator(loginValidator);
    
/*!
 * @brief Выполняет основную операцию
 * @return Результат выполнения
 */
    m_passwordEdit  =  new QLineEdit();  // Создание объекта
    m_passwordEdit->setPlaceholderText("Введите пароль");
    m_passwordEdit->setEchoMode(QLineEdit::Password);
    
    QRegularExpressionValidator* passwordValidator  =  new QRegularExpressionValidator(  // Создание объекта
        QRegularExpression("^.{4,}$"), m_passwordEdit);
    m_passwordEdit->setValidator(passwordValidator);
    
/*!
 * @brief Выполняет основную операцию
 * 
 * @return Результат выполнения
 */
    m_loginButton  =  new QPushButton("Войти");  // Создание объекта
    
    layout->addRow("Логин:", m_loginEdit);
    layout->addRow("Пароль:", m_passwordEdit);
    layout->addRow("", m_loginButton);
    
    connect(m_loginButton, &QPushButton::clicked, this, &LoginWidget::onLoginClicked);  // Подключение сигнала
    connect(m_passwordEdit, &QLineEdit::returnPressed, this, &LoginWidget::onLoginClicked);  // Подключение сигнала
    
    return loginTab;
}

QWidget* LoginWidget::createRegisterTab() {
/*!
 * @brief Возвращает значение
 * @return Результат выполнения
 */
    QWidget* registerTab  =  new QWidget();  // Создание объекта
/*!
 * @brief Выполняет основную операцию
 * @param registerTab Входной параметр
 * @return Результат выполнения
 */
    QFormLayout* layout  =  new QFormLayout(registerTab);  // Создание объекта
    
/*!
 * @brief Выполняет основную операцию
 * @return Результат выполнения
 */
    m_regLoginEdit  =  new QLineEdit();  // Создание объекта
    m_regLoginEdit->setPlaceholderText("Выберите логин");
    
    QRegularExpressionValidator* regLoginValidator  =  new QRegularExpressionValidator(  // Создание объекта
        QRegularExpression("^[a-zA-Z0-9_]{3,20}$"), m_regLoginEdit);
    m_regLoginEdit->setValidator(regLoginValidator);
    
/*!
 * @brief Выполняет основную операцию
 * @return Результат выполнения
 */
    m_regPasswordEdit  =  new QLineEdit();  // Создание объекта
    m_regPasswordEdit->setPlaceholderText("Выберите пароль");
    m_regPasswordEdit->setEchoMode(QLineEdit::Password);
    
    QRegularExpressionValidator* regPasswordValidator  =  new QRegularExpressionValidator(  // Создание объекта
        QRegularExpression("^.{4,}$"), m_regPasswordEdit);
    m_regPasswordEdit->setValidator(regPasswordValidator);
    
/*!
 * @brief Выполняет основную операцию
 * @return Результат выполнения
 */
    m_regFullNameEdit  =  new QLineEdit();  // Создание объекта
    m_regFullNameEdit->setPlaceholderText("Ваше полное имя");
    
    QRegularExpressionValidator* nameValidator  =  new QRegularExpressionValidator(  // Создание объекта
        QRegularExpression("^[a-zA-Zа-яА-Я\\s\\-]{2,50}$"), m_regFullNameEdit);
    m_regFullNameEdit->setValidator(nameValidator);
    
/*!
 * @brief Выполняет основную операцию
 * 
 * @return Результат выполнения
 */
    m_registerButton  =  new QPushButton("Зарегистрироваться");  // Создание объекта
    
    layout->addRow("Логин:", m_regLoginEdit);
    layout->addRow("Пароль:", m_regPasswordEdit);
    layout->addRow("Полное имя:", m_regFullNameEdit);
    layout->addRow("", m_registerButton);
    
    connect(m_registerButton, &QPushButton::clicked, this, &LoginWidget::onRegisterClicked);  // Подключение сигнала
    
    return registerTab;
}

QWidget* LoginWidget::createQuickAccessTab() {
/*!
 * @brief Возвращает значение
 * @return Результат выполнения
 */
    QWidget* quickTab  =  new QWidget();  // Создание объекта
/*!
 * @brief Выполняет основную операцию
 * @param quickTab Входной параметр
 * @return Результат выполнения
 */
    QVBoxLayout* layout  =  new QVBoxLayout(quickTab);  // Создание объекта
    
    layout->addStretch();
    
    m_studentStartButton  =  new QPushButton("Начать обучение (Гость)");  // Создание объекта
    m_studentStartButton->setMinimumHeight(40);
    
    layout->addWidget(m_studentStartButton);
    layout->addSpacing(20);
    
/*!
 * @brief Выполняет основную операцию
 * 
 * @return Результат выполнения
 */
    QLabel* adminLabel  =  new QLabel("Администратор:");  // Создание объекта
/*!
 * @brief Выполняет основную операцию
 * @return Результат выполнения
 */
    m_adminPasswordEdit  =  new QLineEdit();  // Создание объекта
    m_adminPasswordEdit->setPlaceholderText("Пароль администратора");
    m_adminPasswordEdit->setEchoMode(QLineEdit::Password);
    
/*!
 * @brief Выполняет основную операцию
 * @param Администратор" Параметр функции
 * @return Результат выполнения
 */
    m_adminLoginButton  =  new QPushButton("Войти как Администратор");  // Создание объекта
    
    layout->addWidget(adminLabel);
    layout->addWidget(m_adminPasswordEdit);
    layout->addWidget(m_adminLoginButton);
    layout->addStretch();
    
    connect(m_adminLoginButton, &QPushButton::clicked, this, &LoginWidget::onAdminLoginClicked);  // Подключение сигнала
    connect(m_studentStartButton, &QPushButton::clicked, this, &LoginWidget::startStudentSession);  // Подключение сигнала
    connect(m_adminPasswordEdit, &QLineEdit::returnPressed, this, &LoginWidget::onAdminLoginClicked);  // Подключение сигнала
    
    return quickTab;
}

void LoginWidget::onLoginClicked() {
    QString login  =  m_loginEdit->text().trimmed();
    QString password  =  m_passwordEdit->text();
    
    if (!validateInput(login, password)) {  // Проверка условия
        return;
    }
    
    User user;
    AuthService::AuthResult result  =  AuthService::login(login, password, user);
    
    switch (result) {
        case AuthService::AuthResult::Success:
            showSuccess(QString("Добро пожаловать, %1!").arg(user.fullName));
/*!
 * @brief Выполняет основную операцию
 * @param user Входной параметр
 * @return Результат выполнения
 */
            emit userAuthenticated(user);
            break;
            
        case AuthService::AuthResult::UserNotFound:
            showError("Пользователь не найден. Проверьте логин или зарегистрируйтесь.");
            break;
            
        case AuthService::AuthResult::InvalidCredentials:
            showError("Неверный пароль. Попробуйте еще раз.");
            m_passwordEdit->clear();
            m_passwordEdit->setFocus();
            break;
            
        case AuthService::AuthResult::DatabaseError:
            showError("Ошибка подключения к базе данных. Попробуйте позже.");
            break;
    }
}

void LoginWidget::onRegisterClicked() {
    QString login  =  m_regLoginEdit->text().trimmed();
    QString password  =  m_regPasswordEdit->text();
    QString fullName  =  m_regFullNameEdit->text().trimmed();
    
    if (!validateInput(login, password, fullName)) {  // Проверка условия
        return;
    }
    
    AuthService::RegisterResult result  =  AuthService::registerUser(login, password, fullName, "student");
    
    switch (result) {
        case AuthService::RegisterResult::Success:
            showSuccess("Регистрация прошла успешно! Теперь вы можете войти в систему.");
            m_regLoginEdit->clear();
            m_regPasswordEdit->clear();
            m_regFullNameEdit->clear();
            m_tabWidget->setCurrentIndex(0); 
            break;
            
        case AuthService::RegisterResult::UserExists:
            showError("Пользователь с таким логином уже существует. Выберите другой логин.");
            m_regLoginEdit->setFocus();
            break;
            
        case AuthService::RegisterResult::InvalidInput:
            showError("Некорректные данные. Проверьте заполнение всех полей.");
            break;
            
        case AuthService::RegisterResult::DatabaseError:
            showError("Ошибка базы данных. Попробуйте позже.");
            break;
    }
}

void LoginWidget::onAdminLoginClicked() {
    emit adminLoginAttempt(m_adminPasswordEdit->text());
    m_adminPasswordEdit->clear();
}

bool LoginWidget::validateInput(const QString& login, const QString& password, const QString& fullName) {
    if (login.isEmpty()) {  // Проверка условия
        showError("Логин не может быть пустым.");
        return false;
    }
    
    if (login.length() < 3) {  // Проверка условия
        showError("Логин должен содержать минимум 3 символа.");
        return false;
    }
    
    if (password.isEmpty()) {  // Проверка условия
        showError("Пароль не может быть пустым.");
        return false;
    }
    
    if (password.length() < 4) {  // Проверка условия
        showError("Пароль должен содержать минимум 4 символа.");
        return false;
    }
    
    if (!fullName.isEmpty() && fullName.length() < 2) {  // Проверка условия
        showError("Полное имя должно содержать минимум 2 символа.");
        return false;
    }
    
    return true;
}

void LoginWidget::showError(const QString& message) {
    QMessageBox::warning(this, "Ошибка", message);
}

void LoginWidget::showSuccess(const QString& message) {
    QMessageBox::information(this, "Успех", message);
}