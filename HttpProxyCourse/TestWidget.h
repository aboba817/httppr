
#pragma once

#include "DomainTypes.h"
#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QRadioButton>
#include <QVBoxLayout>
#include <QList>
#include <QTimer>
#include <QProgressBar>
#include <QDateTime>

/*!
 * @brief Реализует функциональность класса TestWidget
 */
class TestWidget : public QWidget {
    Q_OBJECT

public:
    
/*!
 * @brief Возвращает значение
 * @param nullptr Входной параметр
 * @return Результат выполнения
 */
    explicit TestWidget(QWidget* parent  =  nullptr);

/*!
 * @brief Выполняет основную операцию
 * @param question Входной параметр
 */
    void showQuestion(const Question& question);

/*!
 * @brief Возвращает значение
 * @return Результат выполнения
 */
    int getSelectedVariantIndex();

/*!
 * @brief Выполняет основную операцию
 * @param questions Входной параметр
 * @param user Входной параметр
 * @param 20 Входной параметр
 */
    void startTest(const QList<Question>& questions, const User& user, int timeLimit  =  20);

/*!
 * @brief Выполняет основную операцию
 */
    void finishTest();

    int getCurrentScore() const;

    int getMaxScore() const;

signals:
    
/*!
 * @brief Выполняет основную операцию
 * @param index Входной параметр
 */
    void answerSubmitted(int index);

/*!
 * @brief Выполняет основную операцию
 * @param score Входной параметр
 * @param maxScore Входной параметр
 * @param timeExpired Входной параметр
 */
    void testFinished(int score, int maxScore, bool timeExpired);

private slots:
    
/*!
 * @brief Выполняет основную операцию
 */
    void onTimeExpired();

/*!
 * @brief Выполняет основную операцию
 */
    void updateTimer();

/*!
 * @brief Выполняет основную операцию
 */
    void onAnswerSubmitted();

private:
    
/*!
 * @brief Сохраняет данные
 * @return Результат выполнения
 */
    bool saveTestResult();

/*!
 * @brief Выполняет основную операцию
 */
    void updateProgress();

/*!
 * @brief Выполняет основную операцию
 */
    void showNextQuestion();

    QLabel* questionLabel;
    QWidget* variantsContainer;
    QVBoxLayout* variantsLayout;
    QPushButton* btnAnswer;
    QList<QRadioButton*> radioButtons;

    QTimer* m_timer;
    QTimer* m_updateTimer;
    QLabel* m_timeLabel;
    QProgressBar* m_progressBar;
    QLabel* m_progressLabel;

    QList<Question> m_questions;
    User m_currentUser;
    int m_currentQuestionIndex;
    int m_correctAnswers;
    int m_timeLimitMinutes;
    QDateTime m_testStartTime;
    bool m_testActive;
};