#ifndef LAB1_EXCEPTION_H
#define LAB1_EXCEPTION_H
#include <exception>
#include <string>

class FileNotFound : public std::exception
{
    std::string err;
public:
    FileNotFound() {
        err.assign("File wasn't found!");
    }

    const char* what() const noexcept override {
        return err.c_str();
    }
};

class WrongFileFormat : public std::exception
{
    std::string err;
public:
    WrongFileFormat() {
        err.assign("Wrong format!");
    }
    const char* what() const noexcept override {
        return err.c_str();
    }
};

#endif //LAB1_EXCEPTION_H
