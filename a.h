#ifndef CHESS_HIERARCHY_H
#define CHESS_HIERARCHY_H

#include <iostream>
#include <string>
#include <stdexcept>
#include <memory>
#include <vector>
#include <cmath>

/**
 * @namespace Chess
 * @brief Пространство имён для шахматных фигур
 */
namespace Chess {

/**
 * @brief Перечисление цветов шахматных фигур
 * 
 * Определяет два возможных цвета для шахматных фигур.
 */
enum class Color { 
    WHITE, /**< Белый цвет */
    BLACK  /**< Чёрный цвет */
};

/**
 * @brief Абстрактный базовый класс для всех шахматных фигур
 * 
 * Класс определяет общий интерфейс для всех шахматных фигур,
 * включая проверку возможности хода и получение символа фигуры.
 * Содержит статические счётчики для отслеживания количества фигур.
 */
class ChessPiece {
protected:
    Color color;          
    int x;                
    int y;                
    bool hasMoved;        
    
    static int whiteCount;
    static int blackCount;
    
public:
    /**
     * @brief Конструктор шахматной фигуры
     * @param col Цвет фигуры
     * @param posX Начальная координата X (0-7)
     * @param posY Начальная координата Y (0-7)
     */
    ChessPiece(Color col, int posX, int posY) 
    : color(col), x(posX), y(posY), hasMoved(false) {
    if (color == Color::WHITE) {
        ++whiteCount;
    } else {
        ++blackCount;
    }
};
    
    /**
     * @brief Виртуальный деструктор
     * 
     * Гарантирует корректное уничтожение объектов производных классов.
     */
    virtual ~ChessPiece() {
    // Уменьшаем счётчик соответствующего цвета
    if (color == Color::WHITE) {
        --whiteCount;
    } else {
        --blackCount;
    }
};
    
    /**
     * @brief Чисто виртуальная функция для проверки возможности хода
     * @param newX Новая координата X
     * @param newY Новая координата Y
     * @return true если ход возможен, false в противном случае
     * 
     * Каждая конкретная фигура должна реализовать свою логику проверки хода.
     */
    virtual bool canMoveTo(int newX, int newY) const = 0;
    
    /**
     * @brief Чисто виртуальная функция для получения символа фигуры
     * @return Символ фигуры в формате Unicode
     * 
     * Возвращает символьное представление фигуры для отображения.
     */
    virtual char getSymbol() const = 0;
    
    /**
     * @brief Виртуальная функция для перемещения фигуры
     * @param newX Новая координата X
     * @param newY Новая координата Y
     * @throws InvalidMoveException если ход невозможен или координаты неверные
     * 
     * Реализация по умолчанию проверяет границы доски и возможность хода.
     */
    virtual void moveTo(int newX, int newY) {
    if (newX < 0 || newX > 7 || newY < 0 || newY > 7) {
        throw InvalidMoveException("Координаты за пределами доски (0-7)");
    }
    
    if (!canMoveTo(newX, newY)) {
        throw InvalidMoveException("Фигура не может совершить такой ход");
    }
    
    x = newX;
    y = newY;
    hasMoved = true;
};
    
    /**
     * @brief Получить цвет фигуры
     * @return Цвет фигуры
     */
    Color getColor() const { return color; }
    
    /**
     * @brief Получить текущую позицию фигуры
     * @param[out] posX Координата X
     * @param[out] posY Координата Y
     */
    void getPosition(int& posX, int& posY) const { posX = x; posY = y; }
    
    /**
     * @brief Проверить, двигалась ли фигура
     * @return true если фигура двигалась, false в противном случае
     */
    bool hasPieceMoved() const { return hasMoved; }
    
    /**
     * @brief Получить тип фигуры
     * @return Строковое представление типа фигуры
     * 
     * Виртуальная функция с реализацией по умолчанию.
     */
    virtual std::string getType() const { return "Шахматная фигура"; }
    
    /**
     * @brief Статическая функция для проверки состояния доски
     * @return true если состояние корректно, false в противном случае
     * 
     * Проверяет базовые ограничения (например, не более 16 фигур каждого цвета).
     */
    static bool validateBoardState() {
    return whiteCount <= 16 && blackCount <= 16;
};
    
    /**
     * @brief Получить количество белых фигур
     * @return Количество белых фигур
     */
    static int getWhiteCount() { return whiteCount; }
    
    /**
     * @brief Получить количество чёрных фигур
     * @return Количество чёрных фигур
     */
    static int getBlackCount() { return blackCount; }
    
    /**
     * @brief Получить общее количество фигур
     * @return Общее количество фигур
     */
    static int getTotalCount() { return whiteCount + blackCount; }
    
    // Правило пяти будет добавлено в следующем коммите
    ChessPiece(const ChessPiece& other) = delete;
    ChessPiece& operator=(const ChessPiece& other) = delete;
    ChessPiece(ChessPiece&& other) = delete;
    ChessPiece& operator=(ChessPiece&& other) = delete;
};
int ChessPiece::whiteCount = 0;
int ChessPiece::blackCount = 0;

}

#endif