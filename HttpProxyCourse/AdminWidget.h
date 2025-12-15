
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

/*!
 * @brief Реализует функциональность класса AdminWidget
 */
class AdminWidget : public QWidget {
    Q_OBJECT

public:
    
/*!
 * @brief Возвращает значение
 * @param course Входной параметр
 * @param nullptr Входной параметр
 * @return Результат выполнения
 */
    explicit AdminWidget(Course* course, QWidget* parent  =  nullptr);

/*!
 * @brief Устанавливает значение
 * @param user Входной параметр
 */
    void setCurrentUser(const User& user);

signals:
    
/*!
 * @brief Выполняет основную операцию
 */
    void backRequested();

private slots:
    
/*!
 * @brief Выполняет основную операцию
 * @param index Входной параметр
 */
    void onTopicChanged(int index);

/*!
 * @brief Сохраняет данные
 */
    void onSaveClicked();

/*!
 * @brief Выполняет основную операцию
 */
    void onLogoutClicked();

/*!
 * @brief Выполняет основную операцию
 */
    void onFilterChanged();

/*!
 * @brief Выполняет основную операцию
 */
    void onRefreshStatistics();

private:
    
/*!
 * @brief Устанавливает значение
 */
    void setupUi();

/*!
 * @brief Создает объект
 * @return Результат выполнения
 */
    QWidget* createCourseEditTab();

/*!
 * @brief Создает объект
 * @return Результат выполнения
 */
    QWidget* createStudentStatisticsTab();

/*!
 * @brief Загружает данные
 */
    void loadTopics();

/*!
 * @brief Выполняет основную операцию
 */
    void updateStudentStatistics();

/*!
 * @brief Устанавливает значение
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