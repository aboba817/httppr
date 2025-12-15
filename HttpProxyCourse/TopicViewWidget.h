
#pragma once

#include "DomainTypes.h"
#include <QWidget>
#include <QTextBrowser>
#include <QPushButton>
#include <QVBoxLayout>

/*!
 * @brief Реализует функциональность класса TopicViewWidget
 */
class TopicViewWidget : public QWidget {
    Q_OBJECT

public:
    
/*!
 * @brief Возвращает значение
 * @param nullptr Входной параметр
 * @return Результат выполнения
 */
    explicit TopicViewWidget(QWidget* parent  =  nullptr);

/*!
 * @brief Выполняет основную операцию
 * @param topic Входной параметр
 * @param topicIndex Входной параметр
 */
    void showTopic(const Topic& topic, int topicIndex);

signals:
    
/*!
 * @brief Выполняет основную операцию
 */
    void startTestRequested();

/*!
 * @brief Выполняет основную операцию
 */
    void backRequested();

/*!
 * @brief Выполняет основную операцию
 * @param topicIndex Входной параметр
 */
    void progressUpdateRequested(int topicIndex);

protected:
    
    void closeEvent(QCloseEvent* event) override;

private slots:
    
/*!
 * @brief Выполняет основную операцию
 */
    void onBackClicked();

private:
    
/*!
 * @brief Выполняет основную операцию
 */
    void updateUserProgress();

    QTextBrowser* textBrowser;
    QPushButton* btnStartTest;
    QPushButton* btnBack;
    int currentTopicIndex;  
};