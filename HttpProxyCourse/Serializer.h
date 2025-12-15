/**
 * Заголовочный файл Serializer.h.
 * Содержит объявления классов и функций для системы HTTP Proxy Course.
 */

#pragma once

#include <QString>
#include "DomainTypes.h"

/**
 * Сериализатор данных курса для сохранения и загрузки в бинарном формате.
 */
class Serializer {
public:
    
    static void save(const Course& course, const QString& filePath);

    static Course load(const QString& filePath);

    static void generateCourseData(const QString& filePath);
};