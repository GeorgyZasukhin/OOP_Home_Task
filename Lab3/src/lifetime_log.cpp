#include "lifetime_log.h"

#include <iostream>

namespace
{
    int live = 0;

    void write(const char* event, const char* type,
               const std::string& name) noexcept
    {
        // Навіть якщо потік налаштований кидати винятки, dtor безпечний.
        try
        {
            std::clog << event << ' ' << type << ' ' << name
                      << " live=" << live << '\n';
        }
        catch (...)
        {
            // Помилка журналу не повинна перервати знищення об'єкта.
        }
    }
}

int lifetime::liveCount() noexcept
{
    return live;
}

void lifetime::created(const char* type, const std::string& name) noexcept
{
    ++live;
    write("ctor", type, name);
}

void lifetime::destroyed(const char* type, const std::string& name) noexcept
{
    --live;
    write("dtor", type, name);
}
