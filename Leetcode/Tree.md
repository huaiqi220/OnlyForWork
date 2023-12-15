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


```