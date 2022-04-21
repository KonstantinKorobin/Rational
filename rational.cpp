#include "rational.h"

template <typename T>
T GCD(const T& first, const T& second) {
  if (second == 0) {
    return first;
  }
  return GCD(second, (first % second));
}

void Rational::Set() {
  if (denominator_ == 0) {
    throw RationalDivisionByZero{};
  }
  if (denominator_ < 0) {
    denominator_ = -denominator_;
    numerator_ = -numerator_;
  }
  int gcd = GCD(abs(numerator_), denominator_);
  numerator_ /= gcd;
  denominator_ /= gcd;
}

Rational::Rational(int numerator, int denominator) : numerator_(numerator), denominator_(denominator) {
  Set();
}

int Rational::GetNumerator() const {
  return numerator_;
}

int Rational::GetDenominator() const {
  return denominator_;
}

void Rational::SetNumerator(int numerator) {
  numerator_ = numerator;
  Set();
}
void Rational::SetDenominator(int denominator) {
  denominator_ = denominator;
  Set();
}

Rational& Rational::operator+=(const Rational& second) {
  numerator_ = numerator_ * second.denominator_ + second.numerator_ * denominator_;
  denominator_ *= second.denominator_;
  Set();
  return *this;
}

Rational& Rational::operator-=(const Rational& second) {
  numerator_ = numerator_ * second.denominator_ - second.numerator_ * denominator_;
  denominator_ *= second.denominator_;
  Set();
  return *this;
}

Rational& Rational::operator*=(const Rational& second) {
  numerator_ *= second.numerator_;
  denominator_ *= second.denominator_;
  Set();
  return *this;
}

Rational& Rational::operator/=(const Rational& second) {
  if (second.numerator_ == 0) {
    throw RationalDivisionByZero();
  }
  numerator_ *= second.denominator_;
  denominator_ *= second.numerator_;
  Set();
  return *this;
}

Rational& Rational::operator++() {
  numerator_ += denominator_;
  return *this;
}

Rational Rational::operator++(int) {
  Rational copy = *this;
  numerator_ += denominator_;
  return copy;
}

Rational& Rational::operator--() {
  numerator_ -= denominator_;
  return *this;
}

Rational Rational::operator--(int) {
  Rational copy = *this;
  numerator_ -= denominator_;
  return copy;
}

Rational operator+(const Rational& number) {
  return number;
}

Rational operator-(const Rational& number) {
  return Rational(-number.numerator_, number.denominator_);
}

Rational operator+(const Rational& first, const Rational& second) {
  Rational result = first;
  result += second;
  return result;
}

Rational operator-(const Rational& first, const Rational& second) {
  Rational result = first;
  result -= second;
  return result;
}

Rational operator*(const Rational& first, const Rational& second) {
  Rational result = first;
  result *= second;
  return result;
}

Rational operator/(const Rational& first, const Rational& second) {
  Rational result = first;
  result /= second;
  return result;
}

bool operator<(const Rational& first, const Rational& second) {
  return first.numerator_ * second.denominator_ < second.numerator_ * first.denominator_;
}

bool operator<=(const Rational& first, const Rational& second) {
  return !(second < first);
}

bool operator>(const Rational& first, const Rational& second) {
  return second < first;
}

bool operator>=(const Rational& first, const Rational& second) {
  return !(first < second);
}

bool operator==(const Rational& first, const Rational& second) {
  return first.numerator_ == second.numerator_ && first.denominator_ == second.denominator_;
}

bool operator!=(const Rational& first, const Rational& second) {
  return !(first == second);
}

std::ostream& operator<<(std::ostream& out, const Rational& number) {
  out << number.numerator_;
  if (number.denominator_ != 1) {
    out << "/" << number.denominator_;
  }
  return out;
}

std::istream& operator>>(std::istream& in, Rational& number) {
  int numerator = 0;
  int denominator = 1;
  in >> numerator;
  if (in.peek() == '/') {
    in.ignore(1);
    in >> denominator;
  }
  if (denominator == 0) {
    throw RationalDivisionByZero{};
  }
  number = Rational(numerator, denominator);
  number.Set();
  return in;
}
