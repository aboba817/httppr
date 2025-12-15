#include "StudentProfileWidget.h"
#include "TestResultDao.h"
#include "DatabaseManager.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QMessageBox>
#include <QDebug>
#include <QFont>
#include <QDateTime>

StudentProfileWidget::StudentProfileWidget(QWidget* parent)
    : QWidget(parent)
    , m_testHistoryModel(nullptr) {
    setWindowTitle("Профиль студента");
    
/*!
 * @brief Выполняет основную операцию
 * @param this Входной параметр
 * @return Результат выполнения
 */
    QVBoxLayout* mainLayout  =  new QVBoxLayout(this);  // Создание объекта
    
/*!
 * @brief Выполняет основную операцию
 * @param студента" Параметр функции
 * @param this Входной параметр
 * @return Результат выполнения
 */
    QLabel* titleLabel  =  new QLabel("Профиль студента", this);  // Создание объекта
    QFont titleFont  =  titleLabel->font();
    titleFont.setPointSize(16);
    titleFont.setBold(true);
    titleLabel->setFont(titleFont);
    titleLabel->setAlignment(Qt::AlignCenter);
    
/*!
 * @brief Выполняет основную операцию
 * @return Результат выполнения
 */
    QHBoxLayout* buttonLayout  =  new QHBoxLayout();  // Создание объекта
/*!
 * @brief Выполняет основную операцию
 * @param Назад" Параметр функции
 * @param this Входной параметр
 * @return Результат выполнения
 */
    m_backButton  =  new QPushButton("← Назад", this);  // Создание объекта
/*!
 * @brief Выполняет основную операцию
 * @param Обновить" Параметр функции
 * @param this Входной параметр
 * @return Результат выполнения
 */
    m_refreshButton  =  new QPushButton("🔄 Обновить", this);  // Создание объекта
    
    buttonLayout->addWidget(m_backButton);
    buttonLayout->addStretch();
    buttonLayout->addWidget(m_refreshButton);
    
    mainLayout->addWidget(titleLabel);
    mainLayout->addLayout(buttonLayout);
    mainLayout->addSpacing(10);
    mainLayout->addWidget(createUserInfoSection());
    mainLayout->addWidget(createStatisticsSection());
    mainLayout->addWidget(createTestHistorySection(), 1); 
    
    connect(m_backButton, &QPushButton::clicked, this, &StudentProfileWidget::onBackClicked);  // Подключение сигнала
    connect(m_refreshButton, &QPushButton::clicked, this, &StudentProfileWidget::onRefreshClicked);  // Подключение сигнала
    
/*!
 * @brief Выполняет основную операцию
 * @param this Входной параметр
 * @return Результат выполнения
 */
    m_testHistoryModel  =  new QSqlQueryModel(this);  // Создание объекта
}

void StudentProfileWidget::setCurrentUser(const User& user) {
    m_currentUser  =  user;
    refreshData();
}

void StudentProfileWidget::setUser(const User& user) {
    
    setCurrentUser(user);
}

void StudentProfileWidget::setResultsModel(QAbstractItemModel* model) {
    if (m_testHistoryTable) {  // Проверка условия
        m_testHistoryTable->setModel(model);
    }
}

void StudentProfileWidget::refreshData() {
    if (!m_currentUser.isValid()) {  // Проверка условия
        return;
    }
    
    updateUserInfo();
    updateStatistics();
    updateTestHistory();
}

void StudentProfileWidget::onBackClicked() {
/*!
 * @brief Выполняет основную операцию
 * @return Результат выполнения
 */
    emit backRequested();
}

void StudentProfileWidget::onRefreshClicked() {
    refreshData();
    QMessageBox::information(this, "Обновлено", "Данные профиля обновлены.");
}

QWidget* StudentProfileWidget::createUserInfoSection() {
/*!
 * @brief Выполняет основную операцию
 * @param пользователе" Параметр функции
 * @param this Входной параметр
 * @return Результат выполнения
 */
    QGroupBox* groupBox  =  new QGroupBox("Информация о пользователе", this);  // Создание объекта
/*!
 * @brief Выполняет основную операцию
 * @param groupBox Входной параметр
 * @return Результат выполнения
 */
    QGridLayout* layout  =  new QGridLayout(groupBox);  // Создание объекта
    
    layout->addWidget(new QLabel("Полное имя:"), 0, 0);  // Создание объекта
/*!
 * @brief Выполняет основную операцию
 * 
 * @param groupBox Входной параметр
 * @return Результат выполнения
 */
    m_userNameLabel  =  new QLabel("—", groupBox);  // Создание объекта
    layout->addWidget(m_userNameLabel, 0, 1);
    
    layout->addWidget(new QLabel("Логин:"), 1, 0);  // Создание объекта
/*!
 * @brief Выполняет основную операцию
 * 
 * @param groupBox Входной параметр
 * @return Результат выполнения
 */
    m_userLoginLabel  =  new QLabel("—", groupBox);  // Создание объекта
    layout->addWidget(m_userLoginLabel, 1, 1);
    
    layout->addWidget(new QLabel("Роль:"), 2, 0);  // Создание объекта
/*!
 * @brief Выполняет основную операцию
 * 
 * @param groupBox Входной параметр
 * @return Результат выполнения
 */
    m_userRoleLabel  =  new QLabel("—", groupBox);  // Создание объекта
    layout->addWidget(m_userRoleLabel, 2, 1);
    
    layout->setColumnStretch(1, 1);
    
    return groupBox;
}

QWidget* StudentProfileWidget::createStatisticsSection() {
/*!
 * @brief Выполняет основную операцию
 * @param тестирования" Параметр функции
 * @param this Входной параметр
 * @return Результат выполнения
 */
    QGroupBox* groupBox  =  new QGroupBox("Статистика тестирования", this);  // Создание объекта
/*!
 * @brief Выполняет основную операцию
 * @param groupBox Входной параметр
 * @return Результат выполнения
 */
    QGridLayout* layout  =  new QGridLayout(groupBox);  // Создание объекта
    
    layout->addWidget(new QLabel("Всего тестов:"), 0, 0);  // Создание объекта
/*!
 * @brief Выполняет основную операцию
 * 
 * @param groupBox Входной параметр
 * @return Результат выполнения
 */
    m_totalTestsLabel  =  new QLabel("—", groupBox);  // Создание объекта
    layout->addWidget(m_totalTestsLabel, 0, 1);
    
    layout->addWidget(new QLabel("Средний балл:"), 0, 2);  // Создание объекта
/*!
 * @brief Выполняет основную операцию
 * 
 * @param groupBox Входной параметр
 * @return Результат выполнения
 */
    m_averageScoreLabel  =  new QLabel("—", groupBox);  // Создание объекта
    layout->addWidget(m_averageScoreLabel, 0, 3);
    
    layout->addWidget(new QLabel("Лучший результат:"), 1, 0);  // Создание объекта
/*!
 * @brief Выполняет основную операцию
 * 
 * @param groupBox Входной параметр
 * @return Результат выполнения
 */
    m_bestScoreLabel  =  new QLabel("—", groupBox);  // Создание объекта
    layout->addWidget(m_bestScoreLabel, 1, 1);
    
    layout->addWidget(new QLabel("Последний тест:"), 1, 2);  // Создание объекта
/*!
 * @brief Выполняет основную операцию
 * 
 * @param groupBox Входной параметр
 * @return Результат выполнения
 */
    m_lastTestLabel  =  new QLabel("—", groupBox);  // Создание объекта
    layout->addWidget(m_lastTestLabel, 1, 3);
    
    layout->setColumnStretch(1, 1);
    layout->setColumnStretch(3, 1);
    
    return groupBox;
}

QWidget* StudentProfileWidget::createTestHistorySection() {
/*!
 * @brief Выполняет основную операцию
 * @param тестирования" Параметр функции
 * @param this Входной параметр
 * @return Результат выполнения
 */
    QGroupBox* groupBox  =  new QGroupBox("История тестирования", this);  // Создание объекта
/*!
 * @brief Выполняет основную операцию
 * @param groupBox Входной параметр
 * @return Результат выполнения
 */
    QVBoxLayout* layout  =  new QVBoxLayout(groupBox);  // Создание объекта
    
/*!
 * @brief Выполняет основную операцию
 * @param groupBox Входной параметр
 * @return Результат выполнения
 */
    m_testHistoryTable  =  new QTableView(groupBox);  // Создание объекта
    m_testHistoryTable->setAlternatingRowColors(true);
    m_testHistoryTable->setSelectionBehavior(QAbstractItemView::SelectRows);
    m_testHistoryTable->setSortingEnabled(true);
    
    m_testHistoryTable->horizontalHeader()->setStretchLastSection(true);
    m_testHistoryTable->verticalHeader()->setVisible(false);
    
    layout->addWidget(m_testHistoryTable);
    
    return groupBox;
}

void StudentProfileWidget::updateUserInfo() {
    if (!m_currentUser.isValid()) {  // Проверка условия
        m_userNameLabel->setText("—");
        m_userLoginLabel->setText("—");
        m_userRoleLabel->setText("—");
        return;
    }
    
    m_userNameLabel->setText(m_currentUser.fullName);
    m_userLoginLabel->setText(m_currentUser.login);
    
    QString roleText  =  m_currentUser.role;
    if (roleText  ==  "admin") {  // Проверка условия
        roleText  =  "Администратор";
/*!
 * @brief Выполняет основную операцию
 * 
 * @return Результат выполнения
 */
    } else if (roleText  ==  "student") {  // Проверка условия
        roleText  =  "Студент";
    }
    m_userRoleLabel->setText(roleText);
}

void StudentProfileWidget::updateStatistics() {
    if (!m_currentUser.isValid()) {  // Проверка условия
        m_totalTestsLabel->setText("—");
        m_averageScoreLabel->setText("—");
        m_bestScoreLabel->setText("—");
        m_lastTestLabel->setText("—");
        return;
    }
    
    QList<TestResult> results  =  TestResultDao::findByUserId(m_currentUser.id);
    int totalTests  =  results.size();
    
    m_totalTestsLabel->setText(QString::number(totalTests));
    
    if (totalTests > 0) {  // Проверка условия
        
        double avgPercentage  =  TestResultDao::getAverageScore(m_currentUser.id);
        
        TestResult bestResult  =  TestResultDao::getBestResult(m_currentUser.id);
        double bestPercentage  =  bestResult.getPercentage();
        
        QDateTime lastTestDate  =  results.first().testDate;
        
        m_averageScoreLabel->setText(QString("%1%").arg(avgPercentage, 0, 'f', 1));
        m_bestScoreLabel->setText(QString("%1%").arg(bestPercentage, 0, 'f', 1));
        m_lastTestLabel->setText(lastTestDate.toString("dd.MM.yyyy hh:mm"));
    } else {
        m_averageScoreLabel->setText("—");
        m_bestScoreLabel->setText("—");
        m_lastTestLabel->setText("—");
    }
}

void StudentProfileWidget::updateTestHistory() {
    if (!m_currentUser.isValid() || !DatabaseManager::instance().isConnected()) {  // Проверка условия
        m_testHistoryModel->clear();
        return;
    }
    
    QString queryString  =  
        "SELECT "
            "id as \"ID\", "
            "test_date as \"Дата и время\", "
            "score as \"Набрано баллов\", "
            "max_score as \"Максимум баллов\", "
            "ROUND(CAST(score AS FLOAT) / CAST(max_score AS FLOAT) * 100, 1) as \"Процент (%)\" "
        "FROM test_results "
        "WHERE user_id  =  ? "
        "ORDER BY test_date DESC";
    
    QSqlQuery query(DatabaseManager::instance().database());  // Работа с базой данных
    query.prepare(queryString);  // Выполнение SQL запроса
    query.addBindValue(m_currentUser.id);
    
    if (!query.exec()) {  // Проверка условия
        qCritical() << "Failed to fetch test history:" << query.lastError().text();
        QMessageBox::warning(this, "Ошибка", "Не удалось загрузить историю тестов.");
        return;
    }
    
    m_testHistoryModel->setQuery(query);
    m_testHistoryTable->setModel(m_testHistoryModel);
    
    if (m_testHistoryModel->lastError().isValid()) {  // Проверка условия
        qCritical() << "Model error:" << m_testHistoryModel->lastError().text();
        QMessageBox::warning(this, "Ошибка", "Ошибка при отображении данных.");
        return;
    }
    
    m_testHistoryTable->resizeColumnsToContents();
    
    qDebug() << "Test history updated for user" << m_currentUser.login 
             << "- found" << m_testHistoryModel->rowCount() << "records";
}