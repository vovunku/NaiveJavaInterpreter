project(NaiveJava)
set(
        HEADERS
        ${NaiveJava_SOURCE_DIR}/driver.hh
        ${NaiveJava_SOURCE_DIR}/parser.hh
)

BISON_TARGET(
        MyParser
        parser.y
        ${NaiveJava_SOURCE_DIR}/parser.cpp
        DEFINES_FILE ${NaiveJava_SOURCE_DIR}/parser.hh
)

FLEX_TARGET(
        MyScanner
        scanner.l
        ${NaiveJava_SOURCE_DIR}/scanner.cpp
)

ADD_FLEX_BISON_DEPENDENCY(MyScanner MyParser)

add_executable(
        NaiveJava
        main.cpp
        driver.cpp
        ${BISON_MyParser_OUTPUTS}
        ${FLEX_MyScanner_OUTPUTS}
)
target_include_directories(NaiveJava PRIVATE ${NaiveJava_SOURCE_DIR})