#include <iostream>
#include <memory>
#include <type_traits>
#include <typeinfo>
#include <stdexcept>

class Any {
private:
    struct Concept {
        virtual ~Concept() = default;
        virtual void* get() = 0;
        virtual const std::type_info& type() const = 0;
    };

    template <typename T>
    struct Model : public Concept {
        T data;
        Model(const T& data) : data(data) {}
        void* get() override { return &data; }
        const std::type_info& type() const override { return typeid(T); }
    };

    std::unique_ptr<Concept> ptr;

public:
    template <typename T>
    Any(const T& value) : ptr(std::make_unique<Model<T>>(value)) {}

    template <typename T>
    T& get() {
        if (typeid(T) != ptr->type()) {
            throw std::bad_cast();
        }
        return *static_cast<T*>(ptr->get());
    }
};

int main() {
    Any a(5);
    std::cout << a.get<int>() << std::endl; // 5
    try {
        std::cout << a.get<std::string>() << std::endl; // error
    } catch (const std::bad_cast& e) {
        std::cout << "Error: " << e.what() << std::endl;
    }
    return 0;
}