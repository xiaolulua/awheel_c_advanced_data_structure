/*
 * BinarySearchTree.h
 *  添加元素时需自己做判断元素是否合法
 *  Created on: 2020年1月29日
 *      Author: LuYonglei
 */

#ifndef SRC_BINARYSEARCHTREE_H_
#define SRC_BINARYSEARCHTREE_H_
#include <queue>
#include <stack>

const bool RED = false;
const bool BLACK = true;

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
		preorderTraversal(root_, visitor);
	}

	void inorderTraversal(bool (*visitor)(Element e)) {
		//中序遍历
		inorderTraversal(root_, visitor);
	}

	void postorderTraversal(bool (*visitor)(Element e)) {
		//后序遍历
		postorderTraversal(root_, visitor);
	}

	void levelOrderTraversal(bool (*visitor)(Element e)) {
		//层序遍历，迭代实现
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
		bool color_;
		_Node(Element e_, _Node *parent_) :
				e(e_), parent(parent_), left(nullptr), right(nullptr), color_(
						RED) {
			//节点构造函数
		}

		inline bool isLeaf() {
			return (left == nullptr && right == nullptr);
		}

		inline bool hasTwoChildren() {
			return (left != nullptr && right != nullptr);
		}

		inline bool isLeftChild() {
			//判断节点是否是父亲节点的左子结点
			return parent != nullptr && parent->left == this;
		}

		inline bool isRightChild() {
			//判断节点是否是父亲节点的右子结点
			return parent != nullptr && parent->right == this;
		}

		inline _Node* sibling() {
			//返回兄弟节点
			if (this->parent != nullptr) {
				if (this->isLeftChild())
					return this->parent->right;
				else
					return this->parent->left;
			}
			return nullptr;
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

	bool colorOf(NODE *node) {
		//返回节点的颜色
		return node == nullptr ? BLACK : node->color_;
	}

	bool isBlack(NODE *node) {
		//node是否为黑色
		return node == nullptr ? true : node->color_ == BLACK;
	}

	bool isRed(NODE *node) {
		//node是否为红色
		return node == nullptr ? false : node->color_ == RED;
	}

	NODE* color(NODE *node, bool color) {
		//对节点染色
		if (node == nullptr)
			return node;
		node->color_ = color;
		return node;
	}

	NODE* red(NODE *node) {
		//把节点染成红色
		return color(node, RED);
	}

	NODE* black(NODE *node) {
		//把节点染成黑色
		return color(node, BLACK);
	}

	void afterRotate(NODE *gNode, NODE *pNode, NODE *child) {
		//在左旋转与右旋转中统一调用
		pNode->parent = gNode->parent;
		if (gNode->isLeftChild())
			gNode->parent->left = pNode;
		else if (gNode->isRightChild())
			gNode->parent->right = pNode;
		else
			//此时gNode->parent 为nullptr，gNode为root节点
			root_ = pNode;
		if (child != nullptr)
			child->parent = gNode;
		gNode->parent = pNode;

	}

	void rotateLeft(NODE *gNode) {
		//对gNode进行左旋转
		NODE *pNode = gNode->right;
		NODE *child = pNode->left;
		gNode->right = child;
		pNode->left = gNode;
		afterRotate(gNode, pNode, child);

	}

	void rotateRight(NODE *gNode) {
		//对gNode进行右旋转
		NODE *pNode = gNode->left;
		NODE *child = pNode->right;
		gNode->left = child;
		pNode->right = gNode;
		afterRotate(gNode, pNode, child);

	}

	void afterAdd(NODE *node) {
		while (true) {
			//添加node之后的操作
			NODE *parentNode = node->parent;
			//没有父节点时，新添加的节点是root_或者上溢到root_
			if (parentNode == nullptr) {
				black(node);
				return;
			}
			//1.当父亲节点为黑色节点时，不做任何处理,直接返回
			if (isBlack(parentNode))
				return;
			NODE *uncleNode = parentNode->sibling();
			NODE *grandNode = red(parentNode->parent);
			if (isRed(uncleNode)) {
				//2.uncle节点是红色,(上溢,只需要染色)
				black(parentNode);
				black(uncleNode);
				//祖父节点当作是新添加的节点
				node = grandNode;
				continue;
			}
			//3.uncle节点是黑色或者uncle节点为null
			if (parentNode->isLeftChild()) {
				if (node->isLeftChild()) {
					//LL
					black(parentNode);
				} else {
					//LR
					black(node);
					rotateLeft(parentNode);
				}
				rotateRight(grandNode);
				return;
			} else {
				if (node->isLeftChild()) {
					//RL
					black(node);
					rotateRight(parentNode);
				} else {
					//RR
					black(parentNode);
				}
				rotateLeft(grandNode);
				return;
			}
		}
	}

	void add(Element e, int (*cmp_)(Element e1, Element e2)) {
		//当树为空时，添加的节点作为树的根节点
		if (root_ == nullptr) {
			root_ = new NODE(e, nullptr);
			size_++;
			afterAdd(root_);
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
		afterAdd(newNode);
	}

	void afterRemove(NODE *node) {
		while (true) {
			//删除节点之后的操作
			//node是要被释放内存的节点或是是替代的节点
			//1.如果删除的是红色节点，直接删掉即可
			//此处代表删除的节点为红色叶子节点
			if (isRed(node)) {
				//2.如果删除的节点是黑色节点,且替代的节点为红色节点
				//此处代表删除的节点的度为1,且要删除的节点含有一个红色子节点
				black(node);
				return;
			}
			//3.如果删除的节点是黑色节点,且替代的节点为黑色节点(nullptr)
			//此处代表要删除的是黑色叶子节点或根节点
			NODE *parentNode = node->parent;
			//如果删除的是根节点
			if (parentNode == nullptr)
				return;

			//此时node为叶子节点
			//但想获得他的兄弟节点不能调用sibling()，因为在调用afterRemove()之前，若node为parent的left就已经将parent的left置为nullptr
			//若node为parent的right就已经将parent的right置为nullptr,此时再调用sibling()就会得不到准确的信息
			bool left = parentNode->left == nullptr || node->isLeftChild();
			NODE *siblingNode = left ? parentNode->right : parentNode->left;
			if (left) {
				//被删除的节点在左边，兄弟节点在右边
				if (isRed(siblingNode)) {
					//兄弟节点是红色，要转化成兄弟节点是黑色
					black(siblingNode);
					red(parentNode);
					rotateLeft(parentNode);
					//更换兄弟
					siblingNode = parentNode->right;
				}
				//以下代码处理兄弟节点是黑色(兄弟节点必然为黑色)
				if (isBlack(siblingNode->left) && isBlack(siblingNode->right)) {
					//兄弟节点没有红色子节点，父节点要向下和兄弟节点合并
					bool parentIsBlack = isBlack(parentNode);
					black(parentNode);
					red(siblingNode);
					if (parentIsBlack) {
						//如果父亲节点是黑色，会产生下溢
						node = parentNode;
						continue;
					}
					return;
				} else {
					//兄弟节点至少有一个红色子节点,向兄弟节点借元素
					//兄弟节点的右边是黑色的，兄弟要先旋转
					if (isBlack(siblingNode->right)) {
						rotateRight(siblingNode);
						siblingNode = parentNode->right;
					}
					color(siblingNode, colorOf(parentNode));
					black(parentNode);
					black(siblingNode->right);
					rotateLeft(parentNode);
					return;
				}
			} else {
				//被删除的节点在右边，兄弟节点在左边
				if (isRed(siblingNode)) {
					//兄弟节点是红色，要转化成兄弟节点是黑色
					black(siblingNode);
					red(parentNode);
					rotateRight(parentNode);
					//更换兄弟
					siblingNode = parentNode->left;
				}
				//以下代码处理兄弟节点是黑色(兄弟节点必然为黑色)
				if (isBlack(siblingNode->left) && isBlack(siblingNode->right)) {
					//兄弟节点没有红色子节点，父节点要向下和兄弟节点合并
					bool parentIsBlack = isBlack(parentNode);
					black(parentNode);
					red(siblingNode);
					if (parentIsBlack) {
						//如果父亲节点是黑色，会产生下溢
						node = parentNode;
						continue;
					}
					return;
				} else {
					//兄弟节点至少有一个红色子节点,向兄弟节点借元素
					//兄弟节点的左边是黑色的，兄弟要先旋转
					if (isBlack(siblingNode->left)) {
						rotateLeft(siblingNode);
						siblingNode = parentNode->left;
					}
					color(siblingNode, colorOf(parentNode));
					black(parentNode);
					black(siblingNode->left);
					rotateRight(parentNode);
					return;
				}
			}
		}
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
			afterRemove(replacement);
			delete node_;
		} else if (node_->parent == nullptr) {			//node_是叶子节点，也是根节点
			root_ = nullptr;
			delete node_;
		} else {			//node_是叶子节点，但不是根节点
			if (node_->parent->left == node_)
				node_->parent->left = nullptr;
			else
				node_->parent->right = nullptr;
			afterRemove(node_);
			delete node_;
		}
	}

	void preorderTraversal(NODE *node, bool (*visitor)(Element e)) {
		//迭代实现前序遍历
		if (node == nullptr || visitor == nullptr)
			return;
		using namespace std;
		stack<NODE*> s;
		while (true) {
			if (node != nullptr) {
				//访问node节点
				if (visitor(node->e))
					return;
				//右子节点入栈
				if (node->right != nullptr)
					s.push(node->right);
				//向左走
				node = node->left;
			} else if (s.size() == 0) {
				return;
			} else {
				//没有左边节点，但是栈不为空
				node = s.top();
				s.pop();
			}
		}
	}

	void inorderTraversal(NODE *node, bool (*visitor)(Element e)) {
		//迭代实现中序遍历
		if (node == nullptr || visitor == nullptr)
			return;
		using namespace std;
		stack<NODE*> s;
		while (true) {
			if (node != nullptr) {
				//向左走
				s.push(node);
				node = node->left;
			} else if (s.size() == 0) {
				return;
			} else {
				//node为nullptr,且栈不为空
				node = s.top();
				s.pop();
				//访问node节点
				if (visitor(node->e))
					return;
				//对右子节点进行中序遍历
				node = node->right;
			}
		}
	}

	void postorderTraversal(NODE *node, bool (*visitor)(Element e)) {
		//迭代实现后序遍历
		if (node == nullptr || visitor == nullptr)
			return;
		using namespace std;
		//记录上一次弹出被访问的节点
		NODE *prevNode = nullptr;
		stack<NODE*> s;
		s.push(node);
		while (s.size() != 0) {
			NODE *top = s.top();
			if (top->isLeaf()
					|| (prevNode != nullptr && prevNode->parent == s.top())) {
				//栈顶为叶子节点或者（上一次有弹出元素且弹出元素的父节点是当前栈顶元素）
				prevNode = s.top();
				s.pop();
				//访问node节点
				if (visitor(prevNode->e))
					return;
			} else {
				if (top->right != nullptr)
					s.push(top->right);
				if (top->left != nullptr)
					s.push(top->left);
			}
		}
	}

	void levelOrderTraversal(NODE *node, bool (*visitor)(Element e)) {
		if (node == nullptr || visitor == nullptr)
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

