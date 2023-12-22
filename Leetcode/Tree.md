## 1110删点成林

树形DFS，在搜索过程中，如果当前节点是要删除的节点，那么将其左右子树加入答案，然后返回空指针，否则返回当前节点。

```CPP
vector<TreeNode*> delNodes(TreeNode* root, vector<int>& to_delete) {
    unordered_set<int> to_delete_set(to_delete.begin(),to_delete.end());
    vector<TreeNode*> roots;
    dfs(root,true,to_delete_set,roots);
    return roots;
}

TreeNode* dfs(TreeNode* node, bool is_root,unordered_set<int> to_delete_set,vector<TreeNode*>& roots){
    if(node == nullptr){
        return nullptr;
    }
    bool deleted = to_delete_set.count(node->val)? true : false;
    node->left = dfs(node->left,deleted,to_delete_set,roots);
    node->right = dfs(node->right,deleted,to_delete_set,roots);
    if(deleted){
        return nullptr;
    }else{
        if(is_root){
            roots.emplace_back(node);
        }
        return node;
    }
    return nullptr;
}
// 递归十几行代码给他秒了，多做题啊，不会就是题做少了
vector<TreeNode*> delNodes(TreeNode* root, vector<int>& to_delete) {
    vector<TreeNode*> res;
    backorderTreeHelper(root,to_delete,res);
    if(root != nullptr) res.push_back(root);
    return res;
}
void backorderTreeHelper(TreeNode* &root,vector<int>& to_delete,vector<TreeNode*>& res){
    if(root == nullptr) return;
    backorderTreeHelper(root->left,to_delete,res);
    backorderTreeHelper(root->right,to_delete,res);
    if(find(to_delete.begin(),to_delete.end(),root->val) != to_delete.end()){
        if(root->left)res.push_back(root->left);
        if(root->right)res.push_back(root->right);
        root = nullptr;
    }
    return;
}
```

## 144 二叉树的前序遍历

迭代是以前写二叉树时候练习的少的方法，主要是用一个栈，用一个node结点，然后再适当的时候

stk.pop() and node = node->right

```CPP
// 递归
void preorderTraversal(TreeNode* root, vector<int>& res){
    if(root == nullptr)return;
    res.push_back(root->val);
    preorderTraversal(root->left,res);
    preorderTraversal(root->right,res);
}

// 迭代
vector<int> preorderTraversal(TreeNode* root) {
    vector<int> res;
    if(root == nullptr)return res;
    stack<TreeNode*> stk;
    TreeNode* node = root;
    while(!stk.empty() || node != nullptr){
        while(node != nullptr){
            res.emplace_back(node->val);
            stk.emplace(node);
            node = node->left;
        }
        node = stk.top();
        stk.pop();
        node = node->right;
    }
    return res;
}
```


## 145 二叉树的后序遍历

递归方法就不在这写了，写的比较多，主要写迭代方法

为了实现这一逻辑，使用了 prev 变量来追踪上一个被访问的节点。具体来说，当栈顶节点的右子树为空或者已经访问过（即 root->right == nullptr || root->right == prev），就可以安全地访问当前节点，然后将 prev 设置为当前节点，将 root 设为 nullptr，以确保下一步能够正确处理栈顶的节点。


```CPP
vector<int> postorderTraversal(TreeNode *root) {
    vector<int> res;
    if (root == nullptr) {
        return res;
    }
    stack<TreeNode *> stk;
    TreeNode *prev = nullptr;
    while (root != nullptr || !stk.empty()) {
        while (root != nullptr) {
            stk.emplace(root);
            root = root->left;
        }
        root = stk.top();
        stk.pop();
        // 主要就是理解这一步，后序遍历只有右节点空或者右节点已经遍历情况下再访问根节点。
        if (root->right == nullptr || root->right == prev) {
            res.emplace_back(root->val);
            prev = root;
            root = nullptr;
        } else {
            stk.emplace(root);
            root = root->right;
        }
    }
    return res;
}
```

## 94 二叉树中序遍历

```CPP
vector<int> inorderTraversal(TreeNode* root) {
    vector<int> res;
    stack<TreeNode*> stk;
    while(root != nullptr || !stk.empty()){
        while(root != nullptr){
            stk.push(root);
            root = root->left;
        }
        root = stk.top();
        stk.pop();
        res.push_back(root->val);
        root = root->right;
    }
    return res;
}
```

## 102 层序遍历 && 107 层序遍历II && 199 二叉树的右视图 && 637 二叉树的层平均值

自己写了一版，不太优雅，还有空指针的错误，排查了一小会，
在这记录下标准的模板。

```CPP
vector<vector<int>> levelOrder(TreeNode* root) {
    vector<vector<int>> res;
    if(root == nullptr) return res;
    queue<TreeNode*> q;
    q.push(root);
    while(!q.empty()){
        int lsize = q.size();
        res.push_back(vector<int>());
        for(int i = 0 ; i < lsize; i++){
            auto node = q.front();q.pop();
            res.back().push_back(node->val);
            if(node->left != nullptr)q.push(node->left);
            if(node->right != nullptr)q.push(node->right);
        }
    }
    return res;
}   
// 其实跟我写的也没太大区别，有一点点区别就是可以用lsize记录当前层有多少个元素，就不用先把nextl记录到宁外的vector最后再填到queue里

// 加左右子结点的时候先判空
```
注：max_element(begin(),end());返回的是一个迭代器，*提领就是最大值。

## 429 N叉树的层序遍历


```CPP
//跟二叉树的层序是一个搞法
vector<vector<int>> levelOrder(Node* root) {
    vector<vector<int>> res;
    if(root == nullptr) return res;
    queue<Node*> q;
    q.push(root);
    while(!q.empty()){
        res.push_back(vector<int>());
        int lsize = q.size();
        for(int i =0;i < lsize; i++){
            res.back().push_back(q.front()->val);
            vector<Node*> childs = q.front()->children;
            for(auto item : childs){
                q.push(item);
            }
            q.pop();
        }
    }
    return res;
}
```

## 116 填充每个节点的下一个右侧节点指针 && 117 填充每个节点的下一个右侧节点指针II

**这俩题目很有意思，116是完美二叉树，117是一般二叉树，我的做法针对所有二叉树都有效，但或许，完美二叉树时有简单做法？**

直接做法，在经典的vector<vector<int>>中最后添加一个nullptr,然后遍历连接

但其实不需要把res全部存下来。

改进了一下，使用deque没有存全部节点，速度也一般，可能由于deque不是顺序容器。既然最后结果一般，代码就不粘贴在这了。

用vector试试

```CPP
Node* connect(Node* root) {
    vector<Node*> temp;
    temp.push_back(root);
    if(root == nullptr) return root;
    int left = 0;
    int right = temp.size()  ;
    // [0,1)
    while(left != right){
        temp.push_back(nullptr); 
        for(int i = left; i < right;i++){
            temp[i]->next = temp[i + 1];
            if(temp[i]->left)temp.push_back(temp[i]->left);
            if(temp[i]->right)temp.push_back(temp[i]->right);
        }
        left = right + 1;
        right = temp.size(); 
    }
    return root;
}
// 这个方法指针变化是比较复杂的
```

总而言之，能够快速的把层序遍历代码背出来，这题就不具有太大难度。

## 104 二叉树的最大深度

直接层序遍历，然后查看res矩阵的size，这是一种方法，或者回溯给一个参数level，level++与ans取大，也是一种方法。

```CPP
// 回溯取大  8ms
int maxDepth(TreeNode* root) {
    int ans = 0;
    backTracking(root,ans,1);
    return ans;
}
void backTracking(TreeNode* root, int& ans, int level){
    if(root == nullptr) return;
    if(root != nullptr){
        ans = level > ans ? level : ans;
    }
    backTracking(root->left,ans,level + 1);
    backTracking(root->right,ans,level + 1);
}
// 层序遍历取res的size  12ms
int maxDepth(TreeNode* root) {
    vector<vector<int>> res;
    if(root == nullptr) return 0;
    queue<TreeNode*> q;
    q.push(root);
    while(!q.empty()){
        int lsize = q.size();
        res.push_back(vector<int>());
        for(int i = 0; i < lsize; i++){
            TreeNode* node = q.front();
            q.pop();
            if(node->left)q.push(node->left);
            if(node->right)q.push(node->right);
            res.back().push_back(node->val);
        }
    }
    return res.size();
}
```

## 111 二叉树的最小深度
思路就是在104最大深度的level实现基础上，把ans赋值算法改成小于号，同时必须叶子节点才有权改动ans。速度不是特别快

```CPP
int minDepth(TreeNode* root) {
    int ans = 1000000;
    if(root == nullptr) return 0;
    backTracking(root,ans,1);
    return ans;
}
void backTracking(TreeNode* root, int& ans, int level){
    if(root == nullptr) return;
    if(root != nullptr and root->left == nullptr and root->right == nullptr){
        ans = level < ans ? level : ans;
    }
    backTracking(root->left,ans,level + 1);
    backTracking(root->right,ans,level + 1);
}

```





