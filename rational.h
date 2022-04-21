#pragma once
#include <cmath>
#include <iostream>
#include <cstdlib>
#include <stdexcept>

class RationalDivisionByZero : public std::runtime_error {
 public:
  RationalDivisionByZero() : std::runtime_error("RationalDivisionByZero") {
  }
};

class Rational {
 private:
  int numerator_;
  int denominator_;

  void Set();

 public:
  Rational(int numerator = 0, int denominator = 1);  // NOLINT

  int GetNumerator() const;
  int GetDenominator() const;

  void SetNumerator(int numerator);
  void SetDenominator(int denominator);

  Rational& operator++();
  Rational operator++(int);

  Rational& operator--();
  Rational operator--(int);

  Rational& operator+=(const Rational& second);
  Rational& operator-=(const Rational& second);
  Rational& operator*=(const Rational& second);
  Rational& operator/=(const Rational& second);

  friend Rational operator-(const Rational& number);
  friend bool operator<(const Rational& first, const Rational& second);
  friend bool operator==(const Rational& first, const Rational& second);
  friend std::istream& operator>>(std::istream& in, Rational& number);
  friend std::ostream& operator<<(std::ostream& out, const Rational& number);
};

Rational operator+(const Rational& first, const Rational& second);
Rational operator-(const Rational& first, const Rational& second);
Rational operator*(const Rational& first, const Rational& second);
Rational operator/(const Rational& first, const Rational& second);
Rational operator+(const Rational& number);
Rational operator-(const Rational& number);

bool operator<(const Rational& first, const Rational& second);
bool operator<=(const Rational& first, const Rational& second);
bool operator>(const Rational& first, const Rational& second);
bool operator>=(const Rational& first, const Rational& second);
bool operator==(const Rational& first, const Rational& second);
bool operator!=(const Rational& first, const Rational& second);

std::istream& operator>>(std::istream& in, Rational& number);
std::ostream& operator<<(std::ostream& out, const Rational& number);