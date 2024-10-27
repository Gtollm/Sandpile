#include <cstdint>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <iterator>

#include "parser.hpp"
#include "text.hpp"

const char *kNoInput = "No input file provided. Exiting...";
const char *kWrongInput =
    "Multiple input file paths provided, first will be used";
const char *kWrongParametrs =
    "Wrong Parameters, check Help. Program will choose default parameters "
    "for unrecognised parameters";
const char *kFileNotOpened = "Error opening input file. Exiting...";
const char *kShortArgPrefix = "-";
const char *kLongArgPrefix = "--";
const char *kEqualSign = "=";

struct functionName {
  const char *name;
  void (Args::*function)(const char *);
};

void Error(const char *error_message, bool should_exit) {
  std::cout << error_message << std::endl;
  if (should_exit) {
    exit(1);
  }
}

Args::Args(const char *input, const char *output, uint32_t max_iter,
           uint32_t frequency)
    : input_(input),
      output_(output),
      max_iter_(max_iter),
      frequency_(frequency) {}

void Args::SetInput(const char *input) { this->input_ = input; }

void Args::SetOutput(const char *output) { this->output_ = output; }

void Args::SetMaxIter(const uint32_t max_iter) {
  this->max_iter_ = max_iter;
}

void Args::SetMaxIter(const char *max_iter) {
  this->max_iter_ = toInt(max_iter);
}

void Args::SetFrequency(const uint32_t frequency) {
  this->frequency_ = frequency;
}

void Args::SetFrequency(const char *frequency) {
  this->frequency_ = toInt(frequency);
}

const char *Args::GetInput() const { return this->input_; }

const char *Args::GetOutput() const { return this->output_; }

uint32_t Args::GetMaxIter() const { return this->max_iter_; }

uint32_t Args::GetFrequency() const { return this->frequency_; }

[[noreturn]] void Args::Help(const char *n) {
  std::cout
      << "\tUsage:\n AnalyzeLog [options] [file ...]\n AnalyzeLog [file "
         "...] [options]\n AnalyzeLog [options] [file ...] [options]\n";
  std::cout << "Options" << std::endl;
  std::cout
      << "\t--output [path], -o[path] - path to file, to which mistakes "
         "will be written"
      << std::endl;
  std::cout << "\t--max_iter [N], -m [N] - maximum number of iterations "
               "allowed to happend";
  std::cout << "\t--freq [N], -f [N] - how frequent should picture be saved";
  exit(0);
}

bool Args::SetArg(int argc, const char **argv,
                  void (Args::*set)(const char *), const char *name,
                  int &curr) {
  ValidatorType type = ValidateArg(argv[curr], name);
  if (strCmp(name, "help") == 0 && type != ValidatorType::INVALID) {
    this->Help();
  }
  switch (type) {
    case ValidatorType::SHORT_SPACE:
      if (curr + 1 < argc && strnCmp(argv[curr + 1], kShortArgPrefix,
                                     strLen(kShortArgPrefix)) != 0) {
        curr++;
        (this->*set)(argv[curr]);
      }
      return true;
    case ValidatorType::SHORT_EQUALITY:
      (this->*set)(argv[curr] + strLen(name) + strLen(kShortArgPrefix) + 1);
      return true;
    case ValidatorType::LONG_SPACE:
      if (curr + 1 < argc &&
          strnCmp(argv[curr + 1], kLongArgPrefix, 1) != 0) {
        curr++;
        (this->*set)(argv[curr]);
      }
      return true;
    case ValidatorType::LONG_EQUALITY:
      (this->*set)(argv[curr] + strLen(name) + strLen(kLongArgPrefix) + 1);
      return true;
    case ValidatorType::INVALID:
      break;
  }
  return false;
}

ValidatorType Args::ValidateArg(const char *arg, const char *name) const {
  char *shortened = new char[strLen(kShortArgPrefix) + 2];
  strCopy(shortened, kShortArgPrefix, strLen(kShortArgPrefix));
  strCat(shortened, name, 1);
  char *longed = new char[strLen(name) + strLen(kLongArgPrefix) + 1];
  strCopy(longed, kLongArgPrefix, strLen(kLongArgPrefix));
  strCat(longed, name, strLen(name));
  char *shortened_eq = new char[strLen(shortened) + strLen(kEqualSign) + 1];
  strCopy(shortened_eq, shortened, strLen(shortened));
  strCat(shortened_eq, kEqualSign, strLen(kEqualSign));
  char *longed_eq = new char[strLen(longed) + strLen(kEqualSign) + 1];
  strCopy(longed_eq, longed, strLen(longed));
  strCat(longed_eq, kEqualSign, strLen(kEqualSign));
  ValidatorType type = ValidatorType::INVALID;
  if (strCmp(arg, shortened) == 0) {
    type = ValidatorType::SHORT_SPACE;
  } else if (strnCmp(arg, shortened_eq, strLen(shortened_eq)) == 0) {
    type = ValidatorType::SHORT_EQUALITY;
  } else if (strCmp(arg, longed) == 0) {
    type = ValidatorType::LONG_SPACE;
  } else if (strnCmp(arg, longed_eq, strLen(longed_eq)) == 0) {
    type = ValidatorType::LONG_EQUALITY;
  }
  delete[] shortened;
  delete[] longed;
  delete[] shortened_eq;
  delete[] longed_eq;
  return type;
}

void Args::ReadArg(int argc, const char **argv, int &curr) {
  int length;
  if (strnCmp(argv[curr], kShortArgPrefix, strLen(kShortArgPrefix)) != 0) {
    Error(kWrongInput);
    return;
  }
  char *tmp;
  functionName list[] = {
      {"input", &Args::SetInput},      {"output", &Args::SetOutput},
      {"max_iter", &Args::SetMaxIter}, {"freq", &Args::SetFrequency},
      {"help", &Args::Help},
  };
  bool value_set = false;
  for (int i = 0; i < std::size(list); ++i) {
    value_set = value_set ||
                SetArg(argc, argv, list[i].function, list[i].name, curr);
  }
  if (!value_set) {
    Error(kWrongParametrs);
  }
  return;
}

void Args::ReadArgs(int argc, const char **argv) {
  for (int i = 0; i < argc; ++i) {
    ReadArg(argc, argv, i);
  }
  if (!this->input_) {
    Error(kNoInput);
  }
}
