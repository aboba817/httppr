/**
 * Заголовочный файл TestResultDao.h.
 * Содержит объявления классов и функций для системы HTTP Proxy Course.
 */

#pragma once

#include <QString>
#include <QDateTime>
#include <QList>

struct TestResult {
    int id;                  
    int userId;              
    QDateTime testDate;      
    int score;               
    int maxScore;            
    
    TestResult() : id(-1), userId(-1), score(0), maxScore(0) {}
    
    TestResult(int uid, int userScore, int maxUserScore, const QDateTime& date  =  QDateTime::currentDateTime())
        : id(-1), userId(uid), testDate(date), score(userScore), maxScore(maxUserScore) {}
    
    double getPercentage() const {
        return maxScore > 0 ? (static_cast<double>(score) / maxScore) * 100.0 : 0.0;
    }
};

/**
 * Объект доступа к данным результатов тестирования.
 */
class TestResultDao {
public:
    
    /**
     * Сохраняет данные в хранилище.
     */
    static bool save(const TestResult& result);

    static QList<TestResult> findByUserId(int userId);

    static QList<TestResult> findAll();

    static TestResult getBestResult(int userId);

    static double getAverageScore(int userId);

    static bool deleteByUserId(int userId);
};