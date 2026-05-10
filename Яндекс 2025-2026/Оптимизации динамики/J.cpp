#include<bits/stdc++.h>

# define int long long

using namespace std;

mt19937 rnd(179);

struct Node {
    int x, k, px, pk, y;
    Node *l = nullptr, *r = nullptr;
    Node(int x = 0, int k = 0, int px = 0, int pk = 0, int y = rnd()) : x(x), k(k), px(px), pk(pk), y(y) {}
};

void push(Node *v) {
    if (v == nullptr) return;
    v->x += v->px;
    v->k += v->pk;
    if (v->l) {
        v->l->px += v->px;
        v->l->pk += v->pk;
    }
    if (v->r) {
        v->r->px += v->px;
        v->r->pk += v->pk;
    }
    v->px = 0;
    v->pk = 0;
}

Node* mrg(Node* a, Node* b) {
    if (!a) return b;
    if (!b) return a;
    push(a);
    push(b);
    if (b->y > a->y) {
        auto r1 = mrg(a, b->l);
        b->l = r1;
        return b;
    }
    auto r1 = mrg(a->r, b);
    a->r = r1;
    return a;
}

pair<Node*, Node*> split_x(Node* r, int x) {
    if (!r) return {nullptr, nullptr};
    push(r);
    if (r->x >= x) {
        auto [r1, r2] = split_x(r->l, x);
        r->l = r2;
        return {r1, r};
    }
    auto [r1, r2] = split_x(r->r, x);
    r->r = r1;
    return {r, r2};
}

pair<Node*, Node*> split_k(Node* r, int k) {
    if (!r) return {nullptr, nullptr};
    push(r);
    if (r->k >= k) {
        auto [r1, r2] = split_k(r->l, k);
        r->l = r2;
        return {r1, r};
    }
    auto [r1, r2] = split_k(r->r, k);
    r->r = r1;
    return {r, r2};
}

Node* getl(Node* r) {
    if (r == nullptr) return nullptr;
    push(r);
    if (r->l == nullptr) return r;
    return getl(r->l);
}

Node* getr(Node* r) {
    if (r == nullptr) return nullptr;
    push(r);
    if (r->r == nullptr) return r;
    return getr(r->r);
}

vector<pair<int, int>> all;

void write(Node* r) {
    if (r == nullptr) return;
    push(r);
    write(r->l);
    all.push_back({r->x, r->k});
    write(r->r);
}

void print(Node* r) {
    if (r == nullptr) return;
    push(r);
    print(r->l);
    cout << r->x << " " << r->k << endl;
    print(r->r);
}

signed main() {
    int n, k;
    cin >> n >> k;
    vector<int> a(n);
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
    }
    __int128 h = 0;
    Node* root = new Node();
    for (int i = 0; i < n; ++i) {
        auto [r1, r2] = split_k(root, 0);
        auto left = getl(r2);
        if (r2) r2->px += k;
        if (r1) r1->px -= k;
        Node* add = new Node(left->x - k, 0);
        root = mrg(r1, mrg(add, r2));
        left = getl(root);
        h += a[i] - left->x;
        auto [r3, r4] = split_x(root, a[i]);
        left = getl(r4);
        if (!left || left->x != a[i]) {
            Node* ch = getr(r3);
            Node* add = new Node(a[i], ch->k + 1);
            if (r3) r3->pk -= 1;
            if (r4) r4->pk += 1;
            root = mrg(r3, mrg(add, r4));
        } else {
            if (r3) r3->pk -= 1;
            if (r4) r4->pk += 1;
            root = mrg(r3, r4);
        }
    }
    __int128 ans = h;
    write(root);
    for (int i = 0; i < (int)all.size() - 1; ++i) {
        h += all[i].second * (all[i + 1].first - all[i].first);
        ans = min(ans, h);
    }
    cout << (long long)ans << endl;
    return 0;
}
