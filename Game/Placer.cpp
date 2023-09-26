#include "stdafx.h"
#include "Placer.h"
#include "SoundMgr.h"

#include "ResourceLoader.h"

#include "MyGameObjectLayer.h"
#include "MyRenderTag.h"
#include "MyRenderOrder.h"

#include "Room1x1.h"
#include "Player.h"
#include "Door.h"
#include "Camerawork.h"

#include "BlackFly.h"
#include "RedFly.h"
#include "ClosedGaper.h"
#include "Muliboom.h"
#include "BabyMonster.h"
#include "BabyPlum.h"
#include "UnknownBoss.h"

#include "UIHealthBar.h"
#include "UIHeart.h"
#include "UICollectibles.h"

#include "BrownRock01.h"
#include "BrownRock02.h"
#include "BrownRock03.h"
#include "BrownBombRock.h"
#include "IronBlock.h"
#include "BlueRock.h"
#include "BlackBowl1.h"
#include "BlackBowl2.h"
#include "WhiteBowl.h"

#include "ItemBlueHeart.h"
#include "ItemBomb.h"
#include "ItemCoin.h"
#include "ItemKey.h"
#include "ItemRedHeart.h"

#include "NormalBox.h"
#include "GoldBox.h"
#include "ItemTable.h"

#include "EquipItemOnion.h"
#include "EquipItemMomSheels.h"
#include "EquipItemMartyr.h"
#include "EquipItemBrimston.h"
#include "EquipItemMomLipstick.h"
#include "EquipItemHeart.h"

Machine* Placer::g_machine = nullptr;

bool Placer::g_shouldReset = false;

void Placer::SetMachine(Machine* machine)
{
    g_machine = machine;
}

void Placer::Place()
{
    Release();
    SetPhysics();
    LoadResources();
    MakeObjects();

    CSoundMgr::Get_Instance()->PlayBGM(L"m_catacombs.ogg");
}

void Placer::Release()
{
    ResetPhysics();
    ReleaseResources();
    ReleaseObjects();

    CSoundMgr::Get_Instance()->StopAll();
}

void Placer::ResetPhysics()
{
    Physics2D::SetAllOffCollisionLayer();
}

void Placer::SetPhysics()
{
    Physics2D::SetCollisionLayer(GO_LAYER_DOOR, GO_LAYER_PLAYER, true);

    Physics2D::SetCollisionLayer(GO_LAYER_PLAYER, GO_LAYER_ENEMY, true);
    Physics2D::SetCollisionLayer(GO_LAYER_PLAYER, GO_LAYER_DAMAGABLE, true);
    Physics2D::SetCollisionLayer(GO_LAYER_PLAYER, GO_LAYER_OBJECT, true);
    Physics2D::SetCollisionLayer(GO_LAYER_PLAYER, GO_LAYER_GROUNDWALL, true);

    Physics2D::SetCollisionLayer(GO_LAYER_ENEMY, GO_LAYER_ENEMY, true);
    Physics2D::SetCollisionLayer(GO_LAYER_ENEMY, GO_LAYER_DAMAGABLE, true);
    Physics2D::SetCollisionLayer(GO_LAYER_ENEMY, GO_LAYER_OBJECT, true);
    Physics2D::SetCollisionLayer(GO_LAYER_ENEMY, GO_LAYER_GROUNDWALL, true);

    Physics2D::SetCollisionLayer(GO_LAYER_DAMAGABLE, GO_LAYER_OBJECT, true);
    Physics2D::SetCollisionLayer(GO_LAYER_DAMAGABLE, GO_LAYER_PROJ_WALL, true);

    Physics2D::SetCollisionLayer(GO_LAYER_PLAYER_TRIGGERZONE, GO_LAYER_PLAYER, true);

    Physics2D::SetCollisionLayer(GO_LAYER_ITEM, GO_LAYER_PLAYER, true);
    Physics2D::SetCollisionLayer(GO_LAYER_ITEM, GO_LAYER_OBJECT, true);
    Physics2D::SetCollisionLayer(GO_LAYER_ITEM, GO_LAYER_GROUNDWALL, true);
}

void Placer::ReleaseResources()
{
    ResourceLoader::Release();
}

void Placer::LoadResources()
{
    ResourceLoader::LoadRoomResources(TEXT("../Image/Backdrop/"), TEXT("0a_library"));
    ResourceLoader::LoadRoomResources(TEXT("../Image/Backdrop/"), TEXT("0b_shop"));
    ResourceLoader::LoadRoomResources(TEXT("../Image/Backdrop/"), TEXT("01_basement"));
    ResourceLoader::LoadRoomResources(TEXT("../Image/Backdrop/"), TEXT("02_cellar"));
    ResourceLoader::LoadRoomResources(TEXT("../Image/Backdrop/"), TEXT("11_chest"));
    ResourceLoader::LoadKeyResources(TEXT("../Image/Grid/"), TEXT("door_01_normaldoor"));
    ResourceLoader::LoadDoorResources(TEXT("../Image/Grid/"), TEXT("door_00_shopdoor"));
    ResourceLoader::LoadDoorResources(TEXT("../Image/Grid/"), TEXT("door_01_normaldoor"));
    ResourceLoader::LoadDoorResources(TEXT("../Image/Grid/"), TEXT("door_02_treasureroomdoor"));
    ResourceLoader::LoadDoorResources(TEXT("../Image/Grid/"), TEXT("door_10_bossroomdoor"));
    ResourceLoader::LoadDoorResources(TEXT("../Image/Grid/"), TEXT("door_12_cellardoor"));
    ResourceLoader::LoadDoorResources(TEXT("../Image/Grid/"), TEXT("door_13_librarydoor_0"));
    ResourceLoader::LoadPlayerResources(TEXT("../Image/Character/"), TEXT("character_001_isaac"));
    ResourceLoader::LoadTearResources();
    ResourceLoader::LoadBloodTearResources();
    ResourceLoader::LoadBrimstonPlayerResources();
    ResourceLoader::LoadBrimstonLaserResources();
    ResourceLoader::LoadShadowResources();
    ResourceLoader::LoadSmallFlyResources();
    ResourceLoader::LoadBombResources();
    ResourceLoader::LoadGaperHeadResources();
    ResourceLoader::LoadBloodPoofResources();
    ResourceLoader::LoadPoofResources();
    ResourceLoader::LoadObstacleResources();
    ResourceLoader::LoadMuliboomHeadResources();
    ResourceLoader::LoadBabyMonsterResources();
    ResourceLoader::LoadTargetResources();
    ResourceLoader::LoadUIResources();
    ResourceLoader::LoadBabyPlumBossResources();
    ResourceLoader::LoadBlueBabayBossResources();
    ResourceLoader::LoadItemBombResources();
    ResourceLoader::LoadItemKeyResources();
    ResourceLoader::LoadItemCoinResources();
    ResourceLoader::LoadItemHeartResources();
    ResourceLoader::LoadIsaacFontResources();
    ResourceLoader::LoadPoolResources();
    ResourceLoader::LoadItemResources();
    ResourceLoader::LoadStartRoomResources();
    ResourceLoader::LoadTestResources();
}

void Placer::ReleaseObjects()
{
    g_machine->DeleteAllGameObjectsAndComponent();
    g_machine->Reset();
}

void Placer::MakeObjects()
{
    // Init ==========================================================================================================================
    const static float floorWidth = 182;
    const static float floorHeight = 104;
    const static float cornerLength = 52;

    std::vector<Room1x1*> rooms;
    auto createRoom = [&](const int& ix, const int& iy, const TCHAR* bmpKey) -> Room1x1*
    {
        Room1x1* room = CompGenerate<Room1x1>();
        room->SetRoomLeftTop(Room::IndexToRoomLeftTopCoord(ix, iy));
        room->InitGenerateRoom(bmpKey);
        rooms.push_back(room);
        return room;
    };
    auto createBloodRoom = [&](const int& ix, const int& iy) -> Room1x1*
    {
        Room1x1* room = CompGenerate<Room1x1>();
        room->SetRoomLeftTop(Room::IndexToRoomLeftTopCoord(ix, iy));
        room->InitGenerateBloodRoom();
        rooms.push_back(room);
        return room;
    };

    //          0       1       2       3       4       5       6       7       8       9       10
    //  0
    //  1
    //  2
    //  3
    //  4                               boss1   11              gold5   gold4
    //  5                                       10      9       8       7
    //  6                                                               6
    //  7                                                               5       gold3
    //  8                                       gold1   2       3       4
    //  9                                               1               gold2
    // 10                                               start

    Room1x1* room_start = createRoom(5, 10, TEXT("01_basement"));
    Room1x1* room_1 = createRoom(5, 9, TEXT("01_basement"));
    Room1x1* room_2 = createRoom(5, 8, TEXT("01_basement"));
    Room1x1* room_gold1 = createRoom(4, 8, TEXT("0b_shop"));
    Room1x1* room_3 = createRoom(6, 8, TEXT("02_cellar"));
    Room1x1* room_4 = createRoom(7, 8, TEXT("02_cellar"));
    Room1x1* room_gold2 = createRoom(7, 9, TEXT("0b_shop"));
    Room1x1* room_5 = createRoom(7, 7, TEXT("02_cellar"));
    Room1x1* room_gold3 = createRoom(8, 7, TEXT("0b_shop"));
    Room1x1* room_6 = createRoom(7, 6, TEXT("0a_library"));
    Room1x1* room_7 = createRoom(7, 5, TEXT("0a_library"));
    Room1x1* room_gold4 = createRoom(7, 4, TEXT("0b_shop"));
    Room1x1* room_8 = createRoom(6, 5, TEXT("0a_library"));
    Room1x1* room_gold5 = createRoom(6, 4, TEXT("0b_shop"));
    Room1x1* room_9 = createRoom(5, 5, TEXT("01_basement"));
    Room1x1* room_10 = createRoom(4, 5, TEXT("01_basement"));
    Room1x1* room_11 = createRoom(4, 4, TEXT("01_basement"));
    Room1x1* room_boss1 = createBloodRoom(3, 4);

    room_start->InitGenerateDoor(0, TEXT("door_01_normaldoor"), 0, 0);
    room_1->InitGenerateDoor(0, TEXT("door_01_normaldoor"), 0, TEXT("door_01_normaldoor"));
    room_2->InitGenerateDoor(TEXT("door_02_treasureroomdoor"), 0, TEXT("door_01_normaldoor"), TEXT("door_01_normaldoor"));
    room_3->InitGenerateDoor(TEXT("door_12_cellardoor"), 0, TEXT("door_12_cellardoor"), 0);
    room_4->InitGenerateDoor(TEXT("door_12_cellardoor"), TEXT("door_12_cellardoor"), 0, TEXT("door_02_treasureroomdoor"));
    room_5->InitGenerateDoor(0, TEXT("door_12_cellardoor"), TEXT("door_02_treasureroomdoor"), TEXT("door_12_cellardoor"));
    room_6->InitGenerateDoor(0, TEXT("door_13_librarydoor_0"), 0, TEXT("door_13_librarydoor_0"));
    room_7->InitGenerateDoor(TEXT("door_13_librarydoor_0"), TEXT("door_02_treasureroomdoor"), 0, TEXT("door_13_librarydoor_0"));
    room_8->InitGenerateDoor(TEXT("door_13_librarydoor_0"), TEXT("door_02_treasureroomdoor"), TEXT("door_13_librarydoor_0"), 0);
    room_9->InitGenerateDoor(TEXT("door_01_normaldoor"), 0, TEXT("door_01_normaldoor"), 0);
    room_10->InitGenerateDoor(0, TEXT("door_01_normaldoor"), TEXT("door_01_normaldoor"), 0);
    room_11->InitGenerateDoor(TEXT("door_10_bossroomdoor"), 0, 0, TEXT("door_01_normaldoor"));
    room_gold1->InitGenerateDoor(0, 0, TEXT("door_02_treasureroomdoor"), 0);
    room_gold2->InitGenerateDoor(0, TEXT("door_02_treasureroomdoor"), 0, 0);
    room_gold3->InitGenerateDoor(TEXT("door_02_treasureroomdoor"), 0, 0, 0);
    room_gold4->InitGenerateDoor(0, 0, 0, TEXT("door_02_treasureroomdoor"));
    room_gold5->InitGenerateDoor(0, 0, 0, TEXT("door_02_treasureroomdoor"));
    room_boss1->InitGenerateDoor(0, 0, TEXT("door_10_bossroomdoor"), 0);

    room_start->topDoor()->Connect(room_1->bottomDoor());
    room_1->topDoor()->Connect(room_2->bottomDoor());
    room_2->leftDoor()->Connect(room_gold1->rightDoor());
    room_2->rightDoor()->Connect(room_3->leftDoor());
    room_3->rightDoor()->Connect(room_4->leftDoor());
    room_4->bottomDoor()->Connect(room_gold2->topDoor());
    room_4->topDoor()->Connect(room_5->bottomDoor());
    room_5->rightDoor()->Connect(room_gold3->leftDoor());
    room_5->topDoor()->Connect(room_6->bottomDoor());
    room_6->topDoor()->Connect(room_7->bottomDoor());
    room_7->topDoor()->Connect(room_gold4->bottomDoor());
    room_7->leftDoor()->Connect(room_8->rightDoor());
    room_8->topDoor()->Connect(room_gold5->bottomDoor());
    room_8->leftDoor()->Connect(room_9->rightDoor());
    room_9->leftDoor()->Connect(room_10->rightDoor());
    room_10->topDoor()->Connect(room_11->bottomDoor());
    room_11->leftDoor()->Connect(room_boss1->rightDoor());

    for (auto& r : rooms)
        r->RoomObjDisableWithTime(0);

    room_gold1->rightDoor()->Lock();
    room_gold3->leftDoor()->Lock();
    room_gold5->bottomDoor()->Lock();

    room_start->RoomObjEnable();
    room_start->SetDoorsUseState(true);
    room_start->SetDoorsOpen(true);

    CompGenerate<Player>(room_start->center());
    CompGenerate<UIHealthBar>();
    CompGenerate<UIHeart>();
    CompGenerate<UICollectibles>();

    Camera2D* camera = CompGenerate<Camera2D>();
    camera->setHorizontal(floorWidth * 2 + cornerLength * 2);
    camera->setVertical(floorHeight * 2 + cornerLength * 2);
    Camerawork* camwork = camera->gameObject()->AddComponent<Camerawork>();
    camwork->SetTarget(Player::instance()->transform());
    camwork->SetUseBorder(true);
    camwork->SetBorder(room_start->roomLeft(), room_start->roomTop(), room_start->roomRight(), room_start->roomBottom());
    // Init ==========================================================================================================================

    // room_start
    SpriteRenderer* mainControlGuide = CompGenerate<SpriteRenderer>(room_start->center(), room_start->transform());
    mainControlGuide->setSprite(SpriteManager::Find(TEXT("controls")));
    mainControlGuide->setRenderTag(RD_TAG_FLOOR_OVERLAY);
    mainControlGuide->setRenderOrder(-10000);

    room_start->AddObstacle(0, 0, CompGenerate<BlueRock>());
    room_start->AddObstacle(1, 0, CompGenerate<BrownRock01>());
    room_start->AddObstacle(0, 1, CompGenerate<BrownRock01>());

    room_start->AddObstacle(13, 0, CompGenerate<BlueRock>());
    room_start->AddObstacle(12, 0, CompGenerate<BrownRock01>());
    room_start->AddObstacle(13, 1, CompGenerate<BrownRock01>());

    room_start->AddObstacle(0, 7, CompGenerate<BrownRock01>());
    room_start->AddObstacle(0, 6, CompGenerate<BrownRock01>());
    room_start->AddObstacle(1, 7, CompGenerate<BrownRock01>());

    room_start->AddObstacle(13, 7, CompGenerate<BrownRock01>());
    room_start->AddObstacle(12, 7, CompGenerate<BrownRock01>());
    room_start->AddObstacle(13, 6, CompGenerate<BrownRock01>());

    //room_start->AddMonsterAtCenter(CompGenerate<UnknownBoss>());

    // room_1
    room_1->AddMonster(5, 3, CompGenerate<BlackFly>());
    room_1->AddMonster(8, 3, CompGenerate<BlackFly>());

    room_1->AddItem(5, 5, CompGenerate<ItemBomb>());
    room_1->AddItem(8, 5, CompGenerate<ItemBomb>());

    room_1->AddObstacle(5, 3, CompGenerate<BrownRock01>());
    room_1->AddObstacle(6, 3, CompGenerate<BlueRock>());
    room_1->AddObstacle(7, 3, CompGenerate<BrownRock02>());
    room_1->AddObstacle(8, 3, CompGenerate<BrownRock01>());
    room_1->AddObstacle(5, 4, CompGenerate<BrownRock01>());
    room_1->AddObstacle(6, 4, CompGenerate<BrownRock02>());
    room_1->AddObstacle(7, 4, CompGenerate<BrownRock03>());
    room_1->AddObstacle(8, 4, CompGenerate<BrownRock03>());

    // room_2
    room_2->AddMonster(0, 0, CompGenerate<RedFly>());
    room_2->AddMonster(13, 0, CompGenerate<RedFly>());
    room_2->AddMonster(0, 7, CompGenerate<RedFly>());
    room_2->AddMonster(13, 7, CompGenerate<RedFly>());

    room_2->AddItem(5, 5, CompGenerate<ItemRedHeart>());
    room_2->AddItem(8, 5, CompGenerate<ItemRedHeart>());

    room_2->AddObstacle(5, 3, CompGenerate<BrownRock01>());
    room_2->AddObstacle(6, 3, CompGenerate<BrownRock02>());
    room_2->AddObstacle(7, 3, CompGenerate<BrownRock03>());
    room_2->AddObstacle(8, 3, CompGenerate<BrownRock02>());
    room_2->AddObstacle(5, 4, CompGenerate<BrownRock03>());
    room_2->AddObstacle(6, 4, CompGenerate<BrownRock02>());
    room_2->AddObstacle(7, 4, CompGenerate<BrownRock01>());
    room_2->AddObstacle(8, 4, CompGenerate<BrownRock02>());

    // gold1
    ItemTable* heartTable = CompGenerate<ItemTable>();
    heartTable->SetEquipItem<EquipItemHeart>();
    room_gold1->AddEquipItemPlacerAtCenter(heartTable);

    // room_3
    room_3->AddMonster(7, 1, CompGenerate<ClosedGaper>());
    room_3->AddMonster(6, 6, CompGenerate<ClosedGaper>());

    room_3->AddEquipItemPlacerAtCenter(CompGenerate<NormalBox>());

    room_3->AddObstacle(8, 2, CompGenerate<BrownRock01>());
    room_3->AddObstacle(8, 5, CompGenerate<BrownRock01>());
    room_3->AddObstacle(5, 2, CompGenerate<BrownRock01>());
    room_3->AddObstacle(5, 5, CompGenerate<BrownRock01>());

    // room_4
    room_4->AddMonster(10, 0, CompGenerate<Muliboom>());
    room_4->AddMonster(10, 1, CompGenerate<Muliboom>());
    room_4->AddMonster(10, 6, CompGenerate<Muliboom>());
    room_4->AddMonster(10, 7, CompGenerate<Muliboom>());

    room_4->AddObstacle(4, 2, CompGenerate<BlackBowl1>());
    room_4->AddObstacle(4, 5, CompGenerate<BlackBowl2>());
    room_4->AddObstacle(9, 2, CompGenerate<BlackBowl1>());
    room_4->AddObstacle(9, 5, CompGenerate<BlackBowl2>());

    // gold2
    ItemTable* onionTable = CompGenerate<ItemTable>();
    onionTable->SetEquipItem<EquipItemOnion>();

    room_gold2->AddEquipItemPlacerAtCenter(onionTable);

    // room_5
    room_5->AddMonster(5, 2, CompGenerate<BabyMonster>());
    room_5->AddMonster(8, 2, CompGenerate<BabyMonster>());

    room_5->AddItemAtCenter(CompGenerate<ItemBlueHeart>());

    room_5->AddObstacle(4, 2, CompGenerate<BlackBowl1>());
    room_5->AddObstacle(4, 5, CompGenerate<BlackBowl2>());
    room_5->AddObstacle(9, 2, CompGenerate<BlackBowl1>());
    room_5->AddObstacle(9, 5, CompGenerate<BlackBowl2>());

    // gold3
    ItemTable* martyrTable = CompGenerate<ItemTable>();
    martyrTable->SetEquipItem<EquipItemMartyr>();
    room_gold3->AddEquipItemPlacerAtCenter(martyrTable);

    // room_6
    room_6->AddMonster(0, 0, CompGenerate<BlackFly>());
    room_6->AddMonster(1, 0, CompGenerate<RedFly>());
    room_6->AddMonster(12, 0, CompGenerate<RedFly>());
    room_6->AddMonster(13, 0, CompGenerate<BlackFly>());
    room_6->AddMonster(5, 3, CompGenerate<ClosedGaper>());
    room_6->AddMonster(8, 3, CompGenerate<ClosedGaper>());
    room_6->AddMonster(0, 0, CompGenerate<Muliboom>());
    room_6->AddMonster(13, 0, CompGenerate<Muliboom>());

    // room_7
    room_7->AddMonster(0, 0, CompGenerate<BlackFly>());
    room_7->AddMonster(1, 0, CompGenerate<RedFly>());
    room_7->AddMonster(2, 0, CompGenerate<RedFly>());
    room_7->AddMonster(11, 0, CompGenerate<RedFly>());
    room_7->AddMonster(12, 0, CompGenerate<RedFly>());
    room_7->AddMonster(13, 0, CompGenerate<BlackFly>());
    room_7->AddMonster(3, 3, CompGenerate<ClosedGaper>());
    room_7->AddMonster(4, 3, CompGenerate<ClosedGaper>());
    room_7->AddMonster(5, 3, CompGenerate<ClosedGaper>());
    room_7->AddMonster(8, 3, CompGenerate<ClosedGaper>());
    room_7->AddMonster(9, 3, CompGenerate<ClosedGaper>());
    room_7->AddMonster(10, 3, CompGenerate<ClosedGaper>());

    // gold4
    ItemTable* momSheelsTable = CompGenerate<ItemTable>();
    momSheelsTable->SetEquipItem<EquipItemMomSheels>();
    room_gold4->AddEquipItemPlacerAtCenter(momSheelsTable);

    // room_8
    room_8->AddMonster(0, 0, CompGenerate<BabyMonster>());
    room_8->AddMonster(0, 1, CompGenerate<BabyMonster>());
    room_8->AddMonster(0, 2, CompGenerate<BabyMonster>());
    room_8->AddMonster(0, 3, CompGenerate<BabyMonster>());
    room_8->AddMonster(0, 4, CompGenerate<BabyMonster>());
    room_8->AddMonster(0, 5, CompGenerate<BabyMonster>());
    room_8->AddMonster(0, 6, CompGenerate<BabyMonster>());
    room_8->AddMonster(0, 7, CompGenerate<BabyMonster>());
    
    room_8->AddItem(4, 3, CompGenerate<ItemKey>());
    room_8->AddItem(4, 4, CompGenerate<ItemKey>());
    room_8->AddItem(9, 3, CompGenerate<ItemKey>());
    room_8->AddItem(9, 4, CompGenerate<ItemKey>());

    room_8->AddObstacle(4, 2, CompGenerate<WhiteBowl>());
    room_8->AddObstacle(4, 5, CompGenerate<WhiteBowl>());
    room_8->AddObstacle(9, 2, CompGenerate<WhiteBowl>());
    room_8->AddObstacle(9, 5, CompGenerate<WhiteBowl>());
    room_8->AddObstacle(1, 1, CompGenerate<WhiteBowl>());
    room_8->AddObstacle(12, 1, CompGenerate<WhiteBowl>());
    room_8->AddObstacle(1, 6, CompGenerate<WhiteBowl>());
    room_8->AddObstacle(12, 6, CompGenerate<WhiteBowl>());
    room_8->AddObstacle(1, 3, CompGenerate<WhiteBowl>());
    room_8->AddObstacle(12, 3, CompGenerate<WhiteBowl>());

    room_8->AddObstacle(1, 3, CompGenerate<WhiteBowl>());
    room_8->AddObstacle(12, 3, CompGenerate<WhiteBowl>());
    room_8->AddObstacle(1, 4, CompGenerate<WhiteBowl>());
    room_8->AddObstacle(12, 4, CompGenerate<WhiteBowl>());

    // gold5
    ItemTable* momLipstickTable = CompGenerate<ItemTable>();
    momLipstickTable->SetEquipItem<EquipItemMomLipstick>();
    room_gold5->AddEquipItemPlacerAtCenter(momLipstickTable);

    // room_9
    ItemTable* brimstonItemTable = CompGenerate<ItemTable>();
    brimstonItemTable->SetEquipItem<EquipItemBrimston>();
    GoldBox* martyrGoldBox1 = CompGenerate<GoldBox>();
    martyrGoldBox1->SetEquipItem<EquipItemMartyr>();
    GoldBox* onionGoldBox1 = CompGenerate<GoldBox>();
    onionGoldBox1->SetEquipItem<EquipItemOnion>();
    room_9->AddEquipItemPlacer(5, 4, martyrGoldBox1);
    room_9->AddEquipItemPlacerAtCenter(brimstonItemTable);
    room_9->AddEquipItemPlacer(8, 4, onionGoldBox1);

    // room_10
    room_10->AddMonster(0, 0, CompGenerate<BabyMonster>());
    room_10->AddMonster(0, 1, CompGenerate<BabyMonster>());
    room_10->AddMonster(0, 2, CompGenerate<BabyMonster>());
    room_10->AddMonster(0, 3, CompGenerate<BabyMonster>());
    room_10->AddMonster(0, 4, CompGenerate<BabyMonster>());
    room_10->AddMonster(0, 5, CompGenerate<BabyMonster>());
    room_10->AddMonster(0, 6, CompGenerate<BabyMonster>());
    room_10->AddMonster(0, 7, CompGenerate<BabyMonster>());

    GoldBox* martyrGoldBox2 = CompGenerate<GoldBox>();
    martyrGoldBox2->SetEquipItem<EquipItemMartyr>();
    GoldBox* onionGoldBox2 = CompGenerate<GoldBox>();
    onionGoldBox2->SetEquipItem<EquipItemOnion>();
    room_10->AddEquipItemPlacer(5, 4, martyrGoldBox2);
    room_10->AddEquipItemPlacer(8, 4, onionGoldBox2);

    // room_11
    room_11->AddMonster(0, 0, CompGenerate<BlackFly>());
    room_11->AddMonster(1, 0, CompGenerate<RedFly>());
    room_11->AddMonster(2, 0, CompGenerate<RedFly>());
    room_11->AddMonster(11, 0, CompGenerate<RedFly>());
    room_11->AddMonster(12, 0, CompGenerate<RedFly>());
    room_11->AddMonster(13, 0, CompGenerate<BlackFly>());
    room_11->AddMonster(3, 3, CompGenerate<ClosedGaper>());
    room_11->AddMonster(4, 3, CompGenerate<ClosedGaper>());
    room_11->AddMonster(5, 3, CompGenerate<ClosedGaper>());
    room_11->AddMonster(8, 3, CompGenerate<ClosedGaper>());
    room_11->AddMonster(9, 3, CompGenerate<ClosedGaper>());
    room_11->AddMonster(10, 3, CompGenerate<ClosedGaper>());

    // boss1
    room_boss1->AddMonsterAtCenter(CompGenerate<BabyPlum>());

    /*
    auto createBlackFly = [&](const Vector2& p) -> BlackFly*
    {
        GameObject* flyObj = new GameObject(p);
        BlackFly* fly = flyObj->AddComponent<BlackFly>();
        return fly;
    };

    auto createRedFly = [&](const Vector2& p) -> RedFly*
    {
        GameObject* flyObj = new GameObject(p);
        RedFly* fly = flyObj->AddComponent<RedFly>();
        return fly;
    };

    auto createGaper = [&](const Vector2& p) -> ClosedGaper*
    {
        GameObject* closedGaper = new GameObject(p);
        ClosedGaper* gaper = closedGaper->AddComponent<ClosedGaper>();
        return gaper;
    };

    auto createObstacle = [&](const Vector2& p, int idx) -> RoomObstacle*
    {
        GameObject* obj = new GameObject(p);
        switch (idx)
        {
            case 1: return obj->AddComponent<BrownRock01>();
            case 2: return obj->AddComponent<BrownRock02>();
            case 3: return obj->AddComponent<BrownRock03>();
            case 4: return obj->AddComponent<BrownBombRock>();
            case 5: return obj->AddComponent<IronBlock>();
            default: return nullptr;
        }
    };

    auto createMuliboom = [&](const Vector2& p) -> Muliboom*
    {
        GameObject* muliboomObj = new GameObject(p);
        Muliboom* muliboom = muliboomObj->AddComponent<Muliboom>();
        return muliboom;
    };

    auto createBabyMonster = [&](const Vector2& p) -> BabyMonster*
    {
        GameObject* obj = new GameObject(p);
        BabyMonster* mon = obj->AddComponent<BabyMonster>();
        return mon;
    };

    GameObject* centerRoomObj = new GameObject();
    Room1x1* centerRoom = centerRoomObj->AddComponent<Room1x1>();
    centerRoom->InitGenerateRoom(TEXT("02_cellar"));
    centerRoom->InitGenerateDoor(TEXT("door_10_bossroomdoor"), TEXT("door_12_cellardoor"), TEXT("door_12_cellardoor"), TEXT("door_12_cellardoor"));
    centerRoom->SetRoomLeftTop(Room::IndexToRoomLeftTopCoord(0, 0));

    GameObject* rightRoomObj = new GameObject();
    Room1x1* rightRoom = rightRoomObj->AddComponent<Room1x1>();
    rightRoom->InitGenerateRoom(TEXT("01_basement"));
    rightRoom->InitGenerateDoor(TEXT("door_01_normaldoor"), 0, 0, 0);
    rightRoom->SetRoomLeftTop(Room::IndexToRoomLeftTopCoord(1, 0));

    GameObject* bottomRoomObj = new GameObject();
    Room1x1* bottomRoom = bottomRoomObj->AddComponent<Room1x1>();
    bottomRoom->InitGenerateRoom(TEXT("01_basement"));
    bottomRoom->InitGenerateDoor(0, TEXT("door_01_normaldoor"), 0, 0);
    bottomRoom->SetRoomLeftTop(Room::IndexToRoomLeftTopCoord(0, 1));

    GameObject* topRoomObj = new GameObject();
    Room1x1* topRoom = topRoomObj->AddComponent<Room1x1>();
    topRoom->InitGenerateRoom(TEXT("0a_library"));
    topRoom->InitGenerateDoor(0, 0, 0, TEXT("door_13_librarydoor_0"));
    topRoom->SetRoomLeftTop(Room::IndexToRoomLeftTopCoord(0, -1));

    GameObject* leftRoomObj = new GameObject();
    Room1x1* leftRoom = leftRoomObj->AddComponent<Room1x1>();
    leftRoom->InitGenerateRoom(TEXT("01_basement"));
    leftRoom->InitGenerateDoor(0, 0, TEXT("door_10_bossroomdoor"), 0);
    leftRoom->SetRoomLeftTop(Room::IndexToRoomLeftTopCoord(-1, 0));

    centerRoom->bottomDoor()->Connect(bottomRoom->topDoor());
    centerRoom->rightDoor()->Connect(rightRoom->leftDoor());
    centerRoom->leftDoor()->Connect(leftRoom->rightDoor());
    centerRoom->topDoor()->Connect(topRoom->bottomDoor());
    centerRoom->topDoor()->Lock();

    rightRoom->RoomObjDisableWithTime(0);
    bottomRoom->RoomObjDisableWithTime(0);
    leftRoom->RoomObjDisableWithTime(0);
    topRoom->RoomObjDisableWithTime(0);

    centerRoom->SetDoorsUseState(true);
    centerRoom->SetDoorsOpen(true);

    GameObject* playerObj = new GameObject(centerRoom->center());
    Player* player = playerObj->AddComponent<Player>();

    centerRoom->AddObstacle(3, 4, createObstacle({}, 1));
    centerRoom->AddObstacle(10, 4, createObstacle({}, 2));
    centerRoom->AddObstacle(5, 5, createObstacle({}, 3));
    centerRoom->AddObstacle(8, 5, createObstacle({}, 4));
    centerRoom->AddObstacle(7, 5, createObstacle({}, 5));

    GameObject* healthObj = new GameObject();
    UIHealthBar* hpBar = healthObj->AddComponent<UIHealthBar>();

    GameObject* heartObj = new GameObject();
    UIHeart* heartUI = heartObj->AddComponent<UIHeart>();

    GameObject* collectibleObj = new GameObject();
    UICollectibles* collectibleUI = collectibleObj->AddComponent<UICollectibles>();

    GameObject* babyPlumObj = new GameObject();
    BabyPlum* babyPlum = babyPlumObj->AddComponent<BabyPlum>();
    leftRoom->AddMonsterAtCenter(babyPlum);

    bottomRoom->AddMonster(12, 0, createRedFly({}));
    bottomRoom->AddMonster(13, 0, createRedFly({}));
    bottomRoom->AddMonster(0, 0, createBlackFly({}));
    bottomRoom->AddMonster(1, 0, createBlackFly({}));
    bottomRoom->AddMonster(0, 1, createGaper({}));
    bottomRoom->AddMonster(13, 1, createGaper({}));
    bottomRoom->AddObstacle(3, 4, createObstacle({}, 1));
    bottomRoom->AddObstacle(10, 4, createObstacle({}, 2));
    bottomRoom->AddObstacle(7, 5, createObstacle({}, 5));

    GoldBox* brimstonBox = CompGenerate<GoldBox>();
    brimstonBox->SetEquipItem<EquipItemBrimston>();
    bottomRoom->AddEquipItemPlacer(6, 1, brimstonBox);

    rightRoom->AddMonster(13, 0, createMuliboom({}));
    rightRoom->AddMonster(12, 0, createMuliboom({}));
    rightRoom->AddMonster(11, 0, createMuliboom({}));

    rightRoom->AddItem(0, 0, CompGenerate<ItemBlueHeart>());
    rightRoom->AddItem(1, 0, CompGenerate<ItemBomb>());
    rightRoom->AddItem(2, 0, CompGenerate<ItemCoin>());
    rightRoom->AddItem(3, 0, CompGenerate<ItemKey>());
    rightRoom->AddItem(4, 0, CompGenerate<ItemRedHeart>());

    rightRoom->AddEquipItemPlacer(0, 4, CompGenerate<NormalBox>());
    rightRoom->AddEquipItemPlacer(3, 4, CompGenerate<NormalBox>());
    rightRoom->AddEquipItemPlacer(6, 4, CompGenerate<NormalBox>());

    ItemTable* onionItemTable = CompGenerate<ItemTable>();
    onionItemTable->SetEquipItem<EquipItemOnion>();
    rightRoom->AddEquipItemPlacer(6, 1, onionItemTable);

    GoldBox* momsheelsGoldBox = CompGenerate<GoldBox>();
    momsheelsGoldBox->SetEquipItem<EquipItemMomSheels>();
    rightRoom->AddEquipItemPlacer(7, 1, momsheelsGoldBox);

    GoldBox* martyr1GoldBox = CompGenerate<GoldBox>();
    martyr1GoldBox->SetEquipItem<EquipItemMartyr>();
    rightRoom->AddEquipItemPlacer(8, 1, martyr1GoldBox);

    GoldBox* martyr2GoldBox = CompGenerate<GoldBox>();
    martyr2GoldBox->SetEquipItem<EquipItemMartyr>();
    rightRoom->AddEquipItemPlacer(9, 1, martyr2GoldBox);

    topRoom->AddMonster(0, 0, createBabyMonster({}));
    topRoom->AddMonster(13, 0, createBabyMonster({}));
    topRoom->AddMonster(0, 1, createBabyMonster({}));
    topRoom->AddMonster(13, 1, createBabyMonster({}));
    topRoom->AddMonster(0, 2, createBabyMonster({}));
    topRoom->AddMonster(13, 2, createBabyMonster({}));
    topRoom->AddObstacle(3, 2, createObstacle({}, 1));
    topRoom->AddObstacle(10, 2, createObstacle({}, 2));
    topRoom->AddObstacle(7, 2, createObstacle({}, 5));
    topRoom->AddObstacle(3, 4, createObstacle({}, 1));
    topRoom->AddObstacle(10, 4, createObstacle({}, 2));
    topRoom->AddObstacle(7, 4, createObstacle({}, 5));
    topRoom->AddObstacle(3, 6, createObstacle({}, 1));
    topRoom->AddObstacle(10, 6, createObstacle({}, 2));
    topRoom->AddObstacle(7, 6, createObstacle({}, 5));

    GameObject* cameraObject = new GameObject();
    cameraObject->transform()->setSize({ 1.0f, 1.0f });
    Camera2D* camera = cameraObject->AddComponent<Camera2D>();
    camera->setHorizontal(floorWidth * 2 + cornerLength * 2);
    camera->setVertical(floorHeight * 2 + cornerLength * 2);
    Camerawork* camwork = cameraObject->AddComponent<Camerawork>();
    camwork->SetTarget(playerObj->transform());
    camwork->SetUseBorder(true);
    camwork->SetBorder(centerRoom->roomLeft(), centerRoom->roomTop(), centerRoom->roomRight(), centerRoom->roomBottom());
    */
}
