#include <iostream>
#include <cmath>
using namespace std;

struct binTree {
	int inf;
	binTree* left;
	binTree* right;
};

binTree* createTree(int L, int R, int arr[]) {
	binTree* tr;
	int m;
	if (L > R) return nullptr;
	m = (L + R) / 2;

	tr = new binTree;
	tr->inf = arr[m];

	tr->left = createTree(L, m-1, arr);
	tr->right = createTree(m+1, R, arr);
	return tr;
}

void printBinTree(binTree* tr, int level = 0, char branch = '-') {
	if (tr != NULL) {
		printBinTree(tr->right, level + 1, '/');
		for (int i = 0; i < level; i++) cout << "    ";
		cout << branch << "--" << tr->inf << endl;
		printBinTree(tr->left, level + 1, '\\');
	}
}

binTree* findKeyBranch(binTree* tr, int key) {
	binTree *trt = tr;
	if (trt) {
		if (trt->inf != key) {
			if (trt->inf > key) {
				trt = findKeyBranch(trt->left, key);

			}
			else {
				trt = findKeyBranch(trt->right, key);
			}
		}

	}
	return trt;
}

void symWrite(binTree* tr) {
	if (tr == NULL) return;
	symWrite(tr->left);
	cout << tr->inf << ' ';
	symWrite(tr->right);
}

void unWrite(binTree* tr) {
	if (tr == NULL) return;
	unWrite(tr->left);
	unWrite(tr->right);
	cout << tr->inf << ' ';
}

void Write(binTree* tr) {
	if (tr == NULL) return;
	cout << tr->inf << ' ';
	Write(tr->left);
	Write(tr->right);
}

void deleteBranch(binTree *&deltr) {
	if (deltr->left != NULL) {
		deleteBranch(deltr->left);
	}
	if (deltr->right != NULL) {
		deleteBranch(deltr->right);
	}
	deltr->right = NULL;
	deltr->left = NULL;

	deltr = nullptr;
	delete deltr;
}

void deleteKeyBranch(binTree *tr, int key) {
	binTree* deltr = findKeyBranch(tr, key);
	cout << deltr->inf << endl;
	deleteBranch(deltr);
	deltr = nullptr;

}

int levelOfTree(binTree* tr) {
	int level = 0;
	if (tr != NULL) {
		level = levelOfTree(tr->right);
		level++;
	}
	return level;
}

int main() {
	int arr[] { 0,1,2,3,4,5,6,7,8,9,10,11,12,13,14 };
	binTree* tr = createTree(0, sizeof(arr)/4-1, arr);
	cout << "Pryamoi obhod: "; Write(tr); cout << endl;
	cout << "Obratni obhod: "; unWrite(tr); cout << endl;
	cout << "Symetric obhod: "; symWrite(tr); cout << endl;

	cout << "\033[1;33m";
	printBinTree(tr);
	cout << "\033[1;37m";
	int key;
	cout << "Enter key: ";
	cin >> key;
	deleteKeyBranch(tr, key);
	cout << "\033[1;34m";
	printBinTree(tr);
	cout << "\033[1;37m";
	deleteBranch(tr);
}