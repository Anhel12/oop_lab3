#include "a.h"
#include <iostream>
#include <vector>
#include <memory>

using namespace std;

// Тест 1: Простое создание фигур
void testCreation() {
    cout << "=== Тест 1: Создание фигур ===\n";
    
    // Создаём разные фигуры
    Chess::Rook rook(Chess::Color::WHITE, 0, 0);
    Chess::Bishop bishop(Chess::Color::BLACK, 2, 0);
    Chess::Knight knight(Chess::Color::WHITE, 1, 0);
    Chess::Queen queen(Chess::Color::BLACK, 3, 0);
    Chess::King king(Chess::Color::WHITE, 4, 0);
    
    cout << "Создано фигур: " << Chess::ChessPiece::getTotalCount() << endl;
    cout << "Белых: " << Chess::ChessPiece::getWhiteCount() << endl;
    cout << "Черных: " << Chess::ChessPiece::getBlackCount() << endl;
}

// Тест 2: Проверка движения
void testMovement() {
    cout << "\n=== Тест 2: Проверка движения ===\n";
    
    Chess::Rook rook(Chess::Color::WHITE, 0, 0);
    
    // Ладья может двигаться по вертикали
    cout << "Ладья из (0,0) в (0,4): ";
    if (rook.canMoveTo(0, 4)) {
        cout << "МОЖЕТ" << endl;
    } else {
        cout << "НЕ МОЖЕТ" << endl;
    }
    
    // Ладья может двигаться по горизонтали
    cout << "Ладья из (0,0) в (4,0): ";
    if (rook.canMoveTo(4, 0)) {
        cout << "МОЖЕТ" << endl;
    } else {
        cout << "НЕ МОЖЕТ" << endl;
    }
    
    // Ладья НЕ может двигаться по диагонали
    cout << "Ладья из (0,0) в (4,4): ";
    if (rook.canMoveTo(4, 4)) {
        cout << "МОЖЕТ" << endl;
    } else {
        cout << "НЕ МОЖЕТ" << endl;
    }
    
    Chess::Knight knight(Chess::Color::WHITE, 4, 4);
    
    // Конь может двигаться буквой Г
    cout << "\nКонь из (4,4) в (6,5): ";
    if (knight.canMoveTo(6, 5)) {
        cout << "МОЖЕТ" << endl;
    } else {
        cout << "НЕ МОЖЕТ" << endl;
    }
}

// Тест 3: Полиморфизм
void testPolymorphism() {
    cout << "\n=== Тест 3: Полиморфизм ===\n";
    
    // Создаём разные фигуры
    Chess::Rook rook(Chess::Color::WHITE, 0, 0);
    Chess::Bishop bishop(Chess::Color::BLACK, 2, 0);
    Chess::Knight knight(Chess::Color::WHITE, 1, 0);
    Chess::Queen queen(Chess::Color::BLACK, 3, 0);
    Chess::King king(Chess::Color::WHITE, 4, 0);
    
    cout << rook.getType() << endl;
    cout << bishop.getType() << endl;
    cout << knight.getType() << endl;
    cout << queen.getType() << endl;
    cout << king.getType() << endl;
}

// Тест 4: Копирование
void testCopy() {
    cout << "\n=== Тест 4: Копирование фигур ===\n";
    
    // Создаём оригинальную фигуру
    Chess::Rook original(Chess::Color::WHITE, 0, 0);
    
    // Копируем
    Chess::Rook copy = original;
    
    cout << "\n Оригинал: " << original << endl;
    cout << "\n Копия: " << copy << endl;

    copy.moveTo(3,0);

    cout << "\n Оригинал: " << original << endl;
    cout << "\n Копия: " << copy << endl;
}


// Тест 5: Статические члены
void testStatic() {
    cout << "\n=== Тест 5: Статические счетчики ===\n";
    
    int before = Chess::ChessPiece::getTotalCount();
    cout << "Было фигур: " << before << endl;
    
    // Создаем фигуры в отдельном блоке
    {
        Chess::Rook r1(Chess::Color::WHITE, 0, 0);
        Chess::Rook r2(Chess::Color::WHITE, 7, 0);
        Chess::Bishop b1(Chess::Color::BLACK, 2, 0);
        
        cout << "Создали 3 фигуры. Теперь: " 
             << Chess::ChessPiece::getTotalCount() << endl;
        cout << "Белых: " << Chess::ChessPiece::getWhiteCount() << endl;
        cout << "Черных: " << Chess::ChessPiece::getBlackCount() << endl;
    }
    
    // После блока фигуры уничтожаются
    cout << "После блока снова: " << Chess::ChessPiece::getTotalCount() << endl;
}

// Тест 6: Ферзь (множественное наследование)
void testQueen() {
    cout << "\n=== Тест 6: Ферзь (множественное наследование) ===\n";
    
    Chess::Queen queen(Chess::Color::WHITE, 3, 3);
    
    // Проверяем как ChessPiece
    cout << " (" << queen.getType() << ")" << endl;
    
    cout << "Из (3,3) в (3,7) (вертикаль): ";
    if (queen.canMoveTo(3, 7)) cout << "МОЖЕТ" << endl;
    else cout << "НЕ МОЖЕТ" << endl;
    
    cout << "Из (3,3) в (7,7) (диагональ): ";
    if (queen.canMoveTo(7, 7)) cout << "МОЖЕТ" << endl;
    else cout << "НЕ МОЖЕТ" << endl;
    
    // Проверяем как CombinedPiece
    Chess::CombinedPiece* combine = &queen;
    cout << "\nКак комбинированная фигура: " 
         << combine->getCombinedAbilities() << endl;
}

// Тест 7: Симуляция маленькой доски
void testMiniBoard() {
    cout << "\n=== Тест 7: Маленькая шахматная доска ===\n";
    
    vector<unique_ptr<Chess::ChessPiece>> chessboard;
    
    // Ставим несколько фигур
    chessboard.push_back(make_unique<Chess::Rook>(Chess::Color::WHITE, 0, 0));
    chessboard.push_back(make_unique<Chess::Knight>(Chess::Color::WHITE, 1, 0));
    chessboard.push_back(make_unique<Chess::Bishop>(Chess::Color::WHITE, 2, 0));
    chessboard.push_back(make_unique<Chess::Queen>(Chess::Color::WHITE, 3, 0));
    chessboard.push_back(make_unique<Chess::King>(Chess::Color::WHITE, 4, 0));
    
    chessboard.push_back(make_unique<Chess::Rook>(Chess::Color::BLACK, 7, 7));
    chessboard.push_back(make_unique<Chess::Knight>(Chess::Color::BLACK, 6, 7));
    
    cout << "На доске " << chessboard.size() << " фигур" << endl;
    
    // Проверяем ходы для каждой фигуры
    int count = 0;
    for (const auto& figura : chessboard) {
        // Проверяем, может ли фигура сделать хоть один ход
        for (int x = 0; x < 8; x++) {
            for (int y = 0; y < 8; y++) {
                if (figura->canMoveTo(x, y)) {
                    count++;
                    break;
                }
            }
            if (count > 0) break;
        }
    }
    
    cout << "Из них могут сделать ход: " << count << endl;
    cout << "Состояние доски корректно: " 
         << (Chess::ChessPiece::validateBoardState() ? "ДА" : "НЕТ") << endl;
}

int main() {
    cout << "ТЕСТЫ ДЛЯ ШАХМАТНЫХ ФИГУР\n";
    cout << "=========================\n";
    
    try {
        testCreation();
        testMovement();
        testPolymorphism();
        testCopy();
        testStatic();
        testQueen();
        testMiniBoard();
        
        cout << "\n=========================\n";
        cout << "ВСЕ ТЕСТЫ ПРОЙДЕНЫ УСПЕШНО!\n";
        cout << "=========================\n";
        
    } catch (const exception& e) {
        cout << "\n!!! ОШИБКА: " << e.what() << endl;
        return 1;
    }
    
    return 0;
}