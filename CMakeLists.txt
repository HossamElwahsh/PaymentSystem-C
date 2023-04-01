cmake_minimum_required(VERSION 3.24)
project(PaymentSystem C)

set(CMAKE_C_STANDARD 11)

include_directories(Application)
include_directories(Card)
include_directories(Server)
include_directories(Terminal)

add_executable(PaymentSystem
        Application/app.c
        Application/app.h
        Card/card.c
        Card/card.h
        Server/server.c
        Server/server.h
        Terminal/terminal.c
        Terminal/terminal.h Test/test.c Test/test.h Console/console.c)
