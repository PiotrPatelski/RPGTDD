set(HEADERS
    GameMock.hpp
    WindowMock.hpp
    ClockMock.hpp
    StateMachineMock.hpp
    StateMock.hpp
    EngineMock.hpp
    CoreBuilderMock.hpp
    ButtonBuilderMock.hpp
    ButtonListBuilderMock.hpp
    ButtonMenuBuilderMock.hpp
    AssetsManagerMock.hpp
    GuiManagerMock.hpp
    GuiActionMock.hpp
    ConfigManagerMock.hpp
    UserInterfaceMock.hpp
    InputListenerMock.hpp
    KeyboardMapMock.hpp
    MouseEventListenerMock.hpp
    ButtonListMock.hpp
    TileMapManagerMock.hpp
    TileBuilderMock.hpp
    TileMock.hpp)

add_library(Mocks ${HEADERS})
set_target_properties(Mocks PROPERTIES LINKER_LANGUAGE CXX)