target_include_directories(${EXEC_NAME} PRIVATE .)
target_sources(${EXEC_NAME} PRIVATE
        main.cpp
        weatherapi.cpp
        weatherapi.h
)
