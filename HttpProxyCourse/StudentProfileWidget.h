
#pragma once

#include "DomainTypes.h"
#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QTableView>
#include <QPushButton>
#include <QSqlQueryModel>
#include <QHeaderView>
#include <QGroupBox>
#include <QGridLayout>
#include <QSqlQuery>

/*!
 * @brief Реализует функциональность класса StudentProfileWidget
 */
class StudentProfileWidget : public QWidget {
    Q_OBJECT

public:
    
/*!
 * @brief Возвращает значение
 * @param nullptr Входной параметр
 * @return Результат выполнения
 */
    explicit StudentProfileWidget(QWidget* parent  =  nullptr);

/*!
 * @brief Устанавливает значение
 * @param user Входной параметр
 */
    void setCurrentUser(const User& user);

/*!
 * @brief Устанавливает значение
 * @param user Входной параметр
 */
    void setUser(const User& user);

/*!
 * @brief Выполняет основную операцию
 */
    void refreshData();

/*!
 * @brief Устанавливает значение
 * @param model Входной параметр
 */
    void setResultsModel(QAbstractItemModel* model);

signals:
    
/*!
 * @brief Выполняет основную операцию
 */
    void backRequested();

private slots:
    
/*!
 * @brief Выполняет основную операцию
 */
    void onBackClicked();

/*!
 * @brief Выполняет основную операцию
 */
    void onRefreshClicked();

private:
    
/*!
 * @brief Создает объект
 * @return Результат выполнения
 */
    QWidget* createUserInfoSection();

/*!
 * @brief Создает объект
 * @return Результат выполнения
 */
    QWidget* createStatisticsSection();

/*!
 * @brief Создает объект
 * @return Результат выполнения
 */
    QWidget* createTestHistorySection();

/*!
 * @brief Выполняет основную операцию
 */
    void updateUserInfo();

/*!
 * @brief Выполняет основную операцию
 */
    void updateStatistics();

/*!
 * @brief Выполняет основную операцию
 */
    void updateTestHistory();

    User m_currentUser;

    QLabel* m_userNameLabel;
    QLabel* m_userLoginLabel;
    QLabel* m_userRoleLabel;

    QLabel* m_totalTestsLabel;
    QLabel* m_averageScoreLabel;
    QLabel* m_bestScoreLabel;
    QLabel* m_lastTestLabel;

    QTableView* m_testHistoryTable;
    QSqlQueryModel* m_testHistoryModel;

    QPushButton* m_backButton;
    QPushButton* m_refreshButton;
};