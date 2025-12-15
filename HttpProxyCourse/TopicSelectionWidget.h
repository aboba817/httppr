
#pragma once

#include "DomainTypes.h"
#include <QWidget>
#include <QLabel>
#include <QListWidget>
#include <QPushButton>
#include <QVBoxLayout>

/*!
 * @brief Реализует функциональность класса TopicSelectionWidget
 */
class TopicSelectionWidget : public QWidget {
    Q_OBJECT

public:
    
/*!
 * @brief Возвращает значение
 * @param nullptr Входной параметр
 * @return Результат выполнения
 */
    explicit TopicSelectionWidget(QWidget* parent  =  nullptr);

/*!
 * @brief Устанавливает значение
 * @param topics Входной параметр
 */
    void setTopics(const QList<Topic>& topics);

/*!
 * @brief Устанавливает значение
 * @param topicId Входной параметр
 */
    void setLastStudiedTopic(int topicId);

signals:
    
/*!
 * @brief Выполняет основную операцию
 * @param index Входной параметр
 */
    void topicSelected(int index);

/*!
 * @brief Выполняет основную операцию
 */
    void logoutRequested();

/*!
 * @brief Выполняет основную операцию
 */
    void profileRequested();

private slots:
    
/*!
 * @brief Выполняет основную операцию
 */
    void onSelectClicked();

/*!
 * @brief Выполняет основную операцию
 * @param item Входной параметр
 */
    void onListDoubleClicked(QListWidgetItem* item);

/*!
 * @brief Выполняет основную операцию
 */
    void onProfileClicked();

private:
    QLabel* m_titleLabel;
    QListWidget* m_topicsList;
    QPushButton* m_selectButton;
    QPushButton* m_profileButton;
    QPushButton* m_logoutButton;
};