#include "DecisionTree.h"
#include <iostream>
#include "AttackAction.h"
#include "MoveToLOSAction.h"
#include "MoveToPlayerAction.h"
#include "PatrolAction.h"

DecisionTree::DecisionTree()
{
	m_buildTree();
}

DecisionTree::~DecisionTree()
= default;

Agent* DecisionTree::getAgent() const
{
	return m_agent;
}

LOSCondition* DecisionTree::getLOSNode() const
{
	return m_LOSNode;
}

RadiusCondition* DecisionTree::getRadiusNode() const
{
	return m_RadiusNode;
}

CloseCombatCondition* DecisionTree::getCloseCombatNode() const
{
	return m_CloseCombatNode;
}

void DecisionTree::setAgent(Agent* agent)
{
	m_agent = agent;
}

TreeNode* DecisionTree::AddNode(TreeNode* parent, TreeNode* child_node, const TreeNodeType type)
{
	switch (type)
	{
	case LEFT_TREE_NODE:
		parent->Left = child_node;
		break;
	case RIGHT_TREE_NODE:
		parent->Right = child_node;
		break;
	}
	child_node->Parent = parent;
	return child_node;
}

void DecisionTree::Display()
{
	for (auto* node : m_treeNodeList)
	{
		std::cout << node->name << std::endl;
	}
}

void DecisionTree::Update()
{
	// Do some checks here or in PlayScene...
}

void DecisionTree::clean()
{
	// Clear all the nodes.
	for (auto node : m_treeNodeList)
	{
		delete node;
		node = nullptr;
	}
	m_treeNodeList.clear();
	m_treeNodeList.shrink_to_fit();
	// Wrangle the remaining pointers. Optional.
	m_LOSNode = nullptr;
	m_RadiusNode = nullptr;
	m_CloseCombatNode = nullptr;
}

// in-order traversal
std::string DecisionTree::MakeDecision()
{
	auto currentNode = m_treeNodeList[0]; // Start at root node.
	while (!currentNode->isLeaf)
	{
		currentNode = (currentNode->data) ? (currentNode->Right) : (currentNode->Left);
		// currentNode = dynamic_cast<ConditionNode*>(currentNode)->Condition() ? (currentNode->Right) : (currentNode->Left);
	}
	return currentNode->name; // Print out action's name.
	// return static_cast<ActionNode*>(currentNode)->Action();
}

void DecisionTree::m_buildTree()
{
	// Create and add root node.
	m_LOSNode = new LOSCondition();
	m_treeNodeList.push_back(m_LOSNode);

	m_RadiusNode = new RadiusCondition();
	AddNode(m_LOSNode, m_RadiusNode, LEFT_TREE_NODE);
	m_treeNodeList.push_back(m_RadiusNode);

	m_CloseCombatNode = new CloseCombatCondition();
	AddNode(m_LOSNode, m_CloseCombatNode, RIGHT_TREE_NODE);
	m_treeNodeList.push_back(m_CloseCombatNode);

	TreeNode* patrolNode = AddNode(m_RadiusNode, new PatrolAction(), LEFT_TREE_NODE);
	m_treeNodeList.push_back(patrolNode);

	TreeNode* moveToLOSNode = AddNode(m_RadiusNode, new MoveToLOSAction(), RIGHT_TREE_NODE);
	m_treeNodeList.push_back(moveToLOSNode);

	TreeNode* moveToPlayerNode = AddNode(m_CloseCombatNode, new MoveToPlayerAction(), LEFT_TREE_NODE);
	m_treeNodeList.push_back(moveToPlayerNode);

	TreeNode* attackNode = AddNode(m_CloseCombatNode, new AttackAction(), RIGHT_TREE_NODE);
	m_treeNodeList.push_back(attackNode);
}
