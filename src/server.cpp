#include <iostream>
#include <string>
#include <uWebSockets/App.h>
#include <string_view>
#include <vector>
#include <thread>
#include <algorithm>
#include <atomic>

struct UserConnection {
    std::string user_name;
    int user_id;
};

int main()
{
    std::atomic<int> latest_user_id = -1;
    std::vector<std::thread*>  threads(std::thread::hardware_concurrency());

    std::transform(threads.begin(), threads.end(), threads.begin(), [&latest_user_id](auto* thr) {
        return new std::thread([&latest_user_id]() {
            uWS::App().ws<UserConnection>("/*", {
                .open = [&latest_user_id](auto* ws) {
                    // Действие при подключении пользователя
                    UserConnection* data = dynamic_cast<UserConnection*>(ws->getUserData());
                    if (data)
                    {
                        data->user_id = (++latest_user_id);
                        std::cout << data->user_id << " connected\n";
                    }
                },
                .message = [](auto* ws, std::string_view messege, uWS::OpCode opCode) {
                        // Действие при получении сообщания
                    std::cout << "Messege echo " <<  messege<< "\n";
                }
                }).listen(9999, [](auto* tkn) {
                    if (tkn)
                    {
                        std::cout << "Server started\n";
                    }
                    else
                    {
                        std::cout << "Failed server start\n";
                    }
                 }).run(); // ws://127.0.0.1
            });
        });

    /*
        uWS::App().ws<UserConnection>("/*", {
            .open = [&](auto* ws) {
                    // Действие при подключении пользователя
                    UserConnection* data = dynamic_cast<UserConnection*>(ws->getUserData());
                    if (data)
                    {
                        data->user_id = (++latest_user_id);
                    }
                },
            .message = [](auto* ws, std::string_view messege, uWS::OpCode opCode) {
                    // Действие при получении сообщания
            }
        }); // ws://127.0.0.1
        */

    for (auto& thread : threads)
    {
        thread->join();
    }

    std::cout << "hello";
    return 0;
}