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
}

void PlayScene::clean()
{
	removeAllChildren();
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

	// Setup the Grid
	m_buildGrid();
	auto offset = glm::vec2(Config::TILE_SIZE * 0.5f, Config::TILE_SIZE * 0.5f);
	
	// Add Target to Scene
	m_pTarget = new Target();
	//m_pTarget->getTransform()->position = m_getTile(15, 11)->getTransform()->position + offset; // position in world space matches grid space
	//m_pTarget->setGridPosition(15, 11);
	//m_getTile(15, 11)->setTileStatus(GOAL);
	m_spawnTarget();
	addChild(m_pTarget);

	// Add StarShip to Scene
	m_pStarShip = new StarShip();
	//m_pStarShip->getTransform()->position = m_getTile(1, 3)->getTransform()->position + offset; // position in world space matches grid space
	//m_pStarShip->setGridPosition(1, 3);
	//m_getTile(1, 3)->setTileStatus(START);
	m_spawnStarShip();
	addChild(m_pStarShip);

	m_computeTileCosts();

	m_buildMines();
	m_spawnMines();

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
	
	ImGui::Begin("GAME3001 - M2021 - Lab 6", nullptr, ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_MenuBar);

	if(ImGui::Checkbox("Toggle Grid", &m_bToggleGrid))
	{
		// toggle grid on/off
		m_setGridEnabled(m_bToggleGrid);
	}

	ImGui::Separator();

	static int start_position[2] = { m_pStarShip->getGridPosition().x, m_pStarShip->getGridPosition().y };
	if(ImGui::SliderInt2("Start Position", start_position, 0, Config::COL_NUM - 1))
	{
		if(start_position[1] > Config::ROW_NUM - 1)
		{
			start_position[1] = Config::ROW_NUM - 1;
		}

		m_getTile(m_pStarShip->getGridPosition())->setTileStatus(UNVISITED);
		m_pStarShip->getTransform()->position = m_getTile(start_position[0], start_position[1])->getTransform()->position + offset;
		m_pStarShip->setGridPosition(start_position[0], start_position[1]);
		m_getTile(m_pStarShip->getGridPosition())->setTileStatus(START);

		m_resetGrid();

		m_spawnMines();
	}

	ImGui::Separator();
	
	static int goal_position[2] = { m_pTarget->getGridPosition().x, m_pTarget->getGridPosition().y};
	if(ImGui::SliderInt2("Goal Position", goal_position, 0, Config::COL_NUM - 1))
	{
		if (goal_position[1] > Config::ROW_NUM - 1)
		{
			goal_position[1] = Config::ROW_NUM - 1;
		}

		m_getTile(m_pTarget->getGridPosition())->setTileStatus(UNVISITED);
		m_pTarget->getTransform()->position = m_getTile(goal_position[0], goal_position[1])->getTransform()->position + offset;
		m_pTarget->setGridPosition(goal_position[0], goal_position[1]);
		m_getTile(m_pTarget->getGridPosition())->setTileStatus(GOAL);

		m_resetGrid();
		
		m_computeTileCosts();

		m_spawnMines();
	}

	ImGui::Separator();

	if (ImGui::Button("Find Shortest Path"))
	{
		m_findShortestPath();
	}

	

	ImGui::Separator();

	if (ImGui::Button("Reset"))
	{
		m_resetGrid();
	}

	
	ImGui::End();
}

void PlayScene::m_buildMines()
{
	for (int index = 0; index < m_mineNum; ++index)
	{
		auto mine = new Mine();
		addChild(mine);
		m_pMines.push_back(mine);
		mine = nullptr;
	}
}

void PlayScene::m_eraseMines()
{
	for (auto mine : m_pMines)
	{
		removeChild(mine);
		delete mine;
		mine = nullptr;
	}

	m_pMines.clear();
	m_pMines.resize(0);
	m_pMines.shrink_to_fit();
}

void PlayScene::m_spawnMines()
{
	for (int index = 0; index < m_mineNum; ++index)
	{
		m_spawnObject(m_pMines[index]);
		m_getTile(m_pMines[index]->getGridPosition())->setTileStatus(IMPASSABLE);
	}
}

void PlayScene::m_buildGrid()
{
	auto tileSize = Config::TILE_SIZE; // alias for Tile size

	// add tiles to the grid
	for (int row = 0; row < Config::ROW_NUM; ++row)
	{
		for (int col = 0; col < Config::COL_NUM; ++col)
		{
			Tile* tile = new Tile(); // create a new empty tile
			tile->getTransform()->position = glm::vec2(col * tileSize, row * tileSize); // world position
			tile->setGridPosition(col, row);
			addChild(tile);
			tile->addLabels();
			tile->setEnabled(false);
			m_pGrid.push_back(tile);
		}
	}

	// create references (connections) for each tile (node) to its neighbours (nodes)
	for (int row = 0; row < Config::ROW_NUM; ++row)
	{
		for (int col = 0; col < Config::COL_NUM; ++col)
		{
			Tile* tile = m_getTile(col, row);

			// TopMost Row?
			if(row == 0)
			{
				tile->setNeighbourTile(TOP_TILE, nullptr);
			}
			else
			{
				// setup Top Neighbour
				tile->setNeighbourTile(TOP_TILE, m_getTile(col, row - 1));
			}
			
			// RightMost Col?
			if (col == Config::COL_NUM - 1)
			{
				tile->setNeighbourTile(RIGHT_TILE, nullptr);
			}
			else
			{
				// setup Right Neighbour
				tile->setNeighbourTile(RIGHT_TILE, m_getTile(col + 1, row));
			}

			// BottomMost Row?
			if (row == Config::ROW_NUM - 1)
			{
				tile->setNeighbourTile(BOTTOM_TILE, nullptr);
			}
			else
			{
				// Setup the Bottom Neighbour
				tile->setNeighbourTile(BOTTOM_TILE, m_getTile(col, row + 1));
			}

			// LeftMost Col?
			if (col == 0)
			{
				tile->setNeighbourTile(LEFT_TILE, nullptr);
			}
			else
			{
				// Setup the Left Neighbour
				tile->setNeighbourTile(LEFT_TILE, m_getTile(col - 1, row));
			}
		}
	}
}

void PlayScene::m_computeTileCosts()
{
	float distance = 0.0f;
	float dx = 0.0f;
	float dy = 0.0f;

	float f = 0.0f;
	float g = 0.0f;
	float h = 0.0f;
	
	for (auto tile : m_pGrid)
	{
		// Distance function (Euclidean Distance)
		g = Util::distance(tile->getGridPosition(), m_pTarget->getGridPosition());

		// Heuristic Calculation (Manhattan Distance)
		dx = abs(tile->getGridPosition().x - m_pTarget->getGridPosition().x);
		dy = abs(tile->getGridPosition().y - m_pTarget->getGridPosition().y);
		h = dx + dy;

		// PathFinding function
		f = g + h;

		tile->setTileCost(f);
	}
}

void PlayScene::m_findShortestPath()
{
	if(m_pPathList.empty())
	{
		// Step 1 - Initialization & Add Start Position to the Open List
		auto start_tile = m_getTile(m_pStarShip->getGridPosition());
		start_tile->setTileStatus(OPEN);
		m_pOpenList.push_back(start_tile);

		bool goal_found = false;

		// Step 2 - Loop until the OpenList is empty or the Goal is found
		while(!m_pOpenList.empty() && !goal_found)
		{
			auto min = INFINITY;
			Tile* min_tile; // temp Tile pointer - initialized as nullptr
			int min_tile_index = 0;
			int count = 0; // count = the neighbour index

			// create a temporary neighbour list from the current tile
			std::vector<Tile* > neighbour_list;
			for (int index = 0; index < NUM_OF_NEIGHBOUR_TILES; ++index)
			{
				if((m_pOpenList[0]->getNeighbourTile(static_cast<NeighbourTile>(index)) != nullptr) && (m_pOpenList[0]->getNeighbourTile(static_cast<NeighbourTile>(index))->getTileStatus() != IMPASSABLE))
				{
					neighbour_list.push_back(m_pOpenList[0]->getNeighbourTile(static_cast<NeighbourTile>(index)));
				}
			}

			// for each neighbour tile pointer in the neighbour_list -> find the tile with the minimum tile cost and return it
			for (auto neighbour : neighbour_list)
			{
				if(neighbour != nullptr)
				{
					// if the neighbour we are exploring is not the goal
					if(neighbour->getTileStatus() != GOAL)
					{
						if(neighbour->getTileCost() < min)
						{
							min = neighbour->getTileCost();
							min_tile = neighbour;
							min_tile_index = count;
						}
						count++;
					}
					// else if it is the goal -> then exit
					else
					{
						min_tile = neighbour;
						m_pPathList.push_back(min_tile);
						goal_found = true;
						break;
					}
				}
			}

			// remove the reference of the current tile from the open list
			m_pPathList.push_back(m_pOpenList[0]);
			m_pOpenList.pop_back(); // empties the open list

			// add the min_tile to the open_list
			m_pOpenList.push_back(min_tile);
			min_tile->setTileStatus(OPEN);
			neighbour_list.erase(neighbour_list.begin() + min_tile_index);

			// push all remaining neighbours in the neighbour_list to the closed list
			for (auto neighbour : neighbour_list)
			{
				if(neighbour->getTileStatus() == UNVISITED)
				{
					neighbour->setTileStatus(CLOSED);
					m_pClosedList.push_back(neighbour);
				}
			}
			
		}
	}

	m_displayPathList();
}

void PlayScene::m_displayPathList()
{
	std::cout << "- New Path ---------------------------------------" << std::endl;
	
	for (auto node : m_pPathList)
	{
		std::cout << "(" << node->getGridPosition().x << ", " << node->getGridPosition().y << ")" << std::endl;
	}

	std::cout << "--------------------------------------------------" << std::endl;
	std::cout << "Path Length: " << m_pPathList.size() << std::endl;
	std::cout << "--------------------------------------------------\n" << std::endl;
}

int PlayScene::m_spawnObject(NavigationObject* object)
{
	auto offset = glm::vec2(Config::TILE_SIZE * 0.5f, Config::TILE_SIZE * 0.5f);

	Tile* random_tile = nullptr;
	int random_tile_index = 0;

	// search for a random UNVISITED tile
	do
	{
		random_tile_index = static_cast<int>(Util::RandomRange(0, m_pGrid.size() - 1));
		random_tile = m_pGrid[random_tile_index];
	}
	while (random_tile->getTileStatus() != UNVISITED); // keep looping  until a UNVISITED tile is found

	// if moving a tile that already exists then set it's previous position to UNVISITED
	m_getTile(object->getGridPosition())->setTileStatus(UNVISITED);

	// move the game object to the random tile in world space
	object->getTransform()->position = m_getTile(random_tile->getGridPosition())->getTransform()->position + offset;

	// set the gridPosition of the object to the randomTile grid position
	object->setGridPosition(random_tile->getGridPosition());

	return random_tile_index;
}

void PlayScene::m_spawnStarShip()
{
	m_spawnObject(m_pStarShip);
	m_getTile(m_pStarShip->getGridPosition())->setTileStatus(START);
	std::cout << "StarShip Spawn Position : (" << m_pStarShip->getGridPosition().x << ", " << m_pStarShip->getGridPosition().y << ")" << std::endl;
}

void PlayScene::m_spawnTarget()
{
	m_spawnObject(m_pTarget);
	m_getTile(m_pTarget->getGridPosition())->setTileStatus(GOAL);
	std::cout << "Target Spawn Position : (" << m_pTarget->getGridPosition().x << ", " << m_pTarget->getGridPosition().y << ")" << std::endl;
}

void PlayScene::m_setGridEnabled(const bool state)
{
	for (auto tile : m_pGrid)
	{
		tile->setEnabled(state);
		tile->setLabelsEnabled(state);
	}

	m_isGridEnabled = state;
	
}

bool PlayScene::m_getGridEnabled() const
{
	return m_isGridEnabled;
}

Tile* PlayScene::m_getTile(const int col, const int row)
{
	return m_pGrid[(row * Config::COL_NUM) + col];
}

Tile* PlayScene::m_getTile(glm::vec2 grid_position)
{
	const auto col = grid_position.x;
	const auto row = grid_position.y;
	
	return m_pGrid[(row * Config::COL_NUM) + col];
}

void PlayScene::m_resetGrid()
{
	for (auto tile : m_pOpenList)
	{
		tile->setTileStatus(UNVISITED);
	}

	for (auto tile : m_pClosedList)
	{
		tile->setTileStatus(UNVISITED);
	}

	for (auto tile : m_pPathList)
	{
		tile->setTileStatus(UNVISITED);
	}

	m_pOpenList.clear();
	m_pClosedList.clear();
	m_pPathList.clear();

	// reset the Start Tile
	m_getTile(m_pStarShip->getGridPosition())->setTileStatus(START);
	
	// reset the Goal Tile
	m_getTile(m_pTarget->getGridPosition())->setTileStatus(GOAL);
}
