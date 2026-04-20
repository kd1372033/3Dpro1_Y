#include "GameScene.h"

void GameScene::PreUpdate()
{
	KdDebugGUI::Instance().AddLog("PreUpdate()");
}

void GameScene::Update()
{
	KdDebugGUI::Instance().AddLog("Update()");
}

void GameScene::Draw()
{
	KdDebugGUI::Instance().AddLog("Draw()");
}

void GameScene::Init()
{
	KdDebugGUI::Instance().AddLog("Init()");
}

void GameScene::Release()
{
	KdDebugGUI::Instance().AddLog("Release()");
}
