#include "PlayScene.h"
#include "Game.h"
#include "EventManager.h"

// required for IMGUI
#include "imgui.h"
#include "imgui_sdl.h"
#include "Renderer.h"
#include "Util.h"

PlayScene::PlayScene()
{
	PlayScene::start();
}

PlayScene::~PlayScene()
= default;

void PlayScene::draw()
{
	drawDisplayList();
	SDL_SetRenderDrawColor(Renderer::Instance().getRenderer(), 255, 255, 255, 255);
}

void PlayScene::update()
{
	updateDisplayList();
	m_CheckShipLOS(m_pTarget);

	/*m_CheckAgentLOS(m_pShip, m_pTarget);
	m_CheckPathNodeLOS();*/

	// Set three conditions of decision tree here.
	//decisionTree->getLOSNode()->setLOS(decisionTree->getAgent()->hasLOS()); // Or use m_pShip if you want to be lazy/wrong.
	//decisionTree->getRadiusNode()->setIsWithinRadius(
	//	Util::distance(m_pShip->getTransform()->position, m_pTarget->getTransform()->position) <= 400.0f);
	//decisionTree->getCloseCombatNode()->setIsWithinCombatRange(
	//	Util::distance(m_pShip->getTransform()->position, m_pTarget->getTransform()->position) <= 60.0f);
}

void PlayScene::clean()
{
	removeAllChildren();
	// Clean up DecisionTree because it's not a DisplayObject.
	decisionTree->clean();
	delete decisionTree; 
}

void PlayScene::handleEvents()
{
	EventManager::Instance().update();

	if (EventManager::Instance().isKeyDown(SDL_SCANCODE_ESCAPE))
	{
		TheGame::Instance().quit();
	}
}

void PlayScene::start()
{
	// Set GUI Title
	m_guiTitle = "Play Scene";

	m_buildGrid();

	// add the ship to the scene as a start point
	m_pShip = new Ship();
	m_pShip->getTransform()->position = glm::vec2(150.f, 300.f);
	addChild(m_pShip, 3);

	// add the Obstacle to the scene as a start point
	m_pObstacle1 = new Obstacle();
	m_pObstacle1->getTransform()->position = glm::vec2(380.f, 280.f);
	addChild(m_pObstacle1);

	// add the Obstacle to the scene as a start point
	m_pObstacle2 = new Obstacle();
	m_pObstacle2->getTransform()->position = glm::vec2(380.f, 80.f);
	addChild(m_pObstacle2);

	// add the Obstacle to the scene as a start point
	m_pObstacle3 = new Obstacle();
	m_pObstacle3->getTransform()->position = glm::vec2(380.f, 480.f);
	addChild(m_pObstacle3);

	// added the target to the scene a goal
	m_pTarget = new Target();
	m_pTarget->getTransform()->position = glm::vec2(600.f, 300.f);
	addChild(m_pTarget);

	// Create test tree
	decisionTree = new DecisionTree();
	decisionTree->setAgent(m_pShip);
	decisionTree->Display(); // Optional.

	/*std::cout << "------------------------" << std::endl;
	std::cout << decisionTree->MakeDecision() << std::endl;
	std::cout << "------------------------\n" << std::endl;*/

	ImGuiWindowFrame::Instance().setGUIFunction(std::bind(&PlayScene::GUI_Function, this));
}

void PlayScene::GUI_Function()
{
	// TODO:
	// Toggle Visibility for the StarShip and the Target
		
	auto offset = glm::vec2(Config::TILE_SIZE * 0.5f, Config::TILE_SIZE * 0.5f);
	
	// Always open with a NewFrame
	ImGui::NewFrame();

	// See examples by uncommenting the following - also look at imgui_demo.cpp in the IMGUI filter
	//ImGui::ShowDemoWindow();
	
	ImGui::Begin("GAME3001 - M2021 - Lab 9", nullptr, ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_MenuBar);

	static bool gridVisible = true;
	if (ImGui::Checkbox("Toggle Grid", &gridVisible))
	{
		m_toggleGrid(gridVisible);
	}

	ImGui::Separator();

	// allow ship rotation
	static int angle;
	if (ImGui::SliderInt("Ship Direction", &angle, -360, 360))
	{
		m_pShip->setCurrentHeading(angle);

		/*std::cout << "------------------------" << std::endl;
		std::cout << decisionTree->MakeDecision() << std::endl;
		std::cout << "------------------------\n" << std::endl;*/
	}

	ImGui::Separator();

	static int shipPosition[] = { m_pShip->getTransform()->position.x, m_pShip->getTransform()->position.y };
	if (ImGui::SliderInt2("Ship Position", shipPosition, 0, 800))
	{
		m_pShip->getTransform()->position.x = shipPosition[0];
		m_pShip->getTransform()->position.y = shipPosition[1];

		/*std::cout << "------------------------" << std::endl;
		std::cout << decisionTree->MakeDecision() << std::endl;
		std::cout << "------------------------\n" << std::endl;*/
	}

	static int targetPosition[] = { m_pTarget->getTransform()->position.x, m_pTarget->getTransform()->position.y };
	if (ImGui::SliderInt2("Target Position", targetPosition, 0, 800))
	{
		m_pTarget->getTransform()->position.x = targetPosition[0];
		m_pTarget->getTransform()->position.y = targetPosition[1];

		/*std::cout << "------------------------" << std::endl;
		std::cout << decisionTree->MakeDecision() << std::endl;
		std::cout << "------------------------\n" << std::endl;*/
	}

	ImGui::Separator();
	
	ImGui::End();
}

void PlayScene::m_buildGrid()
{
	auto tileSize = Config::TILE_SIZE;

	// add path_nodes to the Grid
	for (int row = 0; row < Config::ROW_NUM; ++row)
	{
		for (int col = 0; col < Config::COL_NUM; ++col)
		{
			PathNode* path_node = new PathNode();
			path_node->getTransform()->position = glm::vec2(
				(col * tileSize) + tileSize * 0.5f, (row * tileSize) + tileSize * 0.5f);
			addChild(path_node);
			m_pGrid.push_back(path_node);
		}
	}
}

void PlayScene::m_toggleGrid(bool state)
{
	for (auto path_node : m_pGrid)
	{
		path_node->setVisible(state);
	}
}

void PlayScene::m_CheckShipLOS(DisplayObject* target_object)
{
	m_pShip->setHasLOS(false);
	// if ship to target distance is less than or equal to LOS Distance
	auto ShipToTargetDistance = Util::getClosestEdge(m_pShip->getTransform()->position, target_object );
	if (ShipToTargetDistance <= m_pShip->getLOSDistance())
	{
		std::vector<DisplayObject*> contactList;
		for (auto object : getDisplayList())
		{
			if ((object->getType() != m_pShip->getType()) && (object->getType() != target_object->getType()))
			{
				// check if object is farther than than the target
				auto ShipToObjectDistance = Util::getClosestEdge(m_pShip->getTransform()->position, object);
				if (ShipToObjectDistance <= ShipToTargetDistance)
					contactList.push_back(object);
			}
		}
		auto hasLOS = CollisionManager::LOSCheck(m_pShip->getTransform()->position,
			m_pShip->getTransform()->position + m_pShip->getCurrentDirection() * m_pShip->getLOSDistance(),
			contactList, target_object);
		m_pShip->setHasLOS(hasLOS);
	}
}

//void PlayScene::m_CheckPathNodeLOS()
//{
//
//}

//PathNode* PlayScene::m_findClosestPathNode(Agent* agent)
//{
//
//}