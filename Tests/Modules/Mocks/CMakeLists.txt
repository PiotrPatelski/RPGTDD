set(HEADERS
    GameMock.h
    WindowMock.h
    ClockMock.h
    StateMachineMock.h
    StateMock.h
    EngineMock.h
    CoreBuilderMock.h
    AssetsManagerMock.h
    GuiManagerMock.hpp)

add_library(Mocks ${HEADERS})
set_target_properties(Mocks PROPERTIES LINKER_LANGUAGE CXX)