/*
 * BinarySearchTree.h
 *  添加元素时需自己做判断元素是否合法
 *  Created on: 2020年1月29日
 *      Author: LuYonglei
 */

#ifndef SRC_BINARYSEARCHTREE_H_
#define SRC_BINARYSEARCHTREE_H_
#include <queue>

template<typename Element>
class BinarySearchTree {
public:

	BinarySearchTree(int (*cmp)(Element e1, Element e2)); //比较函数指针

	virtual ~BinarySearchTree();

	int size(); //元素的数量

	bool isEmpty(); //是否为空

	void clear() {
		//清空所有元素
		NODE *node = root_;
		root_ = nullptr;
		using namespace std;
		queue<NODE*> q;
		q.push(node);
		while (!q.empty()) {
			NODE *tmp = q.front();
			if (tmp->left != nullptr)
				q.push(tmp->left);
			if (tmp->right != nullptr)
				q.push(tmp->right);
			delete tmp;
			q.pop();
		}
	}

	void add(Element e) {
		//添加元素
		add(e, cmp_);
	}

	void remove(Element e) {
		//删除元素
		remove(Node(e, cmp_));
	}

	bool contains(Element e) {
		//是否包含某元素
		return Node(e, cmp_) != nullptr;
	}

	void preorderTraversal(bool (*visitor)(Element e)) {
		//前序遍历
		if (visitor == nullptr)
			return;
		bool stop = false; //停止标志，若stop为true，则停止遍历
		preorderTraversal(root_, stop, visitor);
	}

	void inorderTraversal(bool (*visitor)(Element e)) {
		//中序遍历
		if (visitor == nullptr)
			return;
		bool stop = false; //停止标志，若stop为true，则停止遍历
		inorderTraversal(root_, stop, visitor);
	}

	void postorderTraversal(bool (*visitor)(Element e)) {
		//后序遍历
		if (visitor == nullptr)
			return;
		bool stop = false; //停止标志，若stop为true，则停止遍历
		postorderTraversal(root_, stop, visitor);
	}

	void levelOrderTraversal(bool (*visitor)(Element e)) {
		//层序遍历，迭代实现
		if (visitor == nullptr)
			return;
		levelOrderTraversal(root_, visitor);
	}

	int height() {
		//树的高度
		return height(root_);
	}

	bool isComplete() {
		//判断是否是完全二叉树
		return isComplete(root_);
	}

private:

	int size_;

	typedef struct _Node {
		Element e;
		_Node *parent;
		_Node *left;
		_Node *right;
		_Node(Element e_, _Node *parent_) :
				e(e_), parent(parent_), left(nullptr), right(nullptr) {
			//节点构造函数
		}

		inline bool isLeaf() {
			return (left == nullptr && right == nullptr);
		}

		inline bool hasTwoChildren() {
			return (left != nullptr && right != nullptr);
		}

	} NODE;

	NODE *root_;

	int (*cmp_)(Element e1, Element e2); //为实现树的排序的个性化配置，私有成员保存一个比较函数指针

	NODE* Node(Element e, int (*cmp_)(Element e1, Element e2)) {
		//返回e元素所在的节点
		NODE *node = root_;
		while (node != nullptr) {
			int cmp = cmp_(e, node->e);
			if (cmp == 0) //找到了元素
				return node;
			if (cmp > 0) { //待寻找元素大于节点存储的元素
				node = node->right;
			} else { //待寻找元素小于节点存储的元素
				node = node->left;
			}
		}
		return nullptr;
	}

	NODE* predecessor(NODE *node) {
		//返回node的前驱节点
		if (node == nullptr)
			return nullptr;
		//前驱节点在左子树
		NODE *tmp = node->left;
		if (tmp != nullptr) {
			while (tmp->right != nullptr)
				tmp = tmp->right;
			return tmp;
		}
		//从父节点，祖父节点中寻找前驱节点
		while (node->parent != nullptr && node == node->parent->left) {
			node = node->parent;
		}
		return node->parent;
	}

	NODE* successor(NODE *node) {
		//返回node的后继节点
		if (node == nullptr)
			return nullptr;
		//后继节点在右子树
		NODE *tmp = node->right;
		if (tmp != nullptr) {
			while (tmp->left != nullptr)
				tmp = tmp->left;
			return tmp;
		}
		//从父节点，祖父节点中寻找后继节点
		while (node->parent != nullptr && node == node->parent->right) {
			node = node->parent;
		}
		return node->parent;
	}

	void add(Element e, int (*cmp_)(Element e1, Element e2)) {
		//当树为空时，添加的节点作为树的根节点
		if (root_ == nullptr) {
			root_ = new NODE(e, nullptr);
			size_++;
			return;
		}
		//当添加的节点不是第一个节点
		NODE *parent = root_;
		NODE *node = root_;
		int cmp = 0; //比较结果
		while (node != nullptr) {
			parent = node; //保存父节点
			cmp = cmp_(e, node->e); //由函数指针来比较
			if (cmp > 0) {
				node = node->right; //添加的元素大于节点中的元素
			} else if (cmp < 0) {
				node = node->left; //添加的元素小于节点中的元素
			} else {
				node->e = e; //相等时就覆盖
				return; //添加的元素等于节点中的元素,直接返回
			}
		}
		//判断要插入父节点的哪个位置
		NODE *newNode = new NODE(e, parent); //为新元素创建节点
		if (cmp > 0) {
			parent->right = newNode; //添加的元素大于节点中的元素
		} else {
			parent->left = newNode; //添加的元素小于节点中的元素
		}
		size_++;
	}

	void remove(NODE *node_) {
		//删除某一节点
		if (node_ == nullptr)
			return;
		size_--;
		//优先删除度为2的节点
		if (node_->hasTwoChildren()) {
			NODE *pre = successor(node_); //找到node_的后继节点
			node_->e = pre->e; //用后继节点的值覆盖度为2的节点的值
			//删除后继节点(后继节点的度只能为1或0)
			node_ = pre;
		}
		//此时node_的度必然为0或1
		NODE *replacement = node_->left != nullptr ? node_->left : node_->right;
		if (replacement != nullptr) {			//node_的度为1
			replacement->parent = node_->parent;
			if (node_->parent == nullptr)			//度为1的根节点
				root_ = replacement;
			else if (node_->parent->left == node_)
				node_->parent->left = replacement;
			else
				node_->parent->right = replacement;
			delete node_;
		} else if (node_->parent == nullptr) {			//node_是叶子节点，也是根节点
			root_ = nullptr;
			delete node_;
		} else {			//node_是叶子节点，但不是根节点
			if (node_->parent->left == node_)
				node_->parent->left = nullptr;
			else
				node_->parent->right = nullptr;
			delete node_;
		}
	}

	void preorderTraversal(NODE *node, bool &stop, bool (*visitor)(Element e)) {
		//递归实现前序遍历
		if (node == nullptr || stop == true)
			return;
		stop = visitor(node->e);
		preorderTraversal(node->left, stop, visitor);
		preorderTraversal(node->right, stop, visitor);
	}

	void inorderTraversal(NODE *node, bool &stop, bool (*visitor)(Element e)) {
		//递归实现中序遍历
		if (node == nullptr || stop == true)
			return;
		inorderTraversal(node->left, stop, visitor);
		if (stop == true)
			return;
		stop = visitor(node->e);
		inorderTraversal(node->right, stop, visitor);
	}

	void postorderTraversal(NODE *node, bool &stop,
			bool (*visitor)(Element e)) {
		//递归实现后序遍历
		if (node == nullptr || stop == true)
			return;
		postorderTraversal(node->left, stop, visitor);
		postorderTraversal(node->right, stop, visitor);
		if (stop == true)
			return;
		stop = visitor(node->e);
	}

	void levelOrderTraversal(NODE *node, bool (*visitor)(Element e)) {
		if (node == nullptr)
			return;
		using namespace std;
		queue<NODE*> q;
		q.push(node);
		while (!q.empty()) {
			NODE *node = q.front();
			if (visitor(node->e) == true)
				return;
			if (node->left != nullptr)
				q.push(node->left);
			if (node->right != nullptr)
				q.push(node->right);
			q.pop();
		}
	}

	int height(NODE *node) {
		//某一节点的高度
		if (node == nullptr)
			return 0;
		using namespace std;
		queue<NODE*> q;
		q.push(node);
		int height = 0;
		int levelSize = 1; //每一层起始的节点个数
		while (!q.empty()) {
			NODE *node = q.front();
			levelSize--;
			if (node->left != nullptr)
				q.push(node->left);
			if (node->right != nullptr)
				q.push(node->right);
			q.pop();
			if (levelSize == 0) {
				height++;
				levelSize = q.size();
			}
		}
		return height;
	}

	bool isComplete(NODE *node) {
		if (node == nullptr)
			return false;
		using namespace std;
		queue<NODE*> q;
		q.push(node);
		bool leaf = false; //判断接下来的节点是否为叶子节点
		while (!q.empty()) {
			NODE *node = q.front();
			if (leaf && !node->isLeaf()) //判断叶子节点
				return false;
			if (node->left != nullptr) {
				q.push(node->left);
			} else if (node->right != nullptr) { //node->left == nullptr && node->right != nullptr
				return false;
			}
			if (node->right != nullptr) {
				q.push(node->right);
			} else { //node->right==nullptr
				leaf = true;
			}
			q.pop();
		}
		return true;
	}

};

template<typename Element>
BinarySearchTree<Element>::BinarySearchTree(int (*cmp)(Element e1, Element e2)) :
		size_(0), root_(nullptr), cmp_(cmp) {
	//树的构造函数
}

template<typename Element>
BinarySearchTree<Element>::~BinarySearchTree() {
	// 析构函数
	clear();
}

template<typename Element>
inline int BinarySearchTree<Element>::size() {
	//返回元素个数
	return size_;
}

template<typename Element>
inline bool BinarySearchTree<Element>::isEmpty() {
	//判断是否为空树
	return size_ == 0;
}

#endif /* SRC_BINARYSEARCHTREE_H_ */

