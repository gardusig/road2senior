#include <bits/stdc++.h>

template <typename T>
class SegmentTree1D
{
public:
	SegmentTree1D(const int lo, const int hi)
	{
		this->lo = lo;
		this->hi = hi;
		this->value = LLONG_MAX;
		this->left = nullptr;
		this->right = nullptr;

		if (lo != hi)
		{
			const int mid = lo + ((hi - lo) >> 1);
			this->left = std::make_unique<SegmentTree1D>(lo, mid);
			this->right = std::make_unique<SegmentTree1D>(mid + 1, hi);
		}
	}

	void update(const int index, const T new_value)
	{
		if (index < this->lo or index > this->hi)
		{
			return;
		}
		if (index == this->lo and index == this->hi)
		{
			this->value = new_value;
			return;
		}
		this->left->update(index, new_value);
		this->right->update(index, new_value);
		this->value = std::min(this->left->value, this->right->value);
	}

	T query(const int lo, const int hi)
	{
		if (this->lo > hi or this->hi < lo)
		{
			return LLONG_MAX;
		}
		if (this->lo >= lo and this->hi <= hi)
		{
			return this->value;
		}
		const T l = this->left->query(lo, hi);
		const T r = this->right->query(lo, hi);
		return std::min(l, r);
	}

private:
	int lo;
	int hi;
	T value;
	std::unique_ptr<SegmentTree1D> left;
	std::unique_ptr<SegmentTree1D> right;
};

int main()
{
	std::ios_base::sync_with_stdio();
	std::cin.tie(0);
	std::cout.tie(0);

	int N, A, B;
	std::cin >> N >> A >> B;

	std::vector<int> v(N);
	for (int &i : v)
	{
		std::cin >> i;
	}

	std::vector<long long int> sum(N + 1);
	sum[0] = 0;
	for (int i = 1; i <= N; i += 1)
	{
		sum[i] = sum[i - 1] + v[i - 1];
	}

	std::unique_ptr<SegmentTree1D<long long int>> segtree(new SegmentTree1D<long long int>(0, N + 1));

	for (int i = 0; i <= N; i += 1)
	{
		segtree->update(i, sum[i]);
	}

	long long int ans = LLONG_MIN;

	for (int i = A; i <= N; i += 1)
	{
		const long long int smallest = segtree->query(std::max(0, i - B), i - A);
		ans = std::max(ans, sum[i] - smallest);
	}

	std::cout << ans << std::endl;

	return 0;
}