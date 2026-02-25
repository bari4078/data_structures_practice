#include <bits/stdc++.h>

using namespace std;

template <typename T>
class AVL_tree{

private:
    struct Node{
        T key;
        Node* left;
        Node* right;
        int height;

        Node(T k){
            height = 1;
            key = k;
            left = right = nullptr;
        }
    };

    Node* root;

    Node* rightRotate(Node* A){
        Node* B = A->left;
        Node* Y = B->right;

        A->left = Y;
        B->right = A;

        A->height = max(getHeight(A->right),getHeight(A->left)) + 1;
        B->height = max(getHeight(B->right),getHeight(B->left)) + 1;

        return B;
    }

    Node* leftRotate(Node* B){
        Node* A = B->right;
        Node* Y = A->left;

        B->right = Y;
        A->left = B;

        B->height = max(getHeight(B->right),getHeight(B->left)) + 1;
        A->height = max(getHeight(A->right),getHeight(A->left)) + 1;
        return A;
    }

    Node* insert_bst(Node* node,T key,bool &flag){
        if(node == nullptr){
            flag = true;
            return new Node(key);
        }

        if(key < node->key){
            node->left = insert_bst(node->left,key,flag);
        
        }
        else if(key > node->key){
            node->right = insert_bst(node->right,key,flag);
        }
        else{
            flag = false;
            return node;
        }

        node->height = max(getHeight(node->left),getHeight(node->right)) + 1;

        int bf = getBalanceFactor(node);

        //case 1, left er left boro
        if(bf > 1 && key < node->left->key){
            return rightRotate(node);
        }

        //case 2, right er right boro
        if(bf < -1 && key>node->right->key){
            return leftRotate(node);
        }

        //case 3, left er right
        if(bf > 1 && key > node->left->key){
            node->left = leftRotate(node->left);
            return rightRotate(node);
        }

        //case 4, right er left
        if(bf < -1 && key < node->right->key){
            node->right = rightRotate(node->right); 
            return leftRotate(node);
        }

        return node;
    }

    Node* minNode(Node* node){
        Node* curr = node;
        while(curr->left){
            curr = curr->left;
        }
        return curr;
    }

    Node* deleteNode(Node* node,T key,bool& flag){
        if(node == nullptr){
            flag = false;
            return nullptr;
        }

        if(key < node->key){
            node->left = deleteNode(node->left,key,flag);
            
        }
        else if(key > node->key){
            node->right = deleteNode(node->right,key,flag);
        }
        else{
            flag = true;
            auto temp = node;
            if(node->left == nullptr){
                node = node->right;
                delete temp;
            }else if(node->right == nullptr){
                node = node->left;
                delete temp;
            }else{
                auto succ = minNode(node->right);
                node->key = succ->key;
                bool dummy;
                deleteNode(node->right,succ->key,dummy);
            }
        }

        if(node == nullptr) return nullptr;

        node->height = max(getHeight(node->left),getHeight(node->right)) + 1;

        int bf = getBalanceFactor(node);

        if(bf > 1){
            //left left
            if(getBalanceFactor(node->left) >= 0){
                node = rightRotate(node);  
            }
            else{
                node->left = leftRotate(node->left);
                node = rightRotate(node);
            }
        }
        else if(bf < -1){
            if(getBalanceFactor(node->right) <= 0){
                node = leftRotate(node);
            }
            else{
                node->right = rightRotate(node->right);
                node = leftRotate(node);
            }
        }

        return node;
    }

    void preOrder(Node* node){
        if(node == nullptr) return;
        cout<<node->key<<" ";
        preOrder(node->left);
        preOrder(node->right);
    }

    void inOrder(Node *node){
        if(node == nullptr) return;
        inOrder(node->left);
        cout<<node->key<<" ";
        inOrder(node->right);
    }

    void postOrder(Node* node){
        if(node == nullptr) return;
        postOrder(node->left);
        postOrder(node->right);
        cout<<node->key<<" ";
    }

    void levelOrder(){
        if(!root) return;
        Node* curr = root;
        queue<Node*> q;
        q.push(curr);
        vector<T> res;
        while(!q.empty()){
            curr = q.front();
            q.pop();
            res.push_back(curr->key);
            if(curr->left) q.push(curr->left);
            if(curr->right) q.push(curr->right);
        }

        for(auto &e:res){
            cout<<e<<" ";   
        }
    }

public:
    AVL_tree(){
        root = nullptr;
    }
    int getHeight(Node *n){
        if(n == nullptr) return 0;
        return n->height;
    }

    int getBalanceFactor(Node *n){
        if(n == nullptr) return 0;
        return (getHeight(n->left) - getHeight(n->right));
    }

    int insert(T key){
        bool flag=false;
        root = insert_bst(root, key, flag);

        if(flag) return 1;
        return 0;
    }

    int remove(T key){
        bool flag = false;
        root = deleteNode(root,key,flag);

        if(flag) return 1;
        return 0;
    }

    void traverse(int choice){
        switch (choice)
        {
        case 1:
            preOrder(root);
            break;
        case 2:
            inOrder(root);
            break;
        case 3:
            postOrder(root);
            break;
        case 4:
            levelOrder();
            break;
        default:
            break;
        }
    }
};

int main(){
    freopen("input2.txt","r",stdin);
    freopen("output2.txt","w",stdout);

    int n;

    cin>>n;
    cout<<n<<"\n";
    AVL_tree<int> t;
    while(n--){
        int c;
        cin>>c;
        switch (c){
        case 0:{
            int k;
            cin>>k;
            int out = t.remove(k);
            cout<<c<<" "<<k<<" "<<out<<"\n";
        }
            break;
        case 1:{
            int k;
            cin>>k;
            int out = t.insert(k);
            cout<<c<<" "<<k<<" "<<out<<"\n";
        }
        break;
        case 2:{
            int way;
            cin>>way;
            
            t.traverse(way);
            cout<<endl;
        }
        default:
            break;
        }
    }
}