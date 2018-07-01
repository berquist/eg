set(SRC
    consumer.cpp
    class_template_header.cpp
    main.cpp
    )

add_executable(class_template_header.x ${SRC})
target_link_libraries(class_template_header.x ${ARMADILLO_LIBRARIES})
