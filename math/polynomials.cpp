#include "Math.h"



namespace Poly {
#define add(a,b) (a + b >= mod ? a + b - mod : a + b)
#define dec(a,b) (a < b ? a - b + mod : a - b)
#define ls (p << 1)
#define rs (ls | 1)
	const int N = 1e5;
	const int mod = 998244353;
	inline int fpow(int a, int b) {
		int ret = 1;

		for (; b; b >>= 1)
			(b & 1) && (ret = (long long)ret * a % mod), a = (long long)a * a % mod;

		return ret;
	}
	const int LG = 17;
	const int N = 1 << LG + 1;
	const int G = 3;
	int lg2[N + 5];
	int rev[N + 5], fac[N + 5], ifac[N + 5], inv[N + 5];
	int rt[N + 5];
	inline void init() {
		for (int i = 2; i <= N; ++i)
			lg2[i] = lg2[i >> 1] + 1;

		rt[0] = 1, rt[1 << LG] = fpow(G, (mod - 1) >> LG + 2);

		for (int i = LG; i; --i)
			rt[1 << i - 1] = (long long)rt[1 << i] * rt[1 << i] % mod;

		for (int i = 1; i < N; ++i)
			rt[i] = (long long)rt[i & i - 1] * rt[i & -i] % mod;

		fac[0] = 1;

		for (int i = 1; i <= N; ++i)
			fac[i] = (long long)fac[i - 1] * i % mod;

		ifac[N] = fpow(fac[N], mod - 2);

		for (int i = N; i; --i)
			ifac[i - 1] = (long long)ifac[i] * i % mod;

		for (int i = 1; i <= N; ++i)
			inv[i] = (long long)ifac[i] * fac[i - 1] % mod;
	}
	class poly {
	public:
		std::vector<int> polynomial;
		inline poly(int x = 0) {
			x && (polynomial.push_back(x), 1);
		}
		inline poly(const std::vector<int>& o) {
			polynomial = o, shrink();
		}
		inline poly(const poly& o) {
			polynomial = o.polynomial, shrink();
		}
		inline void shrink() {
			for (; !polynomial.empty() && !polynomial.back(); polynomial.pop_back());
		}
		inline int size() const {
			return polynomial.size();
		}
		inline void resize(int x) {
			polynomial.resize(x);
		}
		inline int operator[](int x) const {
			if (x < 0 || x >= size())
				return 0;

			return polynomial[x];
		}
		inline void clear() {
			std::vector<int>().swap(polynomial);
		}
		inline poly rever() const {
			return poly(std::vector<int>(polynomial.rbegin(), polynomial.rend()));
		}
	private:
		inline void dif() {
			int n = size();

			for (int i = 0, len = n >> 1; len; i++, len >>= 1)
				for (int j = 0, *w = rt; j < n; j += len << 1, w++)
					for (int k = j, R; k < j + len; k++) {
						R = (long long)*w * polynomial[k + len] % mod;
						polynomial[k + len] = dec(polynomial[k], R);
						polynomial[k] = add(polynomial[k], R);
					}
		}
		inline void dit() {
			int n = size();

			for (int i = 0, len = 1; len < n; i++, len <<= 1)
				for (int j = 0, *w = rt; j < n; j += len << 1, w++)
					for (int k = j, R; k < j + len; k++) {
						R = add(polynomial[k], polynomial[k + len]);
						polynomial[k + len] = (long long)(polynomial[k] - polynomial[k + len] + mod) * *w % mod;
						polynomial[k] = R;
					}

			reverse(polynomial.begin() + 1, polynomial.end());

			for (int i = 0; i < n; i++)
				polynomial[i] = (long long)polynomial[i] * inv[n] % mod;
		}
	public:
		inline std::complex<double>* ft(std::complex<double>* polynomial, int size) {
			int n = size;
			if (n == 1)
				return new std::complex<double>{ polynomial[0] };
			std::complex<double>* arr = new std::complex<double>[n / 2];
			for (int k = 0; k < n / 2; k++)
				arr[k] = polynomial[2 * k];
			std::complex<double>* q = ft(arr, n / 2);

			for (int k = 0; k < n / 2; k++)
				arr[k] = polynomial[2 * k + 1];
			std::complex<double>* r = ft(arr, (n + 1) / 2);

			std::complex<double>* y = new std::complex<double>[n];
			for (int k = 0; k < n / 2; k++) {
				double kth = -2 * 4 * acos(-1) / n;
				std::complex<double> wk = { std::cos(kth), std::sin(kth) };
				y[k] = q[k] + wk * r[k];
				y[k + n / 2] = q[k] - wk * r[k];
			}
			delete[] r;
			delete[] q;
			delete[] arr;
			return y;
		}
		inline std::complex<double>* ft(poly* polynomial) {
			std::complex<double>* p = new std::complex<double>;
			for (int i = 0; i < polynomial->size(); i++)
				p[i] = (double)(polynomial->polynomial[i]);
			return ft(p, polynomial->size());
		}
		inline poly ift(std::complex<double>* polynomial, int size) {
			int n = size;
			std::complex<int>* y = new std::complex<int>[n];
			for (int i = 0; i < n; i++)
				y[i] = { polynomial[i].real(), -polynomial[i].imag() };

			std::complex<double>* p = new std::complex<double>;
			for (int i = 0; i < n; i++)
				p[i] = { (double)(y[i].real()), (double)(y[i].imag()) };
			p = ft(p, n);

			for (int i = 0; i < n; i++)
				p[i] = { p[i].real(), -p[i].imag() };

			for (int i = 0; i < n; i++)
				y[i] = { p[i].real() / n, p[i].imag() / n };
			std::vector<int> ret;
			for (int i = 0; i < n; i++)
				ret.push_back(y[i].real());
			delete[] y;
			return *new poly(ret);
		}
		friend poly pad(poly arr, int n) {
			poly padded;
			padded.resize(n);
			for (int i = 0; i < n; i++)
				padded.polynomial[i] = (i < arr.size()) ? arr[i] : 0;
			return padded;
		}
		inline void ntt(int type = 1) {
			type == 1 ? dif() : dit();
		}
		friend inline poly fft(poly a, poly b) {
			int exp = 32 - std::log(a.size() + b.size() - 2) / std::log(2);
			int len = (int)fpow(2, exp);
			a = pad(a, len);
			b = pad(b, len);
			std::complex<double>* c = a.ft(&a), * d = b.ft(&b);
			std::complex<double>* e = new std::complex<double>[len];
			for (int i = 0; i < len; i++)
				e[i] = c[i] * d[i];
			return a.ift(e, len);
		}
		friend inline poly operator+(const poly& a, const poly& b) {
			std::vector<int> ret(std::max(a.size(), b.size()));

			for (int i = 0; i < ret.size(); i++)
				ret[i] = add(a[i], b[i]);

			return poly(ret);
		}
		friend inline poly operator-(const poly& a, const poly& b) {
			std::vector<int> ret(std::max(a.size(), b.size()));

			for (int i = 0; i < ret.size(); i++)
				ret[i] = dec(a[i], b[i]);

			return poly(ret);
		}
		friend inline poly operator*(poly a, poly b) {
			if (a.polynomial.empty() || b.polynomial.empty())
				return poly();

			if (a.size() < 40 || b.size() < 40) {
				if (a.size() > b.size())
					std::swap(a, b);

				poly ret;
				ret.resize(a.size() + b.size() - 1);

				for (int i = 0; i < ret.size(); ++i)
					for (int j = 0; j <= i && j < a.size(); ++j)
						ret.polynomial[i] = (ret[i] + (long long)a[j] * b[i - j]) % mod;

				ret.shrink();
				return ret;
			}

			int lim = 1, tot = a.size() + b.size() - 1;

			for (; lim < tot; lim <<= 1);

			a.resize(lim), b.resize(lim);
			a.ntt(), b.ntt();

			for (int i = 0; i < lim; ++i)
				a.polynomial[i] = (long long)a[i] * b[i] % mod;

			a.ntt(-1), a.shrink();
			return a;
		}
		poly& operator+=(const poly& o) {
			resize(std::max(size(), o.size()));

			for (int i = 0; i < o.size(); i++)
				polynomial[i] = add(polynomial[i], o[i]);

			return *this;
		}
		poly& operator-=(const poly& o) {
			resize(std::max(size(), o.size()));

			for (int i = 0; i < o.size(); i++)
				polynomial[i] = dec(polynomial[i], o[i]);

			return *this;
		}
		poly& operator*=(poly o) {
			return (*this) = (*this) * o;
		}
		poly deriv() const {
			if (polynomial.empty())
				return poly();

			std::vector<int> ret(size() - 1);

			for (int i = 0; i < size() - 1; i++)
				ret[i] = (long long)(i + 1) * polynomial[i + 1] % mod;

			return poly(ret);
		}
		poly integ() const {
			if (polynomial.empty())
				return poly();

			std::vector<int> ret(size() + 1);

			for (int i = 0; i < size(); i++)
				ret[i + 1] = (long long)polynomial[i] * inv[i + 1] % mod;

			return poly(ret);
		}
		inline poly modxn(int n) const {
			if (polynomial.empty())
				return poly();

			n = std::min(n, size());
			return poly(std::vector<int>(polynomial.begin(), polynomial.begin() + n));
		}
		inline poly inver(int m) const {
			poly ret(fpow(polynomial[0], mod - 2)), f, g;

			for (int k = 1; k < m;) {
				k <<= 1, f.resize(k), g.resize(k);

				for (int i = 0; i < k; i++)
					f.polynomial[i] = (*this)[i], g.polynomial[i] = ret[i];

				f.ntt(), g.ntt();

				for (int i = 0; i < k; i++)
					f.polynomial[i] = (long long)f[i] * g[i] % mod;

				f.ntt(-1);

				for (int i = 0; i < (k >> 1); i++)
					f.polynomial[i] = 0;

				f.ntt();

				for (int i = 0; i < k; i++)
					f.polynomial[i] = (long long)f[i] * g[i] % mod;

				f.ntt(-1);
				ret.resize(k);

				for (int i = (k >> 1); i < k; i++)
					ret.polynomial[i] = dec(0, f[i]);
			}

			return ret.modxn(m);
		}
		inline std::pair<poly, poly> div(poly o) const {
			if (size() < o.size())
				return std::make_pair(poly(), *this);

			poly f, g;
			f = (rever().modxn(size() - o.size() + 1) * o.rever().inver(size() - o.size() + 1)).modxn(
				size() - o.size() + 1).rever();
			g = (modxn(o.size() - 1) - o.modxn(o.size() - 1) * f.modxn(o.size() - 1)).modxn(o.size() - 1);
			return std::make_pair(f, g);
		}
		inline poly log(int m) const {
			return (deriv() * inver(m)).integ().modxn(m);
		}
		inline poly exp(int m) const {
			poly ret(1), iv, it, d = deriv(), itd, itd0, t1;

			if (m < 70) {
				ret.resize(m);

				for (int i = 1; i < m; i++) {
					for (int j = 1; j <= i; j++)
						ret.polynomial[i] = (ret[i] + (long long)j * operator[](j) % mod * ret[i - j]) % mod;

					ret.polynomial[i] = (long long)ret[i] * inv[i] % mod;
				}

				return ret;
			}

			for (int k = 1; k < m;) {
				k <<= 1;
				it.resize(k >> 1);

				for (int i = 0; i < (k >> 1); ++i)
					it.polynomial[i] = ret[i];

				itd = it.deriv(), itd.resize(k >> 1);
				iv = ret.inver(k >> 1), iv.resize(k >> 1);
				it.ntt(), itd.ntt(), iv.ntt();

				for (int i = 0; i < (k >> 1); i++)
					it.polynomial[i] = (long long)it[i] * iv[i] % mod,
					itd.polynomial[i] = (long long)itd[i] * iv[i] % mod;

				it.ntt(-1), itd.ntt(-1), it.polynomial[0] = dec(it[0], 1);

				for (int i = 0; i < k - 1; i++)
					itd.polynomial[i % (k >> 1)] = dec(itd[i % (k >> 1)], d[i]);

				itd0.resize((k >> 1) - 1);

				for (int i = 0; i < (k >> 1) - 1; i++)
					itd0.polynomial[i] = d[i];

				itd0 = (itd0 * it).modxn((k >> 1) - 1);
				t1.resize(k - 1);

				for (int i = (k >> 1) - 1; i < k - 1; i++)
					t1.polynomial[i] = itd[(i + (k >> 1)) % (k >> 1)];

				for (int i = k >> 1; i < k - 1; i++)
					t1.polynomial[i] = dec(t1[i], itd0[i - (k >> 1)]);

				t1 = t1.integ();

				for (int i = 0; i < (k >> 1); i++)
					t1.polynomial[i] = t1[i + (k >> 1)];

				for (int i = (k >> 1); i < k; i++)
					t1.polynomial[i] = 0;

				t1.resize(k >> 1), t1 = (t1 * ret).modxn(k >> 1), t1.resize(k);

				for (int i = (k >> 1); i < k; i++)
					t1.polynomial[i] = t1[i - (k >> 1)];

				for (int i = 0; i < (k >> 1); i++)
					t1.polynomial[i] = 0;

				ret -= t1;
			}

			return ret.modxn(m);
		}
		inline poly sqrt(int m) const {
			poly ret(1), f, g;

			for (int k = 1; k < m;) {
				k <<= 1;
				f = ret, f.resize(k >> 1);
				f.ntt();

				for (int i = 0; i < (k >> 1); i++)
					f.polynomial[i] = (long long)f[i] * f[i] % mod;

				f.ntt(-1);

				for (int i = 0; i < k; i++)
					f.polynomial[i % (k >> 1)] = dec(f[i % (k >> 1)], (*this)[i]);

				g = (2 * ret).inver(k >> 1), f = (f * g).modxn(k >> 1), f.resize(k);

				for (int i = (k >> 1); i < k; i++)
					f.polynomial[i] = f[i - (k >> 1)];

				for (int i = 0; i < (k >> 1); i++)
					f.polynomial[i] = 0;

				ret -= f;
			}

			return ret.modxn(m);
		}
		inline poly pow(int m, int k1, int k2 = -1) const {
			if (polynomial.empty())
				return poly();

			if (k2 == -1)
				k2 = k1;

			int t = 0;

			for (; t < size() && !polynomial[t]; t++);

			if ((long long)t * k1 >= m)
				return poly();

			poly ret;
			ret.resize(m);
			int u = fpow(polynomial[t], mod - 2), v = fpow(polynomial[t], k2);

			for (int i = 0; i < m - t * k1; i++)
				ret.polynomial[i] = (long long)operator[](i + t) * u % mod;

			ret = ret.log(m - t * k1);

			for (int i = 0; i < ret.size(); i++)
				ret.polynomial[i] = (long long)ret[i] * k1 % mod;

			ret = ret.exp(m - t * k1), t *= k1, ret.resize(m);

			for (int i = m - 1; i >= t; i--)
				ret.polynomial[i] = (long long)ret[i - t] * v % mod;

			for (int i = 0; i < t; i++)
				ret.polynomial[i] = 0;

			return ret;
		}
	};
}