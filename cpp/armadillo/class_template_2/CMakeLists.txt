set(SRC
    consumer.cpp
    class_template_2.cpp
    main.cpp
    )

add_executable(class_template_2.x ${SRC})
target_link_libraries(class_template_2.x ${ARMADILLO_LIBRARIES})
