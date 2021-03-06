#include <iostream>
#include <tuple>

#include "core/string.h"


void jle::alarm_msg(const jle::alarm& al)
{
    std::cout << "ouch...: "  << al << std::endl;

}


int main()
{
    {
        auto result = jle::s_try_s2d("3.1415926535", 0.);
        if(std::get<1>(result))
            std::cout <<  std::get<0>(result) << std::endl;
    }

    {
        auto result = jle::s_try_s2dur("3m 4s 132ms", 0s);
        if(std::get<1>(result))
            std::cout <<  std::get<0>(result) << std::endl;
    }

}
