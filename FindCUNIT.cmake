MESSAGE(STATUS "Check for CUnit")

FIND_PATH(CUNIT_INCLUDE_DIR CUnit/CUnit.h /usr/local/include /usr/include)
FIND_PATH(CUNIT_INCLUDE_DIR CUnit/Basic.h /usr/local/include /usr/include)
FIND_PATH(CUNIT_INCLUDE_DIR CUnit/Console.h /usr/local/include /usr/include)

FIND_LIBRARY(CUNIT_LIBRARY NAMES cunit PATHS /usr/lib /usr/local/lib)

if(CUNIT_INCLUDE_DIR AND CUNIT_LIBRARY)
    SET(CUNIT_FOUND TRUE)
endif()

if (CUNIT_FOUND)
    MESSAGE(STATUS "Check for CUnit -- ok")
else()
    MESSAGE(FATAL_ERROR "Check for CUnit -- not found")
endif()
