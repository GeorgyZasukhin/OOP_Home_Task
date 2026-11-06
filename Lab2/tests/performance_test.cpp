#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "performance.h"

#include <limits>
#include <tuple>
#include <utility>

struct PerformanceTestAccess
{
    static bool invariant(const Performance& performance)
    {
        return performance.checkInvariant();
    }
};

// Копія всього стану дозволяє виявити будь-яку небажану зміну.
auto state(const Performance& p)
{
    return std::make_tuple(p.title(), p.director(), p.premiereDate(),
                           p.totalSeats(), p.soldTickets());
}

TEST_CASE("case_1")
{
    // Початковий об'єкт є коректною порожньою чернеткою.
    const Performance p;
    CHECK(p.title().empty());
    CHECK(p.director().empty());
    CHECK(p.premiereDate().empty());
    CHECK(p.totalSeats() == 0);
    CHECK(p.soldTickets() == 0);
    CHECK(p.freeSeats() == 0);
    CHECK(p.isSoldOut());
    CHECK(PerformanceTestAccess::invariant(p));
}

TEST_CASE("case_2")
{
    // Успішна зміна всіх незалежних полів.
    Performance p;
    CHECK(p.setTitle("Лісова пісня"));
    CHECK(p.setDirector("Олена Коваленко"));
    CHECK(p.setPremiereDate("2026-11-06"));
    CHECK(p.setTotalSeats(100));
    CHECK(p.title() == "Лісова пісня");
    CHECK(p.director() == "Олена Коваленко");
    CHECK(p.premiereDate() == "2026-11-06");
    CHECK(p.totalSeats() == 100);
    CHECK(PerformanceTestAccess::invariant(p));
}

TEST_CASE("case_3")
{
    // Відхилення порожніх і пробільних рядків не змінює стан.
    Performance p;
    REQUIRE(p.setTitle("Hamlet"));
    REQUIRE(p.setDirector("Director"));
    const auto before = state(p);
    CHECK_FALSE(p.setTitle(""));
    CHECK_FALSE(p.setTitle(" \t\r\n"));
    CHECK_FALSE(p.setDirector(""));
    CHECK_FALSE(p.setDirector("\t "));
    CHECK(state(p) == before);
    CHECK(PerformanceTestAccess::invariant(p));
}

TEST_CASE("case_4")
{
    // Некоректний формат дати та відсутність змін після відмови.
    Performance p;
    REQUIRE(p.setPremiereDate("2026-11-06"));
    const auto before = state(p);
    for (const auto& date : {"", "2026-1-01", "06.11.2026",
                             "202a-11-06", "2026/11/06"})
    {
        CHECK_FALSE(p.setPremiereDate(date));
        CHECK(state(p) == before);
        CHECK(PerformanceTestAccess::invariant(p));
    }
}

TEST_CASE("case_5")
{
    // Високосність: століття мають окреме правило.
    CHECK(Performance::isValidDate("2024-02-29"));
    CHECK(Performance::isValidDate("2000-02-29"));
    CHECK_FALSE(Performance::isValidDate("1900-02-29"));
    CHECK_FALSE(Performance::isValidDate("2100-02-29"));
    CHECK_FALSE(Performance::isValidDate("2026-02-29"));
}

TEST_CASE("case_6")
{
    // Межі року, місяця та дня.
    CHECK(Performance::isValidDate("0001-01-01"));
    CHECK(Performance::isValidDate("9999-12-31"));
    for (const auto& date : {"0000-01-01", "2026-00-01",
                             "2026-13-01", "2026-04-31",
                             "2026-01-00", "2026-01-32"})
    {
        CHECK_FALSE(Performance::isValidDate(date));
    }
}

TEST_CASE("case_7")
{
    // Від'ємна місткість не змінює стан.
    Performance p;
    REQUIRE(p.setTotalSeats(10));
    const auto before = state(p);
    CHECK_FALSE(p.setTotalSeats(-1));
    CHECK(state(p) == before);
    CHECK(PerformanceTestAccess::invariant(p));
}

TEST_CASE("case_8")
{
    // Продаж останнього квитка.
    Performance p;
    REQUIRE(p.setTotalSeats(1));
    CHECK(p.sellTicket());
    CHECK(p.soldTickets() == 1);
    CHECK(p.freeSeats() == 0);
    CHECK(p.isSoldOut());
    CHECK(PerformanceTestAccess::invariant(p));
}

TEST_CASE("case_9")
{
    // Продаж у заповнений зал відхиляється.
    Performance p;
    REQUIRE(p.setTotalSeats(1));
    REQUIRE(p.sellTicket());
    const auto before = state(p);
    CHECK_FALSE(p.sellTicket());
    CHECK(state(p) == before);
    CHECK(PerformanceTestAccess::invariant(p));
}

TEST_CASE("case_10")
{
    // Зал без місць також не дозволяє продажу.
    Performance p;
    const auto before = state(p);
    CHECK_FALSE(p.sellTicket());
    CHECK(state(p) == before);
    CHECK(PerformanceTestAccess::invariant(p));
}

TEST_CASE("case_11")
{
    // Повернення проданого квитка відновлює вільне місце.
    Performance p;
    REQUIRE(p.setTotalSeats(1));
    REQUIRE(p.sellTicket());
    CHECK(p.returnTicket());
    CHECK(p.soldTickets() == 0);
    CHECK(p.freeSeats() == 1);
    CHECK_FALSE(p.isSoldOut());
    CHECK(PerformanceTestAccess::invariant(p));
}

TEST_CASE("case_12")
{
    // Зайве повернення не може зробити лічильник від'ємним.
    Performance p;
    REQUIRE(p.setTotalSeats(1));
    REQUIRE(p.sellTicket());
    REQUIRE(p.returnTicket());
    const auto before = state(p);
    CHECK_FALSE(p.returnTicket());
    CHECK(state(p) == before);
    CHECK(PerformanceTestAccess::invariant(p));
}

TEST_CASE("case_13")
{
    // Місткість не може стати меншою за кількість продажів.
    Performance p;
    REQUIRE(p.setTotalSeats(3));
    REQUIRE(p.sellTicket());
    REQUIRE(p.sellTicket());
    const auto before = state(p);
    CHECK_FALSE(p.setTotalSeats(1));
    CHECK(state(p) == before);
    CHECK(p.setTotalSeats(2));
    CHECK(p.isSoldOut());
    CHECK(PerformanceTestAccess::invariant(p));
}

TEST_CASE("case_14")
{
    // Максимальний int та повернення до нульової місткості.
    Performance p;
    CHECK(p.setTotalSeats(std::numeric_limits<int>::max()));
    CHECK(p.sellTicket());
    CHECK(p.freeSeats() == std::numeric_limits<int>::max() - 1);
    CHECK(p.returnTicket());
    CHECK(p.setTotalSeats(0));
    CHECK(PerformanceTestAccess::invariant(p));
}

TEST_CASE("case_15")
{
    // Послідовність операцій, копіювання та переміщення чернетки.
    Performance p;
    REQUIRE(p.setTotalSeats(3));
    for (int i = 0; i < 3; ++i)
    {
        CHECK(p.sellTicket());
        CHECK(PerformanceTestAccess::invariant(p));
    }
    for (int i = 0; i < 3; ++i)
    {
        CHECK(p.returnTicket());
        CHECK(PerformanceTestAccess::invariant(p));
    }
    const Performance copy = p;
    CHECK(state(copy) == state(p));
    const Performance moved = std::move(p);
    CHECK(PerformanceTestAccess::invariant(moved));
    CHECK(PerformanceTestAccess::invariant(p));
}
