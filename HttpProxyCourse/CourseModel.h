
#pragma once

#include <QObject>
#include <QString>
#include <QSqlQueryModel>
#include <QSortFilterProxyModel>
#include "DomainTypes.h"

/*!
 * @brief Реализует функциональность класса CourseModel
 */
class CourseModel : public QObject {
    Q_OBJECT

public:
    
/*!
 * @brief Выполняет основную операцию
 * @param nullptr Входной параметр
 * @return Результат выполнения
 */
    explicit CourseModel(QObject* parent  =  nullptr);

/*!
 * @brief Загружает данные
 * @param filePath Входной параметр
 * @return Результат выполнения
 */
    bool loadCourse(const QString& filePath);

/*!
 * @brief Сохраняет данные
 * @param filePath Входной параметр
 * @return Результат выполнения
 */
    bool saveCourse(const QString& filePath);

    int getTopicCount() const;

    const Topic* getTopic(int index) const;

/*!
 * @brief Выполняет основную операцию
 * @param topic Входной параметр
 */
    void addTopic(const Topic& topic);

/*!
 * @brief Выполняет основную операцию
 * @param index Входной параметр
 * @param topic Входной параметр
 * @return Результат выполнения
 */
    bool updateTopic(int index, const Topic& topic);

/*!
 * @brief Выполняет основную операцию
 * @param index Входной параметр
 * @return Результат выполнения
 */
    bool removeTopic(int index);

    QStringList getTopicTitles() const;

    const QList<Topic>& getTopics() const;

signals:
    
/*!
 * @brief Выполняет основную операцию
 */
    void courseDataChanged();

/*!
 * @brief Выполняет основную операцию
 * @param errorMessage Входной параметр
 */
    void errorOccurred(const QString& errorMessage);

private:
    Course m_course;  
};

/*!
 * @brief Реализует функциональность класса TestResultsModel
 */
class TestResultsModel : public QSqlQueryModel {
    Q_OBJECT

public:
    
/*!
 * @brief Выполняет основную операцию
 * @param nullptr Входной параметр
 * @return Результат выполнения
 */
    explicit TestResultsModel(QObject* parent  =  nullptr);

/*!
 * @brief Загружает данные
 * @param userId Входной параметр
 * @return Результат выполнения
 */
    bool loadUserResults(int userId);

/*!
 * @brief Загружает данные
 * @return Результат выполнения
 */
    bool loadAllResults();

/*!
 * @brief Сохраняет данные
 * @param userId Входной параметр
 * @param score Входной параметр
 * @param maxScore Входной параметр
 * @return Результат выполнения
 */
    bool saveTestResult(int userId, int score, int maxScore);

    QVariant headerData(int section, Qt::Orientation orientation, int role  =  Qt::DisplayRole) const override;

signals:
    
/*!
 * @brief Выполняет основную операцию
 * @param errorMessage Входной параметр
 */
    void databaseError(const QString& errorMessage);
};

/*!
 * @brief Реализует функциональность класса TestResultsFilterModel
 */
class TestResultsFilterModel : public QSortFilterProxyModel {
    Q_OBJECT

public:
    
/*!
 * @brief Выполняет основную операцию
 * @param nullptr Входной параметр
 * @return Результат выполнения
 */
    explicit TestResultsFilterModel(QObject* parent  =  nullptr);

/*!
 * @brief Устанавливает значение
 * @param surname Входной параметр
 */
    void setNameFilter(const QString& surname);

protected:
    
    bool filterAcceptsRow(int sourceRow, const QModelIndex& sourceParent) const override;

private:
    QString m_nameFilter;  
};