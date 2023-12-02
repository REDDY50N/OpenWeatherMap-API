target_include_directories(${EXEC_NAME} PRIVATE .)

target_sources(${EXEC_NAME} PRIVATE
        ./main.cpp
        ./weatherapi.h
        ./weatherapi.cpp
        #./ApiKeyManager.cpp
        #./ApiKeyManager.h
        #HttpRequest.cpp
        #HttpRequest.h
)

add_subdirectory(ui)
