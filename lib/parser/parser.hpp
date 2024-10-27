#pragma once

#include <cstdint>
#include <ctime>
#include <limits>

enum ValidatorType {
  SHORT_SPACE,
  LONG_SPACE,
  SHORT_EQUALITY,
  LONG_EQUALITY,
  INVALID,
};

class Args {
 public:
  Args(const char *input = nullptr, const char *output = nullptr,
       uint32_t max_iter = std::numeric_limits<uint32_t>::max(),
       uint32_t frequency = 0);
  void SetInput(const char *input);
  void SetOutput(const char *output);
  void SetMaxIter(const uint32_t max_iter);
  void SetMaxIter(const char *max_iter);
  void SetFrequency(const uint32_t frequency_);
  void SetFrequency(const char *frequency_);
  const char *GetInput() const;
  const char *GetOutput() const;
  uint32_t GetMaxIter() const;
  uint32_t GetFrequency() const;
  bool SetArg(int argc, const char **argv, void (Args::*set)(const char *),
              const char *name, int &curr);
  ValidatorType ValidateArg(const char *arg, const char *name) const;
  void ReadArg(int argc, const char **argv, int &curr);
  void ReadArgs(int argc, const char **argv);
  [[noreturn]] void Help(const char *n = nullptr);

 private:
  const char *input_;
  const char *output_;
  uint32_t max_iter_;
  uint32_t frequency_;
};

void Error(const char *error_message = nullptr, bool should_exit = false);
