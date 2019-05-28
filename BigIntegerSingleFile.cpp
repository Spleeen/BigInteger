#include <iostream>
#include <sstream>

#define MAX 10000

using namespace std;
class BigInteger {
 private:
  string number;
  bool sign{false};

 public:
  BigInteger() = default;
  explicit BigInteger(string s);
  BigInteger(string s, bool sin);
  explicit BigInteger(int n);
  void setNumber(string s);
  const string& getNumber();
  void setSign(bool s);
  const bool& getSign();
  BigInteger absolute();
  BigInteger& operator=(BigInteger b);
  bool operator==(BigInteger b);
  bool operator!=(BigInteger b);
  bool operator>(BigInteger b);
  bool operator<(BigInteger b);
  bool operator>=(BigInteger b);
  bool operator<=(BigInteger b);
  BigInteger& operator++();
  BigInteger operator++(int);
  BigInteger& operator--();
  BigInteger operator--(int);
  BigInteger operator+(BigInteger b);
  BigInteger operator-(BigInteger b);
  BigInteger operator*(BigInteger b);
  BigInteger operator/(BigInteger b);
  BigInteger operator%(BigInteger b);
  BigInteger& operator+=(const BigInteger& b);
  BigInteger& operator-=(const BigInteger& b);
  BigInteger& operator*=(const BigInteger& b);
  BigInteger& operator/=(const BigInteger& b);
  BigInteger& operator%=(const BigInteger& b);
  int operator[](int n);
  BigInteger operator-();
  operator string();
  friend ostream& operator<<(ostream& os, const BigInteger& bi);
  friend istream& operator>>(istream& os, const BigInteger& bi);

 private:
  bool equals(BigInteger n1, BigInteger n2);
  bool less(BigInteger n1, BigInteger n2);
  bool greater(const BigInteger& n1, const BigInteger& n2);
  string add(string number1, string number2);
  string subtract(string number1, string number2);
  string multiply(string n1, string n2);
  pair<string, long long> divide(string n, long long den);

  long long toInt(string s);
};

BigInteger::BigInteger(string s) {
  if (isdigit(s[0])) {
    setNumber(s);
    sign = false;
  } else {
    setNumber(s.substr(1));
    sign = (s[0] == '-');
  }
}

BigInteger::BigInteger(string s, bool sin) : number(s), sign(sin) {}

BigInteger::BigInteger(int n) {
  stringstream ss;
  string s;
  ss << n;
  ss >> s;

  if (isdigit(s[0])) {
    setNumber(s);
    setSign(false);
  } else {
    setNumber(s.substr(1));
    setSign(s[0] == '-');
  }
}

void BigInteger::setNumber(string s) { number = s; }

const string& BigInteger::getNumber() { return number; }

void BigInteger::setSign(bool s) { sign = s; }

const bool& BigInteger::getSign() { return sign; }

BigInteger BigInteger::absolute() { return BigInteger(getNumber()); }

BigInteger& BigInteger::operator=(BigInteger b) {
  number = b.getNumber();
  sign = b.getSign();
  return *this;
}

bool BigInteger::operator==(BigInteger b) { return equals((*this), b); }

bool BigInteger::operator!=(BigInteger b) { return !equals((*this), b); }

bool BigInteger::operator>(BigInteger b) { return greater((*this), b); }

bool BigInteger::operator<(BigInteger b) { return less((*this), b); }

bool BigInteger::operator>=(BigInteger b) {
  return equals((*this), b) || greater((*this), b);
}

bool BigInteger::operator<=(BigInteger b) {
  return equals((*this), b) || less((*this), b);
}

BigInteger& BigInteger::operator++() {
  *this = *this + BigInteger(1);
  return (*this);
}

BigInteger BigInteger::operator++(int) {
  BigInteger before = (*this);

  *this = *this + BigInteger(1);

  return before;
}

BigInteger& BigInteger::operator--() {
  *this = *this - BigInteger(1);
  return *this;
}

BigInteger BigInteger::operator--(int) {
  BigInteger before = (*this);

  *this = *this - BigInteger(1);

  return before;
}

BigInteger BigInteger::operator+(BigInteger b) {
  BigInteger addition;
  if (getSign() == b.getSign()) {
    addition.setNumber(add(getNumber(), b.getNumber()));
    addition.setSign(getSign());
  } else {
    if (absolute() > b.absolute()) {
      addition.setNumber(subtract(getNumber(), b.getNumber()));
      addition.setSign(getSign());
    } else {
      addition.setNumber(subtract(b.getNumber(), getNumber()));
      addition.setSign(b.getSign());
    }
  }
  if (addition.getNumber() == "0") addition.setSign(false);

  return addition;
}

BigInteger BigInteger::operator-(BigInteger b) {
  b.setSign(!b.getSign());
  return (*this) + b;
}

BigInteger BigInteger::operator*(BigInteger b) {
  BigInteger mul;

  mul.setNumber(multiply(getNumber(), b.getNumber()));
  mul.setSign(getSign() != b.getSign());

  if (mul.getNumber() == "0") mul.setSign(false);

  return mul;
}

BigInteger BigInteger::operator/(BigInteger b) {
  long long den = toInt(b.getNumber());
  BigInteger div;

  div.setNumber(divide(getNumber(), den).first);
  div.setSign(getSign() != b.getSign());

  if (div.getNumber() == "0") div.setSign(false);

  return div;
}

BigInteger BigInteger::operator%(BigInteger b) {
  long long den = toInt(b.getNumber());

  BigInteger rem;
  long long rem_int = divide(number, den).second;
  rem.setNumber(to_string(rem_int));
  rem.setSign(getSign() != b.getSign());

  if (rem.getNumber() == "0") rem.setSign(false);

  return rem;
}

BigInteger& BigInteger::operator+=(const BigInteger& b) {
  (*this) = (*this) + b;
  return (*this);
}

BigInteger& BigInteger::operator-=(const BigInteger& b) {
  (*this) = (*this) - b;
  return (*this);
}

BigInteger& BigInteger::operator*=(const BigInteger& b) {
  (*this) = (*this) * b;
  return (*this);
}

BigInteger& BigInteger::operator/=(const BigInteger& b) {
  (*this) = (*this) / b;
  return (*this);
}

BigInteger& BigInteger::operator%=(const BigInteger& b) {
  (*this) = (*this) % b;
  return (*this);
}

int BigInteger::operator[](int n) {
  return number[number.size() - n - 1] - '0';
}

BigInteger BigInteger::operator-() { return *this * BigInteger(-1); }

BigInteger::operator string() {
  string signedString = (getSign()) ? "-" : "";
  signedString += number;
  return signedString;
}

ostream& operator<<(ostream& os, const BigInteger& bi) {
  os << bi.number;
  return os;
}
istream& operator>>(istream& is, BigInteger& bi) {
  string output;
  is >> output;
  BigInteger b(output);
  bi = b;
  return is;
}
bool BigInteger::equals(BigInteger n1, BigInteger n2) {
  return n1.getNumber() == n2.getNumber() && n1.getSign() == n2.getSign();
}

bool BigInteger::less(BigInteger n1, BigInteger n2) {
  bool sign1 = n1.getSign();
  bool sign2 = n2.getSign();

  if (sign1 && !sign2)
    return true;

  else if (!sign1 && sign2)
    return false;

  else if (!sign1) {
    if (n1.getNumber().length() < n2.getNumber().length()) return true;
    if (n1.getNumber().length() > n2.getNumber().length()) return false;
    return n1.getNumber() < n2.getNumber();
  } else {
    if (n1.getNumber().length() > n2.getNumber().length()) return true;
    if (n1.getNumber().length() < n2.getNumber().length()) return false;
    return n1.getNumber().compare(n2.getNumber()) > 0;
  }
}

bool BigInteger::greater(const BigInteger& n1, const BigInteger& n2) {
  return !equals(n1, n2) && !less(n1, n2);
}

string BigInteger::add(string number1, string number2) {
  string add = (number1.length() > number2.length()) ? number1 : number2;
  char carry = '0';
  int differenceInLength = abs((int)(number1.size() - number2.size()));

  if (number1.size() > number2.size())
    number2.insert(0, differenceInLength, '0');

  else
    number1.insert(0, differenceInLength, '0');

  for (int i = number1.size() - 1; i >= 0; --i) {
    add[i] = ((carry - '0') + (number1[i] - '0') + (number2[i] - '0')) + '0';

    if (i != 0) {
      if (add[i] > '9') {
        add[i] -= 10;
        carry = '1';
      } else
        carry = '0';
    }
  }
  if (add[0] > '9') {
    add[0] -= 10;
    add.insert(0, 1, '1');
  }
  return add;
}

string BigInteger::subtract(string number1, string number2) {
  string sub = (number1.length() > number2.length()) ? number1 : number2;
  int differenceInLength = abs((int)(number1.size() - number2.size()));

  if (number1.size() > number2.size())
    number2.insert(0, differenceInLength, '0');

  else
    number1.insert(0, differenceInLength, '0');

  for (int i = number1.length() - 1; i >= 0; --i) {
    if (number1[i] < number2[i]) {
      number1[i] += 10;
      number1[i - 1]--;
    }
    sub[i] = ((number1[i] - '0') - (number2[i] - '0')) + '0';
  }

  while (sub[0] == '0' && sub.length() != 1) sub.erase(0, 1);

  return sub;
}

string BigInteger::multiply(string n1, string n2) {
  if (n1.length() > n2.length()) n1.swap(n2);

  string res = "0";
  for (int i = n1.length() - 1; i >= 0; --i) {
    string temp = n2;
    int currentDigit = n1[i] - '0';
    int carry = 0;

    for (int j = temp.length() - 1; j >= 0; --j) {
      temp[j] = ((temp[j] - '0') * currentDigit) + carry;

      if (temp[j] > 9) {
        carry = (temp[j] / 10);
        temp[j] -= (carry * 10);
      } else
        carry = 0;

      temp[j] += '0';
    }

    if (carry > 0) temp.insert(0, 1, (carry + '0'));

    temp.append((n1.length() - i - 1), '0');

    res = add(res, temp);
  }

  while (res[0] == '0' && res.length() != 1) res.erase(0, 1);

  return res;
}

pair<string, long long> BigInteger::divide(string n, long long den) {
  long long rem = 0;
  string result;
  result.resize(MAX);

  for (int indx = 0, len = n.length(); indx < len; ++indx) {
    rem = (rem * 10) + (n[indx] - '0');
    result[indx] = rem / den + '0';
    rem %= den;
  }
  result.resize(n.length());

  while (result[0] == '0' && result.length() != 1) result.erase(0, 1);

  if (result.length() == 0) result = "0";

  return make_pair(result, rem);
}

long long BigInteger::toInt(string s) {
  long long sum = 0;

  for (char i : s) sum = (sum * 10) + (i - '0');

  return sum;
}

int main() {
  BigInteger lol("123456789123456789");
  BigInteger ok = lol + BigInteger("22552525542242422424");
  ok /= lol;
  std::cout << ok;
}
