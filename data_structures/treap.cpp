#include <bits/stdc++.h>
using namespace std;
struct node {
	int val, prio;
	node* ls, * rs;
	int siz, rep;
	node(int val_ = 0) {
		val = val_;
		prio = rand();
		ls = rs = nullptr;
		siz = rep = 1;
	}
	void update() {
		siz = rep;
		if (ls)
			siz += ls->siz;
		if (rs)
			siz += rs->siz;
	}
};
int size(node* cur) {
	if (!cur)
		return 0;
	return cur->siz;
}
pair<node*, node*> split_val(node* cur, int val) {
	if (!cur)
		return { nullptr, nullptr };
	if (cur->val <= val) {
		auto res = split_val(cur->rs, val);
		cur->rs = res.first;
		cur->update();
		return { cur, res.second };
	}
	else {
		auto res = split_val(cur->ls, val);
		cur->ls = res.second;
		cur->update();
		return { res.first, cur };
	}
}
tuple<node*, node*, node*> split_rnk(node* cur, int rnk) {
	if (!cur)
		return { nullptr, nullptr, nullptr };
	int lsiz = size(cur->ls);
	if (rnk <= lsiz) {
		node* l, * m, * r;
		tie(l, m, r) = split_rnk(cur->ls, rnk);
		cur->ls = r;
		cur->update();
		return { l, m, cur };
	}
	else if (rnk <= lsiz + cur->rep) {
		node* l = cur->ls;
		node* r = cur->rs;
		cur->ls = cur->rs = nullptr;
		cur->update();
		return { l, cur, r };
	}
	else {
		node* l, * m, * r;
		tie(l, m, r) = split_rnk(cur->rs, rnk - lsiz - cur->rep);
		cur->rs = l;
		cur->update();
		return { cur, m, r };
	}
}
pair<node*, node*> split_siz(node* cur, int siz) {
	if (!cur)
		return { nullptr, nullptr };
	int lsiz = size(cur->ls);
	if (siz <= lsiz) {
		auto res = split_siz(cur->ls, siz);
		cur->ls = res.second;
		cur->update();
		return { res.first, cur };
	}
	else {
		auto res = split_siz(cur->rs, siz - lsiz - cur->rep);
		cur->rs = res.first;
		cur->update();
		return { cur, res.second };
	}
}
node* merge(node* t1, node* t2) {
	if (!t1 && !t2)
		return nullptr;
	if (!t1)
		return t2;
	if (!t2)
		return t1;
	if (t1->prio < t2->prio) {
		t1->rs = merge(t1->rs, t2);
		t1->update();
		return t1;
	}
	else {
		t2->ls = merge(t1, t2->ls);
		t2->update();
		return t2;
	}
}
void insert(node*& cur, int val) {
	auto res = split_val(cur, val);
	auto res2 = split_val(res.first, val - 1);
	if (!res2.second) {
		res2.second = new node(val);
	}
	else {
		res2.second->rep++;
		res2.second->update();
	}
	cur = merge(merge(res2.first, res2.second), res.second);
}
void erase(node*& cur, int val) {
	auto res = split_val(cur, val);
	auto res2 = split_val(res.first, val - 1);
	if (res2.second) {
		if (res2.second->rep > 1) {
			res2.second->rep--;
			res2.second->update();
			res2.first = merge(res2.first, res2.second);
		}
		else {
			if (res.first == res2.second)
				res.first = nullptr;
			delete res2.second;
			res2.second = nullptr;
		}
	}
	cur = merge(res2.first, res.second);
}
int qrnk(node*& cur, int val) {
	auto res = split_val(cur, val - 1);
	int ret = size(res.first) + 1;
	cur = merge(res.first, res.second);
	return ret;
}
int qval(node*& cur, int rnk) {
	node* l, * m, * r;
	tie(l, m, r) = split_rnk(cur, rnk);
	int ret = (m ? m->val : -INF);
	cur = merge(merge(l, m), r);
	return ret;
}
int prev(node*& cur, int val) {
	auto res = split_val(cur, val - 1);
	int ret = qval(res.first, res.first->siz);
	cur = merge(res.first, res.second);
	return ret;
}
int next(node*& cur, int val) {
	auto res = split_val(cur, val);
	int ret = qval(res.second, 1);
	cur = merge(res.first, res.second);
	return ret;
}
bool find(node* cur, int val) {
	if (!cur)
		return false;
	if (cur->val == val)
		return true;
	if (val < cur->val)
		return find(cur->ls, val);
	if (val > cur->val)
		return find(cur->rs, val);
}
