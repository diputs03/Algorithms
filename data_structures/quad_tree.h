#pragma once

#include "data_structure.h"

//compile error
class quadTree {
private:
	//Constants
	static const int NORTH_EAST = 1;
	static const int NORTH_WEST = 2;
	static const int SOUTH_EAST = 3;
	static const int SOUTH_WEST = 4;

	//Functions
	static bool north(int dir) {
		return dir == NORTH_EAST || dir == NORTH_WEST;
	}
public:
	//Classes
	class rectangle {
	public:
		long long x1, y1, x2, y2;
		rectangle(long long x11, long long y11, long long x22, long long y22) {
			this->x1 = x11;
			this->y1 = y11;
			this->x2 = x22;
			this->y2 = y22;
		}

		bool intersects(rectangle* r) {
			return r != nullptr && !(r->x2 < x1 || r->x1 > x2 || r->y1 > y2 || r->y2 < y1);
		}

		bool contains(long long x, long long y) {
			return (x1 <= x && x <= x2) && (y1 <= y && y <= y2);
		}

		bool contains(rectangle* r) {
			return r != nullptr && contains(r->x1, r->y1) && contains(r->x1, r->y2);
		}
	};
private:
	//Classes
	class point {
	public:
		long long x, y;
		point() {

		}
		point(long long xx, long long yy) {
			x = xx;
			y = yy;
		}
	};
	class sortedPoint {
	public:
		point pt;
		double distance;
		sortedPoint(double dis, point po) {
			distance = dis;
			pt = po;
		}

		int compare_to(sortedPoint other) {
			return distance - other.distance;
		}
	};
	class node {
	public:
		//Variables
		int point_count;
		long long* X;
		long long* Y;
		node* nor_wes;
		node* nor_eas;
		node* sou_wes;
		node* sou_eas;
		rectangle* region;

		//Functions
		bool add(long long x, long long y) {
			if (!region->contains(x, y))
				return false;
			if (point_count < num_point) {
				X[point_count] = x;
				Y[point_count] = y;
				point_count++;
				return true;
			}
			else {
				long long cx = (region->x1 + region->x2) / 2;
				long long cy = (region->y1 + region->y2) / 2;

				if (sou_wes == nullptr)
					sou_wes = new node(new rectangle(region->x1, region->y1, cx, cy));
				if (sou_wes->add(x, y))
					return true;

				if (nor_wes == nullptr)
					nor_wes = new node(new rectangle(region->x1, cy, cx, region->y2));
				if (nor_wes->add(x, y))
					return true;

				if (nor_eas == nullptr)
					nor_eas = new node(new rectangle(cx, cy, region->x2, region->y2));
				if (nor_eas->add(x, y))
					return true;

				if (sou_eas == nullptr)
					sou_eas = new node(new rectangle(cx, region->y1, region->x2, cy));
				return sou_eas->add(x, y);
			}
		}

		void k_nearest_neighbors(int k, long long x, long long y, std::priority_queue<sortedPoint>* heap) {
			for (int i = 0; i < point_count; i++) {
				long long xx = X[i], yy = Y[i];
				double radius = heap->empty() ? (double)INT_MAX : heap->top().distance;

				double distance = std::sqrt((xx - x) * (xx - x) + (yy - y) * (yy - y));

				if ((int)heap->size() < k)
					heap->push(*new sortedPoint(distance, *new point(xx, yy)));
				else if (distance < radius) {
					heap->pop();
					heap->push(*new sortedPoint(distance, *new point(xx, yy)));
				}
			}

			int point_quadrant = 0;

			if (nor_wes != nullptr && region->contains(x, y)) {
				nor_wes->k_nearest_neighbors(k, x, y, heap);
				point_quadrant = NORTH_WEST;
			}
			else if (nor_eas != nullptr && region->contains(x, y)) {
				nor_eas->k_nearest_neighbors(k, x, y, heap);
				point_quadrant = NORTH_EAST;
			}
			else if (sou_wes != nullptr && region->contains(x, y)) {
				sou_wes->k_nearest_neighbors(k, x, y, heap);
				point_quadrant = SOUTH_WEST;
			}
			else if (sou_eas != nullptr && region->contains(x, y)) {
				sou_eas->k_nearest_neighbors(k, x, y, heap);
				point_quadrant = SOUTH_EAST;
			}

			if (point_quadrant)
				return;

			double radius = heap->empty() ? INT_MAX : heap->top().distance;

			long long cx = (region->x1 + region->x2) / 2;
			long long cy = (region->y1 + region->y2) / 2;

			long long dx = std::abs(x - cx);
			long long dy = std::abs(y - cy);

			bool chech_horizontal_cell = radius >= dx;
			bool check_vertical_cell = radius >= dy;
			bool check_diagonal_cell = chech_horizontal_cell && check_vertical_cell;

			if (heap->size() == k)
				if (north(point_quadrant))
					if (point_quadrant == NORTH_WEST) {
						if (nor_eas != nullptr)
							nor_eas->k_nearest_neighbors(k, x, y, heap);
						if (sou_wes != nullptr)
							sou_wes->k_nearest_neighbors(k, x, y, heap);
						if (sou_eas != nullptr)
							sou_eas->k_nearest_neighbors(k, x, y, heap);
					}
					else {
						if (nor_wes != nullptr)
							nor_wes->k_nearest_neighbors(k, x, y, heap);
						if (sou_eas != nullptr)
							sou_eas->k_nearest_neighbors(k, x, y, heap);
						if (nor_wes != nullptr)
							nor_wes->k_nearest_neighbors(k, x, y, heap);
					}
				else
					if (point_quadrant == SOUTH_WEST) {
						if (sou_eas != nullptr)
							sou_eas->k_nearest_neighbors(k, x, y, heap);
						if (nor_wes != nullptr)
							nor_wes->k_nearest_neighbors(k, x, y, heap);
						if (nor_eas != nullptr)
							nor_eas->k_nearest_neighbors(k, x, y, heap);
					}
					else {
						if (sou_wes != nullptr)
							sou_wes->k_nearest_neighbors(k, x, y, heap);
						if (nor_wes != nullptr)
							nor_wes->k_nearest_neighbors(k, x, y, heap);
						if (nor_wes != nullptr)
							nor_wes->k_nearest_neighbors(k, x, y, heap);
					}
			else
				if (north(point_quadrant))
					if (point_quadrant == NORTH_WEST) {
						if (chech_horizontal_cell)
							if (nor_eas != nullptr)
								nor_eas->k_nearest_neighbors(k, x, y, heap);
						if (check_vertical_cell)
							if (sou_wes != nullptr)
								sou_wes->k_nearest_neighbors(k, x, y, heap);
						if (check_diagonal_cell)
							if (sou_eas != nullptr)
								sou_eas->k_nearest_neighbors(k, x, y, heap);
					}
					else {
						if (chech_horizontal_cell)
							if (nor_wes != nullptr)
								nor_wes->k_nearest_neighbors(k, x, y, heap);
						if (check_vertical_cell)
							if (sou_eas != nullptr)
								sou_eas->k_nearest_neighbors(k, x, y, heap);
						if (check_diagonal_cell)
							if (nor_wes != nullptr)
								nor_wes->k_nearest_neighbors(k, x, y, heap);
					}
				else
					if (point_quadrant == SOUTH_WEST) {
						if (chech_horizontal_cell)
							if (sou_eas != nullptr)
								sou_eas->k_nearest_neighbors(k, x, y, heap);
						if (check_vertical_cell)
							if (nor_wes != nullptr)
								nor_wes->k_nearest_neighbors(k, x, y, heap);
						if (check_diagonal_cell)
							if (nor_eas != nullptr)
								nor_eas->k_nearest_neighbors(k, x, y, heap);
					}
					else {
						if (chech_horizontal_cell)
							if (sou_wes != nullptr)
								sou_wes->k_nearest_neighbors(k, x, y, heap);
						if (check_vertical_cell)
							if (nor_wes != nullptr)
								nor_wes->k_nearest_neighbors(k, x, y, heap);
						if (check_diagonal_cell)
							if (nor_wes != nullptr)
								nor_wes->k_nearest_neighbors(k, x, y, heap);
					}
		}

		node(rectangle* region) {
			this->region = region;
			X = new long long[num_point];
			Y = new long long[num_point];
		}

		int count(rectangle* area) {
			if (area == nullptr || !region->intersects(area))
				return 0;
			int count = 0;
			if (area->contains(region))
				count = point_count;
			else
				for (int i = 0; i < point_count; i++)
					if (area->contains(X[i], Y[i]))
						count++;
			if (nor_wes != nullptr)
				count += nor_wes->count(area);
			if (nor_eas != nullptr)
				count += nor_eas->count(area);
			if (sou_wes != nullptr)
				count += sou_wes->count(area);
			if (sou_eas != nullptr)
				count += sou_eas->count(area);

			return count;
		}

		std::list<point>* k_nearest_neighbors(int k, long long x, long long y) {
			std::priority_queue<sortedPoint>* h = new std::priority_queue<sortedPoint>;

			k_nearest_neighbors(k, x, y, h);

			std::list<point>* neighbors = new std::list<point>;

			while (h->size()) {
				neighbors->push_back(h->top().pt);
				h->pop();
			}

			return neighbors;
		}
	};

	//Functions
	void getPoints(node* node, std::list<point>* points) {
		if (node == NULL)
			return;
		for (int i = 0; i < node->point_count; i++)
			points->push_back(*(new point(node->X[i], node->Y[i])));
		getPoints(node->nor_wes, points);
		getPoints(node->nor_eas, points);
		getPoints(node->sou_wes, points);
		getPoints(node->sou_eas, points);
	}
public:
	//Variables
	static int num_point;

	const int defualt_num_points = 16;

	node* root;

	//Functions
	quadTree(rectangle* region) {
		num_point = defualt_num_points;
		root = new node(region);
	}

	quadTree(rectangle* region, int points_per_node) {
		num_point = points_per_node;
		root = new node(region);
	}

	bool add(long long x, long long y) {
		return root->add(x, y);
	}

	int count(rectangle* region) {
		return root->count(region);
	}

	std::list<point>* k_nearest_neighbors(int k, long long x, long long y) {
		return root->k_nearest_neighbors(k, x, y);
	}

	std::list<point>* getPoints() {
		std::list<point>* points = new std::list<point>;
		getPoints(root, points);
		return points;
	}
};