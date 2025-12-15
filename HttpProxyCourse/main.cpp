/**
 * Реализация функций и методов для системы HTTP Proxy Course.
 * Файл содержит основную логику работы компонентов приложения.
 */

#include "mainwindow.h"
#include "Serializer.h"
#include "CourseDataConverter.h"
#include "DatabaseManager.h"
#include "Logger.h"
#include <QApplication>
#include <QFile>
#include <QDebug>

/**
 * Главная точка входа в приложение HTTP Proxy Course.
 * Инициализирует систему логирования, проверяет наличие данных курса,
 * подключается к базе данных и запускает главное окно приложения.
 *
 * @param argc Количество аргументов командной строки.
 * @param argv Массив аргументов командной строки.
 * @return Код завершения приложения.
 */
int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    
    // Инициализация системы логирования
    Logger::setFileLogging(true, "application.log");
    Logger::info("Запуск приложения HTTP Proxy Course", "Main");
    
    const QString courseDataFile = "course.dat";
    
    // Проверка наличия файла данных курса и создание при необходимости
    if (!QFile::exists(courseDataFile)) {
        qDebug() << "Course data file not found. Generating binary course data...";
        try {
            Serializer::generateCourseData(courseDataFile);
            qDebug() << "Course data file created successfully!";
        } catch (const std::exception& e) {
            qCritical() << "Failed to generate course data:" << e.what();
            qCritical() << "Application may not work properly without course data.";
        }
    } else {
        qDebug() << "Binary course data file found:" << courseDataFile;
    }
    
    // Инициализация подключения к базе данных
    DatabaseManager& dbManager = DatabaseManager::instance();
    if (!dbManager.connectDb()) {
        qCritical() << "Failed to connect to database. Application will continue with limited functionality.";
    } else {
        qDebug() << "Database connected successfully";
        if (!dbManager.initSchema()) {
            qCritical() << "Failed to initialize database schema. Application will continue with limited functionality.";
        } else {
            qDebug() << "Database schema initialized successfully";
        }
    }
    
    MainWindow w;
    w.show();
    
    Logger::info("Главное окно отображено", "Main");
    
    int result = a.exec();
    
    Logger::info("Завершение работы приложения", "Main");
    return result;
}