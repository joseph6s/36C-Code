#include <map>
#include <vector>
#include <queue>
#include <fstream>
#include <string>
#include <sstream>
#include <cstdlib>
#include <algorithm>
#include <cmath>
#include "datastructure.hpp"
using namespace std;

static int maxValue(int a, int b) 
{
	return a > b ? a : b;
}

Tree::Tree(int width) 
{
	this->max_width = width;
	root = NULL;
}

static TreeNode* newNode(int key, int val, int max_width) 
{
	TreeNode *node = (TreeNode*) malloc(sizeof(TreeNode));
	node->key = key;
	node->val = val;
	node->flag = false;

	node->num_children = 0;
	node->children = (TreeNode**) malloc(sizeof(TreeNode*) * max_width);
	for (int i = 0; i < node->num_children; i++) 
    {
		node->children[i] = NULL;
	}
	return node;
}

static int getHeight(TreeNode *node) 
{
	if (node == NULL) 
    {
		return 0;
	}

	int m = 0;
	for (int i = 0; i < node->num_children; i++) 
    {
		m = maxValue(getHeight(node->children[i]), m);
	}
	return m + 1;
}

int Tree::get_height() 
{
	return getHeight(root);
}

static void getLevels(TreeNode *node, map<int, vector<TreeNode*> > &levels) 
{
	if (node == NULL) 
    {
		return;
	}

	queue<pair<TreeNode*, int> > q;
	q.push(pair<TreeNode*, int>(node, 0));

	while (!q.empty()) 
    {
		pair<TreeNode*, int> now = q.front();
		q.pop();

		TreeNode *n = now.first;
		int lvl = now.second;

		if (levels.find(lvl) == levels.end()) 
        {
			vector<TreeNode*> v;
			v.push_back(n);
			levels[lvl] = v;
		} 
        else 
        {
			levels[lvl].push_back(n);
		}

		for (int i = 0; i < n->num_children; i++) 
        {
			TreeNode *l = n->children[i];
			q.push(pair<TreeNode*, int>(l, lvl + 1));
		}
	}
}

string Tree::left_view() 
{
	map<int, vector<TreeNode*> > levels;
	getLevels(root, levels);

	ostringstream oss;
	map<int, vector<TreeNode*> >::iterator it = levels.begin();
	while (it != levels.end()) 
    {
		oss << it->second[0]->key;

		it++;
		if (it != levels.end()) 
        {
			oss << " ";
		}
	}

	return oss.str();
}

string Tree::right_view() 
{
	map<int, vector<TreeNode*> > levels;
	getLevels(root, levels);

	ostringstream oss;
	map<int, vector<TreeNode*> >::iterator it = levels.begin();
	while (it != levels.end()) 
    {
		oss << it->second[it->second.size() - 1]->key;

		it++;
		if (it != levels.end()) 
        {
			oss << " ";
		}
	}

	return oss.str();
}

static TreeNode* insertRecursive(TreeNode *node, int key, int val, int max_width) 
{
	if (node == NULL) 
	{
		node = newNode(key, val, max_width);
	} 
	else 
	{
		queue<TreeNode*> q;
		q.push(node);

		while (!q.empty()) 
		{
			TreeNode *n = q.front();
			q.pop();

			if (n->num_children < max_width) 
			{
				n->children[n->num_children] = newNode(key, val, max_width);
				n->num_children++;
				break;
			}

			for (int i = 0; i < n->num_children; i++) 
			{
				q.push(n->children[i]);
			}
		}
	}

	return node;
}

void Tree::insert_node(int key, int val) 
{
	root = insertRecursive(root, key, val, this->max_width);
}

static void destroyNodeRecursive(TreeNode *node) 
{
	if (node != NULL) 
    {
		for (int i = 0; i < node->num_children; i++) 
        {
			destroyNodeRecursive(node->children[i]);
		}

		free(node->children);
		free(node);
	}
}

static TreeNode* deleteRecursive(TreeNode *node, int val)
{
	if (node == NULL) 
	{
		return NULL;
	} 
	else 
	{
		if (node->val == val) 
		{
			return NULL;
		}

		for (int i = 0; i < node->num_children; i++) 
		{
			node->children[i] = deleteRecursive(node->children[i], val);
			if (node->children[i] == NULL) 
			{
				int move = 0;
				for (int j = i; j < node->num_children - 1; j++) 
				{
					node->children[j] = node->children[j + 1];
					move++;
				}
				node->num_children--;
				i--;
			}
		}
	}
	return node;
}

void Tree::delete_node(int val) 
{
	root = deleteRecursive(root, val);
}

static void inorder(TreeNode *node) 
{
	if (node == NULL) 
    {
		return;
	}

	cout << node->key << ", " << node->val << endl;

	for (int i = 0; i < node->num_children; i++) 
    {
		inorder(node->children[i]);
	}
}

void Tree::solution(const char *input_path, const char *output_path) 
{
	ifstream input_file(input_path);
	ofstream output_file(output_path);
	if (!input_file.is_open() || !output_file.is_open()) {
		return;
	}

	Tree *tree = NULL;

	string line;
	while (getline(input_file, line)) {
		string type;
		istringstream is(line);
		is >> type;

		if (type == "c") 
        {
            continue;
		} 
        else if (type == "t") 
        {
			int w;
			is >> w;
			tree = new Tree(w);
		} 
        else if (type == "i") 
        {
			int k, v;

			is >> k >> v;
			tree->insert_node(k, v);
		} 
        else if (type == "d") 
        {
			int v;
			is >> v;
			tree->delete_node(v);
		} 
        else if (type == "l") 
        {
			output_file << tree->left_view() << endl;
		} 
        else if (type == "r") 
        {
			output_file << tree->right_view() << endl;
		} 
        else if (type == "h") 
        {
			output_file << tree->get_height() << endl;
		}
	}

	input_file.close();
	output_file.close();
}
