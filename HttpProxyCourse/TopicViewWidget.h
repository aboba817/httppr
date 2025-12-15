/**
 * Заголовочный файл TopicViewWidget.h.
 * Содержит объявления классов и функций для системы HTTP Proxy Course.
 */

#pragma once

#include "DomainTypes.h"
#include <QWidget>
#include <QTextBrowser>
#include <QPushButton>
#include <QVBoxLayout>

/**
 * Виджет просмотра теоретического материала темы.
 */
class TopicViewWidget : public QWidget {
    Q_OBJECT

public:
    
    explicit TopicViewWidget(QWidget *parent  =  nullptr);

    /**
     * Отображает элемент интерфейса.
     */
    void showTopic(const Topic& topic, int topicIndex);

signals:
    
    void startTestRequested();

    void backRequested();

    void progressUpdateRequested(int topicIndex);

protected:
    
    void closeEvent(QCloseEvent* event) override;

private slots:
    
    void onBackClicked();

private:
    
    /**
     * Обновляет состояние компонента.
     */
    void updateUserProgress();

    QTextBrowser* textBrowser;
    QPushButton* btnStartTest;
    QPushButton* btnBack;
    int currentTopicIndex;  
};