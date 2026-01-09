#include "Shop.h"
#include <iostream>
#include <iomanip>
#include <ctime>
#include <stdexcept>
#include <limits>
#include <algorithm>
#include <cmath>

using namespace std;

// Статический метод для получения текущего года
int Shop::getCurrentYear() {
    time_t now = time(0);

    tm localTime;
    localtime_s(&localTime, &now);

    return 1900 + localTime.tm_year;
}

// Статический метод для получения названия месяца
string Shop::getMonthName(int month) {
    const string monthNames[] = {
        "Январь", "Февраль", "Март", "Апрель", "Май", "Июнь",
        "Июль", "Август", "Сентябрь", "Октябрь", "Ноябрь", "Декабрь"
    };

    if (month > 0 && month <= 12) {
        return monthNames[month - 1];
    }
    return "Неизвестный месяц";
}

// Закрытый метод для проверки года
bool Shop::isValidYear(int year) const {
    int currentYear = getCurrentYear();
    return (year >= 1800 && year <= currentYear);
}

// Конструктор без параметров
Shop::Shop() : name("Без названия"), address("Не указан"),
foundationYear(2026), shopNumber(0), totalProfit(0.0) {
    // Инициализируем прибыль по месяцам нулями
    for (int i = 0; i < 12; i++) {
        monthlyProfit[i] = 0.0;
    }
    cout << "Создан магазин по умолчанию: " << name << endl;
}

// Конструктор с параметрами
Shop::Shop(const std::string& name, const std::string& address,
    int foundationYear, int shopNumber) {
    setName(name);
    setAddress(address);
    setFoundationYear(foundationYear);
    setShopNumber(shopNumber);
    totalProfit = 0.0;

    // Инициализируем прибыль по месяцам нулями
    for (int i = 0; i < 12; i++) {
        monthlyProfit[i] = 0.0;
    }

    cout << "Создан магазин с параметрами: " << name << endl;
}

// Деструктор
Shop::~Shop() {
    cout << "Магазин \"" << name << "\" удален" << endl;
}

// Геттеры
string Shop::getName() const {
    return name;
}

string Shop::getAddress() const {
    return address;
}

int Shop::getFoundationYear() const {
    return foundationYear;
}

int Shop::getShopNumber() const {
    return shopNumber;
}

double Shop::getTotalProfit() const {
    return totalProfit;
}

// Геттер прибыли за конкретный месяц
double Shop::getProfitForMonth(int month) const {
    if (month < 1 || month > 12) {
        throw invalid_argument("Месяц должен быть в диапазоне 1-12");
    }
    return monthlyProfit[month - 1];
}

// Геттер общей прибыли за период
double Shop::getTotalProfitForMonths(int startMonth, int endMonth) const {
    if (startMonth < 1 || startMonth > 12 || endMonth < 1 || endMonth > 12) {
        throw invalid_argument("Месяцы должны быть в диапазоне 1-12");
    }
    if (startMonth > endMonth) {
        throw invalid_argument("Начальный месяц должен быть раньше конечного");
    }

    double sum = 0.0;
    for (int month = startMonth; month <= endMonth; month++) {
        sum += monthlyProfit[month - 1];
    }
    return sum;
}

// Геттер средней месячной прибыли за период
double Shop::getAverageMonthlyProfit(int startMonth, int endMonth) const {
    if (startMonth < 1 || startMonth > 12 || endMonth < 1 || endMonth > 12) {
        throw invalid_argument("Месяцы должны быть в диапазоне 1-12");
    }
    if (startMonth > endMonth) {
        throw invalid_argument("Начальный месяц должен быть раньше конечного");
    }

    int monthsCount = endMonth - startMonth + 1;
    if (monthsCount == 0) return 0.0;

    return getTotalProfitForMonths(startMonth, endMonth) / monthsCount;
}

// Геттер прироста прибыли за период (последний месяц / первый месяц)
double Shop::getProfitGrowth(int startMonth, int endMonth) const {
    if (startMonth < 1 || startMonth > 12 || endMonth < 1 || endMonth > 12) {
        throw invalid_argument("Месяцы должны быть в диапазоне 1-12");
    }
    if (startMonth >= endMonth) {
        throw invalid_argument("Нужно минимум 2 месяца для расчета прироста");
    }

    double firstMonthProfit = monthlyProfit[startMonth - 1];
    double lastMonthProfit = monthlyProfit[endMonth - 1];

    if (firstMonthProfit == 0.0) {
        return (lastMonthProfit > 0.0) ? 100.0 : 0.0; // Если начало было 0, а конец > 0
    }

    return ((lastMonthProfit - firstMonthProfit) / firstMonthProfit) * 100.0;
}

// Сеттеры
void Shop::setName(const string& name) {
    if (name.empty()) {
        throw invalid_argument("Название магазина не может быть пустым");
    }
    this->name = name;
}

void Shop::setAddress(const string& address) {
    if (address.empty()) {
        throw invalid_argument("Адрес не может быть пустым");
    }
    this->address = address;
}

void Shop::setFoundationYear(int year) {
    if (!isValidYear(year)) {
        int currentYear = getCurrentYear();
        throw invalid_argument("Год основания должен быть между 1800 и " +
            to_string(currentYear));
    }
    this->foundationYear = year;
}

void Shop::setShopNumber(int number) {
    if (number < 0) {
        throw invalid_argument("Номер магазина не может быть отрицательным");
    }
    this->shopNumber = number;
}

// Установить прибыль за конкретный месяц
void Shop::setProfitForMonth(int month, double profit) {
    if (month < 1 || month > 12) {
        throw invalid_argument("Месяц должен быть в диапазоне 1-12");
    }
    if (profit < 0) {
        throw invalid_argument("Прибыль не может быть отрицательной");
    }

    // Вычитаем старую прибыль и добавляем новую
    totalProfit -= monthlyProfit[month - 1];
    monthlyProfit[month - 1] = profit;
    totalProfit += profit;
}

// Добавить прибыль к существующей за месяц
void Shop::addProfitForMonth(int month, double profit) {
    if (month < 1 || month > 12) {
        throw invalid_argument("Месяц должен быть в диапазоне 1-12");
    }
    if (profit < 0) {
        throw invalid_argument("Нельзя добавить отрицательную прибыль");
    }

    monthlyProfit[month - 1] += profit;
    totalProfit += profit;
}

// Сбросить прибыль по месяцам
void Shop::resetMonthlyProfits() {
    for (int i = 0; i < 12; i++) {
        totalProfit -= monthlyProfit[i];
        monthlyProfit[i] = 0.0;
    }
}

// Метод для вывода информации о магазине
void Shop::displayInfo() const {
    cout << "\n=== ИНФОРМАЦИЯ О МАГАЗИНЕ ===\n";
    cout << "Название: " << name << endl;
    cout << "Адрес: " << address << endl;
    cout << "Год основания: " << foundationYear << endl;
    cout << "Номер магазина: " << shopNumber << endl;
    cout << fixed << setprecision(2);
    cout << "Суммарная прибыль за все время: " << totalProfit << " руб." << endl;
    cout << "==============================\n";
}

// Метод для вывода месячной информации
void Shop::displayMonthlyInfo(int startMonth, int endMonth) const {
    if (startMonth < 1 || startMonth > 12 || endMonth < 1 || endMonth > 12) {
        throw invalid_argument("Месяцы должны быть в диапазоне 1-12");
    }
    if (startMonth > endMonth) {
        throw invalid_argument("Начальный месяц должен быть раньше конечного");
    }

    cout << "\n=== МЕСЯЧНАЯ ПРИБЫЛЬ МАГАЗИНА \"" << name << "\" ===\n";
    cout << fixed << setprecision(2);

    for (int month = startMonth; month <= endMonth; month++) {
        cout << setw(12) << left << getMonthName(month) << ": "
            << setw(10) << right << monthlyProfit[month - 1] << " руб." << endl;
    }

    double total = getTotalProfitForMonths(startMonth, endMonth);
    double average = getAverageMonthlyProfit(startMonth, endMonth);

    cout << "------------------------------------\n";
    cout << setw(12) << left << "Итого:" << ": "
        << setw(10) << right << total << " руб." << endl;
    cout << setw(12) << left << "Средняя:" << ": "
        << setw(10) << right << average << " руб./мес." << endl;

    if (endMonth - startMonth >= 1) {
        double growth = getProfitGrowth(startMonth, endMonth);
        cout << setw(12) << left << "Прирост:" << ": "
            << setw(10) << right << growth << " %" << endl;
    }

    cout << "====================================\n";
}

// Сериализация в указанный файл
void Shop::serialize(const string& filename) const {
    ofstream file(filename);

    if (!file.is_open()) {
        throw runtime_error("Не удалось открыть файл для записи: " + filename);
    }

    // Записываем основные данные
    file << name << endl;
    file << address << endl;
    file << foundationYear << endl;
    file << shopNumber << endl;
    file << totalProfit << endl;

    // Записываем прибыль по месяцам
    for (int i = 0; i < 12; i++) {
        file << monthlyProfit[i] << " ";
    }
    file << endl;

    file.close();
    cout << "Данные магазина \"" << name << "\" сохранены в файл: "
        << filename << endl;
}

// Сериализация в файл по умолчанию
void Shop::serialize() const {
    serialize("shop_data.txt");
}

// Десериализация из указанного файла
void Shop::deserialize(const string& filename) {
    ifstream file(filename);

    if (!file.is_open()) {
        throw runtime_error("Не удалось открыть файл для чтения: " + filename);
    }

    // Считываем основные данные
    string oldName = name;

    getline(file, name);
    getline(file, address);

    int year;
    file >> year;
    setFoundationYear(year);

    int number;
    file >> number;
    setShopNumber(number);

    file >> totalProfit;

    // Считываем прибыль по месяцам
    for (int i = 0; i < 12; i++) {
        file >> monthlyProfit[i];
    }

    // Пропускаем оставшийся символ новой строки
    file.ignore(numeric_limits<streamsize>::max(), '\n');

    file.close();
    cout << "Данные магазина загружены из файла: " << filename
        << " (было: \"" << oldName << "\", стало: \"" << name << "\")" << endl;
}

// Десериализация из файла по умолчанию
void Shop::deserialize() {
    deserialize("shop_data.txt");
}

// Статический метод для сортировки по общей прибыли
void Shop::sortByTotalProfit(vector<Shop*>& shops, int startMonth, int endMonth) {
    sort(shops.begin(), shops.end(),
        [startMonth, endMonth](Shop* a, Shop* b) {
            return a->getTotalProfitForMonths(startMonth, endMonth) >
                b->getTotalProfitForMonths(startMonth, endMonth);
        });
}

// Статический метод для сортировки по приросту прибыли
void Shop::sortByProfitGrowth(vector<Shop*>& shops, int startMonth, int endMonth) {
    sort(shops.begin(), shops.end(),
        [startMonth, endMonth](Shop* a, Shop* b) {
            return a->getProfitGrowth(startMonth, endMonth) >
                b->getProfitGrowth(startMonth, endMonth);
        });
}

// Функция демонстрации работы класса Shop
void demonstrateShopClass() {
    cout << "\n=== ДЕМОНСТРАЦИЯ РАБОТЫ КЛАССА SHOP ===\n\n";

    // 1. Создание объектов разными способами
    cout << "1. СОЗДАНИЕ ОБЪЕКТОВ РАЗНЫМИ СПОСОБАМИ:\n";

    // Два объекта в куче (динамическая память)
    Shop* shop1 = new Shop();
    Shop* shop2 = new Shop();

    // Заполнение через сеттеры
    shop1->setName("Супермаркет 'Пятерочка'");
    shop1->setAddress("ул. Ленина, д. 10");
    shop1->setFoundationYear(2010);
    shop1->setShopNumber(101);

    shop2->setName("Гипермаркет 'Магнит'");
    shop2->setAddress("пр. Мира, д. 25");
    shop2->setFoundationYear(2015);
    shop2->setShopNumber(102);

    // Один объект в стеке через конструктор с параметрами
    Shop shop3("Торговый центр 'Перекресток'", "ул. Советская, д. 15",
        2005, 103);

    cout << "   Создано 3 магазина: 2 в куче, 1 в стеке\n\n";

    // 2. Демонстрация инкапсуляции
    cout << "2. ДЕМОНСТРАЦИЯ ИНКАПСУЛЯЦИИ (доступ только через геттеры):\n";
    cout << "   Магазин 1: " << shop1->getName()
        << " (год основания: " << shop1->getFoundationYear() << ")\n";
    cout << "   Магазин 2: " << shop2->getName()
        << " (адрес: " << shop2->getAddress() << ")\n";
    cout << "   Магазин 3: " << shop3.getName()
        << " (номер: " << shop3.getShopNumber() << ")\n\n";

    // 3. Имитация продаж за сентябрь, октябрь, ноябрь
    cout << "3. ИМИТАЦИЯ ПРОДАЖ ЗА СЕНТЯБРЬ-НОЯБРЬ:\n";

    // Месяцы: сентябрь(8), октябрь(9), ноябрь(10)
    const int SEPTEMBER = 8;
    const int OCTOBER = 9;
    const int NOVEMBER = 10;

    // Задаем прибыль для магазинов
    shop1->setProfitForMonth(SEPTEMBER, 850000.0);
    shop1->setProfitForMonth(OCTOBER, 935000.0);
    shop1->setProfitForMonth(NOVEMBER, 1028500.0);

    shop2->setProfitForMonth(SEPTEMBER, 720000.0);
    shop2->setProfitForMonth(OCTOBER, 792000.0);
    shop2->setProfitForMonth(NOVEMBER, 871200.0);

    shop3.setProfitForMonth(SEPTEMBER, 950000.0);
    shop3.setProfitForMonth(OCTOBER, 1045000.0);
    shop3.setProfitForMonth(NOVEMBER, 1149500.0);

    cout << "   Прибыль установлена для всех магазинов\n\n";

    // 4. Создаем вектор для сортировки
    cout << "4. СОЗДАНИЕ ВЕКТОРА ДЛЯ СОРТИРОВКИ:\n";
    vector<Shop*> shops;
    shops.push_back(shop1);
    shops.push_back(shop2);
    shops.push_back(&shop3);  // адрес объекта в стеке

    cout << "   Вектор содержит " << shops.size() << " магазина\n\n";

    // 5. РЕЙТИНГ 1: Сортировка по убыванию общей прибыли
    cout << "5. РЕЙТИНГ 1: ПО ОБЩЕЙ ПРИБЫЛИ ЗА 3 МЕСЯЦА\n";
    cout << "========================================\n";

    Shop::sortByTotalProfit(shops, SEPTEMBER, NOVEMBER);

    cout << fixed << setprecision(0);
    cout << setw(3) << "№" << setw(30) << "Название магазина"
        << setw(20) << "Общая прибыль" << endl;
    cout << string(53, '-') << endl;

    for (size_t i = 0; i < shops.size(); i++) {
        Shop* shop = shops[i];
        double total = shop->getTotalProfitForMonths(SEPTEMBER, NOVEMBER);

        cout << setw(3) << (i + 1) << " "
            << setw(30) << left << shop->getName() << right
            << setw(20) << total << " руб." << endl;
    }
    cout << endl;

    // 6. РЕЙТИНГ 2: Сортировка по убыванию прироста прибыли
    cout << "6. РЕЙТИНГ 2: ПО ПРИРОСТУ ПРИБЫЛИ (сентябрь → ноябрь)\n";
    cout << "====================================================\n";

    Shop::sortByProfitGrowth(shops, SEPTEMBER, NOVEMBER);

    cout << fixed << setprecision(1);
    cout << setw(3) << "№" << setw(30) << "Название магазина"
        << setw(20) << "Прирост" << endl;
    cout << string(53, '-') << endl;

    for (size_t i = 0; i < shops.size(); i++) {
        Shop* shop = shops[i];
        double growth = shop->getProfitGrowth(SEPTEMBER, NOVEMBER);

        cout << setw(3) << (i + 1) << " "
            << setw(30) << left << shop->getName() << right
            << setw(20) << growth << " %" << endl;
    }
    cout << endl;

    // 7. Демонстрация сериализации
    cout << "7. ДЕМОНСТРАЦИЯ СЕРИАЛИЗАЦИИ:\n";

    try {
        // Сохраняем данные лучшего магазина (по общей прибыли)
        Shop::sortByTotalProfit(shops, SEPTEMBER, NOVEMBER);
        shops[0]->serialize("best_shop.txt");

        cout << "   Данные магазина \"" << shops[0]->getName()
            << "\" сохранены в файл 'best_shop.txt'\n\n";

        // Загружаем данные в новый объект
        Shop loadedShop;
        loadedShop.deserialize("best_shop.txt");

        cout << "   Загруженный магазин: " << loadedShop.getName()
            << " (прибыль: " << loadedShop.getTotalProfit() << " руб.)\n\n";

    }
    catch (const runtime_error& e) {
        cout << "   Ошибка: " << e.what() << endl;
    }

    // 8. Вывод детальной информации о магазинах
    cout << "8. ДЕТАЛЬНАЯ ИНФОРМАЦИЯ О МАГАЗИНАХ:\n";

    shop1->displayInfo();
    shop1->displayMonthlyInfo(SEPTEMBER, NOVEMBER);

    // 9. Очистка динамической памяти
    cout << "9. ОЧИСТКА ДИНАМИЧЕСКОЙ ПАМЯТИ:\n";

    delete shop1;
    delete shop2;

    cout << "   Динамическая память освобождена\n";
    cout << "   Объект в стеке будет удален автоматически\n\n";

    cout << "=== ДЕМОНСТРАЦИЯ ЗАВЕРШЕНА ===\n";
}