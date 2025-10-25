//
// Created by Tisca Catalin on 26.10.2025.
//

#ifndef ECS_H
#define ECS_H



class Engine {
    bool running = true;

public:
    Engine();
    ~Engine() noexcept;

    void run() noexcept;
};



#endif //ECS_H
