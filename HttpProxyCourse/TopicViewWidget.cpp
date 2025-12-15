#include "TopicViewWidget.h"
#include "ProgressDao.h"
#include "SessionManager.h"
#include <QCloseEvent>
#include <QDebug>

TopicViewWidget::TopicViewWidget(QWidget* parent) : QWidget(parent), currentTopicIndex(-1) {
/*!
 * @brief Выполняет основную операцию
 * @param this Входной параметр
 * @return Результат выполнения
 */
    auto layout  =  new QVBoxLayout(this);  // Создание объекта

/*!
 * @brief Выполняет основную операцию
 * @param this Входной параметр
 * @return Результат выполнения
 */
    textBrowser  =  new QTextBrowser(this);  // Создание объекта
    textBrowser->setReadOnly(true);
    textBrowser->setOpenExternalLinks(false);

/*!
 * @brief Выполняет основную операцию
 * @param тесту" Параметр функции
 * @param this Входной параметр
 * @return Результат выполнения
 */
    btnStartTest  =  new QPushButton("Перейти к тесту", this);  // Создание объекта
/*!
 * @brief Выполняет основную операцию
 * @param списку" Параметр функции
 * @param this Входной параметр
 * @return Результат выполнения
 */
    btnBack  =  new QPushButton("Назад к списку", this);  // Создание объекта

    layout->addWidget(textBrowser);
    layout->addWidget(btnStartTest);
    layout->addWidget(btnBack);

    connect(btnStartTest, &QPushButton::clicked, this, &TopicViewWidget::startTestRequested);  // Подключение сигнала
    connect(btnBack, &QPushButton::clicked, this, &TopicViewWidget::onBackClicked);  // Подключение сигнала
}

void TopicViewWidget::showTopic(const Topic& topic, int topicIndex) {
    textBrowser->setHtml(topic.htmlContent);
    currentTopicIndex  =  topicIndex;
    qDebug() << "Showing topic" << topicIndex << ":" << topic.title;
}

void TopicViewWidget::closeEvent(QCloseEvent* event) {
    updateUserProgress();
    QWidget::closeEvent(event);
}

void TopicViewWidget::onBackClicked() {
    updateUserProgress();
/*!
 * @brief Выполняет основную операцию
 * @return Результат выполнения
 */
    emit backRequested();
}

void TopicViewWidget::updateUserProgress() {
    if (currentTopicIndex < 0) {  // Проверка условия
        return; 
    }
    
/*!
 * @brief Выполняет основную операцию
 * @param currentTopicIndex Входной параметр
 * @return Результат выполнения
 */
    emit progressUpdateRequested(currentTopicIndex);
}