#ifndef __EXINT__
#define __EXINT__
#include <string>
#include <iosfwd>
#include <algorithm>
#include "fft.h"

namespace exalg {
	template <typename T>
	T power_of_2_ge_than(T n) {
		T ret = 1;
		while (n > ret) ret <<= 1;
		return ret;
	}

	template<unsigned int base = 10>
	class ExtendedInteger {
		std::string num;
		int toRealNum(char c) {
			if ('0' <= c && c <= '9')
				return c - '0';
			return c - 'A' + 10;
		}
		char toBaseNum(int n) {
			if (0 <= n && n <= 9)
				return n + '0';
			else
				return n - 10 + 'A';
		}
		ExtendedInteger<base> toNonMinus(ExtendedInteger<base> n) {
			if (n.num[0] == '-')
				n.num = n.num.substr(1, n.num.size() - 1);
			return n;
		}
		ExtendedInteger<base> toMinus(ExtendedInteger<base> n) {
			if (n.num[0] != '-' && n.num != "0")
				n.num.insert(n.num.begin(), '-');
			return n;
		}
		std::string strToNonMinus(const std::string& n) const {
			std::string ret;
			if (n[0] == '-')
				ret = n.substr(1, n.size() - 1);
			return ret;
		}
		std::string strToMinus(const std::string& n) const {
			std::string ret;
			ret = n;
			if (ret[0] != '-' && ret != "0") {
				ret.insert(0, '-');
			}
			return ret;
		}
	public:
		ExtendedInteger() { }
		ExtendedInteger(int s) : num(std::to_string(s)) { }
		ExtendedInteger(long long s) : num(std::to_string(s)) { }
		ExtendedInteger(std::string s) { 
			for (int i = 0; i < s.size(); i++) {
				if (s[i] == '.') {
					num = s.substr(0, i);					
					return;
				}
			}
			num = s;
		}
		template<int otherBase>
		ExtendedInteger(ExtendedInteger<otherBase> other) {
			ExtendedInteger<10> mid;
			for (int i = 0; i < other.num.size(); i++)
				mid += toRealNum(other[i]) * (int)pow(otherBase, other.num.size() - i - 1);
			
		}
		bool isMinus() const {
			if (num[0] == '-')
				return true;
			return false;
		}
		void operator=(int s) {
			num = std::to_string(s);
		}
		void operator=(long long s) {
			num = std::to_string(s);
		}
		void operator=(std::string s) {
			for (int i = 0; i < s.size(); i++) {
				if (s[i] == '.') {
					num = s.substr(0, i);
					return;
				}
			}
			num = s;
		}
		void operator=(ExtendedInteger<base> s) {
			num = s.num;
		}
		bool operator<(const ExtendedInteger<base>& other) const {
			std::string cmp1, cmp2;
			if (isMinus() && other.isMinus()) {
				cmp2 = strToNonMinus(num);
				cmp1 = strToNonMinus(other.num);
			}
			else if (isMinus())
				return true;			
			else if (other.isMinus())
				return false;			
			else {
				cmp1 = num;
				cmp2 = other.num;
			}
			if (cmp1.size() == cmp2.size())
				return cmp1 < cmp2;
			return cmp1.size() < cmp2.size();
		}
		bool operator<=(const ExtendedInteger<base>& other) const {
			std::string cmp1, cmp2;
			if (isMinus() && other.isMinus()) {
				cmp2 = strToNonMinus(num);
				cmp1 = strToNonMinus(other.num);
			}
			else if (isMinus())
				return true;
			else if (other.isMinus())
				return false;
			else {
				cmp1 = num;
				cmp2 = other.num;
			}
			if (cmp1.size() == cmp2.size())
				return cmp1 <= cmp2;
			return cmp1.size() <= cmp2.size();
		}
		bool operator>(const ExtendedInteger<base>& other) const {
			std::string cmp1, cmp2;
			if (isMinus() && other.isMinus()) {
				cmp2 = strToNonMinus(num);
				cmp1 = strToNonMinus(other.num);
			}
			else if (isMinus())
				return false;
			else if (other.isMinus())
				return true;
			else {
				cmp1 = num;
				cmp2 = other.num;
			}
			if (cmp1.size() == cmp2.size())
				return cmp1 > cmp2;
			return cmp1.size() > cmp2.size();
		}
		bool operator>=(const ExtendedInteger<base>& other) const {
			std::string cmp1, cmp2;
			if (isMinus() && other.isMinus()) {
				cmp2 = strToNonMinus(num);
				cmp1 = strToNonMinus(other.num);
			}
			else if (isMinus())
				return false;
			else if (other.isMinus())
				return true;
			else {
				cmp1 = num;
				cmp2 = other.num;
			}
			if (cmp1.size() == cmp2.size())
				return cmp1 >= cmp2;
			return cmp1.size() >= cmp2.size();
		}
		bool operator==(const ExtendedInteger<base>& other) const {
			return num == other.num;
		}
		bool operator!=(const ExtendedInteger<base>& other) const {
			return !(operator==(other));
		}
		char at(int idx) {
			return num[idx];
		}
		size_t length() {
			return num.length();
		}
		std::string operator[](std::pair<int, int> a) {
			return num.substr(a.first, a.second - a.first + 1);
		}
		ExtendedInteger<base> operator-() {
			if (this->isMinus())
				return toNonMinus(*this);
			else
				return toMinus(*this);
		}
		ExtendedInteger<base> operator+(ExtendedInteger<base> other) {
			if (other.isMinus() && this->isMinus())
				return toMinus(toNonMinus(other) + toNonMinus(*this));
			if (other.isMinus())
				return *this - toNonMinus(other);
			if (this->isMinus())
				return other - toNonMinus(*this);
			std::string originalNum = num;
			std::reverse(num.begin(), num.end());
			std::reverse(other.num.begin(), other.num.end());
			bool upNum = false;
			int realNum1;
			int realNum2;
			int calcRes;
			std::string* bePlusStr;
			std::string* plusStr;
			if (num.size() < other.num.size()) {
				plusStr = &num;
				bePlusStr = &other.num;
			}
			else {
				plusStr = &other.num;
				bePlusStr = &num;
			}
			for (int i = 0; i < std::min(num.size(), other.num.size()); i++) {
				realNum1 = toRealNum((*bePlusStr)[i]);
				realNum2 = toRealNum((*plusStr)[i]);
				calcRes = realNum1 + realNum2 + upNum;
				upNum = false;
				if (calcRes >= base) {
					calcRes -= base;
					upNum = true;
				}
				(*bePlusStr)[i] = toBaseNum(calcRes);
			}
			for (int i = std::min(num.size(), other.num.size()); i < (*bePlusStr).size(); i++) {
				calcRes = toRealNum((*bePlusStr)[i]) + upNum;
				upNum = false;
				if (calcRes >= base) {
					calcRes -= base;
					upNum = true;
				}

				(*bePlusStr)[i] = toBaseNum(calcRes);
			}
			if (upNum) {
				*bePlusStr += '1';
			}
			ExtendedInteger<base> ret = *bePlusStr;
			num = originalNum;
			reverse(ret.num.begin(), ret.num.end());
			return ret;
		}
		ExtendedInteger<base> operator-(ExtendedInteger<base> other) {
			if (other.isMinus())
				return toNonMinus(other) + *this;
			if (this->isMinus())
				return toMinus(other + toNonMinus(*this));
			std::string originalNum = num;
			bool upNum = false;
			int realNum1;
			int realNum2;
			int calcRes;
			bool retMinus = false;
			std::string* beMinusStr;
			std::string* minusStr;
			if (other > *this) {
				retMinus = true;
				beMinusStr = &other.num;
				minusStr = &num;
			}
			else {
				beMinusStr = &num;
				minusStr = &other.num;
			}
			std::reverse(num.begin(), num.end());
			std::reverse(other.num.begin(), other.num.end());
			for (int i = 0; i < std::min(num.size(), other.num.size()); i++) {
				realNum1 = toRealNum((*beMinusStr)[i]);
				realNum2 = toRealNum((*minusStr)[i]);
				calcRes = realNum1 - realNum2 - upNum;
				upNum = false;
				if (calcRes < 0) {
					calcRes += base;
					upNum = true;
				}
				(*beMinusStr)[i] = toBaseNum(calcRes);
			}
			for (int i = std::min(num.size(), other.num.size()); i < (*beMinusStr).size(); i++) {
				calcRes = toRealNum((*beMinusStr)[i]) - upNum;
				upNum = false;
				if (calcRes < 0) {
					calcRes += base;
					upNum = true;
				}
				(*beMinusStr)[i] = toBaseNum(calcRes);
			}
			while (!(*beMinusStr).empty() && (*beMinusStr).back() == '0')
				(*beMinusStr).pop_back();
			if (beMinusStr->empty())
				*beMinusStr += '0';
			ExtendedInteger<base> ret = *beMinusStr;
			num = originalNum;
			reverse(ret.num.begin(), ret.num.end());
			if (retMinus)
				return toMinus(ret);
			return ret;
		}		
		ExtendedInteger<base> operator*(ExtendedInteger<base> other) {
			if (this->isMinus() && other.isMinus())
				return toNonMinus(*this) * toNonMinus(other);
			else if(this->isMinus() || other.isMinus())
				return toMinus(toNonMinus(*this) * toNonMinus(other));
			std::vector<int> First, Second;
			for (int i = 0; i < num.size(); i++)
				First.push_back(num[i] - '0');
			for (int i = 0; i < other.num.size(); i++)
				Second.push_back(other.num[i] - '0');

			reverse(First.begin(), First.end());
			reverse(Second.begin(), Second.end());

			std::vector<std::complex<double>> complexFirst(First.begin(), First.end());
			std::vector<std::complex<double>> complexSecond(Second.begin(), Second.end());
			int n = power_of_2_ge_than(std::max(complexFirst.size(), complexSecond.size())) * 2;

			complexFirst.resize(n);
			FastFourierTransform(complexFirst);
			complexSecond.resize(n);
			FastFourierTransform(complexSecond);

			for (int i = 0; i < n; i++)
				complexFirst[i] *= complexSecond[i];
			InverseFastFourierTransform(complexFirst);

			std::vector<int> mp;
			ExtendedInteger<base> ret = 0;
			for (int i = 0; i < n; i++) {
				mp.push_back((int)round(complexFirst[i].real()));
			}
			int i = 0;
			while (i < mp.size()) {
				if (mp[i] >= 10) {
					if (i == mp.size() - 1)
						mp.push_back(mp[i] / 10);
					else
						mp[i + 1] += mp[i] / 10;
					mp[i] %= 10;
				}
				++i;
			}
			
			reverse(mp.begin(), mp.end());

			bool start = false;
			ret.num = "";
			for (auto elem : mp) {
				if (elem)start = true;
				if (start)ret.num += elem + '0';
			}
			if (!start)ret.num = '0';
			
			return ret;
		}
		ExtendedInteger<base> operator/(ExtendedInteger<base> other) {

		}
		ExtendedInteger<base> operator%(ExtendedInteger<base> other) {

		}
		ExtendedInteger<base>& operator++() {			
			*this += 1;
			return *this;
		}
		ExtendedInteger<base>& operator++(int) {
			ExtendedInteger<base>& ret = *this;
			*this += 1;
			return ret;
		}
		ExtendedInteger<base>& operator--() {			
			*this -= 1;
			return *this;
		}
		ExtendedInteger<base>& operator--(int) {
			ExtendedInteger<base>& ret = *this;
			*this -= 1;
			return ret;
		}
		ExtendedInteger<base>& operator+=(ExtendedInteger<base> other) {
			ExtendedInteger<base>& ret = *this;
			*this = *this + other;
			return ret;
		}
		ExtendedInteger<base>& operator-=(ExtendedInteger<base> other) {
			ExtendedInteger<base>& ret = *this;
			*this = *this - other;
			return ret;
		}
		ExtendedInteger<base>& operator*=(ExtendedInteger<base> other) {
			ExtendedInteger<base>& ret = *this;
			*this = *this * other;
			return ret;
		}
		ExtendedInteger<base>& operator/=(ExtendedInteger<base> other) {
			ExtendedInteger<base>& ret = *this;
			*this = *this / other;
			return ret;
		}
		ExtendedInteger<base>& operator%=(ExtendedInteger<base> other) {
			ExtendedInteger<base>& ret = *this;
			*this = *this % other;
			return ret;
		}
		friend std::istream& operator>>(std::istream& In, ExtendedInteger<base>& e) {
			In >> e.num;
			for (int i = 0; i < e.num.size(); i++) {
				if (e.num[i] == '.')
					e.num = e.num.substr(0, i);
			}
			return In;
		}
		friend std::ostream& operator<<(std::ostream& Out, const ExtendedInteger<base> e) {
			Out << e.num;
			return Out;
		}
	};
}
#endif
