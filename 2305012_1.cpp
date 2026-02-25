#include <bits/stdc++.h>
using namespace std;

enum COLOR {RED,BLACK};

template<typename T>
class rbTree{
private:
    struct Node{
        T data;
        COLOR color;
        Node* left;
        Node* right;
        Node* parent;
        int size;
        
        Node(T value){
            data = value;

            left = right = parent = nullptr;
            color = RED;
            size = 1;
        }

        
    };

    Node* root;
    Node* leaf;


    int getSize(Node* node){
        if(node == leaf) return 0;
        return node->size;
    }

    void updateSize(Node* node){
        if(node != leaf){
            node->size = 1+ getSize(node->left) + getSize(node->right);
        }
    }

    void rightRotate(Node* A){
        Node* B = A->left;
        Node* R;
        R = B->right;

        A->left = R;
        if(R!= leaf) R->parent = A;

        Node* grandparent = A->parent;

        B->right = A;
        A->parent = B;

        B->parent = grandparent;

        if(grandparent == nullptr){
            root = B;
        }
        else if(grandparent->left == A){
            grandparent->left = B;
        }
        else{
            grandparent->right = B;
        }

        updateSize(A);
        updateSize(B);
    }

    void leftRotate(Node* B){
        Node* A = B->right;
        Node* L = A->left;

        B->right = L;
        if(L != leaf) L->parent = B;

        Node* grandparent = B->parent;

        A->left = B;
        B->parent = A;

        A->parent = grandparent;

        if(grandparent == nullptr){
            root = A;
        }
        else if(B == grandparent->left){
            grandparent->left = A;
        }
        else{
            grandparent->right = A;
        }

        updateSize(B);
        updateSize(A);
        
    }

    bool bstInsert(Node* newNode){
        Node* curr = root;
        Node* parent = nullptr;

        while(curr != leaf){
            parent = curr;

            if(curr->data > newNode->data){
                curr = curr->left;
            }
            else if(curr->data < newNode->data){
                curr = curr->right;
            }
            else{
                return false;
            }
        }

        newNode->parent = parent;
        newNode->left = newNode->right = leaf;
        newNode->color = RED;

        if(parent == nullptr) root = newNode;
        else if(parent->data < newNode->data) parent->right = newNode;
        else parent->left = newNode;

        curr = parent;
        while(curr != nullptr){
            curr->size = curr->size + 1;
            curr = curr->parent;
        }

        return true;
    }

    void fixTree(Node* node){
        while(node != root && node->parent->color == RED){
            Node* parent = node->parent;
            Node* grandparent = parent->parent;
            Node* uncle;
            if(parent == grandparent->left){
                uncle = grandparent->right;

                if(uncle->color == RED){
                    uncle->color = BLACK;
                    parent->color = BLACK;
                    grandparent->color = RED;
                    node = grandparent;
                }
                else{
                    if(node == parent->right){
                        node = parent;
                        leftRotate(node);
                        parent = node->parent;
                        grandparent = parent->parent;
                    }
                    parent->color = BLACK;
                    grandparent->color = RED;
                    node->color = RED;
                    rightRotate(grandparent);
                    
                }
            }
            else{
                uncle = grandparent->left;

                if(uncle->color == RED){
                    uncle->color = BLACK;
                    parent->color = BLACK;
                    grandparent->color = RED;
                    node = grandparent;
                }
                else{
                    if(node == parent->left){
                        node = parent;
                        rightRotate(node);
                        parent = node->parent;
                        grandparent = parent->parent;
                    }
                    parent->color = BLACK;
                    grandparent->color = RED;
                    node->color = RED;
                    leftRotate(grandparent);
                }
            }
        }
        root->color = BLACK;
    }

    void nodeSwap(Node* u,Node* v){
        if(u->parent == nullptr){
            root = v;
        }
        else if(u->parent->left == u){
            u->parent->left = v;
        }
        else{
            u->parent->right = v;
        }

        v->parent = u->parent;
    }

    Node* minNode(Node* root){
        Node* curr = root;
        while(curr->left != leaf){
            curr = curr->left;
        }

        return curr;
    }

    void fixTreeDel(Node* node){
        while(node != root && node->color == BLACK){
            Node* parent = node->parent;
            Node* sibling;

            if(node == parent->left){
                sibling = parent->right;

                if(sibling->color == RED){
                    sibling->color = BLACK;
                    parent->color = RED;
                    leftRotate(parent);
                    sibling = parent->right;
                }

                if(sibling->left->color == BLACK && sibling->right->color == BLACK){
                    sibling->color = RED;
                    node = parent;
                }
                else{
                    if(sibling->right->color == BLACK){
                        sibling->left->color = BLACK;
                        sibling->color = RED;
                        rightRotate(sibling);
                        sibling = parent->right;
                    }
                    sibling->color = parent->color;
                    parent->color = BLACK;
                    sibling->right->color = BLACK;
                    leftRotate(parent);
                    node = root;
                }
            }
            else{
                sibling = parent->left;

                if(sibling->color == RED){
                    sibling->color = BLACK;
                    parent->color = RED;
                    rightRotate(parent);
                    sibling = parent->left;
                }

                if(sibling->left->color == BLACK && sibling->right->color == BLACK){
                    sibling->color = RED;
                    node = parent;
                }
                else{
                    if(sibling->left->color == BLACK){
                        sibling->right->color = BLACK;
                        sibling->color = RED;
                        leftRotate(sibling);
                        sibling = parent->left;
                    }
                    sibling->color = parent->color;
                    parent->color = BLACK;
                    sibling->left->color = BLACK;
                    rightRotate(parent);
                    node = root;
                }
            }
        }
        node->color = BLACK;
    }
public:
    rbTree(){
        leaf = new Node(T());
        leaf->color = BLACK;
        leaf->size = 0;
        leaf->left = leaf->right = leaf;
        leaf->parent = nullptr;

        root = leaf;
    }

    int insert(T value){
        Node* node = new Node(value);

        int flag = bstInsert(node);
        if(flag == 0){
            delete node;
            return 0;
        }
        fixTree(node);
        return 1;
    }

    bool search(T value){
        Node* curr = root;

        while(curr != leaf){
            if(curr->data == value){
                return true;
            }
            else if(curr->data > value){
                curr = curr->left;
            }
            else{
                curr = curr->right;
            }
        }
        return false;
    }

    int countLessThan(T value){
        int count = 0;
        Node* curr = root;

        while(curr != leaf){
            if(value > curr->data){
                count += getSize(curr->left) + 1;
                curr = curr->right;
            }
            else{
                curr = curr->left;
            }
            
        }

        return count;
    }

    int remove(T value){
        Node* curr = root;

        while(curr != leaf){
            if(curr->data == value){
                break;
            }
            else if(curr->data > value){
                curr = curr->left;
            }
            else{
                curr = curr->right;
            }
        }

        if(curr == leaf) return 0;

        Node* nodeToDelete = curr;

        COLOR originalColor = nodeToDelete->color;
        Node* fixNode;
        Node* fixSize;
        if(nodeToDelete->left == leaf){
            fixNode = nodeToDelete->right;
            fixSize = nodeToDelete->parent;
            nodeSwap(nodeToDelete,nodeToDelete->right);
        }
        else if(nodeToDelete->right == leaf){
            fixNode = nodeToDelete->left;
            fixSize =  nodeToDelete->parent;
            nodeSwap(nodeToDelete,nodeToDelete->left);
        }
        else{
            Node* succ = minNode(nodeToDelete->right);
            originalColor = succ->color;
            fixNode = succ->right;

            if(succ->parent == nodeToDelete){
                fixSize = succ;
            }
            else{
                fixSize = succ->parent;
                nodeSwap(succ,succ->right);
                succ->right = nodeToDelete->right;
                succ->right->parent = succ;
            }

            nodeSwap(nodeToDelete,succ);
            succ->left = nodeToDelete->left;
            succ->left->parent = succ;
            succ->color = nodeToDelete->color;

            succ->size = nodeToDelete->size;
        }

        Node* p = fixSize;

        while(p != nullptr){
            p->size--;
            p = p->parent;
        }

        delete nodeToDelete;

        if(originalColor == BLACK){
            fixTreeDel(fixNode);
        }

        return 1;
    }

    
};

int main(){
    freopen("input1.txt","r",stdin);
    freopen("output1.txt","w",stdout);

    int n;
    cin>>n;
    cout<<n<<"\n";
    rbTree<int> t;
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
            break;
        }
        break;
        case 2:{
            int k;
            cin>>k;
            bool found = t.search(k);
            if(found) cout<<c<<" "<<k<<" "<<1<<"\n";
            else cout<<c<<" "<<k<<" "<<0<<"\n";
            break;
        }
        case 3:{
            int k;
            cin>>k;
            cout<<c<<" "<<k<<" "<<t.countLessThan(k)<<"\n";
            break;
        }
        default:
            break;
        }
    }
}