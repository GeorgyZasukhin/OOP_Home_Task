#include "performance.h"

#include <iostream>

void print(const Performance& performance)
{
    std::cout << "Title: " << performance.title()
              << "; director: " << performance.director()
              << "; premiere: " << performance.premiereDate() << '\n'
              << "Seats: " << performance.totalSeats()
              << "; sold: " << performance.soldTickets()
              << "; free: " << performance.freeSeats()
              << "; sold out: "
              << (performance.isSoldOut() ? "yes" : "no") << '\n';
}

int main()
{
    Performance performance;
    if (!performance.setTitle("The Forest Song")
        || !performance.setDirector("Olena Kovalenko")
        || !performance.setPremiereDate("2026-11-06")
        || !performance.setTotalSeats(2))
    {
        std::cerr << "Invalid performance data\n";
        return 1;
    }

    std::cout << std::boolalpha;
    print(performance);
    std::cout << "Sell first: " << performance.sellTicket() << '\n'
              << "Sell last: " << performance.sellTicket() << '\n'
              << "Sell extra: " << performance.sellTicket() << '\n';
    print(performance);

    // Спроба порушити зв'язок між кількістю місць і квитків.
    std::cout << "Reduce seats to 1: "
              << performance.setTotalSeats(1) << '\n'
              << "Return ticket: " << performance.returnTicket() << '\n';
    print(performance);
    return 0;
}
