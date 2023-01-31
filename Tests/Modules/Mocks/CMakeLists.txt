set(HEADERS
    GameMock.hpp
    WindowMock.hpp
    ClockMock.hpp
    StateMachineMock.hpp
    StateMock.hpp
    EngineMock.hpp
    CoreBuilderMock.hpp
    ButtonBuilderMock.hpp
    AssetsManagerMock.hpp
    GuiManagerMock.hpp
    ConfigManagerMock.hpp
    UserInterfaceMock.hpp
    InputListenerMock.hpp
    KeyboardMapMock.hpp
    ButtonEventHandlerMock.hpp)

add_library(Mocks ${HEADERS})
set_target_properties(Mocks PROPERTIES LINKER_LANGUAGE CXX)