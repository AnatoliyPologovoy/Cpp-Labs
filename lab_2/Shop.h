#ifndef SHOP_H
#define SHOP_H

#include <string>
#include <fstream>
#include <vector>

class Shop {
private:
    std::string name;           // название магазина
    std::string address;        // адрес
    int foundationYear;         // год основания
    int shopNumber;             // номер магазина

    // Прибыль по месяцам (1 - январь, 12 - декабрь)
    double monthlyProfit[12];
    double totalProfit;         // суммарная прибыль за все время

    // Закрытый метод для проверки года
    bool isValidYear(int year) const;

public:
    // Конструкторы
    Shop();  // конструктор без параметров
    Shop(const std::string& name, const std::string& address,
        int foundationYear, int shopNumber);

    // Деструктор
    ~Shop();

    // Геттеры
    std::string getName() const;
    std::string getAddress() const;
    int getFoundationYear() const;
    int getShopNumber() const;
    double getTotalProfit() const;

    // Геттеры для прибыли по месяцам
    double getProfitForMonth(int month) const;  // month 1-12
    double getTotalProfitForMonths(int startMonth, int endMonth) const;
    double getAverageMonthlyProfit(int startMonth, int endMonth) const;
    double getProfitGrowth(int startMonth, int endMonth) const; // прирост прибыли

    // Сеттеры с проверками
    void setName(const std::string& name);
    void setAddress(const std::string& address);
    void setFoundationYear(int year);
    void setShopNumber(int number);

    // Методы для работы с прибылью
    void setProfitForMonth(int month, double profit);
    void addProfitForMonth(int month, double profit);
    void resetMonthlyProfits();

    // Метод для вывода информации о магазине
    void displayInfo() const;
    void displayMonthlyInfo(int startMonth = 1, int endMonth = 12) const;

    // Методы сериализации/десериализации
    void serialize() const;
    void serialize(const std::string& filename) const;

    void deserialize();
    void deserialize(const std::string& filename);

    // Статические методы
    static int getCurrentYear();
    static std::string getMonthName(int month);

    // Статические методы для сортировки магазинов
    static void sortByTotalProfit(std::vector<Shop*>& shops, int startMonth, int endMonth);
    static void sortByProfitGrowth(std::vector<Shop*>& shops, int startMonth, int endMonth);
};

void demonstrateShopClass();

#endif // SHOP_H#pragma once
