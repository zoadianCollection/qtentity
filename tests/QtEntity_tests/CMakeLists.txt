set(LIB_NAME qtentity_tests)
include_directories(
  ${CMAKE_CURRENT_SOURCE_DIR}/../../include/
  ${CMAKE_CURRENT_BINARY_DIR} # for moc files
  ${CMAKE_CURRENT_BINARY_DIR}/../../source # for dtentity export header
)

set(QTENTITY_TESTS_HDR
    common.h
    test_entitysystem.h
    test_entitymanager.h
    test_pooledentitysystem.h
    test_prefabsystem.h
	test_scripting.h
)

set(QTENTITY_TESTS_SRC
    common.cpp
    main.cpp
)

QT5_WRAP_CPP(MOC_SOURCES ${QTENTITY_TESTS_HDR})

add_executable(${LIB_NAME} ${QTENTITY_TESTS_HDR} ${QTENTITY_TESTS_SRC} ${MOC_SOURCES})
target_link_libraries(${LIB_NAME} QtEntity QtEntityUtils)
add_test(NAME ${LIB_NAME} COMMAND ${LIB_NAME} )
qt5_use_modules(${LIB_NAME} Test Script)

#execute unit tests after each compile
#add_custom_command(TARGET QtEntity POST_BUILD COMMAND ${LIB_NAME})
