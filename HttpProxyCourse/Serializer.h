
#pragma once

#include <QString>
#include "DomainTypes.h"

/*!
 * @brief Реализует функциональность класса Serializer
 */
class Serializer {
public:
    
/*!
 * @brief Сохраняет данные
 * @param course Входной параметр
 * @param filePath Входной параметр
 * @return Результат выполнения
 */
    static void save(const Course& course, const QString& filePath);

/*!
 * @brief Загружает данные
 * @param filePath Входной параметр
 * @return Результат выполнения
 */
    static Course load(const QString& filePath);

/*!
 * @brief Выполняет основную операцию
 * @param filePath Входной параметр
 * @return Результат выполнения
 */
    static void generateCourseData(const QString& filePath);
};