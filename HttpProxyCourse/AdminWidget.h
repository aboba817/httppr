/**
 * Заголовочный файл AdminWidget.h.
 * Содержит объявления классов и функций для системы HTTP Proxy Course.
 */

#pragma once

#include "DomainTypes.h"
#include "Serializer.h"
#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QComboBox>
#include <QTextEdit>
#include <QPushButton>
#include <QMessageBox>
#include <QTabWidget>
#include <QTableView>
#include <QLineEdit>
#include <QSqlQueryModel>
#include <QSortFilterProxyModel>
#include <QGroupBox>
#include <QGridLayout>
#include <QHeaderView>

/**
 * Административная панель для управления системой.
 */
class AdminWidget : public QWidget {
    Q_OBJECT

public:
    
    explicit AdminWidget(Course* course, QWidget* parent  =  nullptr);

    void setCurrentUser(const User& user);

signals:
    
    void backRequested();

private slots:
    
    void onTopicChanged(int index);

    void onSaveClicked();

    void onLogoutClicked();

    void onFilterChanged();

    void onRefreshStatistics();

private:
    
    /**
     * Настраивает компонент для работы.
     */
    void setupUi();

    QWidget* createCourseEditTab();

    QWidget* createStudentStatisticsTab();

    void loadTopics();

    /**
     * Обновляет состояние компонента.
     */
    void updateStudentStatistics();

    /**
     * Настраивает компонент для работы.
     */
    void setupAccessRights();

    Course* m_course;
    User m_currentUser;

    QVBoxLayout* m_layout;
    QTabWidget* m_tabWidget;
    QPushButton* m_btnLogout;

    QLabel* m_lblHeader;
    QComboBox* m_cbTopics;
    QTextEdit* m_txtHtmlEditor;
    QPushButton* m_btnSave;

    QLineEdit* m_filterEdit;
    QTableView* m_statisticsTable;
    QSqlQueryModel* m_statisticsModel;
    QSortFilterProxyModel* m_proxyModel;
    QPushButton* m_btnRefreshStats;
};