cmake_minimum_required(VERSION 3.23)
project(macos_madness LANGUAGES)
cmake_policy(VERSION 3.23)

# On modern macOS, a lot of libraries have these ".tbd" stubs
# (https://stackoverflow.com/a/55560213); if there is a linker problem, you
# need to do a lot of work to get around it.

option(BUILD_ICONV "Build our own iconv library instead of looking for one" OFF)
set(BUILD_ICONV_ANYWAY OFF)

if(BUILD_ICONV)
    message(STATUS "...Building iconv because requested...")
else(BUILD_ICONV)
    message(STATUS "...Trying to find existing iconv...")
    find_package(Iconv)
    if(Iconv_LIBRARY)
        message(STATUS "Iconv_LIBRARY: ${Iconv_LIBRARY}")
        if(APPLE)
            message(STATUS "...On a Mac, checking validity of Iconv_LIBRARY...")
            string(
                REGEX MATCH
                "libiconv\.tbd$"
                iconv_regex_match_result
                "${Iconv_LIBRARY}"
            )
            message(
                STATUS
                "iconv_regex_match_result: ${iconv_regex_match_result}"
            )
            if(iconv_regex_match_result)
                message(
                    STATUS
                    "...Building iconv because macOS returned an invalid one..."
                )
            endif(iconv_regex_match_result)
        endif(APPLE)
    else(Iconv_LIBRARY)
        message(STATUS "...Building iconv because find_package() failed...")
    endif(Iconv_LIBRARY)
endif(BUILD_ICONV)
