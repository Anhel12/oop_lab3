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
        // Проверка корректности координат
        if (posX < 0 || posX > 7 || posY < 0 || posY > 7) {
            throw std::invalid_argument("Координаты должны быть в диапазоне 0-7");
        }

        if (color == Color::WHITE) {
            ++whiteCount;
        } else {
            ++blackCount;
        }
};

    /**
     * @brief Конструктор копирования
     * @param other Фигура для копирования
     * 
     * Создаёт глубокую копию фигуры с обновлением статических счётчиков.
     */
    ChessPiece(const ChessPiece& other)
    : color(other.color), x(other.x), y(other.y), hasMoved(other.hasMoved) {
    if (color == Color::WHITE) {
        ++whiteCount;
    } else {
        ++blackCount;
    }
}
    /**
     * @brief Оператор присваивания копированием
     * @param other Фигура для копирования
     * @return Ссылка на текущий объект
     * 
     * Выполняет глубокое копирование с корректным обновлением счётчиков.
     */
    ChessPiece& operator=(const ChessPiece& other) {
    if (this != &other) {
        // Уменьшаем старый счётчик
        if (color == Color::WHITE) {
            --whiteCount;
        } else {
            --blackCount;
        }
        
        // Копируем данные
        color = other.color;
        x = other.x;
        y = other.y;
        hasMoved = other.hasMoved;
        
        // Увеличиваем новый счётчик
        if (color == Color::WHITE) {
            ++whiteCount;
        } else {
            ++blackCount;
        }
    }
    return *this;
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

/**
 * @brief Базовый класс для фигур, двигающихся по прямым линиям
 * 
 * Класс реализует общую логику для фигур, которые могут двигаться
 * на любое количество клеток по горизонтали, вертикали или диагонали.
 * Наследует от ChessPiece и добавляет специфичную для скользящих фигур логику.
 * Предоставляет виртуальную функцию с реализацией по умолчанию getMoveType().
 */
class SlidingPiece : public ChessPiece {
protected:
    bool canMoveHorizontally;   ///< Может ли двигаться по горизонтали
    bool canMoveVertically;     ///< Может ли двигаться по вертикали
    bool canMoveDiagonally;     ///< Может ли двигаться по диагонали
    
public:
    /**
     * @brief Конструктор скользящей фигуры
     * @param col Цвет фигуры
     * @param posX Начальная координата X
     * @param posY Начальная координата Y
     * @param horizontal Может двигаться по горизонтали
     * @param vertical Может двигаться по вертикали
     * @param diagonal Может двигаться по диагонали
     */
    SlidingPiece(Color col, int posX, int posY,
                         bool horizontal, bool vertical, bool diagonal)
    : ChessPiece(col, posX, posY),
      canMoveHorizontally(horizontal),
      canMoveVertically(vertical),
      canMoveDiagonally(diagonal) {};
    
    /**
     * @brief Проверяет возможность хода для скользящих фигур
     * @param newX Новая координата X
     * @param newY Новая координата Y
     * @return true если ход возможен, false в противном случае
     * 
     * Переопределяет чисто виртуальную функцию базового класса.
     * Реализует логику движения по прямым линиям.
     */
    virtual bool canMoveTo(int newX, int newY) const {
    int posX, posY;
    getPosition(posX, posY);
    
    // Фигура не может оставаться на месте
    if (newX == posX && newY == posY) {
        return false;
    }
    
    // Проверка выхода за границы доски
    if (newX < 0 || newX > 7 || newY < 0 || newY > 7) {
        return false;
    }
    
    // Проверка горизонтального движения
    if (newY == posY && canMoveHorizontally) {
        return true;
    }
    
    // Проверка вертикального движения
    if (newX == posX && canMoveVertically) {
        return true;
    }
    
    // Проверка диагонального движения
    int deltaX = abs(newX - posX);
    int deltaY = abs(newY - posY);
    if (deltaX == deltaY && canMoveDiagonally) {
        return true;
    }
    
    return false;
};
    
    /**
     * @brief Получить тип движения фигуры
     * @return Строковое описание возможных направлений движения
     * 
     * Виртуальная функция с реализацией по умолчанию.
     * Может быть переопределена в производных классах.
     */
    virtual std::string getMoveType() const {
    if (canMoveHorizontally && canMoveVertically && canMoveDiagonally) {
        return "Все направления (горизонталь, вертикаль, диагональ)";
    } else if (canMoveHorizontally && canMoveVertically) {
        return "Горизонталь и вертикаль";
    } else if (canMoveHorizontally && canMoveDiagonally) {
        return "Горизонталь и диагональ";
    } else if (canMoveVertically && canMoveDiagonally) {
        return "Вертикаль и диагональ";
    } else if (canMoveHorizontally) {
        return "Только горизонталь";
    } else if (canMoveVertically) {
        return "Только вертикаль";
    } else if (canMoveDiagonally) {
        return "Только диагональ";
    } else {
        return "Неизвестно";
    }
};
    
    /**
     * @brief Получить тип фигуры
     * @return Строковое представление типа фигуры
     * 
     * Переопределяет виртуальную функцию базового класса.
     */
    virtual std::string getType() const override { return "Скользящая фигура"; }
    
    /**
     * @brief Виртуальный деструктор
     */
    virtual ~SlidingPiece() = default;
};

/**
 * @brief Базовый класс для фигур, которые могут "перепрыгивать" через другие фигуры
 * 
 * Класс реализует логику для фигур с фиксированными шаблонами движения,
 * таких как конь в шахматах. Эти фигуры могут перемещаться через другие фигуры.
 * Использует статические члены для хранения шаблонов движения.
 */
class JumpingPiece : public ChessPiece {
protected:
    /**
     * @brief Структура для хранения шаблона движения
     */
    struct MovePattern {
        int deltaX;
        int deltaY;
    };
    
    static const MovePattern* movePatterns = {
    {2, 1}, {2, -1}, {-2, 1}, {-2, -1},
    {1, 2}, {1, -2}, {-1, 2}, {-1, -2}
};  ///< Шаблоны допустимых ходов
    static int patternCount;                 ///< Количество шаблонов
    
public:
    /**
     * @brief Конструктор прыгающей фигуры
     * @param col Цвет фигуры
     * @param posX Начальная координата X
     * @param posY Начальная координата Y
     */
    JumpingPiece(Color col, int posX, int posY)
    : ChessPiece(col, posX, posY) {};
    
    /**
     * @brief Проверяет возможность хода для прыгающих фигур
     * @param newX Новая координата X
     * @param newY Новая координата Y
     * @return true если ход возможен, false в противном случае
     * 
     * Переопределяет чисто виртуальную функцию базового класса.
     * Реализует логику движения по фиксированным шаблонам.
     */
    virtual bool canMoveTo(int newX, int newY) const {
    int posX, posY;
    getPosition(posX, posY);
    
    // Фигура не может оставаться на месте
    if (newX == posX && newY == posY) {
        return false;
    }
    
    // Проверка выхода за границы доски
    if (newX < 0 || newX > 7 || newY < 0 || newY > 7) {
        return false;
    }
    
    // Проверка по шаблонам движения
    for (int i = 0; i < patternCount; ++i) {
        int targetX = posX + movePatterns[i].deltaX;
        int targetY = posY + movePatterns[i].deltaY;
        
        if (targetX == newX && targetY == newY) {
            return true;
        }
    }
    
    return false;
}
    
    /**
     * @brief Получить количество допустимых ходов
     * @return Количество возможных ходов с текущей позиции
     * 
     * Виртуальная функция с реализацией по умолчанию.
     * Рассчитывает количество допустимых ходов на пустой доске.
     */
    virtual int getPossibleMoveCount() const {
    int posX, posY;
    getPosition(posX, posY);
    int count = 0;
    
    for (int i = 0; i < patternCount; ++i) {
        int targetX = posX + movePatterns[i].deltaX;
        int targetY = posY + movePatterns[i].deltaY;
        
        if (targetX >= 0 && targetX <= 7 && targetY >= 0 && targetY <= 7) {
            ++count;
        }
    }
    
    return count;
};
    
    /**
     * @brief Получить тип фигуры
     * @return Строковое представление типа фигуры
     * 
     * Переопределяет виртуальную функцию базового класса.
     */
    virtual std::string getType() const override { return "Прыгающая фигура"; }
    
    /**
     * @brief Виртуальный деструктор
     */
    virtual ~JumpingPiece() = default;
};

int JumpingPiece::patternCount = 8;

/**
 * @brief Класс шахматного коня
 * 
 * Конь двигается буквой 'Г': на 2 клетки в одном направлении
 * и на 1 клетку в перпендикулярном направлении.
 * Наследует от JumpingPiece с соответствующими шаблонами движения.
 */
class Knight : public JumpingPiece {
public:
    /**
     * @brief Конструктор коня
     * @param col Цвет фигуры
     * @param posX Начальная координата X
     * @param posY Начальная координата Y
     */
    Knight(Color col, int posX, int posY);
    
    /**
     * @brief Получить тип фигуры
     * @return Строковое представление типа фигуры
     * 
     * Переопределяет виртуальную функцию базового класса.
     */
    virtual std::string getType() const override { return "Конь"; }
    
    /**
     * @brief Виртуальный деструктор
     */
    virtual ~Knight() = default;
};

/**
 * @brief Класс шахматной ладьи
 * 
 * Ладья может двигаться на любое количество клеток по горизонтали или вертикали.
 * Наследует от SlidingPiece с соответствующими параметрами движения.
 * Является первой конкретной реализацией скользящей фигуры.
 */
class Rook : public SlidingPiece {
public:
    /**
     * @brief Конструктор ладьи
     * @param col Цвет фигуры
     * @param posX Начальная координата X
     * @param posY Начальная координата Y
     */
    Rook(Color col, int posX, int posY)
    : SlidingPiece(col, posX, posY, true, true, false) {};
    
    /**
     * @brief Получить тип фигуры
     * @return Строковое представление типа фигуры
     * 
     * Переопределяет виртуальную функцию базового класса.
     */
    virtual std::string getType() const override { return "Ладья"; }
    
    /**
     * @brief Виртуальный деструктор
     */
    virtual ~Rook() = default;
};

/**
 * @brief Класс шахматного слона
 * 
 * Слон может двигаться на любое количество клеток по диагонали.
 * Наследует от SlidingPiece с соответствующими параметрами движения.
 * Демонстрирует альтернативную конфигурацию скользящей фигуры.
 */
class Bishop : public SlidingPiece {
public:
    /**
     * @brief Конструктор слона
     * @param col Цвет фигуры
     * @param posX Начальная координата X
     * @param posY Начальная координата Y
     */
    Bishop(Color col, int posX, int posY)
    : SlidingPiece(col, posX, posY, false, false, true) {};
    
    /**
     * @brief Получить символ слона
     * @return Символ слона в формате Unicode
     * 
     * Переопределяет чисто виртуальную функцию базового класса.
     */
    virtual char getSymbol() const override;
    
    /**
     * @brief Получить тип фигуры
     * @return Строковое представление типа фигуры
     * 
     * Переопределяет виртуальную функцию базового класса.
     */
    virtual std::string getType() const override { return "Слон"; }
    
    /**
     * @brief Виртуальный деструктор
     */
    virtual ~Bishop() = default;
};

/**
 * @brief Интерфейс для фигур с комбинированными возможностями движения
 * 
 * Абстрактный класс определяет интерфейс для фигур, которые могут использовать
 * возможности разных типов движения. Используется для реализации
 * множественного наследования и добавления дополнительного функционала.
 */
class CombinedPiece {
public:
    /**
     * @brief Виртуальный деструктор
     * 
     * Гарантирует корректное уничтожение объектов производных классов.
     */
    virtual ~CombinedPiece() = default;
    
    /**
     * @brief Проверить специальные возможности фигуры
     * @return true если фигура имеет специальные возможности, false в противном случае
     * 
     * Виртуальная функция с реализацией по умолчанию.
     * Может быть переопределена в производных классах.
     */
    virtual bool hasSpecialAbility() const { return false; }
};

/**
 * @brief Класс шахматного ферзя (множественное наследование)
 * 
 * Ферзь объединяет возможности ладьи и слона:
 * может двигаться на любое количество клеток по горизонтали,
 * вертикали или диагонали. Наследует от SlidingPiece и CombinedPiece.
 * Демонстрирует использование множественного наследования в C++.
 */
class Queen : public SlidingPiece, public CombinedPiece {
public:
    /**
     * @brief Конструктор ферзя
     * @param col Цвет фигуры
     * @param posX Начальная координата X
     * @param posY Начальная координата Y
     */
    Queen(Color col, int posX, int posY)
    : SlidingPiece(col, posX, posY, true, true, true) {};
    
    /**
     * @brief Проверить специальные возможности
     * @return true (ферзь имеет специальные возможности)
     * 
     * Переопределяет виртуальную функцию с реализацией по умолчанию.
     */
    virtual bool hasSpecialAbility() const override { return true; }
    
    /**
     * @brief Получить тип фигуры
     * @return Строковое представление типа фигуры
     * 
     * Переопределяет виртуальную функцию базового класса.
     */
    virtual std::string getType() const override { return "Ферзь"; }
    
    /**
     * @brief Виртуальный деструктор
     * 
     * Корректно разрушает объект при множественном наследовании.
     */
    virtual ~Queen() = default;
};
}

#endif