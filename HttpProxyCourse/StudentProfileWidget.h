/**
 * Заголовочный файл StudentProfileWidget.h.
 * Содержит объявления классов и функций для системы HTTP Proxy Course.
 */

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

/**
 * Виджет профиля студента с информацией о прогрессе.
 */
class StudentProfileWidget : public QWidget {
    Q_OBJECT

public:
    
    explicit StudentProfileWidget(QWidget *parent  =  nullptr);

    void setCurrentUser(const User& user);

    void setUser(const User& user);

    void refreshData();

    void setResultsModel(QAbstractItemModel* model);

signals:
    
    void backRequested();

private slots:
    
    void onBackClicked();

    void onRefreshClicked();

private:
    
    QWidget* createUserInfoSection();

    QWidget* createStatisticsSection();

    QWidget* createTestHistorySection();

    /**
     * Обновляет состояние компонента.
     */
    void updateUserInfo();

    /**
     * Обновляет состояние компонента.
     */
    void updateStatistics();

    /**
     * Обновляет состояние компонента.
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