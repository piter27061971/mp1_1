
#include <iostream>
#include <thread>
#include <mutex>
#include <functional>

int max_col_client = 25;
std::atomic_int  kol_clientov = 0;

void clientThread() {
    while (kol_clientov < max_col_client)
    {
        std::this_thread::sleep_for(std::chrono::seconds(1));
        kol_clientov++;
        std::cout << "Новый клиент пришел, количество клиентов: " << kol_clientov << std::endl;
    }
}

void operatorThread() {
    while (true) {
        std::this_thread::sleep_for(std::chrono::seconds(2));
        if (kol_clientov > 0)
        {
            kol_clientov--;
            std::cout << "Оператор обработал клиента, общее количество клиентов: " << kol_clientov << std::endl;
        }
        else
        {
            std::cout << "Опреатор закончил работу, количество клиентов: " << kol_clientov << std::endl;
            break;
        }
    }
}

int main() {

    setlocale(LC_ALL, "");
    std::thread client(clientThread);
    std::thread operatorT(operatorThread);

    client.join();
    operatorT.join();

    return 0;
}