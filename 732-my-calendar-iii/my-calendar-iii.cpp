
struct Node {
  Node* left;
  Node* right;
  int seg;
  int lazy;
};

Node* createNode() {
  Node* node = new Node();
  node->left = nullptr;
  node->right = nullptr;
  node->seg = 0;
  node->lazy = 0;
  return node;
}

void update(Node* node, int st, int en, int l, int r) {
  if(st != en) {
    if(node->left == nullptr) {
      node->left = createNode();
      node->right = createNode();
    }
  }
  if(node->lazy != 0) {
    node->seg += node->lazy;
    if(st != en) {
      node->left->lazy += node->lazy;
      node->right->lazy += node->lazy;
    }
    node->lazy = 0;
  }
  if(st > r || en < l || st > en) {
    return;
  }
  if(st >= l && en <= r) {
    node->seg += 1;
    if(st != en) {
      node->left->lazy += 1;
      node->right->lazy += 1;
    }
    return;
  }
  int mid = (st + en) >> 1;
  update(node->left, st, mid, l, r);
  update(node->right, mid + 1, en, l, r);
  node->seg = max(node->left->seg, node->right->seg);
}
class MyCalendarThree {
private:
  int res;
  Node* root;
public:
  MyCalendarThree() {
    res = 0;
    root = createNode();
  }
  int book(int str, int end) {
    update(root, 0, 1e9, str, end - 1);
    res = max(res, root->seg);
    return res;
  }
};