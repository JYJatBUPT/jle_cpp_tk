#include <iostream>
#include <chrono>

#include "support/signal_slot.hpp"



class class_receptor_do_nothing : public jle::signal_receptor
{

public:
    void do_nothing(void) {};
};



void receptor_do_nothing (void)
{

}


int contador = 0;
void count (void)
{
    ++contador;
}



const long REPETITIONS = 1000000000L;


int main (int /*argc*/, char** /*argv*/)
{
    std::cout << "---------------------------------------------------------------------" << std::endl;
    std::cout << "add int loop " << std::endl << std::endl;
    {
        auto  start = std::chrono::high_resolution_clock::now();
        int acc=0;
        for (int i=0; i<REPETITIONS; ++i)
            acc +=i;
        auto  end = std::chrono::high_resolution_clock::now();

        std:: cout << acc << std::endl;
        std::chrono::duration<double>  time = end-start;
        std::cout << "time: " << time.count() << std::endl;
        std::cout << "calls/millisecond: " << REPETITIONS / time.count() / 1000. << std::endl;
    }



    std::cout << "---------------------------------------------------------------------" << std::endl;
    std::cout << "signal -> function (emit)" << std::endl << std::endl;
    {
        jle::signal<>   svoid;

        svoid.connect( receptor_do_nothing );

        auto  start = std::chrono::high_resolution_clock::now();

        for (int i=0; i<REPETITIONS; ++i)
            svoid.emit();

        auto  end = std::chrono::high_resolution_clock::now();

        std::chrono::duration<double>  time = end-start;
        std::cout << "time: " << time.count() << std::endl;
        std::cout << "calls/millisecond: " << REPETITIONS / time.count() / 1000. << std::endl;
    }

    std::cout << "---------------------------------------------------------------------" << std::endl;
    std::cout << "signal -> function (no emit)" << std::endl << std::endl;
    {
        jle::signal<>   svoid;

        svoid.connect( receptor_do_nothing );

        auto start = std::chrono::high_resolution_clock::now();
        for (int i=0; i<REPETITIONS; ++i)
            svoid();

        auto end = std::chrono::high_resolution_clock::now();

        std::chrono::duration<double> time = end - start;
        std::cout << "time: " << time.count() << std::endl;
        std::cout << "calls/millisecond: " << REPETITIONS / time.count() /1000. << std::endl;
    }

    std::cout << "---------------------------------------------------------------------" << std::endl;
    std::cout << "signal -> method  (emit)" << std::endl << std::endl;
    {
        jle::signal<>   svoid;
        class_receptor_do_nothing class_do_nothing;

        svoid.connect(&class_do_nothing, &class_receptor_do_nothing::do_nothing );

        auto start = std::chrono::high_resolution_clock::now();
        for (int i=0; i<REPETITIONS; ++i)
            svoid.emit();

        auto end = std::chrono::high_resolution_clock::now();

        std::chrono::duration<double> time = end - start;
        std::cout << "time: " << time.count() << std::endl;
        std::cout << "calls/millisecond: " << REPETITIONS / time.count() / 1000. << std::endl;
    }

    std::cout << "---------------------------------------------------------------------" << std::endl;
    std::cout << "direct call function" << std::endl << std::endl;
    {
        auto start = std::chrono::high_resolution_clock::now();
        for (int i=0; i<REPETITIONS; ++i)
            count();

        auto end = std::chrono::high_resolution_clock::now();

        std::cout << contador << std::endl;
        contador = 0;

        std::chrono::duration<double> time = end - start;
        std::cout << "time: " << time.count() << std::endl;
        if (static_cast<int>(time.count()*1000000) == 0)
            std::cout << "too fast..." << std::endl;
        else
            std::cout << "calls/millisecond: " << REPETITIONS / time.count() / 1000. << std::endl;
    }

    std::cout << "---------------------------------------------------------------------" << std::endl;
    std::cout << "signal -> function " << std::endl << std::endl;
    {
        jle::signal<>   svoid;

        svoid.connect( count );

        auto start = std::chrono::high_resolution_clock::now();
        for (int i=0; i<REPETITIONS; ++i)
            svoid();

        auto end = std::chrono::high_resolution_clock::now();

        std::cout << contador << std::endl;
        contador = 0;

        std::chrono::duration<double> time = end-start;
        std::cout << "time: " << time.count() << std::endl;
        std::cout << "calls/millisecond: " << REPETITIONS / time.count() / 1000. << std::endl;
    }

    return 0;
}
