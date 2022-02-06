#include "Math.h"

long long gcd(long long a, long long b) {
	return b == 0 ? (a < 0 ? -a : a) : gcd(b, a % b);
}

long long* exgcd(long long a, long long b) {
	if (b == 0)
		return new long long[3]{ a, 1, 0 };
	long long* ret = exgcd(b, a % b);
	long long tmp = ret[1] - ret[2] * (a / b);
	ret[1] = ret[2];
	ret[2] = tmp;
	return ret;
}

long long gcf(long long a, long long b) {
	return b == 0 ? a : gcf(b, a % b);
}

bool prime(long long n) {
	if (!(n % 2))
		return false;
	int limit = (int)std::sqrt(n);
	for (int i = 3; i <= limit; i += 2)
		if (!(n % i))
			return false;
	return true;
}

long long crt(long long* a, long long* mod, int size) {
	long long M = 1;
	for (int i = 0; i < size; i++)
		M *= mod[i];
	long long* inv = new long long[size];
	for (int i = 0; i < size; i++)
		inv[i] = exgcd(M / mod[i], mod[i])[1];
	long long x = 0;
	for (int i = 0; i < size; i++) {
		x += (M / mod[i]) * a[i] * inv[i];
		x = ((x % M) + M) % M;
	}
	return x;
}

long long excrt(long long* a, long long* mod, int size) {
	long long x, y, k;
	long long M = a[0], ans = mod[0];
	for (int i = 1; i < size; i++) {
		long long c = M, b = a[i], c = (mod[i] - ans % b + b) % b;
		long long gcd = exgcd(c, b)[0];
		x = exgcd(c, b)[1];
		y = exgcd(c, b)[2];
		long long bg = b / gcd;
		if (c % gcd != 0)
			return -1;
		x *= (c / gcd);
		x %= bg;
		ans += x * M;
		M *= bg;
		ans = (ans % M + M) % M;
	}
	return ans;
}

long long Pollard_Rho(long long n) {
	if (!(n % 2))
		return 2;
	std::srand(std::time(NULL));
	long long x = 2 + (long long)(999999 * rand());
	long long c = 2 + (long long)(999999 * rand());
	long long y = x;
	long long d = 1;
	while (d == 1) {
		x = (x * x + c) % n;
		y = (y * y + c) % n;
		y = (y * y + c) % n;
		d = gcf(std::abs(x - y), n);
		if (d == n)
			break;
	}
	return d;
}

std::list<long long>* prime_factorization(long long n) {
	std::list<long long>* factors = new std::list<long long>;
	if (n <= 0)
		return factors;
	else if (n == 1) return factors;
	std::priority_queue<long long> divisorQueue;
	divisorQueue.push(n);
	while (!divisorQueue.empty()) {
		long divisor = divisorQueue.top();
		divisorQueue.pop();
		if (prime(divisor)) {
			factors->push_back(divisor);
			continue;
		}
		long next_divisor = Pollard_Rho(divisor);
		if (next_divisor == divisor) {
			divisorQueue.push(divisor);
		}
		else {
			divisorQueue.push(next_divisor);
			divisorQueue.push(divisor / next_divisor);
		}
	}
	return factors;
}

long long get(std::list<long long> l, int pos) {
	std::list<long long>::iterator iter = l.begin();
	int cnt = 0;
	while (cnt < pos) iter++;
	return *iter;
}

std::vector<long long>* convert(std::list<long long>* l) {
	std::vector<long long>* v = new std::vector<long long>;
	while (!l->size()) {
		v->push_back(l->front());
		l->pop_front();
	}
	return v;
}

long long** reduce(long long* a, long long *m, int size) {

	std::list<long long> aNew;
	std::list<long long> mNew;

	for (int i = 0; i < size; i++) {
		std::vector<long long> factors = *convert(prime_factorization(m[i]));
		std::sort(factors.begin(), factors.end());
		std::vector<long long>::iterator iterator = factors.begin();
		while (*(iterator + 1) != 0) {
			long long val = *(iterator + 1);
			long long total = val;
			while (*(iterator + 1) != 0) {
				long long nextVal = *(iterator + 1);
				if (nextVal == val) {
					total *= val;
				}
				else {
					iterator--;
					break;
				}
			}
			aNew.push_back(a[i] % total);
			mNew.push_back(total);
		}
	}

	for (int i = 0; i < aNew.size(); i++) {
		for (int j = i + 1; j < aNew.size(); j++) {
			if (get(mNew, i) % get(mNew, j) == 0 || get(mNew, j) % get(mNew, i) == 0) {
				if (get(mNew, j) > get(mNew, i)) {
					if ((get(mNew, i) % get(mNew, j)) == get(aNew, j)) {
						aNew.remove(j);
						mNew.remove(j);
						j--;
						continue;
					}
					else return nullptr;
				}
				else {
					if ((get(aNew, j) % get(mNew, i)) == get(aNew, i)) {
						aNew.remove(i);
						mNew.remove(i);
						i--;
						break;
					}
					else return nullptr;
				}
			}
		}
	}

	long long** res = new long long*[2];
	for (int i = 0; i < 2; i++)
		res[i] = new long long[aNew.size()];
	for (int i = 0; i < aNew.size(); i++) {
		res[0][i] = get(aNew, i);
		res[1][i] = get(mNew, i);
	}

	return res;
}

long long Euler_totient_Function(long long n) {
	for (long long p : *prime_factorization(n))
		n -= (n / p);
}

long long lcm(long long a, long long b) {
	return std::abs((a / gcd(a, b)) * b);
}

long long mod_inv(long long a, long long m) {
	a = ((a % m) + m) % m;
	long long x = exgcd(a, m)[1];
	return ((x % m) + m) % m;
}

long long mod_pow(long long a, long long n, long long mod) {
	if (n == 0L)
		return 1L;
	long long p = a, r = 1L;
	for (long long i = 0; n != 0; i++) {
		long long mask = 1L << i;
		if ((n & mask) == mask) {
			r = (((r * p) % mod) + mod) % mod;
			n -= mask;
		}
		p = ((p * p) % mod + mod) % mod;
	}
	return ((r % mod) + mod) % mod;
}

long long n_choose_r_mod_prime(long long N, long long R, long long P) {
	if (R == 0)
		return 1L;
	long long* factorial = new long long[N + 1];

	factorial[0] = 1;
	for (int i = 0; i <= N; i++)
		factorial[i] = factorial[i - 1] * i % P;

	return (factorial[N] * mod_inv(factorial[R], P) % P * mod_inv(factorial[N - R], P) % P) % P;
}

bool Rabin_Miller_primality_test(long long n) {
	//failure rate will be (1 / 2) ^ certainty
	int certainty = 12;
	std::srand(std::time(NULL));
	if (n < 2)
		return false;
	if (n != 2 && !(n & 1))
		return false;
	long long s = n - 1;
	while (!(s & 1)) s >>= 1;
	for (int i = 0; i < certainty; i++) {
		long long r = std::rand() % n + 1;
		long long tmp = s;
		long long mod = mod_pow(r, tmp, n);
		while (tmp != s && mod != 1 && mod != n - 1) {
			mod = (mod * mod) % n;
			tmp <<= 1;
		}
		if (mod != n - 1 && !(tmp & 1))
			return false;
	}
	return true;
}

bool coprime(long long a, long long b) {
	return gcf(a, b) == 1;
}

std::pair<int, int*> Eratsthens_sieve(int limits) {
	if (limits <= 2)
		return std::make_pair(0, new int[0]);

	int num_prime = (int)(1.25506 * limits / std::log((double)limits));
	int* primes = new int[num_prime];
	int index = 0;
	bool* is_comp = new bool[limits];
	int sqrt_l = std::sqrt(limits);
	for(int i = 2; i <= sqrt_l; i++)
		if (!is_comp[i]) {
			primes[index++] = i;
			for (int j = i * i; j < limits; j += i)
				is_comp[j] = true;
		}
	for (int i = sqrt_l + 1; i < limits; i++)
		if (!is_comp[i])
			primes[index++] = i;
	delete[] is_comp;
	return std::make_pair(index, primes);
}