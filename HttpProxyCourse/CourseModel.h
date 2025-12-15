/**
 * Заголовочный файл CourseModel.h.
 * Содержит объявления классов и функций для системы HTTP Proxy Course.
 */

#pragma once

#include <QObject>
#include <QString>
#include <QSqlQueryModel>
#include <QSortFilterProxyModel>
#include "DomainTypes.h"

/**
 * Модель данных курса, содержащая информацию о темах, вопросах и тестах.
 */
class CourseModel : public QObject {
    Q_OBJECT

public:
    
    explicit CourseModel(QObject* parent  =  nullptr);

    /**
     * Загружает данные из хранилища.
     */
    bool loadCourse(const QString& filePath);

    /**
     * Сохраняет данные в хранилище.
     */
    bool saveCourse(const QString& filePath);

    /**
     * Возвращает числовое значение.
     */
    int getTopicCount() const;

    const Topic* getTopic(int index) const;

    void addTopic(const Topic& topic);

    bool updateTopic(int index, const Topic& topic);

    bool removeTopic(int index);

    QStringList getTopicTitles() const;

    const QList<Topic>& getTopics() const;

signals:
    
    void courseDataChanged();

    void errorOccurred(const QString& errorMessage);

private:
    Course m_course;  
};

class TestResultsModel : public QSqlQueryModel {
    Q_OBJECT

public:
    
    explicit TestResultsModel(QObject* parent  =  nullptr);

    /**
     * Загружает данные из хранилища.
     */
    bool loadUserResults(int userId);

    /**
     * Загружает данные из хранилища.
     */
    bool loadAllResults();

    /**
     * Сохраняет данные в хранилище.
     */
    bool saveTestResult(int userId, int score, int maxScore);

    QVariant headerData(int section, Qt::Orientation orientation, int role  =  Qt::DisplayRole) const override;

signals:
    
    void databaseError(const QString& errorMessage);
};

class TestResultsFilterModel : public QSortFilterProxyModel {
    Q_OBJECT

public:
    
    explicit TestResultsFilterModel(QObject* parent  =  nullptr);

    void setNameFilter(const QString& surname);

protected:
    
    bool filterAcceptsRow(int sourceRow, const QModelIndex& sourceParent) const override;

private:
    QString m_nameFilter;  
};