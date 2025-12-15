#include "TestWidget.h"
#include "TestResultDao.h"
#include "DatabaseManager.h"
#include <QMessageBox>
#include <QHBoxLayout>
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>

TestWidget::TestWidget(QWidget* parent) 
    : QWidget(parent)
    , m_currentQuestionIndex(0)
    , m_correctAnswers(0)
    , m_timeLimitMinutes(20)
    , m_testActive(false) {
/*!
 * @brief Выполняет основную операцию
 * @param this Входной параметр
 * @return Результат выполнения
 */
    auto mainLayout  =  new QVBoxLayout(this);  // Создание объекта

/*!
 * @brief Выполняет основную операцию
 * @return Результат выполнения
 */
    auto statusLayout  =  new QHBoxLayout();  // Создание объекта
    
/*!
 * @brief Выполняет основную операцию
 * @param --:--" Параметр функции
 * @param this Входной параметр
 * @return Результат выполнения
 */
    m_timeLabel  =  new QLabel("Время: --:--", this);  // Создание объекта
    m_timeLabel->setStyleSheet("QLabel { color: red; font-weight: bold; }");
    
/*!
 * @brief Выполняет основную операцию
 * @param 0/0" Параметр функции
 * @param this Входной параметр
 * @return Результат выполнения
 */
    m_progressLabel  =  new QLabel("Вопрос: 0/0", this);  // Создание объекта
    
    statusLayout->addWidget(m_timeLabel);
    statusLayout->addStretch();
    statusLayout->addWidget(m_progressLabel);
    
/*!
 * @brief Выполняет основную операцию
 * @param this Входной параметр
 * @return Результат выполнения
 */
    m_progressBar  =  new QProgressBar(this);  // Создание объекта
    m_progressBar->setVisible(false);

/*!
 * @brief Выполняет основную операцию
 * 
 * @param this Входной параметр
 * @return Результат выполнения
 */
    questionLabel  =  new QLabel("Загрузка...", this);  // Создание объекта
    questionLabel->setWordWrap(true);
    QFont f  =  questionLabel->font();
    f.setPointSize(12);
    f.setBold(true);
    questionLabel->setFont(f);

/*!
 * @brief Возвращает значение
 * @param this Входной параметр
 * @return Результат выполнения
 */
    variantsContainer  =  new QWidget(this);  // Создание объекта
/*!
 * @brief Выполняет основную операцию
 * @param variantsContainer Входной параметр
 * @return Результат выполнения
 */
    variantsLayout  =  new QVBoxLayout(variantsContainer);  // Создание объекта
/*!
 * @brief Выполняет основную операцию
 * 
 * @param this Входной параметр
 * @return Результат выполнения
 */
    btnAnswer  =  new QPushButton("Ответить", this);  // Создание объекта

    mainLayout->addLayout(statusLayout);
    mainLayout->addWidget(m_progressBar);
    mainLayout->addSpacing(10);
    mainLayout->addWidget(questionLabel);
    mainLayout->addWidget(variantsContainer);
    mainLayout->addWidget(btnAnswer);
    mainLayout->addStretch();

/*!
 * @brief Выполняет основную операцию
 * @param this Входной параметр
 * @return Результат выполнения
 */
    m_timer  =  new QTimer(this);  // Создание объекта
    m_timer->setSingleShot(true);
    connect(m_timer, &QTimer::timeout, this, &TestWidget::onTimeExpired);  // Подключение сигнала

/*!
 * @brief Выполняет основную операцию
 * @param this Входной параметр
 * @return Результат выполнения
 */
    m_updateTimer  =  new QTimer(this);  // Создание объекта
    connect(m_updateTimer, &QTimer::timeout, this, &TestWidget::updateTimer);  // Подключение сигнала

    connect(btnAnswer, &QPushButton::clicked, this, &TestWidget::onAnswerSubmitted);  // Подключение сигнала
}

void TestWidget::showQuestion(const Question& question) {
    
    while (QLayoutItem* item  =  variantsLayout->takeAt(0)) {
        if (QWidget* widget  =  item->widget()) {  // Проверка условия
            
            if (widget->parent()  ==  variantsContainer) {  // Проверка условия
                widget->deleteLater();
            }
        }
        delete item;
    }
    radioButtons.clear();

    questionLabel->setText(question.text);

    for (const QString& variant : question.variants) {  // Цикл обработки данных
/*!
 * @brief Выполняет основную операцию
 * @param variant Входной параметр
 * @param variantsContainer Входной параметр
 * @return Результат выполнения
 */
        auto rb  =  new QRadioButton(variant, variantsContainer);  // Создание объекта
        variantsLayout->addWidget(rb);
        radioButtons.append(rb);
    }
}

int TestWidget::getSelectedVariantIndex() {
    for (int i  =  0; i < radioButtons.size(); ++i) {  // Цикл обработки данных
        if (radioButtons[i]->isChecked()) {  // Проверка условия
            return i;
        }
    }
    return -1;
}

void TestWidget::startTest(const QList<Question>& questions, const User& user, int timeLimit) {
    m_questions  =  questions;
    m_currentUser  =  user;
    m_timeLimitMinutes  =  timeLimit;
    m_currentQuestionIndex  =  0;
    m_correctAnswers  =  0;
    m_testActive  =  true;
    m_testStartTime  =  QDateTime::currentDateTime();

    m_progressBar->setMaximum(m_questions.size());
    m_progressBar->setValue(0);
    m_progressBar->setVisible(true);

    m_timer->start(m_timeLimitMinutes* 60 * 1000); 
    m_updateTimer->start(1000); 

    updateProgress();
    showNextQuestion();

    qDebug() << "Test started for user" << user.login << "with" << questions.size() << "questions";
}

void TestWidget::finishTest() {
    if (!m_testActive) {  // Проверка условия
        return;
    }

    m_testActive  =  false;
    m_timer->stop();
    m_updateTimer->stop();

    bool timeExpired  =  m_timer->remainingTime()  <=  0;
    
    saveTestResult();

    emit testFinished(m_correctAnswers, m_questions.size(), timeExpired);

    qDebug() << "Test finished. Score:" << m_correctAnswers << "/" << m_questions.size();
}

int TestWidget::getCurrentScore() const {
    return m_correctAnswers;
}

int TestWidget::getMaxScore() const {
    return m_questions.size();
}

void TestWidget::onTimeExpired() {
    QMessageBox::warning(this, "Время истекло", 
                        QString("Время тестирования (%1 мин) истекло!\nТест будет завершен автоматически.")
                        .arg(m_timeLimitMinutes));
    finishTest();
}

void TestWidget::updateTimer() {
    if (!m_testActive) {  // Проверка условия
        return;
    }

    int remainingMs  =  m_timer->remainingTime();
    int remainingSeconds  =  remainingMs / 1000;
    int minutes  =  remainingSeconds / 60;
    int seconds  =  remainingSeconds % 60;

    m_timeLabel->setText(QString("Время: %1:%2")
                        .arg(minutes, 2, 10, QChar('0'))
                        .arg(seconds, 2, 10, QChar('0')));

    if (remainingSeconds < 300) {  // Проверка условия
        m_timeLabel->setStyleSheet("QLabel { color: red; font-weight: bold; }");
/*!
 * @brief Выполняет основную операцию
 * @param 600 Входной параметр
 * @return Результат выполнения
 */
    } else if (remainingSeconds < 600) {  // Проверка условия
        m_timeLabel->setStyleSheet("QLabel { color: orange; font-weight: bold; }");
    } else {
        m_timeLabel->setStyleSheet("QLabel { color: green; font-weight: bold; }");
    }
}

void TestWidget::onAnswerSubmitted() {
    if (!m_testActive) {  // Проверка условия
        return;
    }

    int selectedIndex  =  getSelectedVariantIndex();
    if (selectedIndex  ==  -1) {  // Проверка условия
        QMessageBox::warning(this, "Внимание", "Пожалуйста, выберите вариант ответа.");
        return;
    }

    const Question& currentQuestion  =  m_questions[m_currentQuestionIndex];
    if (selectedIndex  ==  currentQuestion.correctIndex) {  // Проверка условия
        m_correctAnswers++;
    }

    m_currentQuestionIndex++;
    updateProgress();

    if (m_currentQuestionIndex  >=  m_questions.size()) {  // Проверка условия
        finishTest();
    } else {
        showNextQuestion();
    }

/*!
 * @brief Выполняет основную операцию
 * @param selectedIndex Входной параметр
 * @return Результат выполнения
 */
    emit answerSubmitted(selectedIndex);
}

bool TestWidget::saveTestResult() {
    if (!m_currentUser.isValid()) {  // Проверка условия
        qWarning() << "Cannot save test result: invalid user";
        return false;
    }

    TestResult result(m_currentUser.id, m_correctAnswers, m_questions.size());
    
    if (!TestResultDao::save(result)) {  // Проверка условия
        qCritical() << "Failed to save test result through DAO";
        return false;
    }

    qDebug() << "Test result saved for user" << m_currentUser.login 
             << "score:" << m_correctAnswers << "/" << m_questions.size();
    return true;
}

void TestWidget::updateProgress() {
    m_progressLabel->setText(QString("Вопрос: %1/%2")
                            .arg(m_currentQuestionIndex + 1)
                            .arg(m_questions.size()));
    
    m_progressBar->setValue(m_currentQuestionIndex);
}

void TestWidget::showNextQuestion() {
    if (m_currentQuestionIndex < m_questions.size()) {  // Проверка условия
        showQuestion(m_questions[m_currentQuestionIndex]);
        
        if (m_currentQuestionIndex  ==  m_questions.size() - 1) {  // Проверка условия
            btnAnswer->setText("Завершить тест");
        } else {
            btnAnswer->setText("Следующий вопрос");
        }
    }
}