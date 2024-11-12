#include <vector>
#include <memory>

int main() {
    std::vector<std::unique_ptr<int>> v;
    v.push_back(std::make_unique<int>(1));
    v.push_back(std::make_unique<int>(2));

    // Вариант 1: for (auto&& x : v)
    /*for (auto&& x : v) {
        *x = 10; // Изменяем значение, на которое указывает уникальный указатель
    }*/

    // Вариант 2: for (auto& x : v)
    for (auto& x : v) { 
       *x = 10; // Ошибка компиляции: x - константный указатель
    }
}
