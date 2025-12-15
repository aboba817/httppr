
#pragma once

#include <QString>
#include <QDateTime>
#include <QList>

/*!
 * @brief Представляет структуру данных TestResult
 */
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

/*!
 * @brief Реализует функциональность класса TestResultDao
 */
class TestResultDao {
public:
    
/*!
 * @brief Сохраняет данные
 * @param result Входной параметр
 * @return Результат выполнения
 */
    static bool save(const TestResult& result);

    static QList<TestResult> findByUserId(int userId);

    static QList<TestResult> findAll();

/*!
 * @brief Возвращает значение
 * @param userId Входной параметр
 * @return Результат выполнения
 */
    static TestResult getBestResult(int userId);

/*!
 * @brief Возвращает значение
 * @param userId Входной параметр
 * @return Результат выполнения
 */
    static double getAverageScore(int userId);

/*!
 * @brief Выполняет основную операцию
 * @param userId Входной параметр
 * @return Результат выполнения
 */
    static bool deleteByUserId(int userId);
};