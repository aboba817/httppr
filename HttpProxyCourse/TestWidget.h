/**
 * Заголовочный файл TestWidget.h.
 * Содержит объявления классов и функций для системы HTTP Proxy Course.
 */

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

/**
 * Виджет прохождения тестирования по выбранной теме.
 */
class TestWidget : public QWidget {
    Q_OBJECT

public:
    
    explicit TestWidget(QWidget *parent  =  nullptr);

    /**
     * Отображает элемент интерфейса.
     */
    void showQuestion(const Question& question);

    /**
     * Возвращает числовое значение.
     */
    int getSelectedVariantIndex();

    void startTest(const QList<Question>& questions, const User& user, int timeLimit  =  20);

    void finishTest();

    /**
     * Возвращает числовое значение.
     */
    int getCurrentScore() const;

    /**
     * Возвращает числовое значение.
     */
    int getMaxScore() const;

signals:
    
    void answerSubmitted(int index);

    void testFinished(int score, int maxScore, bool timeExpired);

private slots:
    
    void onTimeExpired();

    /**
     * Обновляет состояние компонента.
     */
    void updateTimer();

    void onAnswerSubmitted();

private:
    
    /**
     * Сохраняет данные в хранилище.
     */
    bool saveTestResult();

    /**
     * Обновляет состояние компонента.
     */
    void updateProgress();

    /**
     * Отображает элемент интерфейса.
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