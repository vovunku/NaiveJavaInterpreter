project(BuildAst)
set(
        HEADERS
        ${BuildAst_SOURCE_DIR}/driver.hh
        ${BuildAst_SOURCE_DIR}/parser.hh
)

BISON_TARGET(
        MyParser
        parser.y
        ${BuildAst_SOURCE_DIR}/parser.cpp
        DEFINES_FILE ${BuildAst_SOURCE_DIR}/parser.hh
)

FLEX_TARGET(
        MyScanner
        scanner.l
        ${BuildAst_SOURCE_DIR}/scanner.cpp
)

ADD_FLEX_BISON_DEPENDENCY(MyScanner MyParser)

add_executable(
        BuildAst
        main.cpp
        driver.cpp
        ${BISON_MyParser_OUTPUTS}
        ${FLEX_MyScanner_OUTPUTS}
)
target_include_directories(BuildAst PRIVATE ${BuildAst_SOURCE_DIR})