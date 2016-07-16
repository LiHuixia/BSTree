#pragma once
#include<iostream>
using namespace std;
template<class K, class V>
struct BSTNode
{
	K _key;
	V _value;
	BSTNode *_left;
	BSTNode *_right;
	BSTNode(const K &key, const V &value)
		:_key(key)
		, _value(value)
		, _left(NULL)
		, _right(NULL)
	{}
};

template<class K, class V>
class BSTree
{
	typedef BSTNode< K, V> Node;
public:
	BSTree()
	{
		_root = NULL;
	}
	~BSTree()
	{
		_Destoy(_root);
		_root = NULL;
	}
	bool Insert(const K& key, const V& value)
	{
		if (_root == NULL)
		{
			_root = new Node(key, value);
			return true;
		}
		Node* cur = _root;
		Node* parent = NULL;
		while (cur)
		{
			if (cur->_key > key)
			{
				parent = cur;
				cur = cur->_left;
			}
			else if (cur->_key < key)
			{
				parent = cur;
				cur = cur->_right;
			}
			else
				break;
		}
		if (parent->_key < key)
		{
			parent->_right = new Node(key, value);
		}
		else
		{
			parent->_left = new Node(key, value);
		}
		return true;
	}
	bool Insert_R(const K& key, const V& value);
	Node* Find(const K& key)
	{
		Node* cur = _root;
		while (cur)
		{
			if (cur->_key < key)
			{
				cur = cur->_right;
			}
			else if (cur->_key>key)
			{
				cur = cur->_left;
			}
			else
				return cur;
		}
		return NULL;
	}
	Node* Find_R(const K& key);
	bool Remove(const K& key)
	{
		if (_root == NULL)
		{
			return true;
		}
		Node* cur = _root;
		Node* parent = NULL;
		while (cur)
		{
			if (cur->_key < key)
			{
				parent = cur;
				cur = cur->_right;
			}
			else if (cur->_key > key)
			{
				parent = cur;
				cur = cur->_left;
			}
			else
				break;
		}
		if (cur == NULL)
			return false;
		Node* del;
		if (cur->_left == NULL)
		{
			del = cur;
			if (parent == NULL)
			{
				_root = cur->_right;
			}
			else
			{
				if (cur == parent->_left)
				{
					parent->_left = cur->_right;
				}
				else if (cur == parent->_right)
				{
					parent->_right = cur->_right;

				}
			}
			
		}
		else if (cur->_right == NULL)
		{
			del = cur;
			if (parent == NULL)
			{
				_root = cur->_left;
			}
			else
			{
				if (cur == parent->_left)
				{
					parent->_left = cur->_left;
				}
				else if (cur == parent->_right)
				{
					parent->_right = cur->_left;
				}
			}
			
		}
		//左右均不为空的情况
		else
		{
			parent = cur;
			Node* firstleft = cur->_right;
			while (firstleft->_left != NULL)
			{
				parent = firstleft;
				firstleft = firstleft->_left;
			}
			del = firstleft;
			cur->_value = firstleft->_value;
			cur->_key = firstleft->_key;
			if (parent->_left == firstleft)
			{
				parent->_left = firstleft->_right;
			}
			else
			{
				parent->_right = firstleft->_right;
			}
		}
		delete del;
		del = NULL;
	}
	bool Remove_R(const K& key);
	void InOrder()
	{
		_InOrder(_root);
	}
	
protected:
	void _Destoy(Node * root)
	{
		if (root == NULL)
			return;
		_Destoy(root->_left);
		_Destoy(root->_right);
		delete root;
	}
	void _InOrder(Node* root)
	{
		if (root == NULL)
			return;
		_InOrder(root->_left);
		cout << root->_key << ",";
		_InOrder(root->_right);
	}
protected:
	Node* _root;
};

void Test()
{
	int a[] = { 5, 3, 4, 1, 7, 8, 2, 6, 0, 9 };
	BSTree<int, int> b;
	for (int i = 0; i < (sizeof(a) / sizeof(a[0])); ++i)
	{
		b.Insert(a[i], i);
	}
	b.InOrder();
	cout << "("<<b.Find(5)->_key << "," << b.Find(5)->_value<<")"<< endl;
	cout << "(" << b.Find(7)->_key << "," << b.Find(7)->_value << ")" << endl;
	b.Remove(5);
	b.Remove(4);
	b.InOrder();
} 