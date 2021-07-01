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

static const int L = 0;
static const int R = 1;

BST::BST() : Tree(2) 
{
	root = NULL;
}

static TreeNode* findNode(TreeNode *node, int key) 
{
	if (node == NULL) 
    {
		return NULL;
	}
	if (key == node->key) 
    {
		return node;
	} 
    else if (key < node->key) 
    {
		return findNode(node->children[L], key);
	} 
    else 
    {
		return findNode(node->children[R], key);
	}
}

static TreeNode* findNodeByValue(TreeNode *node, int val) 
{
	if (node == NULL) 
    {
		return NULL;
	}

	if (val == node->val) 
    {
		return node;
	}

	TreeNode *l = findNodeByValue(node->children[L], val);
	if (l) 
    {
		return l;
	}

	TreeNode *r = findNodeByValue(node->children[R], val);
	if (r) 
    {
		return r;
	}
	return NULL;
}

TreeNode* BST::get_left(int key) 
{
	TreeNode *keyNode = findNodeByValue(root, key);
	if (keyNode == NULL) {
		return NULL;
	} 
    else 
    {
		return keyNode->children[L];
	}
}

TreeNode* BST::get_right(int key) 
{
	TreeNode *keyNode = findNodeByValue(root, key);
	if (keyNode == NULL) 
    {
		return NULL;
	} 
    else 
    {
		return keyNode->children[R];
	}
}

static void getLevels(TreeNode *node, int level, int height,
		map<int, vector<TreeNode*> > &levels, map<TreeNode*, int> &heights) 
{
	if (node == NULL) 
    {
		return;
	}

	queue<pair<TreeNode*, int> > q;
	q.push(pair<TreeNode*, int>(node, level));
	heights[node] = height;

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

		TreeNode *l = n->children[L];
		if (l) 
        {
			q.push(pair<TreeNode*, int>(l, lvl - 1));
			heights[l] = heights[n] + 1;
		}

		TreeNode *r = n->children[R];
		if (r) 
        {
			q.push(pair<TreeNode*, int>(r, lvl + 1));
			heights[r] = heights[n] + 1;
		}
	}
}

string BST::top_view() 
{
	map<int, vector<TreeNode*> > levels;
	map<TreeNode*, int> heights;
	getLevels(root, 0, 0, levels, heights);

	ostringstream oss;
	map<int, vector<TreeNode*> >::iterator it = levels.begin();
	while (it != levels.end()) 
    {
		vector<int> temp;
		for (size_t i = 0; i < it->second.size(); i++) 
        {
			if (i > 0 && heights[it->second[i]] != heights[it->second[i - 1]]) 
            {
				break;
			}
			temp.push_back(it->second[i]->key);
		}

		std::sort(temp.begin(), temp.end());

		for (size_t i = 0; i < temp.size(); i++) 
        {
			oss << temp[i];
			if (i < temp.size() - 1)
            {
				oss << " ";
			}
		}

		it++;

		if (it != levels.end())
        {
			oss << " ";
		}
	}

	return oss.str();
}

string BST::bottom_view() 
{
	map<int, vector<TreeNode*> > levels;
	map<TreeNode*, int> heights;
	getLevels(root, 0, 0, levels, heights);

	ostringstream oss;
	map<int, vector<TreeNode*> >::iterator it = levels.begin();
	while (it != levels.end()) 
    {
		vector<int> temp;

		for (int i = (int)it->second.size() - 1; i >= 0; i--) 
        {
			if (i < (int)it->second.size() - 1 && heights[it->second[i]] != heights[it->second[i + 1]]) 
            {
				break;
			}

			temp.push_back(it->second[i]->key);
		}

		std::sort(temp.begin(), temp.end());

		for (size_t i = 0; i < temp.size(); i++) 
        {
			oss << temp[i];
			if (i < temp.size() - 1) 
            {
				oss << " ";
			}
		}

		it++;

		if (it != levels.end()) 
        {
			oss << " ";
		}
	}

	return oss.str();
}

static void inorderList(TreeNode *node, vector<pair<int, int> > &list) 
{
	if (node == NULL) 
    {
		return;
	}

	if (node->children[L]) 
    {
		inorderList(node->children[L], list);
	}
	list.push_back(pair<int, int>(node->key, node->val));
	if (node->children[R]) 
    {
		inorderList(node->children[R], list);
	}
}

static void destroyNodeRecursive(TreeNode *node) 
{
	if (node != NULL) 
    {
		destroyNodeRecursive(node->children[L]);
		destroyNodeRecursive(node->children[R]);

		free(node->children);
		free(node);
	}
}

static TreeNode* newNode(int key, int val, TreeNode *left, TreeNode *right) 
{
	TreeNode *node = (TreeNode*) malloc(sizeof(TreeNode));
	node->num_children = 2;
	node->key = key;
	node->val = val;
	node->flag = false;
	node->children = (TreeNode**) malloc(
			sizeof(TreeNode*) * node->num_children);
	node->children[L] = left;
	node->children[R] = right;
	return node;
}

static TreeNode* rebalanceRecursiveBase(const vector<pair<int, int> > &A) 
{
	if (A.size() == 1) 
    {
		return newNode(A[0].first, A[0].second, NULL, NULL);
	}

	if (A.size() == 2) 
    {
		return newNode(A[1].first, A[1].second,newNode(A[0].first, A[0].second, NULL, NULL), NULL);
	}

	if (A.size() == 3) 
    {
		return newNode(A[1].first, A[1].second,
				newNode(A[0].first, A[0].second, NULL, NULL),
				newNode(A[2].first, A[2].second, NULL, NULL));
	}

	return NULL;
}

static vector<pair<int, int> > subVector(const vector<pair<int, int> > &A,int start, int end) 
{
	vector<pair<int, int> > sub;
	for (int i = start; i < end; i++) {
		sub.push_back(A[i]);
	}
	return sub;
}

static TreeNode* rebalanceRecursive(const vector<pair<int, int> > &A) 
{
	int n = A.size();
	if (n < 4) 
    {
		return rebalanceRecursiveBase(A);
	}

	int h = (int) floor(log(n) / log(2)) + 1;
	int n_left = pow(2, h - 1) - 1;

	TreeNode *left = rebalanceRecursive(subVector(A, 0, n_left));
	TreeNode *right = rebalanceRecursive(subVector(A, n_left + 1, A.size()));

	return newNode(A[n_left].first, A[n_left].second, left, right);
}

void BST::rebalance() 
{
	vector<pair<int, int> > list;
	inorderList(root, list);
	destroyNodeRecursive(root);

	root = rebalanceRecursive(list);
}

static TreeNode* newNode(int key, int val) 
{
	TreeNode *node = (TreeNode*) malloc(sizeof(TreeNode));
	node->num_children = 2;
	node->key = key;
	node->val = val;
	node->flag = false;
	node->children = (TreeNode**) malloc(sizeof(TreeNode*) * node->num_children);
	for (int i = 0; i < node->num_children; i++) 
    {
		node->children[i] = NULL;
	}
	return node;
}

static void destroyNode(TreeNode *node) 
{
	if (node != NULL) 
    {
		free(node->children);
		free(node);
	}
}

static TreeNode* insertRecursive(TreeNode *node, int key, int val) 
{
	if (node == NULL) 
    {
		node = newNode(key, val);
	} 
    else 
    {
		if (key < node->key) 
        {
			node->children[L] = insertRecursive(node->children[L], key, val);
		}
        else 
        {
			node->children[R] = insertRecursive(node->children[R], key, val);
		}
	}

	return node;
}

void BST::insert(int key, int val) 
{
	root = insertRecursive(root, val, key);
}

static TreeNode* deleteRecursive(TreeNode *node, int key) 
{
	if (node == NULL) 
    {
		return node;
	}

	if (key < node->key) 
    {
		node->children[L] = deleteRecursive(node->children[L], key);
		return node;
	} 
    else if (key > node->key) 
    {
		node->children[R] = deleteRecursive(node->children[R], key);
		return node;
	} 
    else 
    {
		if (!node->children[L] && !node->children[R]) 
        {
			destroyNode(node);
			return NULL;
		} 
        else if (!node->children[L] && node->children[R]) 
        {
			TreeNode *t = node->children[R];
			destroyNode(node);
			return t;
		}
        else if (node->children[L] && !node->children[R]) 
        {
			TreeNode *t = node->children[L];
			destroyNode(node);
			return t;
		} 
        else 
        {
			TreeNode *rightLeftMost = node->children[R];
			while (rightLeftMost->children[L]) 
            {
				rightLeftMost = rightLeftMost->children[L];
			}
			node->key = rightLeftMost->key;
			node->val = rightLeftMost->val;
			node->children[R] = deleteRecursive(node->children[R], node->key);
			return node;
		}
	}
}

void BST::del(int key) 
{
	TreeNode *node = findNodeByValue(root, key);
	while (node != NULL) 
    {
		root = deleteRecursive(root, node->key);
		node = findNodeByValue(root, key);
	}
}

static int maxValue(int a, int b)
{
	return a > b ? a : b;
}

static int getHeight(TreeNode *node) 
{
	if (node == NULL) 
    {
		return 0;
	}

	return maxValue(getHeight(node->children[L]), getHeight(node->children[R]))
			+ 1;
}

static void inorder(TreeNode *node) 
{
	if (node == NULL) 
    {
		return;
	}

	if (node->children[L]) 
    {
		inorder(node->children[L]);
	}
	cout << node->key << ", " << node->val << endl;
	if (node->children[R]) 
    {
		inorder(node->children[R]);
	}
}
void BST::solution(const char *input_path, const char *output_path) 
{
	ifstream input_file(input_path);
	ofstream output_file(output_path);
	if (!input_file.is_open() || !output_file.is_open()) 
    {
		return;
	}

	BST bst;

	string line;
	while (getline(input_file, line)) 
    {
		string type;
		istringstream is(line);
		is >> type;

		if (type == "c") 
        {
            continue;
		} 
        else if (type == "e") 
        {
            continue;
		} 
        else if (type == "i") 
        {
			int k, v;
			is >> k >> v;
			bst.insert(k, v);
		} 
        else if (type == "d") 
        {
			int k;
			is >> k;
			bst.del(k);
		} 
        else if (type == "t") 
        {
			output_file << bst.top_view() << endl;
		} 
        else if (type == "b") 
        {
			output_file << bst.bottom_view() << endl;
		} 
        else if (type == "r") 
        {
			bst.rebalance();
		} 
        else if (type == "h") 
        {
			output_file << getHeight(bst.root) << endl;
		}
	}

	input_file.close();
	output_file.close();
}