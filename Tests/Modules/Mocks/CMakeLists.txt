set(HEADERS
    GameMock.h
    WindowMock.h
    ClockMock.h
    StateMachineMock.h
    StateMock.h
    EngineContextMock.h
    GraphicsConfigMock.h)

add_library(Mocks ${HEADERS})
set_target_properties(Mocks PROPERTIES LINKER_LANGUAGE CXX)