#pragma once
#include <string>
#include <stdexcept>
#include <cmath>
#include <sstream>

inline void CheckValidParams(int n)
{
    if (n <= 4)
    {
        throw std::invalid_argument("n must be greater than 4");
    }
}

inline double checkValidInput(const std::string& input)
{
    std::istringstream stream(input);
    double value;
    char extra;

    if (!(stream >> value) || (stream >> extra) ||
        !std::isfinite(value))
    {
        throw std::invalid_argument("Invalid numeric input");
    }

    return value;
}

inline double calculate(double x, int n)
{
    CheckValidParams(n);

    double y = 0.0;

    if (x <= 0)
    {
        for (int i = 2; i <= n - 1; i++)
        {
            y += (x - 1.0) / i;
        }
    }
    else
    {
        for (int i = 0; i <= n - 1; i++)
        {
            for (int j = 0; j <= i; j++)
            {
                y += static_cast<double>(i + 1) / (j + x);
            }
        }
    }

    return y;
}