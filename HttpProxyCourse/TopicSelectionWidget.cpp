#include "TopicSelectionWidget.h"
#include <QMessageBox>

TopicSelectionWidget::TopicSelectionWidget(QWidget* parent) : QWidget(parent) {
/*!
 * @brief Выполняет основную операцию
 * @param изучения:" Параметр функции
 * @param this Входной параметр
 * @return Результат выполнения
 */
    m_titleLabel  =  new QLabel("Выберите тему для изучения:", this);  // Создание объекта
    QFont font  =  m_titleLabel->font();
    font.setBold(true);
    font.setPointSize(12);
    m_titleLabel->setFont(font);

/*!
 * @brief Возвращает значение
 * @param this Входной параметр
 * @return Результат выполнения
 */
    m_topicsList  =  new QListWidget(this);  // Создание объекта
/*!
 * @brief Выполняет основную операцию
 * @param тему" Параметр функции
 * @param this Входной параметр
 * @return Результат выполнения
 */
    m_selectButton  =  new QPushButton("Выбрать тему", this);  // Создание объекта
/*!
 * @brief Выполняет основную операцию
 * @param профиль" Параметр функции
 * @param this Входной параметр
 * @return Результат выполнения
 */
    m_profileButton  =  new QPushButton("👤 Мой профиль", this);  // Создание объекта
/*!
 * @brief Выполняет основную операцию
 * @param меню" Параметр функции
 * @param this Входной параметр
 * @return Результат выполнения
 */
    m_logoutButton  =  new QPushButton("Выход в меню", this);  // Создание объекта

/*!
 * @brief Выполняет основную операцию
 * @param this Входной параметр
 * @return Результат выполнения
 */
    QVBoxLayout* layout  =  new QVBoxLayout(this);  // Создание объекта
    layout->addWidget(m_titleLabel);
    layout->addWidget(m_topicsList);

/*!
 * @brief Выполняет основную операцию
 * @return Результат выполнения
 */
    QHBoxLayout* btnLayout  =  new QHBoxLayout();  // Создание объекта
    btnLayout->addWidget(m_logoutButton);
    btnLayout->addWidget(m_profileButton);
    btnLayout->addStretch();
    btnLayout->addWidget(m_selectButton);
    layout->addLayout(btnLayout);

    connect(m_logoutButton, &QPushButton::clicked, this, &TopicSelectionWidget::logoutRequested);  // Подключение сигнала
    connect(m_profileButton, &QPushButton::clicked, this, &TopicSelectionWidget::onProfileClicked);  // Подключение сигнала
    connect(m_selectButton, &QPushButton::clicked, this, &TopicSelectionWidget::onSelectClicked);  // Подключение сигнала
    connect(m_topicsList, &QListWidget::itemDoubleClicked, this, &TopicSelectionWidget::onListDoubleClicked);  // Подключение сигнала
}

void TopicSelectionWidget::setTopics(const QList<Topic>& topics) {
    m_topicsList->clear();
    for (const auto& topic : topics) {  // Цикл обработки данных
        m_topicsList->addItem(topic.title);
    }
}

void TopicSelectionWidget::setLastStudiedTopic(int topicId) {
    
    if (topicId  >=  0 && topicId < m_topicsList->count()) {  // Проверка условия
        m_topicsList->setCurrentRow(topicId);
        m_topicsList->scrollToItem(m_topicsList->item(topicId));
    }
}

void TopicSelectionWidget::onSelectClicked() {
    int currentRow  =  m_topicsList->currentRow();
    if (currentRow  >=  0) {  // Проверка условия
/*!
 * @brief Выполняет основную операцию
 * @param currentRow Входной параметр
 * @return Результат выполнения
 */
        emit topicSelected(currentRow);
    } else {
        QMessageBox::warning(this, "Внимание", "Пожалуйста, выберите тему из списка.");
    }
}

void TopicSelectionWidget::onListDoubleClicked(QListWidgetItem* item) {
    Q_UNUSED(item);
    onSelectClicked();
}

void TopicSelectionWidget::onProfileClicked() {
/*!
 * @brief Выполняет основную операцию
 * @return Результат выполнения
 */
    emit profileRequested();
}