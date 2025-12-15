
#pragma once

#include <QString>
#include "DomainTypes.h"

/*!
 * @brief Реализует функциональность класса CourseDataConverter
 */
class CourseDataConverter {
public:
    
/*!
 * @brief Выполняет основную операцию
 * @param jsonFilePath Входной параметр
 * @param binaryFilePath Входной параметр
 * @return Результат выполнения
 */
    static bool convertJsonToBinary(const QString& jsonFilePath, const QString& binaryFilePath);

private:
    
/*!
 * @brief Выполняет основную операцию
 * @param jsonFilePath Входной параметр
 * @return Результат выполнения
 */
    static Course parseJsonFile(const QString& jsonFilePath);
};