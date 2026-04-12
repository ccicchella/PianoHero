project(SpartanHeroLib)

set(SOURCE_FILES ids.h
        MainFrame.h
        MainFrame.cpp
        pch.h
        SpartanHero.cpp
        SpartanHero.h
        SpartanHeroView.cpp
        SpartanHeroView.h
        Scoreboard.cpp
        Scoreboard.h
        Item.cpp
        Item.h
        Sound.cpp
        Sound.h
        Soundboard.cpp
        Soundboard.h
        Level.cpp
        Level.h
        PuckItem.cpp
        PuckItem.h
        PuckLongItem.cpp
        PuckLongItem.h
        StaticImage.cpp
        StaticImage.h
        ItemDeclaration.cpp
        ItemDeclaration.h
        SoundBoardDeclaration.cpp
        SoundBoardDeclaration.h
        MeterDeclaration.cpp
        MeterDeclaration.h
        PuckDeclaration.cpp
        PuckDeclaration.h
        Meter.cpp
        Meter.h
        Track.cpp
        Track.h
        Score.cpp
        Score.h
        ItemVisitor.cpp
        ItemVisitor.h
        AddPuck.cpp
        AddPuck.h
)


set(wxBUILD_PRECOMP OFF)
find_package(wxWidgets COMPONENTS core base xrc html xml REQUIRED)

include(${wxWidgets_USE_FILE})

add_library(${PROJECT_NAME} STATIC ${SOURCE_FILES})

target_link_libraries(${PROJECT_NAME} ${wxWidgets_LIBRARIES})

target_precompile_headers(${PROJECT_NAME} PRIVATE pch.h)

# Fetch miniaudio from GitHub
include(FetchContent)
FetchContent_Declare(
        miniaudio
        GIT_REPOSITORY https://github.com/mackron/miniaudio.git
        GIT_TAG 0.11.21
)

FetchContent_MakeAvailable(miniaudio)
include_directories(${miniaudio_SOURCE_DIR})

