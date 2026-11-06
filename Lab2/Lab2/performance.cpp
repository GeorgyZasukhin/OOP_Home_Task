#include "performance.h"

const std::string& Performance::title() const
{
    return title_;
}


const std::string& Performance::director() const
{
    return director_;
}


const std::string& Performance::premiereDate() const
{
    return premiereDate_;
}


int Performance::totalSeats() const
{
    return totalSeats_;
}


int Performance::soldTickets() const
{
    return soldTickets_;
}


int Performance::freeSeats() const
{
    return totalSeats_ - soldTickets_;
}


bool Performance::isSoldOut() const
{
    return freeSeats() == 0;
}


bool Performance::setTitle(const std::string& title)
{
    if (!hasText(title))
    {
        return false;
    }
    title_ = title;
    return true;
}


bool Performance::setDirector(const std::string& director)
{
    if (!hasText(director))
    {
        return false;
    }
    director_ = director;
    return true;
}


bool Performance::setPremiereDate(const std::string& date)
{
    if (!isValidDate(date))
    {
        return false;
    }
    premiereDate_ = date;
    return true;
}


bool Performance::setTotalSeats(int seats)
{
    // Не можна прибрати місця, на які вже продано квитки.
    if (seats < 0 || seats < soldTickets_)
    {
        return false;
    }
    totalSeats_ = seats;
    return true;
}


bool Performance::sellTicket()
{
    if (isSoldOut())
    {
        return false;
    }
    ++soldTickets_;
    return true;
}


bool Performance::returnTicket()
{
    if (soldTickets_ == 0)
    {
        return false;
    }
    --soldTickets_;
    return true;
}


bool Performance::hasText(const std::string& text)
{
    return text.find_first_not_of(" \t\n\r\f\v") != std::string::npos;
}


bool Performance::isValidDate(const std::string& date)
{
    // Спочатку формат, потім календарні обмеження.
    if (date.size() != 10 || date[4] != '-' || date[7] != '-')
    {
        return false;
    }

    for (std::size_t i = 0; i < date.size(); ++i)
    {
        if (i != 4 && i != 7 && (date[i] < '0' || date[i] > '9'))
        {
            return false;
        }
    }

    const int year = (date[0] - '0') * 1000 + (date[1] - '0') * 100
                   + (date[2] - '0') * 10 + date[3] - '0';
    const int month = (date[5] - '0') * 10 + date[6] - '0';
    const int day = (date[8] - '0') * 10 + date[9] - '0';

    if (year == 0 || month < 1 || month > 12 || day < 1)
    {
        return false;
    }

    const int daysInMonth[]
    {
        31, 28, 31, 30, 31, 30,
        31, 31, 30, 31, 30, 31
    };
    const bool leapYear = year % 400 == 0
                       || (year % 4 == 0 && year % 100 != 0);
    const int maxDay = daysInMonth[month - 1]
                     + (month == 2 && leapYear ? 1 : 0);
    return day <= maxDay;
}

bool Performance::checkInvariant() const
{
    return (title_.empty() || hasText(title_))
        && (director_.empty() || hasText(director_))
        && (premiereDate_.empty() || isValidDate(premiereDate_))
        && totalSeats_ >= 0
        && soldTickets_ >= 0 && soldTickets_ <= totalSeats_;
}
