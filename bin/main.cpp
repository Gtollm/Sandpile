#include <algorithm>
#include <cstddef>
#include <cstdint>
#include <iostream>
#include <iterator>

#include "lib/bmp_writer/bmp.hpp"
#include "lib/matrix/matrix.hpp"
#include "lib/parser/parser.hpp"
#include "lib/sandpile/sandpile.hpp"
#include "lib/tsv_reader/tsv_reader.hpp"
#include "lib/vector/vector.hpp"

int main(int argc, const char **argv) {
  Args args;
  args.ReadArgs(argc - 1, argv + 1);
  utils::Vector<utils::Vector<std::uint64_t>> v;

  //  0 0 0 0 0 0 0 0 0 0
  //  0 0 0 0 1 2 1 0 0 0
  //  0 0 0 3 2 0 2 3 0 0
  //  0 0 3 0 3 2 3 0 3 0
  //  0 1 2 3 0 3 0 3 2 1
  //  0 2 0 2 3 0 3 2 0 2
  //  0 1 2 3 0 3 0 3 2 1
  //  0 0 3 0 3 2 3 0 3 0
  //  0 0 0 3 2 0 2 3 0 0
  //  0 0 0 0 1 2 1 0 0 0

  TsvReader reader;
  BmpWriter writer;
  Sandpile sp(&writer);

  reader.ParseTSV(args.GetInput(), &sp);
  sp.Scatter(args.GetMaxIter(), args.GetFrequency());
  writer.WriteBmp(args.GetOutput(), sp.GetMatrix());
  return 0;
}
