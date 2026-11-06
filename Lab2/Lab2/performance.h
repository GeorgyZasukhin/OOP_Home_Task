#pragma once

#include <string>

// Інваріант Performance:
// 1. Назва порожня для чернетки або містить непробільний символ.
// 2. Ім'я режисера порожнє або містить непробільний символ.
// 3. Дата порожня або є реальною датою у форматі YYYY-MM-DD.
// 4. Загальна кількість місць невід'ємна.
// 5. Зв'язок полів: 0 <= soldTickets_ <= totalSeats_.
class Performance
{

public://///////////////////////////////////////////////////////////////////////
    const std::string& title() const;
    const std::string& director() const;
    const std::string& premiereDate() const;
    int totalSeats() const;
    int soldTickets() const;

    // Похідні величини не зберігаються в полях.
    int freeSeats() const;
    bool isSoldOut() const;

    // Некоректний аргумент: false, стан залишається незмінним.
    bool setTitle(const std::string& title);
    bool setDirector(const std::string& director);
    bool setPremiereDate(const std::string& date);
    bool setTotalSeats(int seats);
    bool sellTicket();
    bool returnTicket();

    static bool isValidDate(const std::string& date);


private:////////////////////////////////////////////////////////////////////////

    // Тестовий адаптер викликає приватну перевірку інваріанта.
    friend struct PerformanceTestAccess;
    bool checkInvariant() const;
    static bool hasText(const std::string& text);

    std::string title_;
    std::string director_;
    std::string premiereDate_;
    int totalSeats_ = 0;
    int soldTickets_ = 0;
};
