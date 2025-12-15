/**
 * Заголовочный файл TopicSelectionWidget.h.
 * Содержит объявления классов и функций для системы HTTP Proxy Course.
 */

#pragma once

#include "DomainTypes.h"
#include <QWidget>
#include <QLabel>
#include <QListWidget>
#include <QPushButton>
#include <QVBoxLayout>

/**
 * Виджет выбора темы для изучения.
 */
class TopicSelectionWidget : public QWidget {
    Q_OBJECT

public:
    
    explicit TopicSelectionWidget(QWidget *parent  =  nullptr);

    void setTopics(const QList<Topic>& topics);

    void setLastStudiedTopic(int topicId);

signals:
    
    void topicSelected(int index);

    void logoutRequested();

    void profileRequested();

private slots:
    
    void onSelectClicked();

    void onListDoubleClicked(QListWidgetItem *item);

    void onProfileClicked();

private:
    QLabel *m_titleLabel;
    QListWidget *m_topicsList;
    QPushButton *m_selectButton;
    QPushButton *m_profileButton;
    QPushButton *m_logoutButton;
};