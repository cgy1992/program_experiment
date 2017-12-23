#include "main.h"

using namespace std;

//string tmp;

Node::Node(){
    count = 0;
    ch = '\0';
    parent = lchild = rchild = -1;
}
void Node::change_Node(int count, char ch){
    this->count = count;
    this->ch = ch;
}
bool Node::operator < (const Node& A)const{
    return A.count < count;
}
priority_queue <Node>huffman_node;

struct Node *huffman_tree;

void build_huffman_tree(void){
    huffman_tree = (struct Node*)malloc((2 * char_num - 1) * sizeof(struct Node));
    for (int i = 0; i < char_num; i++){
	huffman_tree[i].count = huffman_char[i].count;
	huffman_tree[i].ch = huffman_char[i].ch;
	huffman_tree[i].index = i;
	huffman_tree[i].lchild = huffman_tree[i].rchild = -1;
    }
    for (int i = char_num; i < 2 * char_num - 1; i++)
	huffman_tree[i].index = i;

    int index(char_num);
    while(huffman_node.size() - 1){
	int min1, min2;
	min1 = huffman_node.top().index; huffman_node.pop();
	min2 = huffman_node.top().index; huffman_node.pop();
	huffman_tree[min1].parent = huffman_tree[min2].parent = index;
	huffman_tree[index].lchild = min1;
	huffman_tree[index].rchild = min2;
	huffman_tree[index].count = huffman_tree[min1].count + huffman_tree[min2].count;
	huffman_tree[index].ch = '\0';
	huffman_node.push(huffman_tree[index]);
	index++;
    }
    /*for (int i = 0; i < 2 * char_num - 1; i++){
	cout << huffman_tree[i].ch << " " << huffman_tree[i].index << " " ;
	cout << huffman_tree[i].lchild << " " << huffman_tree[i].rchild << endl;
    }*/
}

void get_huffman_code(int idx, string tmp){
    char ch = huffman_tree[idx].ch;
    int char_idx;

    for (int i = 0; i < char_num; i++)
	if (huffman_char[i].ch == ch){
	    char_idx = i;
	    break;
	}
    if (huffman_tree[idx].lchild == -1 && huffman_tree[idx].rchild == -1){
	huffman_char[char_idx].bit_length = tmp.size();
	for (int i = 0; i < tmp.size(); i++)
	    huffman_char[char_idx].bit[i] = tmp[i];
//	tmp.erase(tmp.size() - 1);
	return;
    }
    //tmp = tmp + "0";
    get_huffman_code(huffman_tree[idx].lchild, tmp + "0");
    //tmp = tmp + "1";
    get_huffman_code(huffman_tree[idx].rchild, tmp + "1");
}
