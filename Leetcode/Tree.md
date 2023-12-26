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

## 226 翻转二叉树
递归秒了
```CPP
TreeNode* invertTree(TreeNode* root) {
    if(root == nullptr) return nullptr;
    if(root != nullptr){
        TreeNode* l = root->left;
        root->left = root->right;
        root->right = l;
        invertTree(root->left);
        invertTree(root->right);
    }
    return root;
}
```

## 222 完全二叉树节点个数



1. 层序遍历计数，时间复杂度超过11.61%的人，代码就不放在这了。

能不能根据最大深度和最后一层个数直接算出节点有多少个？

2. 直接递归计算左右子树个数，虽然复杂度很高，但是个很易读的方法
```CPP
// 比层次遍历快，可能层次遍历涉及太多不必要的计算，什么Push，for
int countNodes(TreeNode* root) {
    if(root == nullptr)return 0;
    int left = countNodes(root->left);
    int right = countNodes(root->right);
    return left + right + 1;
}
```
3. 位运算与二分查找，代码比较长，面试也难写出来，不放在这了


## 110 平衡二叉树

这是我第一次写出的代码，两次递归，做了大量重复计算。
```CPP
bool isBalanced(TreeNode* root) {
    if(root == nullptr) return true;
    if(isBalanced(root->left) and isBalanced(root->right) and abs(getLevel(root->left) - getLevel(root->right)) <=1){
        return true;
    }
    return false;
}

int getLevel(TreeNode* root){
    int ans = 0;
    if(root == nullptr)return ans;
    return max(getLevel(root->left),getLevel(root->right)) + 1;
}
```

这是把平衡与深度写在一个递归函数里的优化方法

```CPP
bool isBalanced(TreeNode* root) {
    return getHeight(root)>= 0;
}
int getHeight(TreeNode* root){
    int ans = 0;
    if(root == nullptr)return ans;
    int lefth = getHeight(root->left);
    int righth = getHeight(root->right);
    if(lefth == -1 || righth == -1|| abs(lefth - righth) > 1){
        return -1;
    }
    return max(lefth,righth) + 1;
}
```

## 257 二叉树的所有路径

递归一下就实现了，如果把path设置成&的话，就必须push 之后pop

但其实这个题具体来说，直接传值也可以，就不需要每次都pop

```CPP
vector<string> binaryTreePaths(TreeNode* root) {
    vector<string> res;
    string curStr;
    backTracking(root,curStr,res);
    return res;
}
void backTracking(TreeNode* root,string curStr,vector<string>& res){
    if(root == nullptr) return;
    if(root->left == nullptr and root->right == nullptr) {
        curStr += to_string(root->val);
        res.push_back(curStr);
        return;
    }
    if(root->left){
        string ltemp = curStr + to_string(root->val);
        ltemp += "->";
        backTracking(root->left,ltemp,res);
    }
    if(root->right){
        string rtemp = curStr + to_string(root->val);
        rtemp += "->";
        backTracking(root->right,rtemp,res);
    }
    return;
}
```

## 404 左叶子之和

递归秒了

```CPP
int sumOfLeftLeaves(TreeNode* root) {
    int ans = 0;
    backTracking(root,0,ans);
    return ans;
}
void backTracking(TreeNode* root,int mark,int& ans){
    if(root == nullptr) return;
    if(root->left == nullptr and root->right == nullptr and mark == 1){
        ans += root->val;
    }
    backTracking(root->left,1,ans);
    backTracking(root->right,0,ans);
}
```

迭代
```CPP
int sumOfLeftLeaves(TreeNode* root) {
    int ans = 0;
    if(root == nullptr) return ans;
    stack<TreeNode*> stk;
    stk.push(root);
    while(!stk.empty()){
        TreeNode* root = stk.top();
        stk.pop();
        if(root->left and !root->left->left and !root->left->right){
            ans += root->left->val;
        }
        if(root->left) stk.push(root->left);
        if(root->right) stk.push(root->right);
    }
    return ans;
}
```

## 513 找树左下角的值

层序遍历的方法就不写在这了 12ms 63%

正确思路——根左右这么来搜索，第一个level最大的节点一定是最左边的结点。 12ms 64%

```CPP
    int findBottomLeftValue(TreeNode* root) {
        int ans = 0;
        int maxlevel = 0;
        backTracking(root,1,maxlevel,ans);
        return ans;
    }
    void backTracking(TreeNode* root,int level,int& maxlevel,int& ans){
        if(root == nullptr) return;
        if(level > maxlevel){
            maxlevel = level;
            ans = root->val;
        }
        backTracking(root->left,level + 1,maxlevel,ans);
        backTracking(root->right,level + 1,maxlevel,ans);
    }
```

## 106 从中序与后序遍历序列构造二叉树

使用递归，后序遍历的最后一个节点一定是根节点，根据这个信息切割中序后序的左右子树序列，然后递归调用

这题想到递归就非常简单，但在分割左右子树的细节上就比较困难，容易出错。

```CPP
    TreeNode* buildTree(vector<int>& inorder, vector<int>& postorder) {
        int n = inorder.size();
        return buildTreeHelper(inorder, postorder, 0, n - 1, 0, n - 1);
    }
    TreeNode* buildTreeHelper(vector<int>& inorder, vector<int>& postorder, int inorderstart, int inorderend, int postorderstart, int postorderend) {
        if (inorderstart > inorderend) return nullptr;
        int rootval = postorder[postorderend];
        TreeNode* node = new TreeNode(rootval);
        int inorderindex = distance(inorder.begin(), find(inorder.begin(), inorder.end(), rootval));
        int rightSubtreeSize = inorderend - inorderindex;
        node->left = buildTreeHelper(inorder, postorder, inorderstart, inorderindex - 1, postorderstart, postorderend - rightSubtreeSize - 1);
        node->right = buildTreeHelper(inorder, postorder, inorderindex + 1, inorderend, postorderend - rightSubtreeSize, postorderend - 1);
        return node;
    }
```

## 654 最大二叉树

跟上面的中后序构造二叉树一个题目，区别就是本题找左右序列要方便一点。

```CPP
TreeNode* constructMaximumBinaryTree(vector<int>& nums) {
    if(nums.size() == 0) return nullptr;
    vector<int>::iterator mi = max_element(nums.begin(),nums.end());
    int maxi = distance(nums.begin(),mi);
    vector<int> left(nums.begin(),nums.begin() + maxi);
    vector<int> right(nums.begin()+ maxi + 1,nums.end());
    TreeNode* node = new TreeNode(*mi);
    node->left = constructMaximumBinaryTree(left);
    node->right = constructMaximumBinaryTree(right);
    return node;
}
```

```CPP
// 迭代，单调栈
TreeNode* constructMaximumBinaryTree(vector<int>& nums) {
    if(nums.empty()) return nullptr;
    vector<TreeNode*> stack;
    for(int i = 0; i < nums.size(); i++) {
        TreeNode* node = new TreeNode(nums[i]);
        while(!stack.empty() && stack.back()->val < nums[i]) {
            node->left = stack.back();
            stack.pop_back();
        }
        if(!stack.empty()) {
            stack.back()->right = node;
        }
        stack.push_back(node);
    }
    return stack.front();
}
```

## 700 二叉搜索树中的搜索

```CPP
// 递归秒了，改迭代
TreeNode* searchBST(TreeNode* root, int val) {
    if(root->val == val)return root;
    if(root->val < val and root->right == nullptr) return nullptr;
    if(root->val > val and root->left == nullptr) return nullptr;
    if(root->val < val){
        return searchBST(root->right,val);
    }
    if(root->val > val){
        return searchBST(root->left,val);
    }
    return nullptr;
}
```

```CPP
// 写的还可以继续优化，总的来说就是，用一个栈，来模拟程序调用栈
TreeNode* searchBST(TreeNode* root, int val) {
    stack<TreeNode*> stk;
    stk.push(root);
    while(!stk.empty()){
        TreeNode* node = stk.top();
        stk.pop();
        if(node->val == val)return node;
        if(node->val > val and node->left != nullptr) stk.push(node->left);
        if(node->val < val and node->right != nullptr ) stk.push(node->right);!
    }
    return nullptr;
}
```

## 617 合并二叉树

经典的递归方法
```CPP
TreeNode* mergeTrees(TreeNode* root1, TreeNode* root2) {
    if(root1 == nullptr and root2 == nullptr) return nullptr;
    if(root1 and root2){
        root1->val = root1->val + root2->val;
        root1->left = mergeTrees(root1->left,root2->left);
        root1->right = mergeTrees(root1->right,root2->right);
        return root1;
    }
    if(root1 and root2 == nullptr){
        return root1;
    }
    if(root1 == nullptr and root2){
        return root2;
    }
    return nullptr;
}
```

## 98 验证二叉搜索树

递归回溯时候传递判断条件，一个上界MAX和一个下界MIN，对于root节点，MIN为 LONG_MIN，MAX为 LONG_MAX

```CPP
bool isValidBST(TreeNode* root) {
    return backTracking(root,LONG_MAX,LONG_MIN);
}
bool backTracking(TreeNode* root,long max, long min){
    if(root == nullptr) return true;
    if(root->val < min || root->val > max) return false;
    if(root->val > min && root->val < max){
        if(backTracking(root->left,root->val,min) and backTracking(root->right,max,root->val)){
            return true;
        }else{
            return false;
        }
    }
    return false;
}
```

试试改迭代，现在遇到树问题，第一时间递归都改迭代试试能不能做

```CPP
// 中序遍历迭代递增
// 8 ms 88.74%
bool isValidBST(TreeNode* root) {
    long curMIN = LONG_MIN;
    stack<TreeNode*> stk;
    while(!stk.empty() || root != nullptr){
        while(root != nullptr){
            stk.push(root);
            root = root->left;
        }
        root = stk.top();
        stk.pop();
        if(root->val <= curMIN){
            return false;
        }else{
            curMIN = root->val;
        }
        if(root->right){
            root = root->right;
        }else{
            root = nullptr;
        }
    }
    return true;
}
// 二叉树前中后序迭代怎么写别忘了
```

## 530 二叉搜索树的最小绝对差
呃，到手拿着就做，做了个最大差值
```CPP
    int getMinimumDifference(TreeNode* root) {
        TreeNode* node = root;
        int min = root->val;
        int max = root->val;
        while(root!= nullptr){
            min = root->val < min ? root-> val : min;
            root = root->left;
        }
        while(node != nullptr){
            max = node->val > max ? node->val : max;
            node = node->right;
        }
        return abs(max - min);
    }
```
最小差值就，中序遍历吧，然后后减去前，应该是这样
```CPP
int getMinimumDifference(TreeNode* root) {
    stack<TreeNode*> stk;
    int curMin = 100000;
    int mindif = 100000;
    while(!stk.empty() || root != nullptr){
        while(root != nullptr){
            stk.push(root);
            root = root->left;
        }
        root = stk.top();
        stk.pop();
        int curdif = abs(root->val - curMin);
        mindif = mindif > curdif ? curdif : mindif;
        curMin = root->val;
        if(root->right){
            root = root->right;
        }else{
            root = nullptr;
        }
    }
    return mindif;
}
```

## 501 二叉树中的众数

第一次做，层序遍历加map + 转化为vector + 排序 + 输出结果。时间复杂度很高。

```CPP
    // 这次用了个O(1)的方法，也是官方题解的方法，16ms 77.35%，其实也没快太多
    void updateRes(vector<int>& res,int val,int& curNum,int& curCount,int& maxCount){
        if(val == curNum){
            curCount++;
            return;
        }
        if(val != curNum){
            if(curCount == 0){
                curNum = val;
                curCount = 1;
            }else{
                if(curCount > maxCount){
                    maxCount = curCount;
                    res.clear();
                    res.push_back(curNum);
                    curNum = val;
                    curCount = 1;
                }else if(curCount == maxCount){
                    res.push_back(curNum);
                    curNum = val;
                    curCount = 1;                    
                }else {
                    curNum = val;
                    curCount = 1;                    
                }
            }
        }
    }
    vector<int> findMode(TreeNode* root) {
        stack<TreeNode*> stk;
        int curNum = 100001;
        int curCount = 0;
        int maxCount = 0;
        vector<int> res;
        while(!stk.empty() || root != nullptr){
            while(root != nullptr){
                stk.push(root);
                root = root->left;
            }
            root = stk.top();
            stk.pop();
            int val = root->val;
            updateRes(res,val,curNum,curCount,maxCount);
            if(root->right){
                root = root->right;
            }else{
                root = nullptr;
            }
        }
        updateRes(res,1000002,curNum,curCount,maxCount);
        return res;
    }
```

## 235 二叉搜索树的最近公共祖先

这是个中等题，如果是一个一般的二叉树，搜索最近公共祖先比较麻烦，而对于二叉树，就可以利用二叉树左 < 根 < 右的特点。
```CPP
// 24ms 91%
TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
    if(root == nullptr) return nullptr;
    if(p->val < root->val and q->val < root->val) return lowestCommonAncestor(root->left,p,q);
    if(p->val > root->val and q->val > root->val) return lowestCommonAncestor(root->right,p,q);
    if(p->val <= root->val and q->val >= root->val) return root;
    if(p->val >= root->val and q->val <= root->val) return root;
    return nullptr;
}
```
换迭代法做一下
```CPP
// 差不多的做法
TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
    stack<TreeNode*> stk;
    stk.push(root);
    while(!stk.empty()){
        TreeNode* root = stk.top();
        stk.pop();
        if(root == nullptr) return nullptr;
        if(p->val < root->val and q->val < root->val) stk.push(root->left);
        if(p->val > root->val and q->val > root->val) stk.push(root->right);
        if(p->val <= root->val and q->val >= root->val) return root;
        if(p->val >= root->val and q->val <= root->val) return root;
    }
    return nullptr;
}
```

## 236 二叉树的最近公共祖先

跟235的区别是现在不是二叉搜索树了，节点之间没什么联系和关系

必须进行搜索

后续遍历就是DFS，后续遍历使用递归实现比较简单，第一版本我的代码使用int作为backTracking返回值

实际返回node更直观

```CPP
TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
    return backTracking(root, p, q);
}
// 这代码我读了两遍才读懂，要背住，或者自己重新用迭代方法实现一下。
TreeNode* backTracking(TreeNode* root, TreeNode* p, TreeNode* q) {
    if (root == nullptr) return nullptr;
    if (root == p || root == q) {
        return root;
    }
    TreeNode* left = backTracking(root->left, p, q);
    TreeNode* right = backTracking(root->right, p, q);
    if (left && right) {
        // 节点 p 和 q 在不同的子树中，根节点是LCA。
        return root;
    }
    // 如果一个子树为空，则返回非空子树（潜在的LCA）。
    return (left != nullptr) ? left : right;
}
```

## 701 二叉搜索树中的插入操作

如果不需要确保二叉树平衡的情况下，这个插入其实是非常简单的

递归找到需要插入的位置，然后new结点，设置指针就行了。但如果想要确保二叉树平衡，就需要考虑旋转了。

```CPP
TreeNode* insertIntoBST(TreeNode* root, int val) {
    if(root == nullptr) return new TreeNode(val);
    stack<TreeNode*> stk;
    stk.push(root);
    while(!stk.empty()){
        TreeNode* node = stk.top();
        if(val < node->val){
            if(node->left){
                stk.push(node->left);
            }else{
                node->left = new TreeNode(val);
                break;
            }
        }else{
            if(node->right){
                stk.push(node->right);
            }else{
                node->right = new TreeNode(val);
                break;
            }                
        }
    }
    return root;
}
```

## 450 删除二叉搜索树中的节点

写了个把小时没整明白，思路是很清晰的，把左子树接到右子树的最左边。

但代码实现起来非常繁琐复杂， 写了有四五十行。

随想录介绍了这题的正确解法和一种普通二叉树的通用删除方法。
```CPP

```


## 669 修剪二叉搜索树

一开始打算手动模拟，先找到在low 和high之间的root结点，然后在往左找，往右找，巴拉巴拉，太复杂，可以直接递归思路来做。


```CPP
// 递归写法就是这么简洁
TreeNode* trimBST(TreeNode* root, int low, int high) {
    if(root == nullptr) return nullptr;
    if(root->val > high){
        return trimBST(root->left,low,high);
    }else if(root->val < low){
        return trimBST(root->right,low,high);
    }else{
        root->left = trimBST(root->left,low,high);
        root->right = trimBST(root->right,low,high);
        return root;
    }
    return nullptr;
}
```
迭代写法，这个迭代写法for循环写的非常精妙，比起我while循环,parent left种种好多了
```CPP
TreeNode* trimBST(TreeNode* root, int low, int high) {
    while(root && (root->val < low || root->val > high)){
        if(root->val < low){
            root = root->right;
        }else{
            root = root->left;
        }
    }
    if(root == nullptr){
        return nullptr;
    }
    for(auto node = root; node->left;){
        if(node->left->val < low){
            node->left = node->left->right;
        } else {
            node = node->left;
        }
    }
    for (auto node = root; node->right; ) {
        if (node->right->val > high) {
            node->right = node->right->left;
        } else {
            node = node->right;
        }
    }
    return root;      
}
```

## 108 有序数组转换为二叉搜索树

二叉搜索树的中序遍历就是递增数组。感觉这题目递归写法比较好做

```CPP
// 跟二分查找差不多，需要判断left <= right
TreeNode* sortedArrayToBST(vector<int>& nums) {
    return sortedArrayToBST(nums,0,nums.size()- 1);
}
TreeNode* sortedArrayToBST(vector<int>& nums,int left,int right) {
    if(left > right)return nullptr;
    if(left <= right){
        int middle  = left + (right - left) / 2;
        TreeNode* root = new TreeNode(nums[middle]);
        root->left = sortedArrayToBST(nums,left,middle - 1);
        root->right = sortedArrayToBST(nums,middle + 1,right);
        return root;
    }
    return nullptr;
}
```

## 538 把二叉搜索树转换为累加树

二叉树最后一题，加油

第一种做法，迭代的层序遍历到vector，vector处理节点的值 40ms 20.57%

```CPP
TreeNode* convertBST(TreeNode* root) {
    vector<TreeNode*> temp;
    stack<TreeNode*> stk;
    TreeNode* nroot = root;
    while(!stk.empty() || root != nullptr){
        while(root != nullptr){
            stk.push(root);
            root = root->left;
        }
        root = stk.top();
        stk.pop();
        temp.push_back(root);
        if(root->right){
            root = root->right;
        }else{
            root = nullptr;
        }
    }
    int count = 0;
    for(int i = temp.size() - 1; i>=0;i--){
        count += temp[i]->val;
        temp[i]->val = count;
    }
    return nroot;
}
```

第二种做法，直接右根左遍历，count += root->val, root->val = count  36ms 40.06%
```CPP
TreeNode* convertBST(TreeNode* root) {
    int count = 0;
    stack<TreeNode*> stk;
    TreeNode* nroot = root;
    while(!stk.empty() || root != nullptr){
        while(root != nullptr){
            stk.push(root);
            root = root->right;
        }
        root = stk.top();
        stk.pop();
        count += root->val;
        root->val = count;
        if(root->left){
            root = root->left;
        }else{
            root = nullptr;
        }
    }
    return nroot;
}
```

## 随想录二叉树算法部分完结✨✨✨🎉🎉🎉🎉🎉🎉🎉🎉🎉🎉


