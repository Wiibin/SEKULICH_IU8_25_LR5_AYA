/*
Сэкулич Михаил ИУ8-25
Вариант №22

Объект - банковский кредит

Поля:
    название,
    сумма кредита,
    тип валюты,
    ставка в % годовых

Сортировка по сумме кредита (по возрастанию)

Для класса, разработанного в ЛР4,
обеспечить возможность добавления объектов в
    контейнер set (сортировка как указано в задании на ЛР4) (по сумме кредита)
    и в контейнер unordered_set.

Исходные данные как в ЛР4 читать из файла,
вывести на печать для контроля объекты контейнеров.
*/
#include <iostream>
#include <fstream>


#include <string>
#include <set>
#include <unordered_set>

#include <deque>
#include <algorithm>

using namespace std;

class Credit {
private:
    string name;
    double amount;
    string currency;
    double rate;
public:
    Credit() {
        name = "";
        amount = 0;
        currency = "";
        rate = 0;
    }
    Credit(const Credit& cr) {
        name = cr.name;
        amount = cr.amount;
        currency = cr.currency;
        rate = cr.rate;
    }
    Credit& operator=(const Credit& cr) {
        name = cr.name;
        amount = cr.amount;
        currency = cr.currency;
        rate = cr.rate;
        return *this;
    }
    friend ostream& operator<<(ostream& out, Credit& cr);
    friend istream& operator>>(istream& in, Credit& cr);
    friend bool operator<(const Credit cr_a, const Credit cr_b);
    friend bool operator==(const Credit cr_a, const Credit cr_b);
    friend class CreditHasher;
};

ostream& operator<<(ostream& out, Credit& cr) {
    out << "Name: " << cr.name << "\n";
    out << "Amount: " << cr.amount << "\n";
    out << "Currency: " << cr.currency << "\n";
    out << "Rate: " << cr.rate << "\n\n";
    return out;
}
istream& operator>>(istream& in, Credit& cr) {
    in >> cr.name;
    in >> cr.amount;
    in>> cr.currency;
    in >> cr.rate;
    return in;
}
bool operator<(const Credit cr_a, const Credit cr_b) {
    return cr_a.amount < cr_b.amount;
}
bool operator==(const Credit cr_a, const Credit cr_b) {
    return (cr_a.name == cr_b.name) && (cr_a.amount == cr_b.amount) && (cr_a.currency == cr_b.currency) && (cr_a.rate == cr_b.rate);
}

class CreditHasher {
private:
    hash<string> shash;
    hash<double> dhash;
    const size_t coef = 2'946'901;
public:
    size_t operator()(Credit const& cr) const {
        return (coef*coef*coef * shash(cr.name)
                + coef*coef * dhash(cr.amount)
                + coef * shash(cr.currency)
                + dhash(cr.rate));
    }
};

int main() {
    ifstream file("input_credit.txt");
    if (!file) return 1;
    int s;
    file >> s;
    set<Credit> credit_set;
    unordered_set<Credit, CreditHasher> credit_un_set;
    for (int i = 0; i < s; i++) {
        Credit cr;
        file >> cr;
        credit_set.insert(cr);
        credit_un_set.insert(cr);
    }
    file.close();

    cout << "IN SET:\n";
    for (auto cr : credit_set) cout << cr;
    cout << "\n\nIN UNORDERED SET:\n";
    for (auto cr : credit_un_set) cout << cr;
    return 0;
}


