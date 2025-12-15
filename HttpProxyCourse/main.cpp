
#include "mainwindow.h"
#include "Serializer.h"
#include "CourseDataConverter.h"
#include "DatabaseManager.h"
#include "Logger.h"
#include <QApplication>
#include <QFile>
#include <QDebug>

/*!
 * @brief Главная точка входа в приложение
 * @param argc Количество аргументов командной строки
 * @param argv Массив аргументов командной строки
 * @return Код завершения приложения
 */
int main(int argc, char* argv[]) {
    QApplication a(argc, argv);  // Инициализация Qt приложения
    
    Logger::setFileLogging(true, "application.log");  // Логирование события
    Logger::info("Запуск приложения HTTP Proxy Course", "Main");  // Логирование события
    
    const QString courseDataFile = "course.dat";
    
    if (!QFile::exists(courseDataFile)) {  // Проверка условия
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
    
    DatabaseManager& dbManager = DatabaseManager::instance();  // Работа с базой данных
    if (!dbManager.connectDb()) {  // Проверка условия
        qCritical() << "Failed to connect to database. Application will continue with limited functionality.";
    } else {
        qDebug() << "Database connected successfully";
        if (!dbManager.initSchema()) {  // Проверка условия
            qCritical() << "Failed to initialize database schema. Application will continue with limited functionality.";
        } else {
            qDebug() << "Database schema initialized successfully";
        }
    }
    
    MainWindow w;
    w.show();
    
    Logger::info("Главное окно отображено", "Main");  // Логирование события
    
    int result = a.exec();  // Запуск главного цикла приложения
    
    Logger::info("Завершение работы приложения", "Main");  // Логирование события
    return result;
}