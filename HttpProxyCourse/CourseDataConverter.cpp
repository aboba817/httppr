#include "CourseDataConverter.h"
#include "Serializer.h"
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QFile>
#include <QDebug>

bool CourseDataConverter::convertJsonToBinary(const QString& jsonFilePath, const QString& binaryFilePath) {
    
    Course course  =  parseJsonFile(jsonFilePath);
    
    if (course.topics.isEmpty()) {  // Проверка условия
        qCritical() << "Failed to parse JSON file or course is empty:" << jsonFilePath;
        return false;
    }
    
    try {
        
        Serializer::save(course, binaryFilePath);
        qDebug() << "Successfully converted" << course.topics.size() << "topics from JSON to binary format";
        return true;
    } catch (const std::exception& e) {
        qCritical() << "Failed to save binary file:" << e.what();
        return false;
    }
}

Course CourseDataConverter::parseJsonFile(const QString& jsonFilePath) {
    Course course;
    
/*!
 * @brief Выполняет основную операцию
 * @param jsonFilePath Входной параметр
 * @return Результат выполнения
 */
    QFile file(jsonFilePath);
    if (!file.open(QIODevice::ReadOnly)) {  // Проверка условия
        qCritical() << "Cannot open JSON file:" << jsonFilePath;
        return course;
    }
    
    QByteArray jsonData  =  file.readAll();
    file.close();
    
    QJsonParseError parseError;
    QJsonDocument doc  =  QJsonDocument::fromJson(jsonData, &parseError);
    
    if (parseError.error  !=  QJsonParseError::NoError) {  // Проверка условия
        qCritical() << "JSON parse error:" << parseError.errorString();
        return course;
    }
    
    QJsonObject rootObj  =  doc.object();
    QJsonArray topicsArray  =  rootObj["topics"].toArray();
    
    for (const QJsonValue& topicValue : topicsArray) {  // Цикл обработки данных
        QJsonObject topicObj  =  topicValue.toObject();
        
        Topic topic;
        topic.title  =  topicObj["title"].toString();
        topic.htmlContent  =  topicObj["htmlContent"].toString();
        
        QJsonArray questionsArray  =  topicObj["questions"].toArray();
        for (const QJsonValue& questionValue : questionsArray) {  // Цикл обработки данных
            QJsonObject questionObj  =  questionValue.toObject();
            
            Question question;
            question.text  =  questionObj["text"].toString();
            question.correctIndex  =  questionObj["correctIndex"].toInt();
            
            QJsonArray variantsArray  =  questionObj["variants"].toArray();
            for (const QJsonValue& variantValue : variantsArray) {  // Цикл обработки данных
                question.variants.append(variantValue.toString());
            }
            
            topic.questions.append(question);
        }
        
        course.topics.append(topic);
    }
    
    qDebug() << "Parsed" << course.topics.size() << "topics from JSON";
    return course;
}