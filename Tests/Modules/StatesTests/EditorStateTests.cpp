#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <EditorState.hpp>
#include <ConfigManagerMock.hpp>
#include <IniParser.hpp>
#include <EditorGui.hpp>
#include "AssetsManagerMock.hpp"
#include "GuiManagerMock.hpp"
#include "WindowMock.hpp"
#include "ButtonMock.hpp"
#include "UserInterfaceMock.hpp"
#include "InputListenerMock.hpp"
#include "TileMapManagerMock.hpp"
#include "TileMapMock.hpp"
#include "TileMock.hpp"
#include "TileBuilderMock.hpp"

namespace States
{

using namespace ::testing;

struct EditorStateTest : public testing::Test
{
    EditorStateTest()
    {
        configManager = std::make_shared<NiceMock<FileMgmt::ConfigManagerMock>>();
        assetsManager = std::make_unique<NiceMock<FileMgmt::AssetsManagerMock>>();
        guiManager = std::make_unique<NiceMock<Gui::GuiManagerMock>>();
        tileMapManager = std::make_unique<NiceMock<Tiles::TileMapManagerMock>>();
        inputListener = std::make_unique<NiceMock<Events::InputListenerMock>>();
        tileMap = std::make_unique<NiceMock<Tiles::TileMapMock>>();
        tileBuilder = std::make_unique<NiceMock<Tiles::TileBuilderMock>>();
        ON_CALL(*assetsManager, getFont(_)).WillByDefault(ReturnRef(font));
        ON_CALL(*guiManager, createGui(_)).WillByDefault(Return(ByMove(std::make_unique<NiceMock<Gui::UserInterfaceMock>>())));
        ON_CALL(*tileMapManager, createTileMap()).WillByDefault(Return(ByMove(std::make_unique<NiceMock<Tiles::TileMapMock>>())));
        ON_CALL(*tileMapManager, createTileBuilder(_, _)).WillByDefault(Return(ByMove(std::make_unique<NiceMock<Tiles::TileBuilderMock>>())));
    }
    EditorState createSut()
    {
        return EditorState(
            configManager,
            std::move(assetsManager),
            std::move(guiManager),
            std::move(tileMapManager),
            std::move(inputListener));
    }
    std::shared_ptr<FileMgmt::ConfigManagerMock> configManager;
    std::unique_ptr<NiceMock<FileMgmt::AssetsManagerMock>> assetsManager;
    std::unique_ptr<NiceMock<Gui::GuiManagerMock>> guiManager;
    std::unique_ptr<NiceMock<Tiles::TileMapManagerMock>> tileMapManager;
    std::unique_ptr<NiceMock<Events::InputListenerMock>> inputListener;
    std::unique_ptr<NiceMock<Tiles::TileMapMock>> tileMap;
    std::unique_ptr<NiceMock<Tiles::TileBuilderMock>> tileBuilder;
    NiceMock<::Types::WindowMock> window;
    sf::Font font;
};

TEST_F(EditorStateTest, editorStateInitializesGuiWithManager)
{
    EXPECT_CALL(*guiManager, createGui(A<const sf::Font&>())).WillOnce
        (Return(ByMove(std::make_unique<NiceMock<Gui::UserInterfaceMock>>())));
    auto sut = createSut();
}

TEST_F(EditorStateTest, editorStateUpdatesCreatedGuiWithMousePosition)
{
    auto gui = std::make_unique<NiceMock<Gui::UserInterfaceMock>>();

    const float deltaTimme = 0.f;
    const sf::Vector2i mousePosition{30, 30};
    EXPECT_CALL(window, getMousePosition()).WillOnce(Return(mousePosition));
    EXPECT_CALL(*gui, update(Eq(mousePosition)));
    EXPECT_CALL(*guiManager, createGui(A<const sf::Font&>())).WillOnce
        (Return(ByMove(std::move(gui))));

    auto sut = createSut();
    sut.update(window, deltaTimme);
}

TEST_F(EditorStateTest, editorStateDrawsCreatedGuiWithWindow)
{
    auto gui = std::make_unique<NiceMock<Gui::UserInterfaceMock>>();

    EXPECT_CALL(*gui, drawTo(A<::Types::Window&>()));
    EXPECT_CALL(*guiManager, createGui(A<const sf::Font&>())).WillOnce
        (Return(ByMove(std::move(gui))));

    auto sut = createSut();
    sut.drawOutput(window);
}

TEST_F(EditorStateTest, editorStateCallsGuiWhenPaused)
{
    auto gui = std::make_unique<NiceMock<Gui::UserInterfaceMock>>();
    EXPECT_CALL(*gui, acceptRequest(A<Events::GuiAction&>()));
    EXPECT_CALL(*guiManager, createGui(A<const sf::Font&>())).WillOnce
        (Return(ByMove(std::move(gui))));

    auto sut = createSut();
    sut.togglePause();
}

TEST_F(EditorStateTest, editorStateCallsKeyActionReturnedByInputListener)
{
    MockFunction<void(States::MapState&)> callback;
    EXPECT_CALL(*inputListener, getKeyboardAction()).WillOnce(Return(
        std::make_optional<Events::StateAction>(callback.AsStdFunction())));
    EXPECT_CALL(callback, Call(A<States::MapState&>()));

    auto sut = createSut();
    sut.update(window, 0.f);
}

TEST_F(EditorStateTest, editorStateDoesNotCallMouseActionWhenPaused)
{
    const sf::Vector2i mousePosition{30, 30};
    EXPECT_CALL(window, getMousePosition()).WillOnce(Return(mousePosition));
    EXPECT_CALL(*inputListener, getMouseAction(Eq(mousePosition))).Times(0);

    auto sut = createSut();
    sut.togglePause();
    sut.update(window, 0.f);
}

TEST_F(EditorStateTest, editorStateCallsMouseActionReturnedByInputListenerWhenNotPaused)
{
    MockFunction<void(States::MapState&)> callback;
    const sf::Vector2i mousePosition{30, 30};
    EXPECT_CALL(window, getMousePosition()).WillOnce(Return(mousePosition));
    EXPECT_CALL(*inputListener, getMouseAction(Eq(mousePosition))).WillOnce(Return(
        std::make_optional<Events::StateAction>(callback.AsStdFunction())));
    EXPECT_CALL(callback, Call(A<States::MapState&>()));

    auto sut = createSut();
    sut.update(window, 0.f);
}

TEST_F(EditorStateTest, editorStateCallsActionReturnedByGui)
{
    MockFunction<void(States::MapState&)> callback;
    auto gui = std::make_unique<NiceMock<Gui::UserInterfaceMock>>();
    EXPECT_CALL(*gui, getActiveAction()).WillOnce(Return(
        std::make_optional<Events::StateAction>(callback.AsStdFunction())));
    EXPECT_CALL(*guiManager, createGui(A<const sf::Font&>())).WillOnce
        (Return(ByMove(std::move(gui))));
    EXPECT_CALL(callback, Call(A<States::MapState&>()));

    auto sut = createSut();
    sut.update(window, 0.f);
}

TEST_F(EditorStateTest, editorStateDoesNotUpdateTileMapWhenPaused)
{
    EXPECT_CALL(*tileMap, update()).Times(0);
    EXPECT_CALL(*tileMapManager, createTileMap()).WillOnce
        (Return(ByMove(std::move(tileMap))));

    auto sut = createSut();
    sut.togglePause();
    sut.update(window, 0.f);
}

TEST_F(EditorStateTest, editorStateUpdatesTileMapWhenNotPaused)
{
    EXPECT_CALL(*tileMap, update());
    EXPECT_CALL(*tileMapManager, createTileMap()).WillOnce
        (Return(ByMove(std::move(tileMap))));

    auto sut = createSut();
    sut.update(window, 0.f);
}

TEST_F(EditorStateTest, editorStateInitializesTileMapWithManager)
{
    EXPECT_CALL(*tileMapManager, createTileMap()).WillOnce
        (Return(ByMove(std::make_unique<NiceMock<Tiles::TileMapMock>>())));
    EXPECT_CALL(*tileMapManager, createTileBuilder(_, _)).WillOnce
        (Return(ByMove(std::make_unique<NiceMock<Tiles::TileBuilderMock>>())));

    auto sut = createSut();
}

TEST_F(EditorStateTest, editorStateDoesNotAddTileWhenGivenPositionIsInvalid)
{
    const sf::Vector2i targetTilePosition{21, 37};
    EXPECT_CALL(*tileMap, isValidPosition(Eq(targetTilePosition))).WillOnce(Return(false));
    EXPECT_CALL(*tileMap, isEmptyAt(_)).Times(0);
    EXPECT_CALL(*tileMap, addTile(_)).Times(0);
    EXPECT_CALL(*tileBuilder, atPosition(_)).Times(0);
    EXPECT_CALL(*tileBuilder, build(_)).Times(0);
    EXPECT_CALL(*tileMapManager, createTileMap()).WillOnce
        (Return(ByMove(std::move(tileMap))));
    EXPECT_CALL(*tileMapManager, createTileBuilder(_, _)).WillOnce
        (Return(ByMove(std::move(tileBuilder))));

    auto sut = createSut();
    sut.tryTileAdditionAt(targetTilePosition);
}

TEST_F(EditorStateTest, editorStateAddsTilesWithTileBuilderAtGivenPositionWhenThereWasNoTilePlacedHereYet)
{
    const sf::Vector2i targetTilePosition{21, 37};
    EXPECT_CALL(*tileMap, isValidPosition(Eq(targetTilePosition))).WillOnce(Return(true));
    EXPECT_CALL(*tileMap, addTile(A<std::unique_ptr<Tiles::Tile>>()));
    EXPECT_CALL(*tileBuilder, atPosition(Eq(targetTilePosition))).WillOnce(ReturnRef(*tileBuilder));
    EXPECT_CALL(*tileBuilder, build(_)).WillOnce(Return(ByMove(std::make_unique<NiceMock<Tiles::TileMock>>())));
    EXPECT_CALL(*tileMapManager, createTileMap()).WillOnce
        (Return(ByMove(std::move(tileMap))));
    EXPECT_CALL(*tileMapManager, createTileBuilder(_, _)).WillOnce
        (Return(ByMove(std::move(tileBuilder))));

    auto sut = createSut();
    sut.tryTileAdditionAt(targetTilePosition);
}

TEST_F(EditorStateTest, editorStateRemovesTilesAtGivenPositionWhenTileIsPresent)
{
    const sf::Vector2i targetTilePosition{21, 37};
    EXPECT_CALL(*tileMap, isValidPosition(Eq(targetTilePosition))).WillOnce(Return(true));
    EXPECT_CALL(*tileMap, isEmptyAt(Eq(targetTilePosition))).WillOnce(Return(false));
    EXPECT_CALL(*tileMap, removeTile(Eq(targetTilePosition)));
    EXPECT_CALL(*tileMapManager, createTileMap()).WillOnce
        (Return(ByMove(std::move(tileMap))));

    auto sut = createSut();
    sut.tryTileRemovalAt(targetTilePosition);
}

TEST_F(EditorStateTest, editorStateDoesNotRemoveAnyTileWhenNoTileIsPresent)
{
    const sf::Vector2i targetTilePosition{21, 37};
    EXPECT_CALL(*tileMap, isValidPosition(Eq(targetTilePosition))).WillOnce(Return(true));
    EXPECT_CALL(*tileMap, isEmptyAt(Eq(targetTilePosition))).WillOnce(Return(true));
    EXPECT_CALL(*tileMap, removeTile(_)).Times(0);
    EXPECT_CALL(*tileMapManager, createTileMap()).WillOnce
        (Return(ByMove(std::move(tileMap))));

    auto sut = createSut();
    sut.tryTileRemovalAt(targetTilePosition);
}

TEST_F(EditorStateTest, editorStateDoesNotRemoveAnyTileWhenPositionIsInvalid)
{
    const sf::Vector2i targetTilePosition{21, 37};
    EXPECT_CALL(*tileMap, isValidPosition(Eq(targetTilePosition))).WillOnce(Return(false));
    EXPECT_CALL(*tileMap, isEmptyAt(_)).Times(0);
    EXPECT_CALL(*tileMap, removeTile(_)).Times(0);
    EXPECT_CALL(*tileMapManager, createTileMap()).WillOnce
        (Return(ByMove(std::move(tileMap))));

    auto sut = createSut();
    sut.tryTileRemovalAt(targetTilePosition);
}

TEST_F(EditorStateTest, editorStateDrawsCreatedTileMapWithWindow)
{
    EXPECT_CALL(*tileMap, drawTo(A<::Types::Window&>()));
    EXPECT_CALL(*tileMapManager, createTileMap()).WillOnce
        (Return(ByMove(std::move(tileMap))));

    auto sut = createSut();
    sut.drawOutput(window);
}

}