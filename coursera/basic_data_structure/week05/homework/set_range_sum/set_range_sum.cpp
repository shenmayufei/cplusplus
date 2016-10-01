#include <cstdio>

// Splay tree implementation

// Vertex of a splay tree
struct Vertex {
  int key;
  // Sum of all the keys in the subtree - remember to update
  // it after each operation that changes the tree.
  long long sum;
  Vertex* left;
  Vertex* right;
  Vertex* parent;

  Vertex(int key, long long sum, Vertex* left, Vertex* right, Vertex* parent) 
  : key(key), sum(sum), left(left), right(right), parent(parent) {}
};

void update(Vertex* v) {
  if (v == NULL) return;
  v->sum = v->key + (v->left != NULL ? v->left->sum : 0ll) + (v->right != NULL ? v->right->sum : 0ll);
  if (v->left != NULL) {
    v->left->parent = v;
  }
  if (v->right != NULL) {
    v->right->parent = v;
  }
}

void small_rotation(Vertex* v) {
  Vertex* parent = v->parent;
  if (parent == NULL) {
    return;
  }
  Vertex* grandparent = v->parent->parent;
  if (parent->left == v) {
    Vertex* m = v->right;
    v->right = parent;
    parent->left = m;
  } else {
    Vertex* m = v->left;
    v->left = parent;
    parent->right = m;
  }
  update(parent);
  update(v);
  v->parent = grandparent;
  if (grandparent != NULL) {
    if (grandparent->left == parent) {
      grandparent->left = v;
    } else {
      grandparent->right = v;
    }
  }
}

void big_rotation(Vertex* v) {
  if (v->parent->left == v && v->parent->parent->left == v->parent) {
    // Zig-zig
    small_rotation(v->parent);
    small_rotation(v);
  } else if (v->parent->right == v && v->parent->parent->right == v->parent) {
    // Zig-zig
    small_rotation(v->parent);
    small_rotation(v);
  } else {
    // Zig-zag
    small_rotation(v);
    small_rotation(v);
  }  
}

// Makes splay of the given vertex and makes
// it the new root.
void splay(Vertex*& root, Vertex* v) {
  if (v == NULL) return;
  while (v->parent != NULL) {
    if (v->parent->parent == NULL) {
      small_rotation(v);
      break;
    }
    big_rotation(v);
  }
  root = v;
}

// Searches for the given key in the tree with the given root
// and calls splay for the deepest visited node after that.
// If found, returns a pointer to the node with the given key.
// Otherwise, returns a pointer to the node with the smallest
// bigger key (next value in the order).
// If the key is bigger than all keys in the tree, 
// returns NULL.
Vertex* find(Vertex*& root, int key) {
  Vertex* v = root;
  Vertex* last = root;
  Vertex* next = NULL;
  while (v != NULL) {
    if (v->key >= key && (next == NULL || v->key < next->key)) {
      next = v;
    }
    last = v;
    if (v->key == key) {
      break;      
    }
    if (v->key < key) {
      v = v->right;
    } else {
      v = v->left;
    }
  }
  splay(root, last);
  return next;
}

void split(Vertex* root, int key, Vertex*& left, Vertex*& right) {
  right = find(root, key);
  splay(root, right);
  if (right == NULL) {
    left = root;
    return;
  }
  left = right->left;
  right->left = NULL;
  if (left != NULL) {
    left->parent = NULL;
  }
  update(left);
  update(right);
}

Vertex* merge(Vertex* left, Vertex* right) {
  if (left == NULL) return right;
  if (right == NULL) return left;
  Vertex* min_right = right;
  while (min_right->left != NULL) {
    min_right = min_right->left;
  }
  splay(right, min_right);
  right->left = left;
  update(right);
  return right;
}

// Code that uses splay tree to solve the problem

Vertex* root = NULL;

void insert(int x) {
  Vertex* left = NULL;
  Vertex* right = NULL;
  Vertex* new_vertex = NULL;  
  // printf("@@@@@@@@before insert root\n");
  // if (root != NULL) {
  //   printf("root key:%d, sum:%lld\n", root->key, root->sum);
  //   if (root->left != NULL) {
  //     printf("root left key:%d, sum:%lld\n", root->left->key, root->left->sum);
  //   }
  // }
  split(root, x, left, right);
  if (right == NULL || right->key != x) {
    new_vertex = new Vertex(x, x, NULL, NULL, NULL);
  }
  // printf("^^^^^^^^^shall merge insert\n");
  // if (left != NULL) {
  //   printf("left, key:%d, sum:%lld\n", left->key, left->sum);
  // }
  // if (new_vertex != NULL) {
  //   printf("new vertex, key:%d, sum:%lld\n", new_vertex->key, new_vertex->sum);
  // }
  // if (right != NULL) {
  //   printf("right, key:%d, sum:%lld\n", right->key, right->sum);
  // }
  // printf("^^^^^^^^^^merge insert complelte\n");

  root = merge(merge(left, new_vertex), right);
  // printf("--start--------\ninsert %d, root key:%d, sum: %lld\n", x,root->key, root->sum);
  // if (root->left != NULL) {
  //   printf("0000   root left key:%d, left sum:%lld\n", root->left->key, root->left->sum);
  //   if (root->left->left != NULL) {
  //     printf("0000   root left left key:%d, left left sum:%lld\n", root->left->left->key, root->left->left->sum);
  //   }
  // }
  // if (root->right != NULL) {
  //   printf("0000   root right key:%d, right sum:%lld\n", root->right->key, root->right->sum);
  // }
  // printf("--end--------\n");
}

void erase(int x) {
  Vertex* v = find(root, x);
  if (v==NULL || v->key != x) return;

  // if found
  // update left
  Vertex* left = v->left;
  v->left = NULL;
  if (left != NULL) {
    left->parent = NULL;
  }
  update(left);

  // delete the x, and update right
  Vertex* right = v->right;
  delete v;
  if (right != NULL) {
    right->parent = NULL;
    update(right);
  }

  root = merge(left, right);
}

bool find(int x) {  
  Vertex* v = find(root, x);
  if (v == NULL) return false;
  return v->key == x;
}

long long sum(int from, int to) {
  // printf("from:%d, to:%d\n", from, to);
  // if (root != NULL) {
  //   printf("0000  root key:%d, sum:%lld\n", root->key, root->sum);
  //   if (root->left != NULL) {
  //     printf("0000   root left key:%d, left sum:%lld\n", root->left->key, root->left->sum);
  //   }
  //   if (root->right != NULL) {
  //     printf("0000   root right key:%d, right sum:%lld\n", root->right->key, root->right->sum);
  //   }
  //   printf("\n");
  // }

  if (from > to) {
    int tmp = from;
    from = to;
    to = tmp;
  }
  Vertex* left = NULL;
  Vertex* middle = NULL;
  Vertex* right = NULL;
  split(root, from, left, middle);
  if (middle == NULL) return 0;
  // printf("00001   middle key:%d, sum:%lld\n", middle->key, middle->sum);
  // if (middle->left != NULL) {
  //   printf("00000001   middle left key:%d, left sum:%lld\n", middle->left->key, middle->left->sum);
  // }
  // if (middle->right != NULL) {
  //   printf("00000001   middle right key:%d, right sum:%lld\n", middle->right->key, middle->right->sum);
  // }
  split(middle, to + 1, middle, right);
  if (middle == NULL) return 0;
  // printf("00002   middle key:%d, sum:%lld\n", middle->key, middle->sum);
  // if (middle->left != NULL) {
  //   printf("00003   middle left key:%d, left sum:%lld\n", middle->left->key, middle->left->sum);
  // }
  // if (middle->right != NULL) {
  //   printf("00000001   middle right key:%d, right sum:%lld\n", middle->right->key, middle->right->sum);
  // }
  long long result =  middle->sum;

  root = merge(merge(left, middle), right);
  return result;
}

const int MODULO = 1000000001;

int main(){
  int n;
  scanf("%d", &n);
  int last_sum_result = 0;
  for (int i = 0; i < n; i++) {
    char buffer[10];
    scanf("%s", buffer);
    char type = buffer[0];
    switch (type) {
      case '+' : {
        int x;
        scanf("%d", &x);
        insert((x + last_sum_result) % MODULO);
      } break;
      case '-' : {
        int x;
        scanf("%d", &x);
        erase((x + last_sum_result) % MODULO);
      } break;            
      case '?' : {
        int x;
        scanf("%d", &x);
        printf(find((x + last_sum_result) % MODULO) ? "Found\n" : "Not found\n");
      } break;
      case 's' : {
        int l, r;
        scanf("%d %d", &l, &r);
        long long res = sum((l + last_sum_result) % MODULO, (r + last_sum_result) % MODULO);
        printf("%lld\n", res);
        last_sum_result = int(res % MODULO);
      }
    }
  }
  return 0;
}
