/**
 * Заголовочный файл CourseDataConverter.h.
 * Содержит объявления классов и функций для системы HTTP Proxy Course.
 */

#pragma once

#include <QString>
#include "DomainTypes.h"

/**
 * Конвертер данных курса между различными форматами.
 */
class CourseDataConverter {
public:
    
    static bool convertJsonToBinary(const QString& jsonFilePath, const QString& binaryFilePath);

private:
    
    static Course parseJsonFile(const QString& jsonFilePath);
};